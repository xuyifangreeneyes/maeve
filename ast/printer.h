#ifndef MENHIR_AST_DUMPER_H
#define MENHIR_AST_DUMPER_H

#include "visitor.h"
#include <iostream>

namespace menhir {
namespace ast {

class Printer : public Visitor {
public:
  explicit Printer(std::ostream &out = std::cout) : indent(0), out(out) {}

  void visit(AstNode &node) override;

  void visit(BuiltinType &node) override;
  void visit(ClassType &node) override;
  void visit(ArrayType &node) override;

  void visit(BinaryExpr &node) override;
  void visit(UnaryExpr &node) override;
  void visit(FunctionCall &node) override;
  void visit(ArrayAccess &node) override;
  void visit(MemberAccess &node) override;
  void visit(NewExpr &node) override;
  void visit(VarExpr &node) override;
  void visit(LiteralInt &node) override;
  void visit(LiteralBool &node) override;
  void visit(LiteralString &node) override;
  void visit(LiteralNull &node) override;

  void visit(CompoundStmt &node) override;
  void visit(VarDeclStmt &node) override;
  void visit(ExprStmt &node) override;
  void visit(IfStmt &node) override;
  void visit(ForStmt &node) override;
  void visit(WhileStmt &node) override;
  void visit(ReturnStmt &node) override;
  void visit(BreakStmt &node) override;
  void visit(ContinueStmt &node) override;
  void visit(EmptyStmt &node) override;

  void visit(VarDecl &node) override;
  void visit(FunctionDecl &node) override;
  void visit(ClassDecl &node) override;

  void visit(AstRoot &node) override;

private:
  std::size_t indent;
  std::ostream &out;

  void println(const std::string &content);
};

} // namespace ast
} // namespace menhir

#endif // MENHIR_AST_DUMPER_H
