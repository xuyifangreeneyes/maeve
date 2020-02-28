
// Generated from Mx.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "MxParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by MxParser.
 */
class  MxVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MxParser.
   */
    virtual antlrcpp::Any visitProgram(MxParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitClass(MxParser::ClassContext *context) = 0;

    virtual antlrcpp::Any visitFunc(MxParser::FuncContext *context) = 0;

    virtual antlrcpp::Any visitVar(MxParser::VarContext *context) = 0;

    virtual antlrcpp::Any visitType(MxParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitNonArrayType(MxParser::NonArrayTypeContext *context) = 0;

    virtual antlrcpp::Any visitPrimitiveType(MxParser::PrimitiveTypeContext *context) = 0;

    virtual antlrcpp::Any visitClassType(MxParser::ClassTypeContext *context) = 0;

    virtual antlrcpp::Any visitVarDecl(MxParser::VarDeclContext *context) = 0;

    virtual antlrcpp::Any visitClassDecl(MxParser::ClassDeclContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDecl(MxParser::FunctionDeclContext *context) = 0;

    virtual antlrcpp::Any visitParameterDecls(MxParser::ParameterDeclsContext *context) = 0;

    virtual antlrcpp::Any visitParameterDecl(MxParser::ParameterDeclContext *context) = 0;

    virtual antlrcpp::Any visitParameterList(MxParser::ParameterListContext *context) = 0;

    virtual antlrcpp::Any visitMemberDecl(MxParser::MemberDeclContext *context) = 0;

    virtual antlrcpp::Any visitClassConstructor(MxParser::ClassConstructorContext *context) = 0;

    virtual antlrcpp::Any visitBlock(MxParser::BlockContext *context) = 0;

    virtual antlrcpp::Any visitBlockStat(MxParser::BlockStatContext *context) = 0;

    virtual antlrcpp::Any visitVarDeclStat(MxParser::VarDeclStatContext *context) = 0;

    virtual antlrcpp::Any visitExprStat(MxParser::ExprStatContext *context) = 0;

    virtual antlrcpp::Any visitIfStat(MxParser::IfStatContext *context) = 0;

    virtual antlrcpp::Any visitLoopStat(MxParser::LoopStatContext *context) = 0;

    virtual antlrcpp::Any visitJumpStat(MxParser::JumpStatContext *context) = 0;

    virtual antlrcpp::Any visitBlankStat(MxParser::BlankStatContext *context) = 0;

    virtual antlrcpp::Any visitIfStatement(MxParser::IfStatementContext *context) = 0;

    virtual antlrcpp::Any visitWhileStat(MxParser::WhileStatContext *context) = 0;

    virtual antlrcpp::Any visitForStat(MxParser::ForStatContext *context) = 0;

    virtual antlrcpp::Any visitReturnStat(MxParser::ReturnStatContext *context) = 0;

    virtual antlrcpp::Any visitBreakStat(MxParser::BreakStatContext *context) = 0;

    virtual antlrcpp::Any visitContinueStat(MxParser::ContinueStatContext *context) = 0;

    virtual antlrcpp::Any visitErrorCreator(MxParser::ErrorCreatorContext *context) = 0;

    virtual antlrcpp::Any visitArrayCreator(MxParser::ArrayCreatorContext *context) = 0;

    virtual antlrcpp::Any visitNonArrayCreator(MxParser::NonArrayCreatorContext *context) = 0;

    virtual antlrcpp::Any visitConstant(MxParser::ConstantContext *context) = 0;

    virtual antlrcpp::Any visitIdExpr(MxParser::IdExprContext *context) = 0;

    virtual antlrcpp::Any visitMemberAccess(MxParser::MemberAccessContext *context) = 0;

    virtual antlrcpp::Any visitBinaryExpr(MxParser::BinaryExprContext *context) = 0;

    virtual antlrcpp::Any visitConstantExpr(MxParser::ConstantExprContext *context) = 0;

    virtual antlrcpp::Any visitFunctionCall(MxParser::FunctionCallContext *context) = 0;

    virtual antlrcpp::Any visitParenExpr(MxParser::ParenExprContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpr(MxParser::UnaryExprContext *context) = 0;

    virtual antlrcpp::Any visitThisExpr(MxParser::ThisExprContext *context) = 0;

    virtual antlrcpp::Any visitNewCreator(MxParser::NewCreatorContext *context) = 0;

    virtual antlrcpp::Any visitSuffixIncDec(MxParser::SuffixIncDecContext *context) = 0;

    virtual antlrcpp::Any visitSubscriptAccess(MxParser::SubscriptAccessContext *context) = 0;


};

