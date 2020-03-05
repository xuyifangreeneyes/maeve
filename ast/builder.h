#ifndef MAEVE_AST_BUILDER_H
#define MAEVE_AST_BUILDER_H

#include "../antlr4-runtime/MxBaseVisitor.h"
#include "node.h"
#include <memory>
#include <vector>

namespace maeve {
namespace ast {

class Builder : public MxBaseVisitor {
  template <typename T>
  std::shared_ptr<T> visit_(antlr4::tree::ParseTree *tree) {
    if (tree == nullptr)
      return nullptr;
    return std::static_pointer_cast<T>(
        visit(tree).as<std::shared_ptr<AstNode>>());
  }

  template <typename T, typename... Tparam>
  antlrcpp::Any wrap_(Tparam &&... param) {
    std::shared_ptr<AstNode> node =
        std::make_shared<T>(std::forward<Tparam>(param)...);
    return antlrcpp::Any(std::move(node));
  }

  template <typename T, typename U>
  std::vector<std::shared_ptr<T>> collect_(std::vector<U> &&cstList) {
    std::vector<std::shared_ptr<T>> list;
    list.reserve(cstList.size());
    for (auto &&entry : cstList) {
      list.push_back(visit_<T>(entry));
    }
    return std::move(list);
  }

public:
  antlrcpp::Any visitProgram(MxParser::ProgramContext *ctx) override;

  antlrcpp::Any visitType(MxParser::TypeContext *ctx) override;

  antlrcpp::Any
  visitPrimitiveType(MxParser::PrimitiveTypeContext *ctx) override;

  antlrcpp::Any visitClassType(MxParser::ClassTypeContext *ctx) override;

  antlrcpp::Any visitVarDecl(MxParser::VarDeclContext *ctx) override;

  antlrcpp::Any visitClassDecl(MxParser::ClassDeclContext *ctx) override;

  antlrcpp::Any visitFunctionDecl(MxParser::FunctionDeclContext *ctx) override;

  antlrcpp::Any
  visitParameterDecl(MxParser::ParameterDeclContext *ctx) override;

  antlrcpp::Any
  visitClassConstructor(MxParser::ClassConstructorContext *ctx) override;

  antlrcpp::Any visitBlock(MxParser::BlockContext *ctx) override;

  antlrcpp::Any visitVarDeclStat(MxParser::VarDeclStatContext *ctx) override;

  antlrcpp::Any visitExprStat(MxParser::ExprStatContext *ctx) override;

  antlrcpp::Any visitBlankStat(MxParser::BlankStatContext *ctx) override;

  antlrcpp::Any visitIfStatement(MxParser::IfStatementContext *ctx) override;

  antlrcpp::Any visitWhileStat(MxParser::WhileStatContext *ctx) override;

  antlrcpp::Any visitForStat(MxParser::ForStatContext *ctx) override;

  antlrcpp::Any visitReturnStat(MxParser::ReturnStatContext *ctx) override;

  antlrcpp::Any visitBreakStat(MxParser::BreakStatContext *ctx) override;

  antlrcpp::Any visitContinueStat(MxParser::ContinueStatContext *ctx) override;

  antlrcpp::Any visitErrorCreator(MxParser::ErrorCreatorContext *ctx) override;

  antlrcpp::Any visitArrayCreator(MxParser::ArrayCreatorContext *ctx) override;

  antlrcpp::Any
  visitNonArrayCreator(MxParser::NonArrayCreatorContext *ctx) override;

  antlrcpp::Any visitConstant(MxParser::ConstantContext *ctx) override;

  antlrcpp::Any visitIdExpr(MxParser::IdExprContext *ctx) override;

  antlrcpp::Any visitMemberAccess(MxParser::MemberAccessContext *ctx) override;

  antlrcpp::Any visitBinaryExpr(MxParser::BinaryExprContext *ctx) override;

  antlrcpp::Any visitFunctionCall(MxParser::FunctionCallContext *ctx) override;

  antlrcpp::Any visitParenExpr(MxParser::ParenExprContext *ctx) override;

  antlrcpp::Any visitUnaryExpr(MxParser::UnaryExprContext *ctx) override;

  antlrcpp::Any visitThisExpr(MxParser::ThisExprContext *ctx) override;

  antlrcpp::Any visitNewCreator(MxParser::NewCreatorContext *ctx) override;

  antlrcpp::Any visitSuffixIncDec(MxParser::SuffixIncDecContext *ctx) override;

  antlrcpp::Any
  visitSubscriptAccess(MxParser::SubscriptAccessContext *ctx) override;
};

} // namespace ast
} // namespace maeve

#endif // MAEVE_AST_BUILDER_H
