
// Generated from Mx.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "MxVisitor.h"


/**
 * This class provides an empty implementation of MxVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  MxBaseVisitor : public MxVisitor {
public:

  virtual antlrcpp::Any visitProgram(MxParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClass(MxParser::ClassContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunc(MxParser::FuncContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVar(MxParser::VarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType(MxParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNonArrayType(MxParser::NonArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimitiveType(MxParser::PrimitiveTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassType(MxParser::ClassTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDecl(MxParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassDecl(MxParser::ClassDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionDecl(MxParser::FunctionDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameterDecls(MxParser::ParameterDeclsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameterDecl(MxParser::ParameterDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameterList(MxParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMemberDecl(MxParser::MemberDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassConstructor(MxParser::ClassConstructorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlock(MxParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlockStat(MxParser::BlockStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDeclStat(MxParser::VarDeclStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprStat(MxParser::ExprStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfStat(MxParser::IfStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLoopStat(MxParser::LoopStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitJumpStat(MxParser::JumpStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlankStat(MxParser::BlankStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfStatement(MxParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhileStat(MxParser::WhileStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitForStat(MxParser::ForStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReturnStat(MxParser::ReturnStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBreakStat(MxParser::BreakStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitContinueStat(MxParser::ContinueStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitErrorCreator(MxParser::ErrorCreatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayCreator(MxParser::ArrayCreatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNonArrayCreator(MxParser::NonArrayCreatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstant(MxParser::ConstantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdExpr(MxParser::IdExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMemberAccess(MxParser::MemberAccessContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBinaryExpr(MxParser::BinaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstantExpr(MxParser::ConstantExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionCall(MxParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParenExpr(MxParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpr(MxParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitThisExpr(MxParser::ThisExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNewCreator(MxParser::NewCreatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSuffixIncDec(MxParser::SuffixIncDecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubscriptAccess(MxParser::SubscriptAccessContext *ctx) override {
    return visitChildren(ctx);
  }


};

