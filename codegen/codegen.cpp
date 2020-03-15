#include "codegen.h"
#include "llvm/IR/Verifier.h"

namespace maeve {

llvm::Type *getInt8Ty() { return llvm::Type::getInt8Ty(TheContext::get()); }

llvm::Type *getInt32Ty() { return llvm::Type::getInt32Ty(TheContext::get()); }

llvm::Type *getInt64Ty() { return llvm::Type::getInt64Ty(TheContext::get()); }

llvm::Type *getVoidTy() { return llvm::Type::getVoidTy(TheContext::get()); }

llvm::Type *getInt8PtrTy() {
  return llvm::Type::getInt8PtrTy(TheContext::get());
}

llvm::Type *getInt32PtrTy() {
  return llvm::Type::getInt32PtrTy(TheContext::get());
}

llvm::Constant *getInt32(uint64_t n) {
  return llvm::ConstantInt::get(getInt32Ty(), n);
}

llvm::Constant *getInt64(uint64_t n) {
  return llvm::ConstantInt::get(getInt64Ty(), n);
}

std::string
getClassName(const std::shared_ptr<ast::MemberAccess> &memberAccess) {
  auto classType =
      std::dynamic_pointer_cast<ast::ClassType>(memberAccess->instance->type);
  assert(classType);
  return classType->name;
}

llvm::AllocaInst *createEntryBlockAlloca(llvm::Function *function,
                                         const std::string &name,
                                         llvm::Type *type) {
  llvm::IRBuilder<> TmpB(&function->getEntryBlock(),
                         function->getEntryBlock().begin());
  return TmpB.CreateAlloca(type, nullptr, name);
}

llvm::Type *Codegen::getArrayPtrTy() const {
  return llvm::PointerType::getUnqual(module->getTypeByName("_Array"));
}

llvm::Type *Codegen::getType(const std::shared_ptr<ast::Type> &type) const {
  if (auto builtinType = std::dynamic_pointer_cast<ast::BuiltinType>(type)) {
    using Kind = ast::BuiltinType::Kind;
    switch (builtinType->kind) {
    case Kind::Int:
      return getInt32Ty();
    case Kind::Bool:
      return getInt8Ty();
    case Kind::String:
      return getInt8PtrTy();
    case Kind::Void:
      return getVoidTy();
    default:
      // Kind::Null is not supposed to appear
      assert(false);
    }
  }
  if (auto classType = std::dynamic_pointer_cast<ast::ClassType>(type)) {
    auto classDecl = classType->classDecl.lock();
    auto structType = module->getTypeByName(classDecl->name);
    assert(structType);
    return llvm::PointerType::getUnqual(structType);
  }
  /*
   * struct _Array {
   *   char *data;
   *   int32_t size;
   * }
   */
  if (auto arrayType = std::dynamic_pointer_cast<ast::ArrayType>(type)) {
    return getArrayPtrTy();
  }

  assert(false);
}

llvm::Function *
Codegen::addFunctionPrototype(const std::string &name, llvm::Type *retType,
                              const std::vector<llvm::Type *> &argTypes) {
  llvm::FunctionType *functionType =
      llvm::FunctionType::get(retType, argTypes, false);
  return llvm::Function::Create(functionType, llvm::Function::ExternalLinkage,
                                name, module.get());
}

void Codegen::addFunctionPrototype(
    const std::shared_ptr<ast::FunctionDecl> &functionDecl,
    const std::shared_ptr<ast::ClassDecl> &classDecl) {
  std::string functionName = functionDecl->name;
  std::vector<llvm::Type *> argTypes;
  if (classDecl) {
    // for class member function and constructor, add prefix for function name
    functionName = "_" + classDecl->name + "_" + functionName;
    // and add class instance as first argument
    llvm::Type *classType =
        llvm::PointerType::getUnqual(module->getTypeByName(classDecl->name));
    argTypes.push_back(classType);
  }
  for (auto &&varDecl : functionDecl->args) {
    argTypes.push_back(getType(varDecl->type));
  }
  // for class constructor, we assume its return type is void
  llvm::Type *retType =
      functionDecl->retType ? getType(functionDecl->retType) : getVoidTy();

  llvm::Function *function =
      addFunctionPrototype(functionDecl->name, retType, argTypes);

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

void Codegen::addStringComparison(const std::string &name) {
  addFunctionPrototype(name, getInt8Ty(), {getInt8PtrTy(), getInt8PtrTy()});
}

void Codegen::addBuiltin() {
  // add struct Array
  llvm::StructType *structType =
      llvm::StructType::create(TheContext::get(), "_Array");
  structType->setBody({getInt8PtrTy(), getInt32Ty()});

  // add builtin functions
  addFunctionPrototype("print", getVoidTy(), {getInt8PtrTy()});
  addFunctionPrototype("println", getVoidTy(), {getInt8PtrTy()});
  addFunctionPrototype("getString", getInt8PtrTy(), {});
  addFunctionPrototype("getInt", getInt32Ty(), {});
  addFunctionPrototype("toString", getInt8PtrTy(), {getInt32Ty()});
  addFunctionPrototype("_string_length", getInt32Ty(), {getInt8PtrTy()});
  addFunctionPrototype("_string_substring", getInt8PtrTy(),
                       {getInt8PtrTy(), getInt32Ty(), getInt32Ty()});
  addFunctionPrototype("_string_parseInt", getInt32Ty(), {getInt8PtrTy()});
  addFunctionPrototype("_string_ord", getInt32Ty(),
                       {getInt8PtrTy(), getInt32Ty()});
  addFunctionPrototype("_string_add", getInt8PtrTy(),
                       {getInt8PtrTy(), getInt8PtrTy()});

  addStringComparison("_string_eq");
  addStringComparison("_string_neq");
  addStringComparison("_string_lt");
  addStringComparison("_string_gt");
  addStringComparison("_string_le");
  addStringComparison("_string_ge");

  addFunctionPrototype("_array_size", getInt32Ty(), {getArrayPtrTy()});
}

llvm::Value *Codegen::getVar(const ast::VarExpr &expr) const {
  ast::NodeId varId = expr.varDecl.lock()->getID();
  auto iter1 = localVars.find(varId);
  if (iter1 != localVars.end()) {
    return iter1->second;
  }
  auto iter2 = globalVars.find(varId);
  if (iter2 != globalVars.end()) {
    return iter2->second;
  }
  return nullptr;
}

llvm::Value *Codegen::getExprValue(ast::Expr &expr) {
  visit(expr);
  auto iter = values.find(expr.getID());
  if (iter != values.end()) {
    return iter->second;
  }
  return nullptr;
}

llvm::GetElementPtrInst *
Codegen::getElementPtrInBounds(llvm::Value *ptr,
                               const std::vector<llvm::Value *> &idxList,
                               const std::string &name) {
  return llvm::GetElementPtrInst::CreateInBounds(ptr, idxList, name,
                                                 builder->GetInsertBlock());
}

void Codegen::assertNotTerminated() const {
  assert(!builder->GetInsertBlock()->getTerminator());
}

Codegen::Codegen()
    : module(std::make_unique<llvm::Module>("module", TheContext::get())),
      builder(std::make_unique<llvm::IRBuilder<>>(TheContext::get())) {
  addBuiltin();
}

void Codegen::createBrIfNotTerminated(llvm::BasicBlock *destBB) {
  if (!builder->GetInsertBlock()->getTerminator()) {
    builder->CreateBr(destBB);
  }
}

void Codegen::dealLoopCondition(ast::Expr &cond, llvm::BasicBlock *bodyBB,
                                llvm::BasicBlock *endBB) {
  llvm::Value *condValue = getExprValue(cond);
  assert(condValue);
  assertNotTerminated();
  builder->CreateCondBr(condValue, bodyBB, endBB);
}

llvm::Value *Codegen::getPointer(std::shared_ptr<ast::Expr> expr) {
  if (auto varExpr = std::dynamic_pointer_cast<ast::VarExpr>(expr)) {
    if (varExpr->name == "this") {
      assert(thisAlloca);
      return thisAlloca;
    } else {
      llvm::Value *var = getVar(*varExpr);
      assert(var);
      return var;
    }
  }
  if (auto memberAccess = std::dynamic_pointer_cast<ast::MemberAccess>(expr)) {
    // we assume that there is no code like `getFoo(1, 2).a = 2`
    llvm::Value *ptrPtr = getPointer(memberAccess->instance);
    assert(ptrPtr);
    llvm::Value *ptr = builder->CreateLoad(ptrPtr);
    uint64_t second =
        structMap[getClassName(memberAccess)][memberAccess->field];
    return getElementPtrInBounds(ptr, {getInt32(0), getInt32(second)}, "elem");
  }
  if (auto arrayAccess = std::dynamic_pointer_cast<ast::ArrayAccess>(expr)) {
    llvm::Value *arrayPtrPtr = getPointer(arrayAccess->array);
    assert(arrayPtrPtr);
    llvm::Value *arrayPtr = builder->CreateLoad(arrayPtrPtr);
    llvm::Value *charPtrPtr =
        getElementPtrInBounds(arrayPtr, {getInt32(0), getInt32(0)}, "charPtr");
    llvm::Value *charPtr = builder->CreateLoad(charPtrPtr);
    llvm::Value *dataPtr = builder->CreateBitCast(
        charPtr, llvm::PointerType::getUnqual(getType(expr->type)));

    llvm::Value *indexValue = getExprValue(*arrayAccess->index);
    assert(indexValue && indexValue->getType()->isIntegerTy(32));
    indexValue = builder->CreateSExt(indexValue, getInt64Ty());

    return getElementPtrInBounds(dataPtr, {indexValue}, "dataPtr");
  }
  assert(false);
}

void Codegen::visit(ast::AstNode &node) { node.accept(*this); }

void Codegen::visit(ast::BinaryExpr &node) {}

void Codegen::visit(ast::UnaryExpr &node) {
  using Op = ast::UnaryExpr::Op;
  switch (node.op) {
  case Op::PreInc:
  case Op::PreDec:
  case Op::PostInc:
  case Op::PostDec: {
    llvm::Value *ptr = getPointer(node.operand);
    llvm::Value *oldValue = builder->CreateLoad(ptr);
    llvm::Value *newValue =
        builder->CreateNSWAdd(oldValue, getInt32(static_cast<uint64_t>((node.op == Op::PreInc || node.op == Op::PostInc) ? 1 : -1)));
    values[node.getID()] =
        (node.op == Op::PreInc || node.op == Op::PreDec) ? newValue : oldValue;
    break;
  }

  }
}

void Codegen::visit(ast::FunctionCall &node) {
  std::string functionName = node.method;
  std::vector<llvm::Value *> args;
  if (node.instance) {
    auto type = node.instance->type;
    if (auto classType = std::dynamic_pointer_cast<ast::ClassType>(type)) {
      functionName = "_" + classType->name + "_" + functionName;
    } else if (auto arrayType =
                   std::dynamic_pointer_cast<ast::ArrayType>(type)) {
      functionName = "_array_" + functionName;
    } else {
      auto builtinType = std::dynamic_pointer_cast<ast::BuiltinType>(type);
      assert(builtinType && builtinType->kind == ast::BuiltinType::String);
      functionName = "_string_" + functionName;
    }
    llvm::Value *instanceValue = getExprValue(*node.instance);
    assert(instanceValue);
    args.push_back(instanceValue);
  }
  for (auto &&arg : node.args) {
    llvm::Value *argValue = getExprValue(*arg);
    assert(argValue);
    args.push_back(argValue);
  }
  llvm::Function *function = module->getFunction(functionName);
  builder->CreateCall(function, args);
}

void Codegen::visit(ast::ArrayAccess &node) {
  auto arrayAccess =
      std::dynamic_pointer_cast<ast::ArrayAccess>(node.shared_from_this());
  assert(arrayAccess);
  llvm::Value *ptr = getPointer(arrayAccess);
  values[node.getID()] = builder->CreateLoad(ptr);
}

void Codegen::visit(ast::MemberAccess &node) {
  auto memberAccess =
      std::dynamic_pointer_cast<ast::MemberAccess>(node.shared_from_this());
  assert(memberAccess);
  llvm::Value *ptr = getPointer(memberAccess);
  values[node.getID()] = builder->CreateLoad(ptr);
}

void Codegen::visit(ast::NewExpr &node) {
  // TODO
}

void Codegen::visit(ast::VarExpr &node) {
  auto varExpr =
      std::dynamic_pointer_cast<ast::VarExpr>(node.shared_from_this());
  assert(varExpr);
  llvm::Value *ptr = getPointer(varExpr);
  values[node.getID()] = builder->CreateLoad(ptr);
}

void Codegen::visit(ast::LiteralInt &node) {
  values[node.getID()] = getInt32(static_cast<uint64_t>(node.value));
}

void Codegen::visit(ast::LiteralBool &node) {
  values[node.getID()] =
      llvm::ConstantInt::get(getInt8Ty(), static_cast<uint64_t>(node.value));
}

void Codegen::visit(ast::LiteralString &node) {
  values[node.getID()] = builder->CreateGlobalStringPtr(node.value);
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
    llvm::Value *initValue = getExprValue(*varDecl->initExpr);
    assert(initValue);
    builder->CreateStore(initValue, allocaInst);
  }
  localVars[varDecl->getID()] = allocaInst;
}

void Codegen::visit(ast::ExprStmt &node) { visit(*node.expr); }

void Codegen::visit(ast::IfStmt &node) {
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
  thisAlloca = nullptr;

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

  // 1. setBody for every StructType
  // 2. record index of field for every struct, which is used in
  // `llvm::GetElementPtrInst::CreateInBounds`
  for (auto &&decl : node.decls) {
    auto classDecl = std::dynamic_pointer_cast<ast::ClassDecl>(decl);
    if (!classDecl)
      continue;
    std::vector<llvm::Type *> fieldTypes;
    std::map<std::string, std::size_t> fieldMap;
    std::size_t i = 0;
    for (auto &&iter : classDecl->decls) {
      auto fieldDecl = std::dynamic_pointer_cast<ast::VarDecl>(iter.second);
      if (!fieldDecl)
        continue;
      // we assume field does not have initialization expression
      assert(!fieldDecl->initExpr);
      fieldTypes.push_back(getType(fieldDecl->type));
      fieldMap[fieldDecl->name] = i;
      ++i;
    }
    // If `Class A` does not have any data field, it looks like
    // `%struct.A = type { i8 }` in LLVM IR.
    if (fieldTypes.empty()) {
      fieldTypes.push_back(getInt8Ty());
    }
    structTypes[decl->name]->setBody(fieldTypes);
    structMap[decl->name] = fieldMap;
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
