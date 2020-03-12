#ifndef MAEVE_CODEGEN_H
#define MAEVE_CODEGEN_H

#include <memory>
#include <stack>
#include <unordered_map>

#include "../ast/node.h"
#include "../ast/visitor.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"

namespace maeve {

class TheContext {
public:
  TheContext(const TheContext &) = delete;
  void operator=(const TheContext &) = delete;

  static llvm::LLVMContext &get() {
    static llvm::LLVMContext context;
    return context;
  }

private:
  TheContext() = default;
};

class Codegen : public ast::Visitor {
public:
  Codegen();

  void visit(ast::AstNode &node) override;

  void visit(ast::BinaryExpr &node) override;
  void visit(ast::UnaryExpr &node) override;
  void visit(ast::FunctionCall &node) override;
  void visit(ast::ArrayAccess &node) override;
  void visit(ast::MemberAccess &node) override;
  void visit(ast::NewExpr &node) override;
  void visit(ast::VarExpr &node) override;
  void visit(ast::LiteralInt &node) override;
  void visit(ast::LiteralBool &node) override;
  void visit(ast::LiteralString &node) override;
  void visit(ast::LiteralNull &node) override;

  void visit(ast::CompoundStmt &node) override;
  void visit(ast::VarDeclStmt &node) override;
  void visit(ast::ExprStmt &node) override;
  void visit(ast::IfStmt &node) override;
  void visit(ast::ForStmt &node) override;
  void visit(ast::WhileStmt &node) override;
  void visit(ast::ReturnStmt &node) override;
  void visit(ast::BreakStmt &node) override;
  void visit(ast::ContinueStmt &node) override;

  void visit(ast::VarDecl &node) override;
  void visit(ast::FunctionDecl &node) override;
  void visit(ast::ClassDecl &node) override;

  void visit(ast::AstRoot &node) override;

private:
  llvm::Function *currentFunction;

  std::unique_ptr<llvm::Module> module;
  std::unique_ptr<llvm::IRBuilder<>> builder;

  std::unordered_map<ast::NodeId, llvm::GlobalVariable *> globalVars;
  std::unordered_map<ast::NodeId, llvm::AllocaInst *> localVars;
  // When we meet a member function, we allocate a stack slot to store
  // `ClassType *self` and record it in `thisAlloca`. For VarExpr `this`, it
  // does not link to VarDecl so we use `thisAlloca` to get `this`.
  llvm::AllocaInst *thisAlloca = nullptr;

  std::unordered_map<ast::NodeId, llvm::Value *> values;

  std::stack<llvm::BasicBlock *> breakDests;
  std::stack<llvm::BasicBlock *> continueDests;

  llvm::Type *getType(const std::shared_ptr<ast::Type> &type) const;
  void addFunctionPrototype(
      const std::shared_ptr<ast::FunctionDecl> &functionDecl,
      const std::shared_ptr<ast::ClassDecl> &classDecl = nullptr);
  void addBuiltinFunction();
  llvm::Value *getExprValue(const ast::Expr &expr) const;

  void assertNotTerminated() const;
  void createBrIfNotTerminated(llvm::BasicBlock *destBB);
  void dealLoopCondition(ast::Expr &cond, llvm::BasicBlock *bodyBB,
                         llvm::BasicBlock *endBB);

  llvm::Value *getPointer(std::shared_ptr<ast::Expr> expr);
};

} // namespace maeve

#endif // MAEVE_CODEGEN_H
