#include "semantic_checker.h"

#include "../ast/node.h"
#include "../utils/error.h"

namespace maeve {

using Kind = ast::BuiltinType::Kind;

std::string quote(const std::string &name) { return "'" + name + "'"; }

std::shared_ptr<ast::BuiltinType> builtinType(Kind kind) {
  return std::make_shared<ast::BuiltinType>(kind);
}

bool isBuiltinType(const std::string &name) {
  return name == "int" || name == "bool" || name == "string";
}

bool assignable(const std::shared_ptr<ast::Type> &lhs,
                const std::shared_ptr<ast::Expr> &rhsExpr) {
  std::shared_ptr<ast::Type> rhs = rhsExpr->type;
  if (!lhs || !rhs) {
    return false;
  }
  auto lhs_ = std::string(*lhs);
  auto rhs_ = std::string(*rhs);
  if (rhs_ == "null" && !(std::dynamic_pointer_cast<ast::BuiltinType>(lhs))) {
    assert(std::dynamic_pointer_cast<ast::LiteralNull>(rhsExpr));
    // When we meet `LiteralNull` during the construction of LLVM IR, we have
    // to specify which type of `llvm::ConstantPointerNull` it is. Hence we
    // update `rhsExpr->type` here.
    rhsExpr->type = lhs;
    return true;
  }
  return lhs_ == rhs_;
}

void mustBeBool(const std::shared_ptr<ast::Type> &type,
                const std::string &stmt) {
  if (std::string(*type) != "bool") {
    throw CompileError("condition of " + stmt + " must be bool");
  }
}

void unknowTypeName(const std::string &name) {
  throw CompileError("unknown type name " + quote(name));
}

void SemanticChecker::checkLoop(const std::string &statement) {
  if (loopCounter == 0) {
    throw CompileError(quote(statement) + " statement not in loop statement");
  }
}

void SemanticChecker::completeSignature(
    const std::shared_ptr<ast::FunctionDecl> &functionDecl) {
  visit_(functionDecl->retType);
  for (auto &&arg : functionDecl->args) {
    visit(*arg->type);
  }
}

void SemanticChecker::visit_(const std::shared_ptr<ast::AstNode> &node) {
  if (!node) {
    return;
  }
  visit(*node);
}

void SemanticChecker::visit(ast::AstNode &node) { node.accept(*this); }

void SemanticChecker::visit(ast::ClassType &node) {
  auto decl = symbolTable.globalLookup(node.name);
  if (!decl) {
    unknowTypeName(node.name);
  }
  auto classDecl = std::dynamic_pointer_cast<ast::ClassDecl>(decl);
  if (!classDecl) {
    unknowTypeName(node.name);
  }
  node.classDecl = classDecl;
}

void SemanticChecker::visit(ast::ArrayType &node) { visit(*node.baseType); }

void SemanticChecker::visit(ast::BinaryExpr &node) {
  visit(*node.lhs);
  visit(*node.rhs);
  using Op = ast::BinaryExpr::Op;
  if (node.op == Op::Assign) {
    if (!node.lhs->lvalue || !assignable(node.lhs->type, node.rhs)) {
      throw CompileError("expression is not assignable");
    }
    node.type = node.lhs->type;
    return;
  }
  auto ltype = std::string(*node.lhs->type);
  auto rtype = std::string(*node.rhs->type);
  if (ltype != rtype) {
    if ((node.op == Op::Eq || node.op == Op::Neq) &&
        (ltype == "null" || rtype == "null")) {
      node.type = builtinType(Kind::Bool);
      return;
    }
    throw CompileError("invalid operands to binary expression");
  }
  switch (node.op) {
  case Op::Add:
    if (ltype != "int" && ltype != "string") {
      throw CompileError("invalid operands to binary expression");
    }
    node.type = node.lhs->type;
    return;
  case Op::Sub:
  case Op::Mul:
  case Op::Div:
  case Op::Mod:
  case Op::Lsft:
  case Op::Rsft:
  case Op::BitAnd:
  case Op::BitOr:
  case Op::BitXor:
    if (ltype != "int") {
      throw CompileError("invalid operands to binary expression");
    }
    node.type = builtinType(Kind::Int);
    return;
  case Op::Lt:
  case Op::Gt:
  case Op::Le:
  case Op::Ge:
    if (ltype != "int" && ltype != "string") {
      throw CompileError("invalid operands to binary expression");
    }
    node.type = builtinType(Kind::Bool);
    return;
  case Op::And:
  case Op::Or:
    if (ltype != "bool") {
      throw CompileError("invalid operands to binary expression");
    }
    node.type = builtinType(Kind::Bool);
    return;
  case Op::Eq:
  case Op::Neq:
    node.type = builtinType(Kind::Bool);
    return;
  default:
    assert(false);
  }
}

void SemanticChecker::visit(ast::UnaryExpr &node) {
  visit(*node.operand);
  auto type = std::string(*node.operand->type);
  using Op = ast::UnaryExpr::Op;
  switch (node.op) {
  case Op::PreInc:
  case Op::PreDec:
  case Op::PostInc:
  case Op::PostDec:
    if (type != "int") {
      throw CompileError("invalid operand of unary expression");
    }
    if (!node.operand->lvalue) {
      throw CompileError("invalid operand of unary expression");
    }
    node.type = builtinType(Kind::Int);
    return;
  case Op::Pos:
  case Op::Neg:
  case Op::BitNot:
    if (type != "int") {
      throw CompileError("invalid operand of unary expression");
    }
    node.type = builtinType(Kind::Int);
    return;
  case Op::Not:
    if (type != "bool") {
      throw CompileError("invalid operand of unary expression");
    }
    node.type = builtinType(Kind::Bool);
    return;
  default:
    assert(false);
  }
}

void SemanticChecker::visit(ast::FunctionCall &node) {
  std::shared_ptr<ast::Decl> decl;
  if (node.instance) {
    auto type = node.instance->type;
    if (auto classType = std::dynamic_pointer_cast<ast::ClassType>(type)) {
      auto classDecl = classType->classDecl.lock();
      assert(classDecl);
      auto iter = classDecl->decls.find(node.method);
      if (iter == classDecl->decls.end()) {
        throw CompileError("use of undeclared identifier " +
                           quote(node.method));
      }
      decl = iter->second;
    } else if (auto arrayType =
                   std::dynamic_pointer_cast<ast::ArrayType>(type)) {
      decl = symbolTable.lookup("_array_" + node.method);
    } else {
      auto builtinType = std::dynamic_pointer_cast<ast::BuiltinType>(type);
      if (!builtinType || builtinType->kind != Kind::String) {
        throw CompileError("no member function for the instance");
      }
      decl = symbolTable.lookup("_string_" + node.method);
    }
  } else {
    decl = symbolTable.lookup(node.method);
  }
  if (!decl) {
    throw CompileError("use of undeclared identifier " + quote(node.method));
  }
  auto funcDecl = std::dynamic_pointer_cast<ast::FunctionDecl>(decl);
  if (!funcDecl) {
    throw CompileError("called object type is not a function");
  }
  for (auto &&arg : node.args) {
    visit(*arg);
  }
  if (funcDecl->args.size() != node.args.size()) {
    throw CompileError("arguments do not match");
  }
  std::size_t n = funcDecl->args.size();
  for (std::size_t i = 0; i < n; ++i) {
    if (!assignable(funcDecl->args[i]->type, node.args[i])) {
      throw CompileError("type error");
    }
  }
  assert(funcDecl->retType);
  node.type = funcDecl->retType;
}

void SemanticChecker::visit(ast::ArrayAccess &node) {
  visit(*node.array);
  auto arrayType = std::dynamic_pointer_cast<ast::ArrayType>(node.array->type);
  if (!arrayType) {
    throw CompileError("subscripted value is not an array");
  }
  visit(*node.index);
  if (std::string(*node.index->type) != "int") {
    throw CompileError("array subscript is not an integer");
  }
  if (arrayType->dim == 1) {
    node.type = arrayType->baseType;
  } else {
    node.type = std::make_shared<ast::ArrayType>(arrayType->baseType,
                                                 arrayType->dim - 1);
  }
  node.lvalue = true;
}

void SemanticChecker::visit(ast::MemberAccess &node) {
  // only accessing data field is processed here while accessing function field
  // is processed when meeting FunctionCall
  visit(*node.instance);
  auto p = std::dynamic_pointer_cast<ast::ClassType>(node.instance->type);
  assert(p);
  auto classDecl = p->classDecl.lock();
  assert(classDecl);
  auto iter = classDecl->decls.find(node.field);
  if (iter == classDecl->decls.end()) {
    throw CompileError("no member named " + quote(node.field) + " in " +
                       classDecl->name);
  }
  auto varDecl = std::dynamic_pointer_cast<ast::VarDecl>(iter->second);
  if (!varDecl) {
    throw CompileError("reference to member function must be called");
  }
  node.type = varDecl->type;
  node.lvalue = true;
}

void SemanticChecker::visit(ast::NewExpr &node) {
  std::shared_ptr<ast::BaseType> baseType;
  if (isBuiltinType(node.name)) {
    if (node.name == "int") {
      baseType = builtinType(Kind::Int);
    } else if (node.name == "bool") {
      baseType = builtinType(Kind::Bool);
    } else if (node.name == "string") {
      baseType = builtinType(Kind::String);
    } else {
      assert(false);
    }
  } else {
    auto p = symbolTable.globalLookup(node.name);
    if (!p) {
      unknowTypeName(node.name);
    }
    auto classDecl = std::dynamic_pointer_cast<ast::ClassDecl>(p);
    if (!classDecl) {
      unknowTypeName(node.name);
    }
    auto classType = std::make_shared<ast::ClassType>(node.name);
    classType->classDecl = classDecl;
    baseType = classType;
  }
  if (node.dim == 0) {
    node.type = baseType;
    return;
  }
  for (auto &&size : node.shape) {
    visit(*size);
    if (std::string(*size->type) != "int") {
      throw CompileError("size of array has non-integer type");
    }
  }
  node.type = std::make_shared<ast::ArrayType>(std::move(baseType), node.dim);
}

void SemanticChecker::visit(ast::VarExpr &node) {
  if (node.name == "this") {
    if (!currentClass) {
      throw CompileError("invalid use of 'this' outside of Class Definition");
    }
    auto classType = std::make_shared<ast::ClassType>(currentClass->name);
    classType->classDecl = currentClass;
    node.type = classType;
    return;
  }
  auto p = symbolTable.lookup(node.name);
  if (!p) {
    throw CompileError("use of undeclared identifier " + quote(node.name));
  }
  auto varDecl = std::static_pointer_cast<ast::VarDecl>(p);
  node.type = varDecl->type;
  node.varDecl = varDecl;
  node.lvalue = true;
}

void SemanticChecker::visit(ast::LiteralInt &node) {
  node.type = builtinType(Kind::Int);
}

void SemanticChecker::visit(ast::LiteralBool &node) {
  node.type = builtinType(Kind::Bool);
}

void SemanticChecker::visit(ast::LiteralString &node) {
  node.type = builtinType(Kind::String);
}

void SemanticChecker::visit(ast::LiteralNull &node) {
  node.type = builtinType(Kind::Null);
}

void SemanticChecker::visit(ast::CompoundStmt &node) {
  symbolTable.enterScope();
  for (auto &&stmt : node.stmts) {
    visit(*stmt);
  }
  symbolTable.exitScope();
}

void SemanticChecker::visit(ast::VarDeclStmt &node) { visit(*node.varDecl); }

void SemanticChecker::visit(ast::ExprStmt &node) { visit(*node.expr); }

void SemanticChecker::visit(ast::IfStmt &node) {
  visit(*node.cond);
  mustBeBool(node.cond->type, "if");
  visit(*node.then);
  visit_(node.otherwise);
}

void SemanticChecker::visit(ast::ForStmt &node) {
  visit_(node.init);
  if (node.cond) {
    visit(*node.cond);
    mustBeBool(node.cond->type, "for");
  }
  visit_(node.step);
  ++loopCounter;
  visit(*node.body);
  --loopCounter;
}

void SemanticChecker::visit(ast::WhileStmt &node) {
  visit(*node.cond);
  mustBeBool(node.cond->type, "while");
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
    if (!assignable(currentFunc->retType, node.value)) {
      throw CompileError("return type not match");
    }
  }
}

void SemanticChecker::visit(ast::BreakStmt &node) { checkLoop("break"); }

void SemanticChecker::visit(ast::ContinueStmt &node) { checkLoop("continue"); }

void SemanticChecker::visit(ast::VarDecl &node) {
  if (node.initExpr) {
    visit(*node.initExpr);
    if (!assignable(node.type, node.initExpr)) {
      throw CompileError("type error");
    }
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
    if (currentClass && currentClass->name == node.name) {
      throw CompileError("constructor cannot have a return type");
    }
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
    assert(!arg->initExpr);
    bool res = symbolTable.addSymbol(arg->name, arg);
    assert(res);
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
    if (auto functionDecl =
            std::dynamic_pointer_cast<ast::FunctionDecl>(it.second)) {
      completeSignature(functionDecl);
      symbolTable.addSymbol(it.first, it.second);
    }
  }
  // we visit `VarDecl` and then visit `FunctionDecl` since data field may be
  // used in member function
  for (auto &&it : node.decls) {
    if (std::dynamic_pointer_cast<ast::VarDecl>(it.second)) {
      visit(*it.second);
    }
  }
  for (auto &&it : node.decls) {
    if (std::dynamic_pointer_cast<ast::FunctionDecl>(it.second)) {
      visit(*it.second);
    }
  }
  symbolTable.exitScope();
  currentClass = nullptr;
}

void SemanticChecker::visit(ast::AstRoot &node) {
  // Class and global function support forward reference.
  for (auto &&decl : node.decls) {
    if (std::dynamic_pointer_cast<ast::ClassDecl>(decl)) {
      symbolTable.addSymbol(decl->name, decl);
    }
  }
  bool findMain = false;
  for (auto &&decl : node.decls) {
    if (auto functionDecl =
            std::dynamic_pointer_cast<ast::FunctionDecl>(decl)) {
      // we may check function call before visiting function declaration.
      completeSignature(functionDecl);
      symbolTable.addSymbol(decl->name, decl);
      if (functionDecl->name == "main") {
        if (!functionDecl->args.empty()) {
          throw CompileError("main function does not have args");
        }
        if (!functionDecl->retType || std::string(*functionDecl->retType) != "int") {
          throw CompileError("return type of main function must be int");
        }
        findMain = true;
      }
    }
  }
  if (!findMain) {
    throw CompileError("cannot find main function");
  }
  for (auto &&decl : node.decls) {
    visit(*decl);
  }
}

} // namespace maeve