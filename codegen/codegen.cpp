#include "codegen.h"
#include "llvm/IR/Verifier.h"

namespace maeve {

llvm::Type *getIntType() { return llvm::Type::getInt32Ty(TheContext::get()); }

llvm::Type *getBoolType() { return llvm::Type::getInt8Ty(TheContext::get()); }

llvm::AllocaInst *createEntryBlockAlloca(llvm::Function *function,
                                         const std::string &name,
                                         llvm::Type *type) {
  llvm::IRBuilder<> TmpB(&function->getEntryBlock(),
                         function->getEntryBlock().begin());
  return TmpB.CreateAlloca(type, nullptr, name);
}

llvm::Type *Codegen::getType(const std::shared_ptr<ast::Type> &type) const {
  if (auto builtinType = std::dynamic_pointer_cast<ast::BuiltinType>(type)) {
    using Kind = ast::BuiltinType::Kind;
    switch (builtinType->kind) {
    case Kind::Int:
      return getIntType();
    case Kind::Bool:
      return getBoolType();
    case Kind::String:
      // TODO: deal with string type
      assert(false);
    case Kind::Void:
      return llvm::Type::getVoidTy(TheContext::get());
    default:
      assert(false);
    }
  }
  if (auto classType = std::dynamic_pointer_cast<ast::ClassType>(type)) {
    auto classDecl = classType->classDecl.lock();
    auto structType = module->getTypeByName(classDecl->name);
    assert(structType);
    return llvm::PointerType::getUnqual(structType);
  }
  // in Mx*, array is implemented by pointer
  auto arrayType = std::dynamic_pointer_cast<ast::ArrayType>(type);
  assert(arrayType);
  auto currentType = getType(arrayType->baseType);
  std::size_t i = arrayType->dim;
  while (i != 0) {
    currentType = llvm::PointerType::getUnqual(currentType);
    --i;
  }
  return currentType;
}

void Codegen::addFunctionPrototype(
    const std::shared_ptr<ast::FunctionDecl> &functionDecl,
    const std::shared_ptr<ast::ClassDecl> &classDecl) {
  std::vector<llvm::Type *> argTypes;
  llvm::Type *classType =
      classDecl
          ? llvm::PointerType::getUnqual(module->getTypeByName(classDecl->name))
          : nullptr;
  // for class member function and constructor, add class instance as first
  // argument
  if (classDecl) {
    argTypes.push_back(classType);
  }
  for (auto &&varDecl : functionDecl->args) {
    argTypes.push_back(getType(varDecl->type));
  }
  // for class constructor, we assume its return type is void
  llvm::Type *retType = functionDecl->retType
                            ? getType(functionDecl->retType)
                            : llvm::Type::getVoidTy(TheContext::get());
  llvm::FunctionType *functionType =
      llvm::FunctionType::get(retType, argTypes, false);
  llvm::Function *function =
      llvm::Function::Create(functionType, llvm::Function::ExternalLinkage,
                             functionDecl->name, module.get());
  std::size_t idx = 0;
  for (auto &&arg : function->args()) {
    std::string argName;
    if (idx == 0 && classDecl) {
      argName = "self";
    } else {
      argName = functionDecl->args[idx++]->name;
    }
    arg.setName(argName);
  }
}

void Codegen::addBuiltinFunction() {
  // TODO
}

llvm::Value *Codegen::getExprValue(const ast::Expr &expr) const {
  auto iter = values.find(expr.getID());
  if (iter != values.end()) {
    return iter->second;
  }
  return nullptr;
}

void Codegen::assertNotTerminated() const {
  assert(!builder->GetInsertBlock()->getTerminator());
}

Codegen::Codegen()
    : module(std::make_unique<llvm::Module>("module", TheContext::get())),
      builder(std::make_unique<llvm::IRBuilder<>>(TheContext::get())) {
  addBuiltinFunction();
}

void Codegen::createBrIfNotTerminated(llvm::BasicBlock *destBB) {
  if (!builder->GetInsertBlock()->getTerminator()) {
    builder->CreateBr(destBB);
  }
}

void Codegen::dealLoopCondition(ast::Expr &cond, llvm::BasicBlock *bodyBB,
                                llvm::BasicBlock *endBB) {
  visit(cond);
  llvm::Value *condValue = getExprValue(cond);
  assert(condValue);
  assertNotTerminated();
  builder->CreateCondBr(condValue, bodyBB, endBB);
}

llvm::Value *Codegen::getPointer(std::shared_ptr<ast::Expr> expr) {
  if (auto varExpr = std::dynamic_pointer_cast<ast::VarExpr>(expr)) {
    if (varExpr->name == "this") {

    } else {
    }
  }
  if (auto memberAccess = std::dynamic_pointer_cast<ast::MemberAccess>(expr)) {
  }
  if (auto arrayAccess = std::dynamic_pointer_cast<ast::ArrayAccess>(expr)) {
  }
  if (auto unaryExpr = std::dynamic_pointer_cast<ast::UnaryExpr>(expr)) {
  }
  assert(false);
}

void Codegen::visit(ast::AstNode &node) { node.accept(*this); }

void Codegen::visit(ast::BinaryExpr &node) {}

void Codegen::visit(ast::UnaryExpr &node) {}

void Codegen::visit(ast::FunctionCall &node) {}

void Codegen::visit(ast::ArrayAccess &node) {}

void Codegen::visit(ast::MemberAccess &node) {}

void Codegen::visit(ast::NewExpr &node) {}

void Codegen::visit(ast::VarExpr &node) {}

void Codegen::visit(ast::LiteralInt &node) {
  values[node.getID()] =
      llvm::ConstantInt::get(getIntType(), static_cast<uint64_t>(node.value));
}

void Codegen::visit(ast::LiteralBool &node) {
  values[node.getID()] =
      llvm::ConstantInt::get(getBoolType(), static_cast<uint64_t>(node.value));
}

void Codegen::visit(ast::LiteralString &node) {
  // TODO
}

void Codegen::visit(ast::LiteralNull &node) {
  assert(!std::dynamic_pointer_cast<ast::BuiltinType>(node.type));
  llvm::Type *type = getType(node.type);
  assert(type->isPointerTy());
  llvm::PointerType *pointerType = (llvm::PointerType *)(getType(node.type));
  values[node.getID()] = llvm::ConstantPointerNull::get(pointerType);
}

void Codegen::visit(ast::CompoundStmt &node) {
  for (auto &&stmt : node.stmts) {
    visit(*stmt);
  }
}

void Codegen::visit(ast::VarDeclStmt &node) {
  llvm::Function *function = builder->GetInsertBlock()->getParent();
  auto varDecl = node.varDecl;
  llvm::AllocaInst *allocaInst =
      createEntryBlockAlloca(function, varDecl->name, getType(varDecl->type));
  if (varDecl->initExpr) {
    visit(*varDecl->initExpr);
    llvm::Value *initValue = getExprValue(*varDecl->initExpr);
    assert(initValue);
    builder->CreateStore(initValue, allocaInst);
  }
  localVars[varDecl->getID()] = allocaInst;
}

void Codegen::visit(ast::ExprStmt &node) { visit(*node.expr); }

void Codegen::visit(ast::IfStmt &node) {
  visit(*node.cond);
  llvm::Value *cond = getExprValue(*node.cond);
  assert(cond);

  llvm::Function *function = builder->GetInsertBlock()->getParent();
  llvm::BasicBlock *thenBB =
      llvm::BasicBlock::Create(TheContext::get(), "then", function);
  llvm::BasicBlock *elseBB =
      node.otherwise
          ? llvm::BasicBlock::Create(TheContext::get(), "else", function)
          : nullptr;
  llvm::BasicBlock *mergeBB =
      llvm::BasicBlock::Create(TheContext::get(), "merge", function);
  if (elseBB) {
    builder->CreateCondBr(cond, thenBB, elseBB);
  } else {
    builder->CreateCondBr(cond, thenBB, mergeBB);
  }

  builder->SetInsertPoint(thenBB);
  visit(*node.then);
  createBrIfNotTerminated(mergeBB);

  if (elseBB) {
    builder->SetInsertPoint(elseBB);
    visit(*node.otherwise);
    createBrIfNotTerminated(mergeBB);
  }

  builder->SetInsertPoint(mergeBB);
}

void Codegen::visit(ast::ForStmt &node) {
  llvm::Function *function = builder->GetInsertBlock()->getParent();
  llvm::BasicBlock *condBB =
      llvm::BasicBlock::Create(TheContext::get(), "for_cond", function);
  llvm::BasicBlock *bodyBB =
      llvm::BasicBlock::Create(TheContext::get(), "for_body", function);
  llvm::BasicBlock *stepBB =
      llvm::BasicBlock::Create(TheContext::get(), "for_step", function);
  llvm::BasicBlock *endBB =
      llvm::BasicBlock::Create(TheContext::get(), "for_end", function);

  breakDests.push(endBB);
  continueDests.push(stepBB);

  if (node.init) {
    visit(*node.init);
  }
  assertNotTerminated();
  builder->CreateBr(condBB);

  builder->SetInsertPoint(condBB);
  if (node.cond) {
    dealLoopCondition(*node.cond, bodyBB, endBB);
  } else {
    builder->CreateBr(bodyBB);
  }

  builder->SetInsertPoint(bodyBB);
  visit(*node.body);
  createBrIfNotTerminated(stepBB);

  builder->SetInsertPoint(stepBB);
  if (node.step) {
    visit(*node.step);
  }
  assertNotTerminated();
  builder->CreateBr(condBB);

  builder->SetInsertPoint(endBB);

  breakDests.pop();
  continueDests.pop();
}

void Codegen::visit(ast::WhileStmt &node) {
  llvm::Function *function = builder->GetInsertBlock()->getParent();
  llvm::BasicBlock *condBB =
      llvm::BasicBlock::Create(TheContext::get(), "while_cond", function);
  llvm::BasicBlock *bodyBB =
      llvm::BasicBlock::Create(TheContext::get(), "while_body", function);
  llvm::BasicBlock *endBB =
      llvm::BasicBlock::Create(TheContext::get(), "while_end", function);

  breakDests.push(endBB);
  continueDests.push(bodyBB);

  builder->CreateBr(condBB);

  builder->SetInsertPoint(condBB);
  dealLoopCondition(*node.cond, bodyBB, endBB);

  builder->SetInsertPoint(bodyBB);
  visit(*node.body);
  createBrIfNotTerminated(bodyBB);

  builder->SetInsertPoint(endBB);

  breakDests.pop();
  continueDests.pop();
}

void Codegen::visit(ast::ReturnStmt &node) {
  if (node.value) {
    visit(*node.value);
    llvm::Value *retValue = getExprValue(*node.value);
    builder->CreateRet(retValue);
  } else {
    builder->CreateRetVoid();
  }
}

void Codegen::visit(ast::BreakStmt &node) {
  builder->CreateBr(breakDests.top());
}

void Codegen::visit(ast::ContinueStmt &node) {
  builder->CreateBr(continueDests.top());
}

/*
 * only global `VarDecl` comes here
 * `VarDecl` in Class does not need AllocaInst
 * `VarDecl` in function argument list is processed when visiting `FunctionDecl`
 * `VarDecl` in `VarDeclStmt` is processed when visiting `VarDeclStmt`
 */
void Codegen::visit(ast::VarDecl &node) {
  module->getOrInsertGlobal(node.name, getType(node.type));
  llvm::GlobalVariable *globalVar = module->getNamedGlobal(node.name);
  globalVar->setLinkage(llvm::GlobalVariable::ExternalLinkage);
  llvm::Type *type = globalVar->getType()->getElementType();
  if (node.initExpr) {
    visit(*node.initExpr);
    llvm::Value *initValue = getExprValue(*node.initExpr);
    assert(initValue);
    llvm::Constant *c = llvm::dyn_cast<llvm::Constant>(initValue);
    assert(c); // or throw an error?
    globalVar->setInitializer(c);
  } else {
    llvm::ConstantAggregateZero *zeroInit =
        llvm::ConstantAggregateZero::get(type);
    globalVar->setInitializer(zeroInit);
  }
  globalVars[node.getID()] = globalVar;
}

void Codegen::visit(ast::FunctionDecl &node) {
  llvm::Function *function = module->getFunction(node.name);
  assert(function && function->empty());

  llvm::BasicBlock *entryBB =
      llvm::BasicBlock::Create(TheContext::get(), "entry", function);
  builder->SetInsertPoint(entryBB);

  // too inefficient
  std::size_t count = 0;
  for (auto &&arg : function->args()) {
    ++count;
  }

  bool isMemberFunction = count == node.args.size() + 1;
  std::size_t idx = 0;
  for (auto &&arg : function->args()) {
    llvm::AllocaInst *allocaInst =
        createEntryBlockAlloca(function, arg.getName(), arg.getType());
    builder->CreateStore(&arg, allocaInst);
    if (isMemberFunction && idx == 0) {
      // this argument is `ClassType *self`
      thisAlloca = allocaInst;
    } else {
      ast::NodeId id = node.args[idx++]->getID();
      localVars[id] = allocaInst;
    }
  }

  currentFunction = function;
  visit(*node.body);
  currentFunction = nullptr;

  llvm::verifyFunction(*function);

  // TODO: add function-level optimization
}

void Codegen::visit(ast::ClassDecl &node) {
  // set body of member functions
  for (auto &&iter : node.decls) {
    auto functionDecl =
        std::dynamic_pointer_cast<ast::FunctionDecl>(iter.second);
    if (functionDecl) {
      visit(*functionDecl);
    }
  }
}

void Codegen::visit(ast::AstRoot &node) {
  // add StructType
  std::map<std::string, llvm::StructType *> structTypes;
  for (auto &&decl : node.decls) {
    auto classDecl = std::dynamic_pointer_cast<ast::ClassDecl>(decl);
    if (!classDecl)
      continue;
    structTypes[decl->name] =
        llvm::StructType::create(TheContext::get(), decl->name);
  }

  // setBody for every StructType
  for (auto &&decl : node.decls) {
    auto classDecl = std::dynamic_pointer_cast<ast::ClassDecl>(decl);
    if (!classDecl)
      continue;
    std::vector<llvm::Type *> fieldTypes;
    for (auto &&iter : classDecl->decls) {
      auto fieldDecl = std::dynamic_pointer_cast<ast::VarDecl>(iter.second);
      if (!fieldDecl)
        continue;
      // we assume field does not have initialization expression
      assert(!fieldDecl->initExpr);
      fieldTypes.push_back(getType(fieldDecl->type));
    }
    // If `Class A` does not have any data field, it looks like
    // `%struct.A = type { i8 }` in LLVM IR.
    if (fieldTypes.empty()) {
      fieldTypes.push_back(getBoolType());
    }
    structTypes[decl->name]->setBody(fieldTypes);
  }

  // add all functions (including member function) to module
  for (auto &&decl : node.decls) {
    if (auto functionDecl =
            std::dynamic_pointer_cast<ast::FunctionDecl>(decl)) {
      addFunctionPrototype(functionDecl);
    } else if (auto classDecl =
                   std::dynamic_pointer_cast<ast::ClassDecl>(decl)) {
      for (auto &&iter : classDecl->decls) {
        auto memberFuncDecl =
            std::dynamic_pointer_cast<ast::FunctionDecl>(iter.second);
        if (!memberFuncDecl)
          continue;
        addFunctionPrototype(functionDecl, classDecl);
      }
    }
  }

  for (auto &&decl : node.decls) {
    visit(*decl);
  }
}

} // namespace maeve
