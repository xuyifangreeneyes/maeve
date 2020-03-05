#ifndef MAEVE_AST_FWD_H
#define MAEVE_AST_FWD_H

namespace maeve {
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
} // namespace maeve

#endif // MAEVE_AST_FWD_H
