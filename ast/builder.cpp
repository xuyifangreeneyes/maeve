#include "builder.h"
#include "../utils/error.h"

namespace maeve {
namespace ast {

antlrcpp::Any Builder::visitProgram(MxParser::ProgramContext *ctx) {
  return wrap_<AstRoot>(collect_<Decl>(ctx->declaration()));
}

antlrcpp::Any Builder::visitType(MxParser::TypeContext *ctx) {
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
    return antlrcpp::Any(std::static_pointer_cast<AstNode>(baseType));
  }
  return wrap_<ArrayType>(std::move(baseType), dim);
}

antlrcpp::Any Builder::visitPrimitiveType(MxParser::PrimitiveTypeContext *ctx) {
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

antlrcpp::Any Builder::visitClassType(MxParser::ClassTypeContext *ctx) {
  return wrap_<ClassType>(ctx->Identifier()->getText());
}

antlrcpp::Any Builder::visitVarDecl(MxParser::VarDeclContext *ctx) {
  std::string name = ctx->Identifier()->getText();
  std::shared_ptr<Type> type = visit_<Type>(ctx->type());
  std::shared_ptr<Expr> expr = visit_<Expr>(ctx->expr());
  return wrap_<VarDecl>(std::move(name), std::move(type), std::move(expr));
}

antlrcpp::Any Builder::visitClassDecl(MxParser::ClassDeclContext *ctx) {
  std::string name = ctx->Identifier()->getText();
  return wrap_<ClassDecl>(std::move(name), collect_<Decl>(ctx->memberDecl()));
}

antlrcpp::Any Builder::visitFunctionDecl(MxParser::FunctionDeclContext *ctx) {
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

antlrcpp::Any Builder::visitParameterDecl(MxParser::ParameterDeclContext *ctx) {
  std::string name = ctx->Identifier()->getText();
  std::shared_ptr<Type> type = visit_<Type>(ctx->type());
  return wrap_<VarDecl>(std::move(name), std::move(type));
}

antlrcpp::Any
Builder::visitClassConstructor(MxParser::ClassConstructorContext *ctx) {
  std::string name = ctx->Identifier()->getText();
  std::vector<std::shared_ptr<VarDecl>> args;
  std::shared_ptr<CompoundStmt> stmt = visit_<CompoundStmt>(ctx->block());
  return wrap_<FunctionDecl>(std::move(name), nullptr, std::move(args),
                             std::move(stmt));
}

antlrcpp::Any Builder::visitBlock(MxParser::BlockContext *ctx) {
  return wrap_<CompoundStmt>(collect_<Stmt>(ctx->statement()));
}

antlrcpp::Any Builder::visitVarDeclStat(MxParser::VarDeclStatContext *ctx) {
  return wrap_<VarDeclStmt>(visit_<VarDecl>(ctx->varDecl()));
}

antlrcpp::Any Builder::visitExprStat(MxParser::ExprStatContext *ctx) {
  return wrap_<ExprStmt>(visit_<Expr>(ctx->expr()));
}

antlrcpp::Any Builder::visitBlankStat(MxParser::BlankStatContext *ctx) {
  return wrap_<EmptyStmt>();
}

antlrcpp::Any Builder::visitIfStatement(MxParser::IfStatementContext *ctx) {
  std::shared_ptr<Expr> cond = visit_<Expr>(ctx->expr());
  std::shared_ptr<Stmt> then = visit_<Stmt>(ctx->statement()[0]);
  std::shared_ptr<Stmt> otherwise = ctx->statement().size() == 1
                                        ? nullptr
                                        : visit_<Stmt>(ctx->statement()[1]);
  return wrap_<IfStmt>(std::move(cond), std::move(then), std::move(otherwise));
}

antlrcpp::Any Builder::visitWhileStat(MxParser::WhileStatContext *ctx) {
  std::shared_ptr<Expr> cond = visit_<Expr>(ctx->expr());
  std::shared_ptr<Stmt> body = visit_<Stmt>(ctx->statement());
  return wrap_<WhileStmt>(std::move(cond), std::move(body));
}

antlrcpp::Any Builder::visitForStat(MxParser::ForStatContext *ctx) {
  std::shared_ptr<Expr> init = visit_<Expr>(ctx->init);
  std::shared_ptr<Expr> cond = visit_<Expr>(ctx->cond);
  std::shared_ptr<Expr> step = visit_<Expr>(ctx->step);
  std::shared_ptr<Stmt> body = visit_<Stmt>(ctx->statement());
  return wrap_<ForStmt>(std::move(init), std::move(cond), std::move(step),
                        std::move(body));
}

antlrcpp::Any Builder::visitReturnStat(MxParser::ReturnStatContext *ctx) {
  std::shared_ptr<Expr> value = visit_<Expr>(ctx->expr());
  return wrap_<ReturnStmt>(std::move(value));
}

antlrcpp::Any Builder::visitBreakStat(MxParser::BreakStatContext *ctx) {
  return wrap_<BreakStmt>();
}

antlrcpp::Any Builder::visitContinueStat(MxParser::ContinueStatContext *ctx) {
  return wrap_<ContinueStmt>();
}

antlrcpp::Any Builder::visitErrorCreator(MxParser::ErrorCreatorContext *ctx) {
  throw CompileError(
      "Array dimension specification in new expression should be left aligned");
}

antlrcpp::Any Builder::visitArrayCreator(MxParser::ArrayCreatorContext *ctx) {
  std::string name = ctx->nonArrayType()->getText();
  std::size_t dim = ctx->LBRACK().size();
  std::vector<std::shared_ptr<Expr>> shape = collect_<Expr>(ctx->expr());
  return wrap_<NewExpr>(std::move(name), dim, std::move(shape));
}

antlrcpp::Any
Builder::visitNonArrayCreator(MxParser::NonArrayCreatorContext *ctx) {
  return wrap_<NewExpr>(ctx->nonArrayType()->getText(), 0);
}

antlrcpp::Any Builder::visitConstant(MxParser::ConstantContext *ctx) {
  std::string literal = ctx->constantType->getText();
  switch (ctx->constantType->getType()) {
  case MxParser::IntConstant:
    return wrap_<LiteralInt>(std::stoi(literal));
  case MxParser::BoolConstant:
    return wrap_<LiteralBool>(literal == "true");
  case MxParser::StringConstant:
    return wrap_<LiteralString>(literal);
  case MxParser::NONE:
    return wrap_<LiteralNull>();
  default:
    assert(false);
  }
}

antlrcpp::Any Builder::visitIdExpr(MxParser::IdExprContext *ctx) {
  return wrap_<VarExpr>(ctx->Identifier()->getText());
}

antlrcpp::Any Builder::visitMemberAccess(MxParser::MemberAccessContext *ctx) {
  std::shared_ptr<Expr> instance = visit_<Expr>(ctx->expr());
  std::string field = ctx->Identifier()->getText();
  return wrap_<MemberAccess>(std::move(instance), std::move(field));
}

antlrcpp::Any Builder::visitBinaryExpr(MxParser::BinaryExprContext *ctx) {
  using Op = BinaryExpr::Op;
  Op op;
  switch (ctx->op->getType()) {
  case MxParser::MUL:
    op = Op::Mul;
    break;
  case MxParser::DIV:
    op = Op::Div;
    break;
  case MxParser::MOD:
    op = Op::Mod;
    break;
  case MxParser::ADD:
    op = Op::Add;
    break;
  case MxParser::SUB:
    op = Op::Sub;
    break;
  case MxParser::LSFT:
    op = Op::Lsft;
    break;
  case MxParser::RSFT:
    op = Op::Rsft;
    break;
  case MxParser::LT:
    op = Op::Lt;
    break;
  case MxParser::GT:
    op = Op::Gt;
    break;
  case MxParser::LE:
    op = Op::Le;
    break;
  case MxParser::GE:
    op = Op::Ge;
    break;
  case MxParser::EQ:
    op = Op::Eq;
    break;
  case MxParser::NEQ:
    op = Op::Neq;
    break;
  case MxParser::BITAND:
    op = Op::BitAnd;
    break;
  case MxParser::BITOR:
    op = Op::BitOr;
    break;
  case MxParser::BITXOR:
    op = Op::BitXor;
    break;
  case MxParser::AND:
    op = Op::And;
    break;
  case MxParser::OR:
    op = Op::Or;
    break;
  case MxParser::ASSIGN:
    op = Op::Assign;
    break;
  default:
    assert(false);
  }
  std::shared_ptr<Expr> lhs = visit_<Expr>(ctx->left);
  std::shared_ptr<Expr> rhs = visit_<Expr>(ctx->right);
  return wrap_<BinaryExpr>(op, std::move(lhs), std::move(rhs));
}

antlrcpp::Any Builder::visitFunctionCall(MxParser::FunctionCallContext *ctx) {
  std::shared_ptr<Expr> callee = visit_<Expr>(ctx->expr());
  std::vector<std::shared_ptr<Expr>> args;
  auto argList = ctx->parameterList();
  if (argList) {
    args = collect_<Expr>(argList->expr());
  }
  return wrap_<FunctionCall>(std::move(callee), std::move(args));
}

antlrcpp::Any Builder::visitParenExpr(MxParser::ParenExprContext *ctx) {
  return visit(ctx->expr());
}

antlrcpp::Any Builder::visitUnaryExpr(MxParser::UnaryExprContext *ctx) {
  using Op = UnaryExpr::Op;
  Op op;
  switch (ctx->op->getType()) {
  case MxParser::INC:
    op = Op::PreInc;
    break;
  case MxParser::DEC:
    op = Op::PreDec;
    break;
  case MxParser::ADD:
    op = Op::Pos;
    break;
  case MxParser::SUB:
    op = Op::Neg;
    break;
  case MxParser::NOT:
    op = Op::Not;
    break;
  case MxParser::BITNOT:
    op = Op::BitNot;
    break;
  default:
    assert(false);
  }
  std::shared_ptr<Expr> operand = visit_<Expr>(ctx->expr());
  return wrap_<UnaryExpr>(op, std::move(operand));
}

antlrcpp::Any Builder::visitThisExpr(MxParser::ThisExprContext *ctx) {
  return wrap_<VarExpr>("this");
}

antlrcpp::Any Builder::visitNewCreator(MxParser::NewCreatorContext *ctx) {
  return visit(ctx->creator());
}

antlrcpp::Any Builder::visitSuffixIncDec(MxParser::SuffixIncDecContext *ctx) {
  using Op = UnaryExpr::Op;
  Op op;
  switch (ctx->op->getType()) {
  case MxParser::INC:
    op = Op::PostInc;
    break;
  case MxParser::DEC:
    op = Op::PostDec;
    break;
  default:
    assert(false);
  }
  std::shared_ptr<Expr> operand = visit_<Expr>(ctx->expr());
  return wrap_<UnaryExpr>(op, std::move(operand));
}

antlrcpp::Any
Builder::visitSubscriptAccess(MxParser::SubscriptAccessContext *ctx) {
  std::shared_ptr<Expr> array = visit_<Expr>(ctx->array);
  std::shared_ptr<Expr> index = visit_<Expr>(ctx->subscript);
  return wrap_<ArrayAccess>(std::move(array), std::move(index));
}

} // namespace ast
} // namespace maeve