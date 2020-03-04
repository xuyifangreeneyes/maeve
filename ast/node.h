#ifndef MENHIR_AST_NODE_H
#define MENHIR_AST_NODE_H

#include "visitor.h"
#include <memory>
#include <string>
#include <vector>

#define MENHIR_AST_PURE_ACCEPT void accept(Visitor &visitor) override = 0;

#define MENHIR_AST_ACCEPT                                                      \
  void accept(Visitor &visitor) override { visitor.visit(*this); }

namespace menhir {
namespace ast {

struct AstNode {
  virtual ~AstNode() = default;

  virtual void accept(Visitor &visitor) = 0;
};

struct Type : AstNode {
  MENHIR_AST_PURE_ACCEPT
};

struct BaseType : AstNode {
  MENHIR_AST_PURE_ACCEPT
};

struct BuiltinType : BaseType {
  enum Kind {Int, Bool, String, Null};

  explicit BuiltinType(Kind kind) : kind(kind) {}

  MENHIR_AST_ACCEPT

  Kind kind;
};

struct ClassDecl;

struct ClassType : BaseType {
  explicit ClassType(std::string name) : name(std::move(name)) {}

  MENHIR_AST_ACCEPT

  std::string name;
  std::weak_ptr<ClassDecl> classDecl;
};

struct ArrayType : AstNode {
  ArrayType(std::shared_ptr<BaseType> baseType, std::size_t dim)
      : baseType(std::move(baseType)), dim(dim) {}

  MENHIR_AST_ACCEPT

  std::shared_ptr<BaseType> baseType;
  std::size_t dim;
};

struct Expr : AstNode {
  MENHIR_AST_PURE_ACCEPT

  std::shared_ptr<Type> type;
};

struct BinaryExpr : Expr {
  enum Op {
      Mul, Div, Mod, Add,    Sub,   Lsft,   Rsft, Lt, Gt,     Le,
      Ge,  Eq,  Neq, BitAnd, BitOr, BitXor, And,  Or, Assign,
  };

  BinaryExpr(Op op, std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs)
      : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

  MENHIR_AST_ACCEPT

  Op op;
  std::shared_ptr<Expr> lhs, rhs;
};

struct UnaryExpr : Expr {
  enum Op {
    PreInc, PreDec, PostInc, PostDec,
    Pos, Neg, Not, BitNot
  };

  UnaryExpr(Op op, std::shared_ptr<Expr> operand)
      : op(op), operand(std::move(operand)) {}

  MENHIR_AST_ACCEPT

  Op op;
  std::shared_ptr<Expr> operand;
};

struct FunctionCall : Expr {
  FunctionCall(std::shared_ptr<Expr> callee,
               std::vector<std::shared_ptr<Expr>> args)
      : callee(std::move(callee)), args(std::move(args)) {}

  MENHIR_AST_ACCEPT

  std::shared_ptr<Expr> callee;
  std::vector<std::shared_ptr<Expr>> args;
};

struct ArrayAccess : Expr {
  ArrayAccess(std::shared_ptr<Expr> array, std::shared_ptr<Expr> index)
      : array(std::move(array)), index(std::move(index)) {}

  MENHIR_AST_ACCEPT

  std::shared_ptr<Expr> array, index;
};

struct MemberAccess : Expr {
  MemberAccess(std::shared_ptr<Expr> instance, std::string field)
      : instance(std::move(instance)), field(std::move(field)) {}

  MENHIR_AST_ACCEPT

  std::shared_ptr<Expr> instance;
  std::string field;
};

struct NewExpr : Expr {
  NewExpr(std::string name, std::size_t dim,
          std::vector<std::shared_ptr<Expr>> shape = {})
      : name(std::move(name)), dim(dim), shape(std::move(shape)) {}

  MENHIR_AST_ACCEPT

  std::string name;
  std::size_t dim;
  std::vector<std::shared_ptr<Expr>> shape;
};

struct VarDecl;

struct VarExpr : Expr {
  explicit VarExpr(std::string name) : name(std::move(name)) {}

  MENHIR_AST_ACCEPT

  std::string name;
  std::weak_ptr<VarDecl> varDecl;
};

struct LiteralExpr : Expr {
  MENHIR_AST_PURE_ACCEPT
};

struct LiteralInt : LiteralExpr {
  explicit LiteralExpr(int value) : value(value) {}

  MENHIR_AST_ACCEPT

  int value;
};

struct LiteralBool : LiteralExpr {
  explicit LiteralBool(bool value) : value(value) {}

  MENHIR_AST_ACCEPT

  bool value;
};

struct LiteralString : LiteralExpr {
  explicit LiteralString(std::string value) : value(std::move(value)) {}

  MENHIR_AST_ACCEPT

  std::string value;
};

struct LiteralNull : LiteralExpr {
  LiteralNull() = default;

  MENHIR_AST_ACCEPT
};

struct Stmt : AstNode {
  MENHIR_AST_PURE_ACCEPT
};

struct CompoundStmt : AstNode {
  explicit CompoundStmt(std::vector<std::shared_ptr<Stmt>> stmts)
      : stmts(std::move(stmts)) {}

  MENHIR_AST_ACCEPT

  std::vector<std::shared_ptr<Stmt>> stmts;
};

struct VarDeclStmt : Stmt {
  explicit VarDeclStmt(std::shared_ptr<VarDecl> varDecl)
      : varDecl(std::move(varDecl)) {}

  MENHIR_AST_ACCEPT

  std::shared_ptr<VarDecl> varDecl;
};

struct ExprStmt : Stmt {
  explicit ExprStmt(std::shared_ptr<Expr> expr) : expr(std::move(expr)) {}

  MENHIR_AST_ACCEPT

  std::shared_ptr<Expr> expr;
};

struct IfStmt : Stmt {
  IfStmt(std::shared_ptr<Expr> cond, std::shared_ptr<Stmt> then,
         std::shared_ptr<Stmt> otherwise)
      : cond(std::move(cond)), then(std::move(then)),
        otherwise(std::move(otherwise)) {}

  MENHIR_AST_ACCEPT

  std::shared_ptr<Expr> cond;
  std::shared_ptr<Stmt> then, otherwise;
};

struct ForStmt : Stmt {
  ForStmt(std::shared_ptr<Expr> init, std::shared_ptr<Expr> cond,
          std::shared_ptr<Expr> step, std::shared_ptr<Stmt> body)
      : init(std::move(init)), cond(std::move(cond)), step(std::move(step)),
        body(std::move(body)) {}

  MENHIR_AST_ACCEPT

  std::shared_ptr<Expr> init, cond, step;
  std::shared_ptr<Stmt> body;
};

struct WhileStmt : Stmt {
  WhileStmt(std::shared_ptr<Expr> cond, std::shared_ptr<Stmt> body)
      : cond(std::move(cond)), body(std::move(body)) {}
  MENHIR_AST_ACCEPT

  std::shared_ptr<Expr> cond;
  std::shared_ptr<Stmt> body;
};

struct ReturnStmt : Stmt {
  ReturnStmt(std::shared_ptr<Expr> value) : value(std::move(value)) {}

  MENHIR_AST_ACCEPT

  std::shared_ptr<Expr> value;
};

struct BreakStmt : Stmt {
  MENHIR_AST_ACCEPT
};

struct ContinueStmt : Stmt {
  MENHIR_AST_ACCEPT
};

struct EmptyStmt : Stmt {
  MENHIR_AST_ACCEPT
};

struct Decl : AstNode {
  MENHIR_AST_PURE_ACCEPT
};

struct VarDecl : Decl {
  VarDecl(std::string name, std::shared_ptr<Type> type,
          std::shared_ptr<Expr> init = nullptr)
      : name(std::move(name)), type(std::move(type)),
        initExpr(std::move(initExpr)) {}

  MENHIR_AST_ACCEPT

  std::name name;
  std::shared_ptr<Type> type;
  std::shared_ptr<Expr> initExpr;
};

struct FunctionDecl : Decl {
  FunctionDecl(std::string name, std::shared_ptr<Type> retType,
               std::vector<std::shared_ptr<VarDecl>> args,
               std::shared_ptr<CompoundStmt> body)
      : name(std::move(name)), retType(std::move(retType)),
        args(std::move(args)), body(std::move(body)) {}

  MENHIR_AST_ACCEPT

  std::string name;
  std::shared_ptr<Type> retType;
  std::vector<std::shared_ptr<VarDecl>> args;
  std::shared_ptr<CompoundStmt> body;
};

struct ClassDecl : Decl {
  ClassDecl(std::string name, std::vector<std::shared_ptr<Decl>> decls)
      : name(std::move(name)), decls(std::move(decls)) {}

  MENHIR_AST_ACCEPT

  std::string name;
  std::vector<std::shared_ptr<Decl>> decls
};

struct Program : AstNode {
  explicit Program(std::vector<std::shared_ptr<Decl>> decls)
      : decls(std::move(decls)) {}

  MENHIR_AST_ACCEPT

  std::vector<std::shared_ptr<Decl>> decls;
};

} // namespace ast
} // namespace menhir

#endif // MENHIR_AST_NODE_H
