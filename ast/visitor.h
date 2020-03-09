#ifndef MAEVE_AST_VISITOR_H
#define MAEVE_AST_VISITOR_H

#include "fwd.h"

namespace maeve {
namespace ast {

class Visitor {
public:
  virtual void visit(AstNode &node) {}

  virtual void visit(BuiltinType &node) {}
  virtual void visit(ClassType &node) {}
  virtual void visit(ArrayType &node) {}

  virtual void visit(BinaryExpr &node) {}
  virtual void visit(UnaryExpr &node) {}
  virtual void visit(FunctionCall &node) {}
  virtual void visit(ArrayAccess &node) {}
  virtual void visit(MemberAccess &node) {}
  virtual void visit(NewExpr &node) {}
  virtual void visit(VarExpr &node) {}
  virtual void visit(LiteralInt &node) {}
  virtual void visit(LiteralBool &node) {}
  virtual void visit(LiteralString &node) {}
  virtual void visit(LiteralNull &node) {}

  virtual void visit(CompoundStmt &node) {}
  virtual void visit(VarDeclStmt &node) {}
  virtual void visit(ExprStmt &node) {}
  virtual void visit(IfStmt &node) {}
  virtual void visit(ForStmt &node) {}
  virtual void visit(WhileStmt &node) {}
  virtual void visit(ReturnStmt &node) {}
  virtual void visit(BreakStmt &node) {}
  virtual void visit(ContinueStmt &node) {}
  virtual void visit(EmptyStmt &node) {}

  virtual void visit(VarDecl &node) {}
  virtual void visit(FunctionDecl &node) {}
  virtual void visit(ClassDecl &node) {}

  virtual void visit(AstRoot &node) {}
};

} // namespace ast
} // namespace maeve

#endif // MAEVE_AST_VISITOR_H
