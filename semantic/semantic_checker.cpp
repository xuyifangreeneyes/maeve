#include "semantic_checker.h"

#include "../ast/node.h"

namespace maeve {

void SemanticChecker::visit(ast::AstNode &node) { node.accept(*this); }

void SemanticChecker::visit(ast::ClassType &node) {}
void SemanticChecker::visit(ast::ArrayType &node) {}

void SemanticChecker::visit(ast::Expr &node) {}
void SemanticChecker::visit(ast::BinaryExpr &node) {}
void SemanticChecker::visit(ast::UnaryExpr &node) {}
void SemanticChecker::visit(ast::FunctionCall &node) {}
void SemanticChecker::visit(ast::ArrayAccess &node) {}
void SemanticChecker::visit(ast::MemberAccess &node) {}
void SemanticChecker::visit(ast::NewExpr &node) {}
void SemanticChecker::visit(ast::VarExpr &node) {}
void SemanticChecker::visit(ast::LiteralExpr &node) {}
void SemanticChecker::visit(ast::LiteralInt &node) {}
void SemanticChecker::visit(ast::LiteralBool &node) {}
void SemanticChecker::visit(ast::LiteralString &node) {}
void SemanticChecker::visit(ast::LiteralNull &node) {}

void SemanticChecker::visit(ast::Stmt &node) {}
void SemanticChecker::visit(ast::CompoundStmt &node) {}

void SemanticChecker::visit(ast::VarDeclStmt &node) {
  visit(*node.varDecl);
  symbolTable.addSymbol(node.varDecl->name, node.varDecl);
}

void SemanticChecker::visit(ast::ExprStmt &node) {}
void SemanticChecker::visit(ast::IfStmt &node) {}
void SemanticChecker::visit(ast::ForStmt &node) {}
void SemanticChecker::visit(ast::WhileStmt &node) {}
void SemanticChecker::visit(ast::ReturnStmt &node) {}
void SemanticChecker::visit(ast::BreakStmt &node) {}
void SemanticChecker::visit(ast::ContinueStmt &node) {}
void SemanticChecker::visit(ast::EmptyStmt &node) {}

void SemanticChecker::visit(ast::VarDecl &node) {
  // It is ensured that the name of VarDecl has already been added into
  // symbolTable before entering this function
  assert(symbolTable.lookup(node.name));

}

void SemanticChecker::visit(ast::FunctionDecl &node) {}

void SemanticChecker::visit(ast::ClassDecl &node) {}

void SemanticChecker::visit(ast::AstRoot &node) {
  // Class and global function support forward reference.
  for (auto &&decl : node.decls) {
    if (std::dynamic_pointer_cast<ast::FunctionDecl>(decl) ||
        std::dynamic_pointer_cast<ast::ClassDecl>(decl)) {
      symbolTable.addSymbol(decl->name, decl);
    }
  }
  for (auto &&decl : node.decls) {
    visit(*decl);
  }
}

} // namespace maeve