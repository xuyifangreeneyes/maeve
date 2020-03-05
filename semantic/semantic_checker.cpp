#include "semantic_checker.h"

#include "../ast/node.h"
#include "../utils/error.h"

namespace maeve {

std::string quote(const std::string &name) { return "'" + name + "'"; }

bool assignable(const std::shared_ptr<ast::Type> &lhs,
                const std::shared_ptr<ast::Type> &rhs) {
  if (!lhs || !rhs) {
    return false;
  }
  auto lhs_ = std::string(*lhs);
  auto rhs_ = std::string(*rhs);
  if (rhs_ == "null" && !(std::dynamic_pointer_cast<ast::BuiltinType>(lhs))) {
    return true;
  }
  return lhs_ == rhs_;
}

void SemanticChecker::checkLoop(const std::string &statement) {
  if (loopCounter == 0) {
    throw CompileError(quote(statement) + " statement not in loop statement");
  }
}

void SemanticChecker::visit(ast::AstNode &node) { node.accept(*this); }

void SemanticChecker::visit(ast::ClassType &node) {}
void SemanticChecker::visit(ast::ArrayType &node) {}

void SemanticChecker::visit(ast::BinaryExpr &node) {}
void SemanticChecker::visit(ast::UnaryExpr &node) {}
void SemanticChecker::visit(ast::FunctionCall &node) {}
void SemanticChecker::visit(ast::ArrayAccess &node) {}
void SemanticChecker::visit(ast::MemberAccess &node) {}

void SemanticChecker::visit(ast::NewExpr &node) {
  auto p = symbolTable.lookup(node.name);
  bool flag = true;
  if (!p) {
    flag = false;
  } else if (auto funcDecl = std::dynamic_pointer_cast<ast::FunctionDecl>(p)) {
    flag = (funcDecl->retType == nullptr);
  } else {
    flag = (std::dynamic_pointer_cast<ast::ClassDecl>(p) != nullptr);
  }
  if (!flag) {
    throw CompileError("unknown type name " + quote(node.name));
  }
  auto q = symbolTable.globalLookup(node.name);
  assert(q);
  auto classDecl = std::static_pointer_cast<ast::ClassDecl>(q);
//  auto classType =
//  if (auto Class)
}

void SemanticChecker::visit(ast::VarExpr &node) {
  auto p = symbolTable.lookup(node.name);
  if (!p) {
    throw CompileError("use of undeclared identifier " + quote(node.name));
  }
  auto varDecl = std::static_pointer_cast<ast::VarDecl>(p);
  node.type = varDecl->type;
  node.varDecl = varDecl;
}

void SemanticChecker::visit(ast::LiteralInt &node) {
  node.type = std::make_shared<ast::BuiltinType>(ast::BuiltinType::Int);
}

void SemanticChecker::visit(ast::LiteralBool &node) {
  node.type = std::make_shared<ast::BuiltinType>(ast::BuiltinType::Bool);
}

void SemanticChecker::visit(ast::LiteralString &node) {
  node.type = std::make_shared<ast::BuiltinType>(ast::BuiltinType::String);
}

void SemanticChecker::visit(ast::LiteralNull &node) {
  node.type = std::make_shared<ast::BuiltinType>(ast::BuiltinType::Null);
}

void SemanticChecker::visit(ast::CompoundStmt &node) {
  symbolTable.enterScope();
  for (auto &&stmt : node.stmts) {
    visit(*stmt);
  }
  symbolTable.exitScope();
}

void SemanticChecker::visit(ast::VarDeclStmt &node) {
  visit(*node.varDecl);
}

void SemanticChecker::visit(ast::ExprStmt &node) {}
void SemanticChecker::visit(ast::IfStmt &node) {}
void SemanticChecker::visit(ast::ForStmt &node) {
  if (node.init) {
    visit(*node.init);
  }
  if (node.cond) {
    visit(*node.cond);
    if (std::string(*(node.cond->type)) != "bool") {
      throw CompileError("condition of for must be bool");
    }
  }
  if (node.step) {
    visit(*node.step);
  }
  ++loopCounter;
  visit(*node.body);
  --loopCounter;
}

void SemanticChecker::visit(ast::WhileStmt &node) {
  visit(*node.cond);
  if (std::string(*(node.cond->type)) != "bool") {
    throw CompileError("condition of while must be bool");
  }
  ++loopCounter;
  visit(*node.body);
  --loopCounter;
}

void SemanticChecker::visit(ast::ReturnStmt &node) {
  assert(currentFunc);
  if (currentClass && currentClass->name == currentFunc->name) {
    throw CompileError("constructor " + quote(currentFunc->name) +
                       " should not return a value");
  }
  assert(currentFunc->retType);
  if (!node.value) {
    if (std::string(*(currentFunc->retType)) != "void") {
      throw CompileError("non-void function " + quote(currentFunc->name) +
                         " should return a value");
    }
  } else {
    visit(*node.value);
    if (!assignable(currentFunc->retType, node.value->type)) {
      throw CompileError("return type not match");
    }
  }
}

void SemanticChecker::visit(ast::BreakStmt &node) { checkLoop("break"); }

void SemanticChecker::visit(ast::ContinueStmt &node) { checkLoop("continue"); }

void SemanticChecker::visit(ast::VarDecl &node) {
  if (node.initExpr) {
    visit(*node.initExpr);
  }
  visit(*node.type);
  auto varDecl =
      std::static_pointer_cast<ast::VarDecl>(node.shared_from_this());
  if (!symbolTable.addSymbol(node.name, varDecl)) {
    throw CompileError("redefinition of " + quote(node.name));
  }
}

void SemanticChecker::visit(ast::FunctionDecl &node) {
  currentFunc =
      std::static_pointer_cast<ast::FunctionDecl>(node.shared_from_this());
  if (node.retType) {
    visit(*node.retType);
  } else {
    // This function is class constructor.
    assert(currentClass);
    if (currentClass->name != node.name) {
      throw CompileError("constructor name " + quote(node.name) +
                         " must match class name " + quote(currentClass->name));
    }
  }
  symbolTable.enterScope();
  for (auto &&arg : node.args) {
    visit(*arg);
  }
  // The reason why we don't directly `visit(*node.body)` is that
  // `visit(*node.body)` introduces another scope.
  for (auto &&stmt : node.body->stmts) {
    visit(*stmt);
  }
  symbolTable.exitScope();
  currentFunc = nullptr;
}

void SemanticChecker::visit(ast::ClassDecl &node) {
  currentClass =
      std::static_pointer_cast<ast::ClassDecl>(node.shared_from_this());
  symbolTable.enterScope();
  // Class member function support forward reference.
  for (auto &&it : node.decls) {
    if (std::dynamic_pointer_cast<ast::FunctionDecl>(it.second)) {
      symbolTable.addSymbol(it.first, it.second);
    }
  }
  for (auto &&it : node.decls) {
    visit(*it.second);
  }
  symbolTable.exitScope();
  currentClass = nullptr;
}

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