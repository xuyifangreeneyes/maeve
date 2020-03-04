#ifndef MENHIR_AST_BUILDER_H
#define MENHIR_AST_BUILDER_H

#include "../antlr4-runtime/MxBaseVisitor.h"
#include "node.h"
#include "../utils/error.h"
#include <memory>
#include <vector>

namespace menhir {
namespace ast {

class AstBuilder : public MxBaseVisitor {
  template <typename T>
  std::shared_ptr<T> visit_(antlr4::tree::ParseTree *tree) {
    if (tree == nullptr)
      return nullptr;
    return visit(tree).as<std::shared_ptr<T>>();
  }

  template <typename T, typename... Tparam>
  antlrcpp::Any wrap_(Tparam &&... param) {
    return antlrcpp::Any(std::make_shared<T>(std::forward<Tparam>(param)...));
  }

  template <typename T, typename U>
  std::vector<std::shared_ptr<T>> collect_(std::vector<U> &&cstList) {
    std::vector<std::shared_ptr<T>> list;
    for (auto &&entry : cstList) {
      list.push_back(visit_<T>(entry));
    }
    return std::move(list);
  }

public:
  antlrcpp::Any visitProgram(MxParser::ProgramContext *ctx) override {
    return wrap_<Program>(collect_<Decl>(ctx->declaration()));
  }

  antlrcpp::Any visitType(MxParser::TypeContext *ctx) override {
    using Kind = BuiltinType::Kind;
    std::string name = ctx->nonArrayType()->getText();
    std::shared_ptr<BaseType> baseType;
    if (name == "int") {
      baseType = std::make_shared<BuiltinType>(Kind::Int);
    } else if (name == "bool") {
      baseType = std::make_shared<BuiltinType>(Kind::Bool);
    } else if (name == "string") {
      baseType = std::make_shared<BuiltinType>(Kind::String);
    } else {
      baseType = std::make_shared<ClassType>(name);
    }
    std::size_t dim = ctx->LBRACK().size();
    if (dim == 0) {
      return antlrcpp::Any(std::move(baseType));
    }
    return wrap_<ArrayType>(std::move(baseType), dim);
  }

  antlrcpp::Any
  visitPrimitiveType(MxParser::PrimitiveTypeContext *ctx) override {
    using Kind = BuiltinType::Kind;
    Kind kind;
    if (ctx->INT()) {
      kind = Kind::Int;
    } else if (ctx->BOOL()) {
      kind = Kind::Bool;
    } else if (ctx->STRING()) {
      kind = Kind::String;
    } else {
      assert(false);
    }
    return wrap_<BuiltinType>(kind);
  }

  antlrcpp::Any
  visitClassType(MxParser::ClassTypeContext *ctx) override {
    return wrap_<ClassType>(ctx->Identifier()->getText());
  }

  antlrcpp::Any visitVarDecl(MxParser::VarDeclContext *ctx) override {
    std::string name = ctx->Identifier()->getText();
    std::shared_ptr<Type> type = visit_<Type>(ctx->type());
    std::shared_ptr<Expr> expr = visit_<Expr>(ctx->expr());
    return wrap_<VarDecl>(std::move(name), std::move(type), std::move(expr));
  }

  antlrcpp::Any visitClassDecl(MxParser::ClassDeclContext *ctx) override {
    std::string name = ctx->Identifier()->getText();
    return wrap_<ClassDecl>(std::move(name), collect_<Decl>(ctx->memberDecl()));
  }

  antlrcpp::Any visitFunctionDecl(MxParser::FunctionDeclContext *ctx) override {
    std::string name = ctx->Identifier()->getText();
    std::shared_ptr<Type> retType;
    if (!ctx->VOID())
      retType = visit_<Type>(ctx->type());
    std::vector<std::shared_ptr<VarDecl>> args;
    auto argDecls = ctx->parameterDecls();
    if (argDecls) {
      args = collect_<VarDecl>(argDecls->parameterDecl());
    }
    std::shared_ptr<CompoundStmt> body = visit_<CompoundStmt>(ctx->block());
    return wrap_<FunctionDecl>(std::move(name), std::move(retType),
                               std::move(args), std::move(body));
  }

  antlrcpp::Any
  visitParameterDecls(MxParser::ParameterDeclsContext *ctx) override {
    assert(false);
  }

  antlrcpp::Any
  visitParameterDecl(MxParser::ParameterDeclContext *ctx) override {
    std::string name = ctx->Identifier()->getText();
    std::shared_ptr<Type> type = visit_<Type>(ctx->type());
    return wrap_<VarDecl>(std::move(name), std::move(type));
  }

  virtual antlrcpp::Any
  visitParameterList(MxParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any
  visitMemberDecl(MxParser::MemberDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any
  visitClassConstructor(MxParser::ClassConstructorContext *ctx) override {
    std::string name = ctx->Identifier()->getText();
    std::vector<std::shared_ptr<VarDecl>> args;
    std::shared_ptr<CompoundStmt> stmt = visit_<CompoundStmt>(ctx->block());
    return wrap_<FunctionDecl>(std::move(name), nullptr, std::move(args),
                               std::move(stmt));
  }

  antlrcpp::Any visitBlock(MxParser::BlockContext *ctx) override {
    return wrap_<CompoundStmt>(collect_<Stmt>(ctx->statement()));
  }

  virtual antlrcpp::Any
  visitBlockStat(MxParser::BlockStatContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitVarDeclStat(MxParser::VarDeclStatContext *ctx) override {
    return wrap_<VarDeclStmt>(visit_<VarDecl>(ctx->varDecl()));
  }

  antlrcpp::Any visitExprStat(MxParser::ExprStatContext *ctx) override {
    return wrap_<ExprStmt>(visit_<Expr>(ctx->expr()));
  }

  antlrcpp::Any visitIfStat(MxParser::IfStatContext *ctx) override {
    assert(false);
  }

  virtual antlrcpp::Any visitLoopStat(MxParser::LoopStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitJumpStat(MxParser::JumpStatContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any visitBlankStat(MxParser::BlankStatContext *ctx) override {
    return wrap_<EmptyStmt>();
  }

  antlrcpp::Any visitIfStatement(MxParser::IfStatementContext *ctx) override {
    std::shared_ptr<Expr> cond = visit_<Expr>(ctx->expr());
    std::shared_ptr<Stmt> then = visit_<Stmt>(ctx->statement()[0]);
    std::shared_ptr<Stmt> otherwise = ctx->statement().size() == 1
                                          ? nullptr
                                          : visit_<Stmt>(ctx->statement()[1]);
    return wrap_<IfStmt>(std::move(cond), std::move(then),
                         std::move(otherwise));
  }

  antlrcpp::Any visitWhileStat(MxParser::WhileStatContext *ctx) override {
    std::shared_ptr<Expr> cond = visit_<Expr>(ctx->expr());
    std::shared_ptr<Stmt> body = visit_<Stmt>(ctx->statement());
    return wrap_<WhileStmt>(std::move(cond), std::move(body));
  }

  antlrcpp::Any visitForStat(MxParser::ForStatContext *ctx) override {
    std::shared_ptr<Expr> init = visit_<Expr>(ctx->init);
    std::shared_ptr<Expr> cond = visit_<Expr>(ctx->cond);
    std::shared_ptr<Expr> step = visit_<Expr>(ctx->step);
    std::shared_ptr<Stmt> body = visit_<Stmt>(ctx->statement());
    return wrap_<ForStmt>(std::move(init), std::move(cond), std::move(step),
                          std::move(body));
  }

  antlrcpp::Any visitReturnStat(MxParser::ReturnStatContext *ctx) override {
    std::shared_ptr<Expr> value = visit_<Expr>(ctx->expr());
    return wrap_<ReturnStmt>(std::move(value));
  }

  antlrcpp::Any visitBreakStat(MxParser::BreakStatContext *ctx) override {
    return wrap_<BreakStmt>();
  }

  antlrcpp::Any visitContinueStat(MxParser::ContinueStatContext *ctx) override {
    return wrap_<ContinueStmt>();
  }

  antlrcpp::Any
  visitErrorCreator(MxParser::ErrorCreatorContext *ctx) override {
    throw CompileError("Array dimension specification in new expression should be left aligned");
  }

  antlrcpp::Any
  visitArrayCreator(MxParser::ArrayCreatorContext *ctx) override {
    std::string name = ctx->nonArrayType()->getText();
    std::size_t dim = ctx->LBRACK().size();
    std::vector<std::shared_ptr<Expr>> shape = collect_<Expr>(ctx->expr());
    return wrap_<NewExpr>(std::move(name), dim, std::move(shape));
  }

  antlrcpp::Any
  visitNonArrayCreator(MxParser::NonArrayCreatorContext *ctx) override {
    return wrap_<NewExpr>(ctx->nonArrayType()->getText(), 0);

  }

  antlrcpp::Any
  visitConstant(MxParser::ConstantContext *ctx) override {
    std::string literal = ctx->constantType->getText();
    switch (ctx->constantType->getType()) {
    case MxParser::IntConstant: return wrap_<LiteralInt>(std::stoi(literal));
    case MxParser::BoolConstant: return wrap_<LiteralBool>(literal == "true");
    case MxParser::StringConstant: return wrap_<LiteralString>(literal);
    case MxParser::NONE: return wrap_<LiteralNull>();
    default: assert(false);
    }
  }

  antlrcpp::Any
  visitIdExpr(MxParser::IdExprContext *ctx) override {
    return wrap_<VarExpr>(ctx->Identifier()->getText());
  }

  antlrcpp::Any
  visitMemberAccess(MxParser::MemberAccessContext *ctx) override {
    std::shared_ptr<Expr> instance = visit_<Expr>(ctx->expr());
    std::string field = ctx->Identifier()->getText();
    return wrap_<MemberAccess>(std::move(instance), std::move(field));
  }

  antlrcpp::Any visitBinaryExpr(MxParser::BinaryExprContext *ctx) override {
    using Op = BinaryExpr::Op;
    Op op;
    switch (ctx->op->getType()) {
    case MxParser::MUL: op = Op::Mul; break;
    case MxParser::DIV: op = Op::Div; break;
    case MxParser::MOD: op = Op::Mod; break;
    case MxParser::ADD: op = Op::Add; break;
    case MxParser::SUB: op = Op::Sub; break;
    case MxParser::LSFT: op = Op::Lsft; break;
    case MxParser::RSFT: op = Op::Rsft; break;
    case MxParser::LT: op = Op::Lt; break;
    case MxParser::GT: op = Op::Gt; break;
    case MxParser::LE: op = Op::Le; break;
    case MxParser::GE: op = Op::Ge; break;
    case MxParser::EQ: op = Op::Eq; break;
    case MxParser::NEQ: op = Op::Neq; break;
    case MxParser::BITAND: op = Op::BitAnd; break;
    case MxParser::BITOR: op = Op::BitOr; break;
    case MxParser::BITXOR: op = Op::BitXor; break;
    case MxParser::AND: op = Op::And; break;
    case MxParser::OR: op = Op::Or; break;
    case MxParser::ASSIGN: op = Op::Assign; break;
    default: assert(false);
    }
    std::shared_ptr<Expr> lhs = visit_<Expr>(ctx->left);
    std::shared_ptr<Expr> rhs = visit_<Expr>(ctx->right);
    return wrap_<BinaryExpr>(op, std::move(lhs), std::move(rhs));
  }

  virtual antlrcpp::Any
  visitConstantExpr(MxParser::ConstantExprContext *ctx) override {
    return visitChildren(ctx);
  }

  antlrcpp::Any
  visitFunctionCall(MxParser::FunctionCallContext *ctx) override {
    std::shared_ptr<Expr> callee = visit_<Expr>(ctx->expr());
    std::vector<std::shared_ptr<Expr>> args;
    auto argList = ctx->parameterList();
    if (argList) {
      args = collect_<Expr>(argList->expr());
    }
    return wrap_<FunctionCall>(std::move(callee), std::move(args));
  }

  antlrcpp::Any
  visitParenExpr(MxParser::ParenExprContext *ctx) override {
    return visit(ctx->expr());
  }

  antlrcpp::Any
  visitUnaryExpr(MxParser::UnaryExprContext *ctx) override {
    using Op = UnaryExpr::Op;
    Op op;
    switch (ctx->op->getType()) {
    case MxParser::INC: op = Op::PreInc; break;
    case MxParser::DEC: op = Op::PreDec; break;
    case MxParser::ADD: op = Op::Pos; break;
    case MxParser::SUB: op = Op::Neg; break;
    case MxParser::NOT: op = Op::Not; break;
    case MxParser::BITNOT: op = Op::BitNot; break;
    default: assert(false);
    }
    std::shared_ptr<Expr> operand = visit_<Expr>(ctx->expr());
    return wrap_<UnaryExpr>(op, std::move(operand));
  }

  antlrcpp::Any
  visitThisExpr(MxParser::ThisExprContext *ctx) override {
    return wrap_<VarExpr>("this");
  }

  antlrcpp::Any
  visitNewCreator(MxParser::NewCreatorContext *ctx) override {
    return visit(ctx->creator());
  }

  antlrcpp::Any
  visitSuffixIncDec(MxParser::SuffixIncDecContext *ctx) override {
    using Op = UnaryExpr::Op;
    Op op;
    switch (ctx->op->getType()) {
    case MxParser::INC: op = Op::PostInc; break;
    case MxParser::DEC: op = Op::PostDec; break;
    default: assert(false);
    }
    std::shared_ptr<Expr> operand = visit_<Expr>(ctx->expr());
    return wrap_<UnaryExpr>(op, std::move(operand));
  }

  antlrcpp::Any
  visitSubscriptAccess(MxParser::SubscriptAccessContext *ctx) override {
    std::shared_ptr<Expr> array = visit_<Expr>(ctx->array);
    std::shared_ptr<Expr> index = visit_<Expr>(ctx->subscript);
    return wrap_<ArrayAccess>(std::move(array), std::move(index));
  }
};

} // namespace ast
} // namespace menhir

#endif // MENHIR_AST_BUILDER_H
