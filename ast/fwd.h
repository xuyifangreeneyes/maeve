#ifndef MENHIR_FWD_H
#define MENHIR_FWD_H

namespace menhir {
namespace ast {

class Visitor;

struct AstNode;

struct Type;
struct BaseType;
struct BuiltinType;
struct ClassType;
struct ArrayType;

struct Expr;
struct BinaryExpr;
struct UnaryExpr;
struct FunctionCall;
struct ArrayAccess;
struct MemberAccess;
struct NewExpr;
struct VarExpr;
struct LiteralExpr;
struct LiteralInt;
struct LiteralBool;
struct LiteralString;
struct LiteralNull;

struct Stmt;
struct CompoundStmt;
struct VarDeclStmt;
struct ExprStmt;
struct IfStmt;
struct ForStmt;
struct WhileStmt;
struct ReturnStmt;
struct BreakStmt;
struct ContinueStmt;
struct EmptyStmt;

struct Decl;
struct VarDecl;
struct FunctionDecl;
struct ClassDecl;

struct AstRoot;

} // namespace ast
} // namespace menhir

#endif // MENHIR_FWD_H
