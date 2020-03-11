#include "codegen.h"
#include "llvm/IR/Verifier.h"

namespace maeve {

llvm::AllocaInst *createEntryBlockAlloca(llvm::Function *function,
                                         const std::string &name,
                                         llvm::Type *type) {
  llvm::IRBuilder<> TmpB(&function->getEntryBlock(),
                         function->getEntryBlock().begin());
  return TmpB.CreateAlloca(type, nullptr, name);
}

llvm::Type *Codegen::getType(const std::shared_ptr<ast::Type> &type) {
  if (auto builtinType = std::dynamic_pointer_cast<ast::BuiltinType>(type)) {
    using Kind = ast::BuiltinType::Kind;
    switch (builtinType->kind) {
    case Kind::Int:
      return llvm::Type::getInt32Ty(TheContext::get());
    case Kind::Bool:
      return llvm::Type::getInt1Ty(TheContext::get());
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

void Codegen::addGlobalVarInit() {
  std::vector<llvm::Type *> argTypes;
  auto functionType = llvm::FunctionType::get(
      llvm::Type::getVoidTy(TheContext::get()), argTypes, false);
  auto function =
      llvm::Function::Create(functionType, llvm::Function::ExternalLinkage,
                             "__global_var_init", module.get());
  llvm::BasicBlock::Create(TheContext::get(), "entry", function);
}

void Codegen::addBuiltinFunction() {
  // TODO
}

Codegen::Codegen()
    : module(std::make_unique<llvm::Module>("module", TheContext::get())),
      builder(std::make_unique<llvm::IRBuilder<>>(TheContext::get())) {
  addGlobalVarInit();
  addBuiltinFunction();
}

void Codegen::visit(ast::AstNode &node) { node.accept(*this); }

/*
 * only global `VarDecl` comes here
 * `VarDecl` in Class does not need Alloca
 * `VarDecl` in function argument list is processed when visiting `FunctionDecl`
 * `VarDecl` in `VarDeclStmt` is processed when visiting `VarDeclStmt`
 */
void Codegen::visit(ast::VarDecl &node) {
  auto type = getType(node.type);

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
    llvm::AllocaInst *alloca =
        createEntryBlockAlloca(function, arg.getName(), arg.getType());
    builder->CreateStore(&arg, alloca);
    if (isMemberFunction && idx == 0) {
      // this argument is `ClassType *self`
      thisAlloca = alloca;
    } else {
      ast::NodeId id = node.args[idx++]->getID();
      vars[id] = alloca;
    }
  }

  visit(*node.body);

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
