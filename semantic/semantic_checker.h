#ifndef MAEVE_SEMANTIC_CHECKER_H
#define MAEVE_SEMANTIC_CHECKER_H

#include "../ast/visitor.h"
#include "symbol_table.h"

namespace maeve {

/*
 *
 * 1. Link VarExpr to VarDecl.
 * 2. Link ClassType to ClassDecl.
 * 3. Check type for Expr.
 * 4. Check other details.
 *
 * */
class SemanticChecker : public ast::Visitor {
public:
  void visit(ast::AstNode &node) override;

  void visit(ast::ClassType &node) override;
  void visit(ast::ArrayType &node) override;

  void visit(ast::Expr &node) override;
  void visit(ast::BinaryExpr &node) override;
  void visit(ast::UnaryExpr &node) override;
  void visit(ast::FunctionCall &node) override;
  void visit(ast::ArrayAccess &node) override;
  void visit(ast::MemberAccess &node) override;
  void visit(ast::NewExpr &node) override;
  void visit(ast::VarExpr &node) override;
  void visit(ast::LiteralExpr &node) override;
  void visit(ast::LiteralInt &node) override;
  void visit(ast::LiteralBool &node) override;
  void visit(ast::LiteralString &node) override;
  void visit(ast::LiteralNull &node) override;

  void visit(ast::Stmt &node) override;
  void visit(ast::CompoundStmt &node) override;
  void visit(ast::VarDeclStmt &node) override;
  void visit(ast::ExprStmt &node) override;
  void visit(ast::IfStmt &node) override;
  void visit(ast::ForStmt &node) override;
  void visit(ast::WhileStmt &node) override;
  void visit(ast::ReturnStmt &node) override;
  void visit(ast::BreakStmt &node) override;
  void visit(ast::ContinueStmt &node) override;
  void visit(ast::EmptyStmt &node) override;

  void visit(ast::VarDecl &node) override;
  void visit(ast::FunctionDecl &node) override;
  void visit(ast::ClassDecl &node) override;

  void visit(ast::AstRoot &node) override;

private:
  std::shared_ptr<ast::ClassDecl> currentClass;
  SymbolTable symbolTable;

};

} // namespace maeve

#endif // MAEVE_SEMANTIC_CHECKER_H
