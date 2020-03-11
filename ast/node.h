#ifndef MAEVE_AST_NODE_H
#define MAEVE_AST_NODE_H

#include "fwd.h"
#include "visitor.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#define MAEVE_AST_PURE_ACCEPT void accept(Visitor &visitor) override = 0;

#define MAEVE_AST_ACCEPT                                                       \
  void accept(Visitor &visitor) override { visitor.visit(*this); }

namespace maeve {
namespace ast {

using NodeId = std::uintptr_t;

struct AstNode : std::enable_shared_from_this<AstNode> {
  virtual ~AstNode() = default;

  NodeId getID() const { return (NodeId)this; }

  virtual void accept(Visitor &visitor) = 0;
};

struct Type : AstNode {

  virtual explicit operator std::string() const = 0;

  MAEVE_AST_PURE_ACCEPT
};

struct BaseType : Type {

  explicit operator std::string() const override = 0;

  MAEVE_AST_PURE_ACCEPT
};

struct BuiltinType : BaseType {
  enum Kind { Int, Bool, String, Void, Null };

  explicit BuiltinType(Kind kind) : kind(kind) {}

  static std::string kind2str(Kind kind) {
    static std::vector<std::string> ops = {"int", "bool", "string", "void",
                                           "null"};
    return ops[kind];
  }

  explicit operator std::string() const override { return kind2str(kind); }

  MAEVE_AST_ACCEPT

  Kind kind;
};

struct ClassType : BaseType {
  explicit ClassType(std::string name) : name(std::move(name)) {}

  MAEVE_AST_ACCEPT

  explicit operator std::string() const override { return name; }

  std::string name;
  std::weak_ptr<ClassDecl> classDecl;
};

struct ArrayType : Type {
  ArrayType(std::shared_ptr<BaseType> baseType, std::size_t dim)
      : baseType(std::move(baseType)), dim(dim) {}

  MAEVE_AST_ACCEPT

  explicit operator std::string() const override {
    return std::string(*baseType) + "^" + std::to_string(dim);
  }

  std::shared_ptr<BaseType> baseType;
  std::size_t dim;
};

struct Expr : AstNode {
  MAEVE_AST_PURE_ACCEPT

  std::shared_ptr<Type> type;
  bool lvalue = false;
};

struct BinaryExpr : Expr {
  enum Op {
    Mul,
    Div,
    Mod,
    Add,
    Sub,
    Lsft,
    Rsft,
    Lt,
    Gt,
    Le,
    Ge,
    Eq,
    Neq,
    BitAnd,
    BitOr,
    BitXor,
    And,
    Or,
    Assign,
  };

  static std::string op2str(Op op) {
    static std::vector<std::string> ops = {
        "Mul",   "Div",    "Mod", "Add", "Sub",   "Lsft", "Rsft",
        "Lt",    "Gt",     "Le",  "Ge",  "Eq",    "Neq",  "BitAnd",
        "BitOr", "BitXor", "And", "Or",  "Assign"};
    return ops[op];
  }

  BinaryExpr(Op op, std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs)
      : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

  MAEVE_AST_ACCEPT

  Op op;
  std::shared_ptr<Expr> lhs, rhs;
};

struct UnaryExpr : Expr {
  enum Op { PreInc, PreDec, PostInc, PostDec, Pos, Neg, Not, BitNot };

  static std::string op2str(Op op) {
    static std::vector<std::string> ops = {"PreInc",  "PreDec", "PostInc",
                                           "PostDec", "Pos",    "Neg",
                                           "Not",     "BitNot"};
    return ops[op];
  }

  UnaryExpr(Op op, std::shared_ptr<Expr> operand)
      : op(op), operand(std::move(operand)) {}

  MAEVE_AST_ACCEPT

  Op op;
  std::shared_ptr<Expr> operand;
};

struct FunctionCall : Expr {
  FunctionCall(std::shared_ptr<Expr> instance, std::string method,
               std::vector<std::shared_ptr<Expr>> args)
      : instance(std::move(instance)), method(std::move(method)),
        args(std::move(args)) {}

  //  FunctionCall(std::string method, std::vector<std::shared_ptr<Expr>> args)
  //    : FunctionCall(nullptr, std::move(method), std::move(args)) {}

  MAEVE_AST_ACCEPT

  std::shared_ptr<Expr> instance;
  std::string method;
  std::vector<std::shared_ptr<Expr>> args;
};

struct ArrayAccess : Expr {
  ArrayAccess(std::shared_ptr<Expr> array, std::shared_ptr<Expr> index)
      : array(std::move(array)), index(std::move(index)) {}

  MAEVE_AST_ACCEPT

  std::shared_ptr<Expr> array, index;
};

struct MemberAccess : Expr {
  MemberAccess(std::shared_ptr<Expr> instance, std::string field)
      : instance(std::move(instance)), field(std::move(field)) {}

  MAEVE_AST_ACCEPT

  std::shared_ptr<Expr> instance;
  std::string field;
};

struct NewExpr : Expr {
  NewExpr(std::string name, std::size_t dim,
          std::vector<std::shared_ptr<Expr>> shape = {})
      : name(std::move(name)), dim(dim), shape(std::move(shape)) {}

  MAEVE_AST_ACCEPT

  std::string name;
  std::size_t dim;
  std::vector<std::shared_ptr<Expr>> shape;
};

struct VarExpr : Expr {
  explicit VarExpr(std::string name) : name(std::move(name)) {}

  MAEVE_AST_ACCEPT

  std::string name;
  std::weak_ptr<VarDecl> varDecl;
};

struct LiteralExpr : Expr {
  MAEVE_AST_PURE_ACCEPT
};

struct LiteralInt : LiteralExpr {
  explicit LiteralInt(int value) : value(value) {}

  MAEVE_AST_ACCEPT

  int value;
};

struct LiteralBool : LiteralExpr {
  explicit LiteralBool(bool value) : value(value) {}

  MAEVE_AST_ACCEPT

  bool value;
};

struct LiteralString : LiteralExpr {
  explicit LiteralString(std::string value) : value(std::move(value)) {}

  MAEVE_AST_ACCEPT

  std::string value;
};

struct LiteralNull : LiteralExpr {
  LiteralNull() = default;

  MAEVE_AST_ACCEPT
};

struct Stmt : AstNode {
  MAEVE_AST_PURE_ACCEPT
};

struct CompoundStmt : Stmt {
  explicit CompoundStmt(std::vector<std::shared_ptr<Stmt>> stmts)
      : stmts(std::move(stmts)) {}

  MAEVE_AST_ACCEPT

  std::vector<std::shared_ptr<Stmt>> stmts;
};

struct VarDeclStmt : Stmt {
  explicit VarDeclStmt(std::shared_ptr<VarDecl> varDecl)
      : varDecl(std::move(varDecl)) {}

  MAEVE_AST_ACCEPT

  std::shared_ptr<VarDecl> varDecl;
};

struct ExprStmt : Stmt {
  explicit ExprStmt(std::shared_ptr<Expr> expr) : expr(std::move(expr)) {}

  MAEVE_AST_ACCEPT

  std::shared_ptr<Expr> expr;
};

struct IfStmt : Stmt {
  IfStmt(std::shared_ptr<Expr> cond, std::shared_ptr<Stmt> then,
         std::shared_ptr<Stmt> otherwise)
      : cond(std::move(cond)), then(std::move(then)),
        otherwise(std::move(otherwise)) {}

  MAEVE_AST_ACCEPT

  std::shared_ptr<Expr> cond;
  std::shared_ptr<Stmt> then, otherwise;
};

struct ForStmt : Stmt {
  ForStmt(std::shared_ptr<Expr> init, std::shared_ptr<Expr> cond,
          std::shared_ptr<Expr> step, std::shared_ptr<Stmt> body)
      : init(std::move(init)), cond(std::move(cond)), step(std::move(step)),
        body(std::move(body)) {}

  MAEVE_AST_ACCEPT

  std::shared_ptr<Expr> init, cond, step;
  std::shared_ptr<Stmt> body;
};

struct WhileStmt : Stmt {
  WhileStmt(std::shared_ptr<Expr> cond, std::shared_ptr<Stmt> body)
      : cond(std::move(cond)), body(std::move(body)) {}
  MAEVE_AST_ACCEPT

  std::shared_ptr<Expr> cond;
  std::shared_ptr<Stmt> body;
};

struct ReturnStmt : Stmt {
  ReturnStmt(std::shared_ptr<Expr> value) : value(std::move(value)) {}

  MAEVE_AST_ACCEPT

  std::shared_ptr<Expr> value;
};

struct BreakStmt : Stmt {
  MAEVE_AST_ACCEPT
};

struct ContinueStmt : Stmt {
  MAEVE_AST_ACCEPT
};

struct EmptyStmt : Stmt {
  MAEVE_AST_ACCEPT
};

struct Decl : AstNode {
  explicit Decl(std::string name) : name(std::move(name)) {}

  MAEVE_AST_PURE_ACCEPT

  std::string name;
};

struct VarDecl : Decl {
  VarDecl(std::string name, std::shared_ptr<Type> type,
          std::shared_ptr<Expr> initExpr = nullptr)
      : Decl(std::move(name)), type(std::move(type)),
        initExpr(std::move(initExpr)) {}

  MAEVE_AST_ACCEPT

  std::shared_ptr<Type> type;
  std::shared_ptr<Expr> initExpr;
};

struct FunctionDecl : Decl {
  FunctionDecl(std::string name, std::shared_ptr<Type> retType,
               std::vector<std::shared_ptr<VarDecl>> args,
               std::shared_ptr<CompoundStmt> body = nullptr)
      : Decl(std::move(name)), retType(std::move(retType)),
        args(std::move(args)), body(std::move(body)) {}

  MAEVE_AST_ACCEPT

  std::shared_ptr<Type> retType;
  std::vector<std::shared_ptr<VarDecl>> args;
  std::shared_ptr<CompoundStmt> body;
};

struct ClassDecl : Decl {
  ClassDecl(std::string name, std::vector<std::shared_ptr<Decl>> decls_);

  MAEVE_AST_ACCEPT

  std::unordered_map<std::string, std::shared_ptr<Decl>> decls;
};

struct AstRoot : AstNode {
  explicit AstRoot(std::vector<std::shared_ptr<Decl>> decls)
      : decls(std::move(decls)) {}

  MAEVE_AST_ACCEPT

  std::vector<std::shared_ptr<Decl>> decls;
};

} // namespace ast
} // namespace maeve

#endif // MAEVE_AST_NODE_H
