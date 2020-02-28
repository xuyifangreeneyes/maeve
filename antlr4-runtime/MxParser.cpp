
// Generated from Mx.g4 by ANTLR 4.7.2


#include "MxVisitor.h"

#include "MxParser.h"


using namespace antlrcpp;
using namespace antlr4;

MxParser::MxParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

MxParser::~MxParser() {
  delete _interpreter;
}

std::string MxParser::getGrammarFileName() const {
  return "Mx.g4";
}

const std::vector<std::string>& MxParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& MxParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

MxParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::ProgramContext::EOF() {
  return getToken(MxParser::EOF, 0);
}

std::vector<MxParser::DeclarationContext *> MxParser::ProgramContext::declaration() {
  return getRuleContexts<MxParser::DeclarationContext>();
}

MxParser::DeclarationContext* MxParser::ProgramContext::declaration(size_t i) {
  return getRuleContext<MxParser::DeclarationContext>(i);
}


size_t MxParser::ProgramContext::getRuleIndex() const {
  return MxParser::RuleProgram;
}


antlrcpp::Any MxParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ProgramContext* MxParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, MxParser::RuleProgram);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(47);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << MxParser::BOOL)
      | (1ULL << MxParser::INT)
      | (1ULL << MxParser::STRING)
      | (1ULL << MxParser::VOID)
      | (1ULL << MxParser::CLASS)
      | (1ULL << MxParser::Identifier))) != 0)) {
      setState(44);
      declaration();
      setState(49);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(50);
    match(MxParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

MxParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MxParser::DeclarationContext::getRuleIndex() const {
  return MxParser::RuleDeclaration;
}

void MxParser::DeclarationContext::copyFrom(DeclarationContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FuncContext ------------------------------------------------------------------

MxParser::FunctionDeclContext* MxParser::FuncContext::functionDecl() {
  return getRuleContext<MxParser::FunctionDeclContext>(0);
}

MxParser::FuncContext::FuncContext(DeclarationContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::FuncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitFunc(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarContext ------------------------------------------------------------------

MxParser::VarDeclContext* MxParser::VarContext::varDecl() {
  return getRuleContext<MxParser::VarDeclContext>(0);
}

MxParser::VarContext::VarContext(DeclarationContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::VarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitVar(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassContext ------------------------------------------------------------------

MxParser::ClassDeclContext* MxParser::ClassContext::classDecl() {
  return getRuleContext<MxParser::ClassDeclContext>(0);
}

MxParser::ClassContext::ClassContext(DeclarationContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::ClassContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitClass(this);
  else
    return visitor->visitChildren(this);
}
MxParser::DeclarationContext* MxParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 2, MxParser::RuleDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(55);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<DeclarationContext *>(_tracker.createInstance<MxParser::ClassContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(52);
      classDecl();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<DeclarationContext *>(_tracker.createInstance<MxParser::FuncContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(53);
      functionDecl();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<DeclarationContext *>(_tracker.createInstance<MxParser::VarContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(54);
      varDecl();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

MxParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MxParser::NonArrayTypeContext* MxParser::TypeContext::nonArrayType() {
  return getRuleContext<MxParser::NonArrayTypeContext>(0);
}

std::vector<tree::TerminalNode *> MxParser::TypeContext::LBRACK() {
  return getTokens(MxParser::LBRACK);
}

tree::TerminalNode* MxParser::TypeContext::LBRACK(size_t i) {
  return getToken(MxParser::LBRACK, i);
}

std::vector<tree::TerminalNode *> MxParser::TypeContext::RBRACK() {
  return getTokens(MxParser::RBRACK);
}

tree::TerminalNode* MxParser::TypeContext::RBRACK(size_t i) {
  return getToken(MxParser::RBRACK, i);
}


size_t MxParser::TypeContext::getRuleIndex() const {
  return MxParser::RuleType;
}


antlrcpp::Any MxParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

MxParser::TypeContext* MxParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 4, MxParser::RuleType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(57);
    nonArrayType();
    setState(62);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MxParser::LBRACK) {
      setState(58);
      match(MxParser::LBRACK);
      setState(59);
      match(MxParser::RBRACK);
      setState(64);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NonArrayTypeContext ------------------------------------------------------------------

MxParser::NonArrayTypeContext::NonArrayTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MxParser::PrimitiveTypeContext* MxParser::NonArrayTypeContext::primitiveType() {
  return getRuleContext<MxParser::PrimitiveTypeContext>(0);
}

MxParser::ClassTypeContext* MxParser::NonArrayTypeContext::classType() {
  return getRuleContext<MxParser::ClassTypeContext>(0);
}


size_t MxParser::NonArrayTypeContext::getRuleIndex() const {
  return MxParser::RuleNonArrayType;
}


antlrcpp::Any MxParser::NonArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitNonArrayType(this);
  else
    return visitor->visitChildren(this);
}

MxParser::NonArrayTypeContext* MxParser::nonArrayType() {
  NonArrayTypeContext *_localctx = _tracker.createInstance<NonArrayTypeContext>(_ctx, getState());
  enterRule(_localctx, 6, MxParser::RuleNonArrayType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(67);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MxParser::BOOL:
      case MxParser::INT:
      case MxParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(65);
        primitiveType();
        break;
      }

      case MxParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(66);
        classType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimitiveTypeContext ------------------------------------------------------------------

MxParser::PrimitiveTypeContext::PrimitiveTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::PrimitiveTypeContext::BOOL() {
  return getToken(MxParser::BOOL, 0);
}

tree::TerminalNode* MxParser::PrimitiveTypeContext::INT() {
  return getToken(MxParser::INT, 0);
}

tree::TerminalNode* MxParser::PrimitiveTypeContext::STRING() {
  return getToken(MxParser::STRING, 0);
}


size_t MxParser::PrimitiveTypeContext::getRuleIndex() const {
  return MxParser::RulePrimitiveType;
}


antlrcpp::Any MxParser::PrimitiveTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitPrimitiveType(this);
  else
    return visitor->visitChildren(this);
}

MxParser::PrimitiveTypeContext* MxParser::primitiveType() {
  PrimitiveTypeContext *_localctx = _tracker.createInstance<PrimitiveTypeContext>(_ctx, getState());
  enterRule(_localctx, 8, MxParser::RulePrimitiveType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << MxParser::BOOL)
      | (1ULL << MxParser::INT)
      | (1ULL << MxParser::STRING))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassTypeContext ------------------------------------------------------------------

MxParser::ClassTypeContext::ClassTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::ClassTypeContext::Identifier() {
  return getToken(MxParser::Identifier, 0);
}


size_t MxParser::ClassTypeContext::getRuleIndex() const {
  return MxParser::RuleClassType;
}


antlrcpp::Any MxParser::ClassTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitClassType(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ClassTypeContext* MxParser::classType() {
  ClassTypeContext *_localctx = _tracker.createInstance<ClassTypeContext>(_ctx, getState());
  enterRule(_localctx, 10, MxParser::RuleClassType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    match(MxParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

MxParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MxParser::TypeContext* MxParser::VarDeclContext::type() {
  return getRuleContext<MxParser::TypeContext>(0);
}

tree::TerminalNode* MxParser::VarDeclContext::Identifier() {
  return getToken(MxParser::Identifier, 0);
}

tree::TerminalNode* MxParser::VarDeclContext::SEMI() {
  return getToken(MxParser::SEMI, 0);
}

tree::TerminalNode* MxParser::VarDeclContext::ASSIGN() {
  return getToken(MxParser::ASSIGN, 0);
}

MxParser::ExprContext* MxParser::VarDeclContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}


size_t MxParser::VarDeclContext::getRuleIndex() const {
  return MxParser::RuleVarDecl;
}


antlrcpp::Any MxParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

MxParser::VarDeclContext* MxParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 12, MxParser::RuleVarDecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(73);
    type();
    setState(74);
    match(MxParser::Identifier);
    setState(77);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MxParser::ASSIGN) {
      setState(75);
      match(MxParser::ASSIGN);
      setState(76);
      expr(0);
    }
    setState(79);
    match(MxParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDeclContext ------------------------------------------------------------------

MxParser::ClassDeclContext::ClassDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::ClassDeclContext::CLASS() {
  return getToken(MxParser::CLASS, 0);
}

tree::TerminalNode* MxParser::ClassDeclContext::Identifier() {
  return getToken(MxParser::Identifier, 0);
}

tree::TerminalNode* MxParser::ClassDeclContext::LBRACE() {
  return getToken(MxParser::LBRACE, 0);
}

tree::TerminalNode* MxParser::ClassDeclContext::RBRACE() {
  return getToken(MxParser::RBRACE, 0);
}

std::vector<MxParser::MemberDeclContext *> MxParser::ClassDeclContext::memberDecl() {
  return getRuleContexts<MxParser::MemberDeclContext>();
}

MxParser::MemberDeclContext* MxParser::ClassDeclContext::memberDecl(size_t i) {
  return getRuleContext<MxParser::MemberDeclContext>(i);
}


size_t MxParser::ClassDeclContext::getRuleIndex() const {
  return MxParser::RuleClassDecl;
}


antlrcpp::Any MxParser::ClassDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitClassDecl(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ClassDeclContext* MxParser::classDecl() {
  ClassDeclContext *_localctx = _tracker.createInstance<ClassDeclContext>(_ctx, getState());
  enterRule(_localctx, 14, MxParser::RuleClassDecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    match(MxParser::CLASS);
    setState(82);
    match(MxParser::Identifier);
    setState(83);
    match(MxParser::LBRACE);
    setState(87);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << MxParser::BOOL)
      | (1ULL << MxParser::INT)
      | (1ULL << MxParser::STRING)
      | (1ULL << MxParser::VOID)
      | (1ULL << MxParser::Identifier))) != 0)) {
      setState(84);
      memberDecl();
      setState(89);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(90);
    match(MxParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclContext ------------------------------------------------------------------

MxParser::FunctionDeclContext::FunctionDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MxParser::TypeContext* MxParser::FunctionDeclContext::type() {
  return getRuleContext<MxParser::TypeContext>(0);
}

tree::TerminalNode* MxParser::FunctionDeclContext::Identifier() {
  return getToken(MxParser::Identifier, 0);
}

tree::TerminalNode* MxParser::FunctionDeclContext::LPAREN() {
  return getToken(MxParser::LPAREN, 0);
}

tree::TerminalNode* MxParser::FunctionDeclContext::RPAREN() {
  return getToken(MxParser::RPAREN, 0);
}

MxParser::BlockContext* MxParser::FunctionDeclContext::block() {
  return getRuleContext<MxParser::BlockContext>(0);
}

MxParser::ParameterDeclsContext* MxParser::FunctionDeclContext::parameterDecls() {
  return getRuleContext<MxParser::ParameterDeclsContext>(0);
}

tree::TerminalNode* MxParser::FunctionDeclContext::VOID() {
  return getToken(MxParser::VOID, 0);
}


size_t MxParser::FunctionDeclContext::getRuleIndex() const {
  return MxParser::RuleFunctionDecl;
}


antlrcpp::Any MxParser::FunctionDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitFunctionDecl(this);
  else
    return visitor->visitChildren(this);
}

MxParser::FunctionDeclContext* MxParser::functionDecl() {
  FunctionDeclContext *_localctx = _tracker.createInstance<FunctionDeclContext>(_ctx, getState());
  enterRule(_localctx, 16, MxParser::RuleFunctionDecl);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(109);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MxParser::BOOL:
      case MxParser::INT:
      case MxParser::STRING:
      case MxParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(92);
        type();
        setState(93);
        match(MxParser::Identifier);
        setState(94);
        match(MxParser::LPAREN);
        setState(96);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << MxParser::BOOL)
          | (1ULL << MxParser::INT)
          | (1ULL << MxParser::STRING)
          | (1ULL << MxParser::Identifier))) != 0)) {
          setState(95);
          parameterDecls();
        }
        setState(98);
        match(MxParser::RPAREN);
        setState(99);
        block();
        break;
      }

      case MxParser::VOID: {
        enterOuterAlt(_localctx, 2);
        setState(101);
        match(MxParser::VOID);
        setState(102);
        match(MxParser::Identifier);
        setState(103);
        match(MxParser::LPAREN);
        setState(105);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << MxParser::BOOL)
          | (1ULL << MxParser::INT)
          | (1ULL << MxParser::STRING)
          | (1ULL << MxParser::Identifier))) != 0)) {
          setState(104);
          parameterDecls();
        }
        setState(107);
        match(MxParser::RPAREN);
        setState(108);
        block();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterDeclsContext ------------------------------------------------------------------

MxParser::ParameterDeclsContext::ParameterDeclsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MxParser::ParameterDeclContext *> MxParser::ParameterDeclsContext::parameterDecl() {
  return getRuleContexts<MxParser::ParameterDeclContext>();
}

MxParser::ParameterDeclContext* MxParser::ParameterDeclsContext::parameterDecl(size_t i) {
  return getRuleContext<MxParser::ParameterDeclContext>(i);
}

std::vector<tree::TerminalNode *> MxParser::ParameterDeclsContext::COMMA() {
  return getTokens(MxParser::COMMA);
}

tree::TerminalNode* MxParser::ParameterDeclsContext::COMMA(size_t i) {
  return getToken(MxParser::COMMA, i);
}


size_t MxParser::ParameterDeclsContext::getRuleIndex() const {
  return MxParser::RuleParameterDecls;
}


antlrcpp::Any MxParser::ParameterDeclsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitParameterDecls(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ParameterDeclsContext* MxParser::parameterDecls() {
  ParameterDeclsContext *_localctx = _tracker.createInstance<ParameterDeclsContext>(_ctx, getState());
  enterRule(_localctx, 18, MxParser::RuleParameterDecls);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    parameterDecl();
    setState(116);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MxParser::COMMA) {
      setState(112);
      match(MxParser::COMMA);
      setState(113);
      parameterDecl();
      setState(118);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterDeclContext ------------------------------------------------------------------

MxParser::ParameterDeclContext::ParameterDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MxParser::TypeContext* MxParser::ParameterDeclContext::type() {
  return getRuleContext<MxParser::TypeContext>(0);
}

tree::TerminalNode* MxParser::ParameterDeclContext::Identifier() {
  return getToken(MxParser::Identifier, 0);
}


size_t MxParser::ParameterDeclContext::getRuleIndex() const {
  return MxParser::RuleParameterDecl;
}


antlrcpp::Any MxParser::ParameterDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitParameterDecl(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ParameterDeclContext* MxParser::parameterDecl() {
  ParameterDeclContext *_localctx = _tracker.createInstance<ParameterDeclContext>(_ctx, getState());
  enterRule(_localctx, 20, MxParser::RuleParameterDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    type();
    setState(120);
    match(MxParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

MxParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MxParser::ExprContext *> MxParser::ParameterListContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::ParameterListContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MxParser::ParameterListContext::COMMA() {
  return getTokens(MxParser::COMMA);
}

tree::TerminalNode* MxParser::ParameterListContext::COMMA(size_t i) {
  return getToken(MxParser::COMMA, i);
}


size_t MxParser::ParameterListContext::getRuleIndex() const {
  return MxParser::RuleParameterList;
}


antlrcpp::Any MxParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ParameterListContext* MxParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 22, MxParser::RuleParameterList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    expr(0);
    setState(127);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MxParser::COMMA) {
      setState(123);
      match(MxParser::COMMA);
      setState(124);
      expr(0);
      setState(129);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MemberDeclContext ------------------------------------------------------------------

MxParser::MemberDeclContext::MemberDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MxParser::VarDeclContext* MxParser::MemberDeclContext::varDecl() {
  return getRuleContext<MxParser::VarDeclContext>(0);
}

MxParser::FunctionDeclContext* MxParser::MemberDeclContext::functionDecl() {
  return getRuleContext<MxParser::FunctionDeclContext>(0);
}

MxParser::ClassConstructorContext* MxParser::MemberDeclContext::classConstructor() {
  return getRuleContext<MxParser::ClassConstructorContext>(0);
}


size_t MxParser::MemberDeclContext::getRuleIndex() const {
  return MxParser::RuleMemberDecl;
}


antlrcpp::Any MxParser::MemberDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitMemberDecl(this);
  else
    return visitor->visitChildren(this);
}

MxParser::MemberDeclContext* MxParser::memberDecl() {
  MemberDeclContext *_localctx = _tracker.createInstance<MemberDeclContext>(_ctx, getState());
  enterRule(_localctx, 24, MxParser::RuleMemberDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(133);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(130);
      varDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(131);
      functionDecl();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(132);
      classConstructor();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassConstructorContext ------------------------------------------------------------------

MxParser::ClassConstructorContext::ClassConstructorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::ClassConstructorContext::Identifier() {
  return getToken(MxParser::Identifier, 0);
}

tree::TerminalNode* MxParser::ClassConstructorContext::LPAREN() {
  return getToken(MxParser::LPAREN, 0);
}

tree::TerminalNode* MxParser::ClassConstructorContext::RPAREN() {
  return getToken(MxParser::RPAREN, 0);
}

MxParser::BlockContext* MxParser::ClassConstructorContext::block() {
  return getRuleContext<MxParser::BlockContext>(0);
}


size_t MxParser::ClassConstructorContext::getRuleIndex() const {
  return MxParser::RuleClassConstructor;
}


antlrcpp::Any MxParser::ClassConstructorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitClassConstructor(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ClassConstructorContext* MxParser::classConstructor() {
  ClassConstructorContext *_localctx = _tracker.createInstance<ClassConstructorContext>(_ctx, getState());
  enterRule(_localctx, 26, MxParser::RuleClassConstructor);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(135);
    match(MxParser::Identifier);
    setState(136);
    match(MxParser::LPAREN);
    setState(137);
    match(MxParser::RPAREN);
    setState(138);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

MxParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::BlockContext::LBRACE() {
  return getToken(MxParser::LBRACE, 0);
}

tree::TerminalNode* MxParser::BlockContext::RBRACE() {
  return getToken(MxParser::RBRACE, 0);
}

std::vector<MxParser::StatementContext *> MxParser::BlockContext::statement() {
  return getRuleContexts<MxParser::StatementContext>();
}

MxParser::StatementContext* MxParser::BlockContext::statement(size_t i) {
  return getRuleContext<MxParser::StatementContext>(i);
}


size_t MxParser::BlockContext::getRuleIndex() const {
  return MxParser::RuleBlock;
}


antlrcpp::Any MxParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

MxParser::BlockContext* MxParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 28, MxParser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(140);
    match(MxParser::LBRACE);
    setState(144);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << MxParser::BOOL)
      | (1ULL << MxParser::INT)
      | (1ULL << MxParser::STRING)
      | (1ULL << MxParser::NONE)
      | (1ULL << MxParser::IF)
      | (1ULL << MxParser::FOR)
      | (1ULL << MxParser::WHILE)
      | (1ULL << MxParser::BREAK)
      | (1ULL << MxParser::CONTINUE)
      | (1ULL << MxParser::RETURN)
      | (1ULL << MxParser::NEW)
      | (1ULL << MxParser::THIS)
      | (1ULL << MxParser::LPAREN)
      | (1ULL << MxParser::LBRACE)
      | (1ULL << MxParser::SEMI)
      | (1ULL << MxParser::ADD)
      | (1ULL << MxParser::SUB)
      | (1ULL << MxParser::NOT)
      | (1ULL << MxParser::BITNOT)
      | (1ULL << MxParser::INC)
      | (1ULL << MxParser::DEC)
      | (1ULL << MxParser::BoolConstant)
      | (1ULL << MxParser::IntConstant)
      | (1ULL << MxParser::StringConstant)
      | (1ULL << MxParser::Identifier))) != 0)) {
      setState(141);
      statement();
      setState(146);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(147);
    match(MxParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

MxParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MxParser::StatementContext::getRuleIndex() const {
  return MxParser::RuleStatement;
}

void MxParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IfStatContext ------------------------------------------------------------------

MxParser::IfStatementContext* MxParser::IfStatContext::ifStatement() {
  return getRuleContext<MxParser::IfStatementContext>(0);
}

MxParser::IfStatContext::IfStatContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::IfStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitIfStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStatContext ------------------------------------------------------------------

MxParser::BlockContext* MxParser::BlockStatContext::block() {
  return getRuleContext<MxParser::BlockContext>(0);
}

MxParser::BlockStatContext::BlockStatContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::BlockStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitBlockStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarDeclStatContext ------------------------------------------------------------------

MxParser::VarDeclContext* MxParser::VarDeclStatContext::varDecl() {
  return getRuleContext<MxParser::VarDeclContext>(0);
}

MxParser::VarDeclStatContext::VarDeclStatContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::VarDeclStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitVarDeclStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- JumpStatContext ------------------------------------------------------------------

MxParser::JumpStatementContext* MxParser::JumpStatContext::jumpStatement() {
  return getRuleContext<MxParser::JumpStatementContext>(0);
}

MxParser::JumpStatContext::JumpStatContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::JumpStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitJumpStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprStatContext ------------------------------------------------------------------

MxParser::ExprContext* MxParser::ExprStatContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::ExprStatContext::SEMI() {
  return getToken(MxParser::SEMI, 0);
}

MxParser::ExprStatContext::ExprStatContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::ExprStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitExprStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LoopStatContext ------------------------------------------------------------------

MxParser::LoopStatementContext* MxParser::LoopStatContext::loopStatement() {
  return getRuleContext<MxParser::LoopStatementContext>(0);
}

MxParser::LoopStatContext::LoopStatContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::LoopStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitLoopStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlankStatContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::BlankStatContext::SEMI() {
  return getToken(MxParser::SEMI, 0);
}

MxParser::BlankStatContext::BlankStatContext(StatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::BlankStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitBlankStat(this);
  else
    return visitor->visitChildren(this);
}
MxParser::StatementContext* MxParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 30, MxParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(158);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<MxParser::BlockStatContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(149);
      block();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<MxParser::VarDeclStatContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(150);
      varDecl();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<MxParser::ExprStatContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(151);
      expr(0);
      setState(152);
      match(MxParser::SEMI);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<MxParser::IfStatContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(154);
      ifStatement();
      break;
    }

    case 5: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<MxParser::LoopStatContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(155);
      loopStatement();
      break;
    }

    case 6: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<MxParser::JumpStatContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(156);
      jumpStatement();
      break;
    }

    case 7: {
      _localctx = dynamic_cast<StatementContext *>(_tracker.createInstance<MxParser::BlankStatContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(157);
      match(MxParser::SEMI);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

MxParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::IfStatementContext::IF() {
  return getToken(MxParser::IF, 0);
}

tree::TerminalNode* MxParser::IfStatementContext::LPAREN() {
  return getToken(MxParser::LPAREN, 0);
}

MxParser::ExprContext* MxParser::IfStatementContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::IfStatementContext::RPAREN() {
  return getToken(MxParser::RPAREN, 0);
}

std::vector<MxParser::StatementContext *> MxParser::IfStatementContext::statement() {
  return getRuleContexts<MxParser::StatementContext>();
}

MxParser::StatementContext* MxParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<MxParser::StatementContext>(i);
}

tree::TerminalNode* MxParser::IfStatementContext::ELSE() {
  return getToken(MxParser::ELSE, 0);
}


size_t MxParser::IfStatementContext::getRuleIndex() const {
  return MxParser::RuleIfStatement;
}


antlrcpp::Any MxParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

MxParser::IfStatementContext* MxParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 32, MxParser::RuleIfStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    match(MxParser::IF);
    setState(161);
    match(MxParser::LPAREN);
    setState(162);
    expr(0);
    setState(163);
    match(MxParser::RPAREN);
    setState(164);
    statement();
    setState(167);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      setState(165);
      match(MxParser::ELSE);
      setState(166);
      statement();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoopStatementContext ------------------------------------------------------------------

MxParser::LoopStatementContext::LoopStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MxParser::LoopStatementContext::getRuleIndex() const {
  return MxParser::RuleLoopStatement;
}

void MxParser::LoopStatementContext::copyFrom(LoopStatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ForStatContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::ForStatContext::FOR() {
  return getToken(MxParser::FOR, 0);
}

tree::TerminalNode* MxParser::ForStatContext::LPAREN() {
  return getToken(MxParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> MxParser::ForStatContext::SEMI() {
  return getTokens(MxParser::SEMI);
}

tree::TerminalNode* MxParser::ForStatContext::SEMI(size_t i) {
  return getToken(MxParser::SEMI, i);
}

tree::TerminalNode* MxParser::ForStatContext::RPAREN() {
  return getToken(MxParser::RPAREN, 0);
}

MxParser::StatementContext* MxParser::ForStatContext::statement() {
  return getRuleContext<MxParser::StatementContext>(0);
}

std::vector<MxParser::ExprContext *> MxParser::ForStatContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::ForStatContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

MxParser::ForStatContext::ForStatContext(LoopStatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::ForStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitForStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileStatContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::WhileStatContext::WHILE() {
  return getToken(MxParser::WHILE, 0);
}

tree::TerminalNode* MxParser::WhileStatContext::LPAREN() {
  return getToken(MxParser::LPAREN, 0);
}

MxParser::ExprContext* MxParser::WhileStatContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::WhileStatContext::RPAREN() {
  return getToken(MxParser::RPAREN, 0);
}

MxParser::StatementContext* MxParser::WhileStatContext::statement() {
  return getRuleContext<MxParser::StatementContext>(0);
}

MxParser::WhileStatContext::WhileStatContext(LoopStatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::WhileStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitWhileStat(this);
  else
    return visitor->visitChildren(this);
}
MxParser::LoopStatementContext* MxParser::loopStatement() {
  LoopStatementContext *_localctx = _tracker.createInstance<LoopStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, MxParser::RuleLoopStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(190);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MxParser::WHILE: {
        _localctx = dynamic_cast<LoopStatementContext *>(_tracker.createInstance<MxParser::WhileStatContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(169);
        match(MxParser::WHILE);
        setState(170);
        match(MxParser::LPAREN);
        setState(171);
        expr(0);
        setState(172);
        match(MxParser::RPAREN);
        setState(173);
        statement();
        break;
      }

      case MxParser::FOR: {
        _localctx = dynamic_cast<LoopStatementContext *>(_tracker.createInstance<MxParser::ForStatContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(175);
        match(MxParser::FOR);
        setState(176);
        match(MxParser::LPAREN);
        setState(178);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << MxParser::NONE)
          | (1ULL << MxParser::NEW)
          | (1ULL << MxParser::THIS)
          | (1ULL << MxParser::LPAREN)
          | (1ULL << MxParser::ADD)
          | (1ULL << MxParser::SUB)
          | (1ULL << MxParser::NOT)
          | (1ULL << MxParser::BITNOT)
          | (1ULL << MxParser::INC)
          | (1ULL << MxParser::DEC)
          | (1ULL << MxParser::BoolConstant)
          | (1ULL << MxParser::IntConstant)
          | (1ULL << MxParser::StringConstant)
          | (1ULL << MxParser::Identifier))) != 0)) {
          setState(177);
          dynamic_cast<ForStatContext *>(_localctx)->init = expr(0);
        }
        setState(180);
        match(MxParser::SEMI);
        setState(182);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << MxParser::NONE)
          | (1ULL << MxParser::NEW)
          | (1ULL << MxParser::THIS)
          | (1ULL << MxParser::LPAREN)
          | (1ULL << MxParser::ADD)
          | (1ULL << MxParser::SUB)
          | (1ULL << MxParser::NOT)
          | (1ULL << MxParser::BITNOT)
          | (1ULL << MxParser::INC)
          | (1ULL << MxParser::DEC)
          | (1ULL << MxParser::BoolConstant)
          | (1ULL << MxParser::IntConstant)
          | (1ULL << MxParser::StringConstant)
          | (1ULL << MxParser::Identifier))) != 0)) {
          setState(181);
          dynamic_cast<ForStatContext *>(_localctx)->cond = expr(0);
        }
        setState(184);
        match(MxParser::SEMI);
        setState(186);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << MxParser::NONE)
          | (1ULL << MxParser::NEW)
          | (1ULL << MxParser::THIS)
          | (1ULL << MxParser::LPAREN)
          | (1ULL << MxParser::ADD)
          | (1ULL << MxParser::SUB)
          | (1ULL << MxParser::NOT)
          | (1ULL << MxParser::BITNOT)
          | (1ULL << MxParser::INC)
          | (1ULL << MxParser::DEC)
          | (1ULL << MxParser::BoolConstant)
          | (1ULL << MxParser::IntConstant)
          | (1ULL << MxParser::StringConstant)
          | (1ULL << MxParser::Identifier))) != 0)) {
          setState(185);
          dynamic_cast<ForStatContext *>(_localctx)->step = expr(0);
        }
        setState(188);
        match(MxParser::RPAREN);
        setState(189);
        statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JumpStatementContext ------------------------------------------------------------------

MxParser::JumpStatementContext::JumpStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MxParser::JumpStatementContext::getRuleIndex() const {
  return MxParser::RuleJumpStatement;
}

void MxParser::JumpStatementContext::copyFrom(JumpStatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ReturnStatContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::ReturnStatContext::RETURN() {
  return getToken(MxParser::RETURN, 0);
}

tree::TerminalNode* MxParser::ReturnStatContext::SEMI() {
  return getToken(MxParser::SEMI, 0);
}

MxParser::ExprContext* MxParser::ReturnStatContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

MxParser::ReturnStatContext::ReturnStatContext(JumpStatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::ReturnStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitReturnStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinueStatContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::ContinueStatContext::CONTINUE() {
  return getToken(MxParser::CONTINUE, 0);
}

tree::TerminalNode* MxParser::ContinueStatContext::SEMI() {
  return getToken(MxParser::SEMI, 0);
}

MxParser::ContinueStatContext::ContinueStatContext(JumpStatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::ContinueStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitContinueStat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStatContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::BreakStatContext::BREAK() {
  return getToken(MxParser::BREAK, 0);
}

tree::TerminalNode* MxParser::BreakStatContext::SEMI() {
  return getToken(MxParser::SEMI, 0);
}

MxParser::BreakStatContext::BreakStatContext(JumpStatementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::BreakStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitBreakStat(this);
  else
    return visitor->visitChildren(this);
}
MxParser::JumpStatementContext* MxParser::jumpStatement() {
  JumpStatementContext *_localctx = _tracker.createInstance<JumpStatementContext>(_ctx, getState());
  enterRule(_localctx, 36, MxParser::RuleJumpStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(201);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MxParser::RETURN: {
        _localctx = dynamic_cast<JumpStatementContext *>(_tracker.createInstance<MxParser::ReturnStatContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(192);
        match(MxParser::RETURN);
        setState(194);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << MxParser::NONE)
          | (1ULL << MxParser::NEW)
          | (1ULL << MxParser::THIS)
          | (1ULL << MxParser::LPAREN)
          | (1ULL << MxParser::ADD)
          | (1ULL << MxParser::SUB)
          | (1ULL << MxParser::NOT)
          | (1ULL << MxParser::BITNOT)
          | (1ULL << MxParser::INC)
          | (1ULL << MxParser::DEC)
          | (1ULL << MxParser::BoolConstant)
          | (1ULL << MxParser::IntConstant)
          | (1ULL << MxParser::StringConstant)
          | (1ULL << MxParser::Identifier))) != 0)) {
          setState(193);
          expr(0);
        }
        setState(196);
        match(MxParser::SEMI);
        break;
      }

      case MxParser::BREAK: {
        _localctx = dynamic_cast<JumpStatementContext *>(_tracker.createInstance<MxParser::BreakStatContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(197);
        match(MxParser::BREAK);
        setState(198);
        match(MxParser::SEMI);
        break;
      }

      case MxParser::CONTINUE: {
        _localctx = dynamic_cast<JumpStatementContext *>(_tracker.createInstance<MxParser::ContinueStatContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(199);
        match(MxParser::CONTINUE);
        setState(200);
        match(MxParser::SEMI);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreatorContext ------------------------------------------------------------------

MxParser::CreatorContext::CreatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MxParser::CreatorContext::getRuleIndex() const {
  return MxParser::RuleCreator;
}

void MxParser::CreatorContext::copyFrom(CreatorContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NonArrayCreatorContext ------------------------------------------------------------------

MxParser::NonArrayTypeContext* MxParser::NonArrayCreatorContext::nonArrayType() {
  return getRuleContext<MxParser::NonArrayTypeContext>(0);
}

tree::TerminalNode* MxParser::NonArrayCreatorContext::LPAREN() {
  return getToken(MxParser::LPAREN, 0);
}

tree::TerminalNode* MxParser::NonArrayCreatorContext::RPAREN() {
  return getToken(MxParser::RPAREN, 0);
}

MxParser::NonArrayCreatorContext::NonArrayCreatorContext(CreatorContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::NonArrayCreatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitNonArrayCreator(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayCreatorContext ------------------------------------------------------------------

MxParser::NonArrayTypeContext* MxParser::ArrayCreatorContext::nonArrayType() {
  return getRuleContext<MxParser::NonArrayTypeContext>(0);
}

std::vector<tree::TerminalNode *> MxParser::ArrayCreatorContext::LBRACK() {
  return getTokens(MxParser::LBRACK);
}

tree::TerminalNode* MxParser::ArrayCreatorContext::LBRACK(size_t i) {
  return getToken(MxParser::LBRACK, i);
}

std::vector<MxParser::ExprContext *> MxParser::ArrayCreatorContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::ArrayCreatorContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MxParser::ArrayCreatorContext::RBRACK() {
  return getTokens(MxParser::RBRACK);
}

tree::TerminalNode* MxParser::ArrayCreatorContext::RBRACK(size_t i) {
  return getToken(MxParser::RBRACK, i);
}

MxParser::ArrayCreatorContext::ArrayCreatorContext(CreatorContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::ArrayCreatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitArrayCreator(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ErrorCreatorContext ------------------------------------------------------------------

MxParser::NonArrayTypeContext* MxParser::ErrorCreatorContext::nonArrayType() {
  return getRuleContext<MxParser::NonArrayTypeContext>(0);
}

std::vector<tree::TerminalNode *> MxParser::ErrorCreatorContext::LBRACK() {
  return getTokens(MxParser::LBRACK);
}

tree::TerminalNode* MxParser::ErrorCreatorContext::LBRACK(size_t i) {
  return getToken(MxParser::LBRACK, i);
}

std::vector<MxParser::ExprContext *> MxParser::ErrorCreatorContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::ErrorCreatorContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MxParser::ErrorCreatorContext::RBRACK() {
  return getTokens(MxParser::RBRACK);
}

tree::TerminalNode* MxParser::ErrorCreatorContext::RBRACK(size_t i) {
  return getToken(MxParser::RBRACK, i);
}

MxParser::ErrorCreatorContext::ErrorCreatorContext(CreatorContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::ErrorCreatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitErrorCreator(this);
  else
    return visitor->visitChildren(this);
}
MxParser::CreatorContext* MxParser::creator() {
  CreatorContext *_localctx = _tracker.createInstance<CreatorContext>(_ctx, getState());
  enterRule(_localctx, 38, MxParser::RuleCreator);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(247);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<CreatorContext *>(_tracker.createInstance<MxParser::ErrorCreatorContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(203);
      nonArrayType();
      setState(208); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(204);
                match(MxParser::LBRACK);
                setState(205);
                expr(0);
                setState(206);
                match(MxParser::RBRACK);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(210); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(214); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(212);
                match(MxParser::LBRACK);
                setState(213);
                match(MxParser::RBRACK);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(216); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(222); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(218);
                match(MxParser::LBRACK);
                setState(219);
                expr(0);
                setState(220);
                match(MxParser::RBRACK);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(224); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<CreatorContext *>(_tracker.createInstance<MxParser::ArrayCreatorContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(226);
      nonArrayType();
      setState(231); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(227);
                match(MxParser::LBRACK);
                setState(228);
                expr(0);
                setState(229);
                match(MxParser::RBRACK);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(233); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(239);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(235);
          match(MxParser::LBRACK);
          setState(236);
          match(MxParser::RBRACK); 
        }
        setState(241);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
      }
      break;
    }

    case 3: {
      _localctx = dynamic_cast<CreatorContext *>(_tracker.createInstance<MxParser::NonArrayCreatorContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(242);
      nonArrayType();
      setState(245);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
      case 1: {
        setState(243);
        match(MxParser::LPAREN);
        setState(244);
        match(MxParser::RPAREN);
        break;
      }

      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantContext ------------------------------------------------------------------

MxParser::ConstantContext::ConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::ConstantContext::BoolConstant() {
  return getToken(MxParser::BoolConstant, 0);
}

tree::TerminalNode* MxParser::ConstantContext::IntConstant() {
  return getToken(MxParser::IntConstant, 0);
}

tree::TerminalNode* MxParser::ConstantContext::StringConstant() {
  return getToken(MxParser::StringConstant, 0);
}

tree::TerminalNode* MxParser::ConstantContext::NONE() {
  return getToken(MxParser::NONE, 0);
}


size_t MxParser::ConstantContext::getRuleIndex() const {
  return MxParser::RuleConstant;
}


antlrcpp::Any MxParser::ConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitConstant(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ConstantContext* MxParser::constant() {
  ConstantContext *_localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
  enterRule(_localctx, 40, MxParser::RuleConstant);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(253);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MxParser::BoolConstant: {
        enterOuterAlt(_localctx, 1);
        setState(249);
        dynamic_cast<ConstantContext *>(_localctx)->constantType = match(MxParser::BoolConstant);
        break;
      }

      case MxParser::IntConstant: {
        enterOuterAlt(_localctx, 2);
        setState(250);
        dynamic_cast<ConstantContext *>(_localctx)->constantType = match(MxParser::IntConstant);
        break;
      }

      case MxParser::StringConstant: {
        enterOuterAlt(_localctx, 3);
        setState(251);
        dynamic_cast<ConstantContext *>(_localctx)->constantType = match(MxParser::StringConstant);
        break;
      }

      case MxParser::NONE: {
        enterOuterAlt(_localctx, 4);
        setState(252);
        dynamic_cast<ConstantContext *>(_localctx)->constantType = match(MxParser::NONE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

MxParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MxParser::ExprContext::getRuleIndex() const {
  return MxParser::RuleExpr;
}

void MxParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IdExprContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::IdExprContext::Identifier() {
  return getToken(MxParser::Identifier, 0);
}

MxParser::IdExprContext::IdExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::IdExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitIdExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemberAccessContext ------------------------------------------------------------------

MxParser::ExprContext* MxParser::MemberAccessContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::MemberAccessContext::DOT() {
  return getToken(MxParser::DOT, 0);
}

tree::TerminalNode* MxParser::MemberAccessContext::Identifier() {
  return getToken(MxParser::Identifier, 0);
}

MxParser::MemberAccessContext::MemberAccessContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::MemberAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitMemberAccess(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryExprContext ------------------------------------------------------------------

std::vector<MxParser::ExprContext *> MxParser::BinaryExprContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::BinaryExprContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

tree::TerminalNode* MxParser::BinaryExprContext::MUL() {
  return getToken(MxParser::MUL, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::DIV() {
  return getToken(MxParser::DIV, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::MOD() {
  return getToken(MxParser::MOD, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::ADD() {
  return getToken(MxParser::ADD, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::SUB() {
  return getToken(MxParser::SUB, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::LSFT() {
  return getToken(MxParser::LSFT, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::RSFT() {
  return getToken(MxParser::RSFT, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::LT() {
  return getToken(MxParser::LT, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::GT() {
  return getToken(MxParser::GT, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::LE() {
  return getToken(MxParser::LE, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::GE() {
  return getToken(MxParser::GE, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::EQ() {
  return getToken(MxParser::EQ, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::NEQ() {
  return getToken(MxParser::NEQ, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::BITAND() {
  return getToken(MxParser::BITAND, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::BITXOR() {
  return getToken(MxParser::BITXOR, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::BITOR() {
  return getToken(MxParser::BITOR, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::AND() {
  return getToken(MxParser::AND, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::OR() {
  return getToken(MxParser::OR, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::ASSIGN() {
  return getToken(MxParser::ASSIGN, 0);
}

MxParser::BinaryExprContext::BinaryExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::BinaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitBinaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstantExprContext ------------------------------------------------------------------

MxParser::ConstantContext* MxParser::ConstantExprContext::constant() {
  return getRuleContext<MxParser::ConstantContext>(0);
}

MxParser::ConstantExprContext::ConstantExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::ConstantExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitConstantExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallContext ------------------------------------------------------------------

MxParser::ExprContext* MxParser::FunctionCallContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::FunctionCallContext::LPAREN() {
  return getToken(MxParser::LPAREN, 0);
}

tree::TerminalNode* MxParser::FunctionCallContext::RPAREN() {
  return getToken(MxParser::RPAREN, 0);
}

MxParser::ParameterListContext* MxParser::FunctionCallContext::parameterList() {
  return getRuleContext<MxParser::ParameterListContext>(0);
}

MxParser::FunctionCallContext::FunctionCallContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::ParenExprContext::LPAREN() {
  return getToken(MxParser::LPAREN, 0);
}

MxParser::ExprContext* MxParser::ParenExprContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::ParenExprContext::RPAREN() {
  return getToken(MxParser::RPAREN, 0);
}

MxParser::ParenExprContext::ParenExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprContext ------------------------------------------------------------------

MxParser::ExprContext* MxParser::UnaryExprContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::UnaryExprContext::INC() {
  return getToken(MxParser::INC, 0);
}

tree::TerminalNode* MxParser::UnaryExprContext::DEC() {
  return getToken(MxParser::DEC, 0);
}

tree::TerminalNode* MxParser::UnaryExprContext::ADD() {
  return getToken(MxParser::ADD, 0);
}

tree::TerminalNode* MxParser::UnaryExprContext::SUB() {
  return getToken(MxParser::SUB, 0);
}

tree::TerminalNode* MxParser::UnaryExprContext::NOT() {
  return getToken(MxParser::NOT, 0);
}

tree::TerminalNode* MxParser::UnaryExprContext::BITNOT() {
  return getToken(MxParser::BITNOT, 0);
}

MxParser::UnaryExprContext::UnaryExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ThisExprContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::ThisExprContext::THIS() {
  return getToken(MxParser::THIS, 0);
}

MxParser::ThisExprContext::ThisExprContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::ThisExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitThisExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NewCreatorContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::NewCreatorContext::NEW() {
  return getToken(MxParser::NEW, 0);
}

MxParser::CreatorContext* MxParser::NewCreatorContext::creator() {
  return getRuleContext<MxParser::CreatorContext>(0);
}

MxParser::NewCreatorContext::NewCreatorContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::NewCreatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitNewCreator(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SuffixIncDecContext ------------------------------------------------------------------

MxParser::ExprContext* MxParser::SuffixIncDecContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::SuffixIncDecContext::INC() {
  return getToken(MxParser::INC, 0);
}

tree::TerminalNode* MxParser::SuffixIncDecContext::DEC() {
  return getToken(MxParser::DEC, 0);
}

MxParser::SuffixIncDecContext::SuffixIncDecContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::SuffixIncDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitSuffixIncDec(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SubscriptAccessContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::SubscriptAccessContext::LBRACK() {
  return getToken(MxParser::LBRACK, 0);
}

tree::TerminalNode* MxParser::SubscriptAccessContext::RBRACK() {
  return getToken(MxParser::RBRACK, 0);
}

std::vector<MxParser::ExprContext *> MxParser::SubscriptAccessContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::SubscriptAccessContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

MxParser::SubscriptAccessContext::SubscriptAccessContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any MxParser::SubscriptAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitSubscriptAccess(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ExprContext* MxParser::expr() {
   return expr(0);
}

MxParser::ExprContext* MxParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MxParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  MxParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, MxParser::RuleExpr, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(273);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MxParser::INC:
      case MxParser::DEC: {
        _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(256);
        dynamic_cast<UnaryExprContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == MxParser::INC

        || _la == MxParser::DEC)) {
          dynamic_cast<UnaryExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(257);
        expr(21);
        break;
      }

      case MxParser::ADD:
      case MxParser::SUB: {
        _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(258);
        dynamic_cast<UnaryExprContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == MxParser::ADD

        || _la == MxParser::SUB)) {
          dynamic_cast<UnaryExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(259);
        expr(20);
        break;
      }

      case MxParser::NOT: {
        _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(260);
        dynamic_cast<UnaryExprContext *>(_localctx)->op = match(MxParser::NOT);
        setState(261);
        expr(19);
        break;
      }

      case MxParser::BITNOT: {
        _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(262);
        dynamic_cast<UnaryExprContext *>(_localctx)->op = match(MxParser::BITNOT);
        setState(263);
        expr(18);
        break;
      }

      case MxParser::NEW: {
        _localctx = _tracker.createInstance<NewCreatorContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(264);
        match(MxParser::NEW);
        setState(265);
        creator();
        break;
      }

      case MxParser::NONE:
      case MxParser::BoolConstant:
      case MxParser::IntConstant:
      case MxParser::StringConstant: {
        _localctx = _tracker.createInstance<ConstantExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(266);
        constant();
        break;
      }

      case MxParser::Identifier: {
        _localctx = _tracker.createInstance<IdExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(267);
        match(MxParser::Identifier);
        break;
      }

      case MxParser::THIS: {
        _localctx = _tracker.createInstance<ThisExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(268);
        match(MxParser::THIS);
        break;
      }

      case MxParser::LPAREN: {
        _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(269);
        match(MxParser::LPAREN);
        setState(270);
        expr(0);
        setState(271);
        match(MxParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(329);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(327);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(275);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(276);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << MxParser::MUL)
            | (1ULL << MxParser::DIV)
            | (1ULL << MxParser::MOD))) != 0))) {
            dynamic_cast<BinaryExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(277);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(17);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(278);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(279);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == MxParser::ADD

          || _la == MxParser::SUB)) {
            dynamic_cast<BinaryExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(280);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(16);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(281);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(282);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == MxParser::LSFT

          || _la == MxParser::RSFT)) {
            dynamic_cast<BinaryExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(283);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(15);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(284);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(285);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == MxParser::LT

          || _la == MxParser::GT)) {
            dynamic_cast<BinaryExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(286);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(14);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(287);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(288);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == MxParser::GE

          || _la == MxParser::LE)) {
            dynamic_cast<BinaryExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(289);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(13);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(290);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(291);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == MxParser::EQ

          || _la == MxParser::NEQ)) {
            dynamic_cast<BinaryExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(292);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(12);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(293);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(294);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = match(MxParser::BITAND);
          setState(295);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(11);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(296);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(297);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = match(MxParser::BITXOR);
          setState(298);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(10);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(299);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(300);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = match(MxParser::BITOR);
          setState(301);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(9);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(302);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(303);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = match(MxParser::AND);
          setState(304);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(8);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(305);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(306);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = match(MxParser::OR);
          setState(307);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(308);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(309);
          dynamic_cast<BinaryExprContext *>(_localctx)->op = match(MxParser::ASSIGN);
          setState(310);
          dynamic_cast<BinaryExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<SuffixIncDecContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(311);

          if (!(precpred(_ctx, 25))) throw FailedPredicateException(this, "precpred(_ctx, 25)");
          setState(312);
          dynamic_cast<SuffixIncDecContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == MxParser::INC

          || _la == MxParser::DEC)) {
            dynamic_cast<SuffixIncDecContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<FunctionCallContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(313);

          if (!(precpred(_ctx, 24))) throw FailedPredicateException(this, "precpred(_ctx, 24)");
          setState(314);
          match(MxParser::LPAREN);
          setState(316);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << MxParser::NONE)
            | (1ULL << MxParser::NEW)
            | (1ULL << MxParser::THIS)
            | (1ULL << MxParser::LPAREN)
            | (1ULL << MxParser::ADD)
            | (1ULL << MxParser::SUB)
            | (1ULL << MxParser::NOT)
            | (1ULL << MxParser::BITNOT)
            | (1ULL << MxParser::INC)
            | (1ULL << MxParser::DEC)
            | (1ULL << MxParser::BoolConstant)
            | (1ULL << MxParser::IntConstant)
            | (1ULL << MxParser::StringConstant)
            | (1ULL << MxParser::Identifier))) != 0)) {
            setState(315);
            parameterList();
          }
          setState(318);
          match(MxParser::RPAREN);
          break;
        }

        case 15: {
          auto newContext = _tracker.createInstance<SubscriptAccessContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->array = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(319);

          if (!(precpred(_ctx, 23))) throw FailedPredicateException(this, "precpred(_ctx, 23)");
          setState(320);
          match(MxParser::LBRACK);
          setState(321);
          dynamic_cast<SubscriptAccessContext *>(_localctx)->subscript = expr(0);
          setState(322);
          match(MxParser::RBRACK);
          break;
        }

        case 16: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(324);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(325);
          match(MxParser::DOT);
          setState(326);
          match(MxParser::Identifier);
          break;
        }

        } 
      }
      setState(331);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool MxParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 21: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool MxParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 16);
    case 1: return precpred(_ctx, 15);
    case 2: return precpred(_ctx, 14);
    case 3: return precpred(_ctx, 13);
    case 4: return precpred(_ctx, 12);
    case 5: return precpred(_ctx, 11);
    case 6: return precpred(_ctx, 10);
    case 7: return precpred(_ctx, 9);
    case 8: return precpred(_ctx, 8);
    case 9: return precpred(_ctx, 7);
    case 10: return precpred(_ctx, 6);
    case 11: return precpred(_ctx, 5);
    case 12: return precpred(_ctx, 25);
    case 13: return precpred(_ctx, 24);
    case 14: return precpred(_ctx, 23);
    case 15: return precpred(_ctx, 22);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> MxParser::_decisionToDFA;
atn::PredictionContextCache MxParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN MxParser::_atn;
std::vector<uint16_t> MxParser::_serializedATN;

std::vector<std::string> MxParser::_ruleNames = {
  "program", "declaration", "type", "nonArrayType", "primitiveType", "classType", 
  "varDecl", "classDecl", "functionDecl", "parameterDecls", "parameterDecl", 
  "parameterList", "memberDecl", "classConstructor", "block", "statement", 
  "ifStatement", "loopStatement", "jumpStatement", "creator", "constant", 
  "expr"
};

std::vector<std::string> MxParser::_literalNames = {
  "", "'bool'", "'int'", "'string'", "'null'", "'void'", "'if'", "'else'", 
  "'for'", "'while'", "'break'", "'continue'", "'return'", "'new'", "'class'", 
  "'this'", "'('", "')'", "'{'", "'}'", "'['", "']'", "';'", "','", "'+'", 
  "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "'=='", "'!='", "'>='", "'<='", 
  "'&&'", "'!'", "'||'", "'<<'", "'>>'", "'~'", "'|'", "'^'", "'&'", "'='", 
  "'++'", "'--'", "'.'"
};

std::vector<std::string> MxParser::_symbolicNames = {
  "", "BOOL", "INT", "STRING", "NONE", "VOID", "IF", "ELSE", "FOR", "WHILE", 
  "BREAK", "CONTINUE", "RETURN", "NEW", "CLASS", "THIS", "LPAREN", "RPAREN", 
  "LBRACE", "RBRACE", "LBRACK", "RBRACK", "SEMI", "COMMA", "ADD", "SUB", 
  "MUL", "DIV", "MOD", "LT", "GT", "EQ", "NEQ", "GE", "LE", "AND", "NOT", 
  "OR", "LSFT", "RSFT", "BITNOT", "BITOR", "BITXOR", "BITAND", "ASSIGN", 
  "INC", "DEC", "DOT", "BoolConstant", "IntConstant", "StringConstant", 
  "Identifier", "LINE_COMMENT", "BLOCK_COMMENT", "WS"
};

dfa::Vocabulary MxParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> MxParser::_tokenNames;

MxParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x38, 0x14f, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x3, 0x2, 0x7, 
    0x2, 0x30, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x33, 0xb, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x3a, 0xa, 0x3, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x3f, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x42, 
    0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x46, 0xa, 0x5, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 
    0x8, 0x50, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x7, 0x9, 0x58, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x5b, 0xb, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 
    0x63, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x5, 0xa, 0x6c, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 
    0x70, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x75, 0xa, 0xb, 
    0xc, 0xb, 0xe, 0xb, 0x78, 0xb, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0x80, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 
    0x83, 0xb, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x88, 0xa, 0xe, 
    0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 
    0x7, 0x10, 0x91, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0x94, 0xb, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0xa1, 0xa, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x5, 0x12, 0xaa, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 
    0xb5, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xb9, 0xa, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x5, 0x13, 0xbd, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 
    0x13, 0xc1, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0xc5, 0xa, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0xcc, 
    0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x6, 
    0x15, 0xd3, 0xa, 0x15, 0xd, 0x15, 0xe, 0x15, 0xd4, 0x3, 0x15, 0x3, 0x15, 
    0x6, 0x15, 0xd9, 0xa, 0x15, 0xd, 0x15, 0xe, 0x15, 0xda, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x6, 0x15, 0xe1, 0xa, 0x15, 0xd, 0x15, 0xe, 
    0x15, 0xe2, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x6, 
    0x15, 0xea, 0xa, 0x15, 0xd, 0x15, 0xe, 0x15, 0xeb, 0x3, 0x15, 0x3, 0x15, 
    0x7, 0x15, 0xf0, 0xa, 0x15, 0xc, 0x15, 0xe, 0x15, 0xf3, 0xb, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0xf8, 0xa, 0x15, 0x5, 0x15, 0xfa, 
    0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0x100, 
    0xa, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 
    0x17, 0x114, 0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x13f, 
    0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x7, 0x17, 0x14a, 0xa, 0x17, 
    0xc, 0x17, 0xe, 0x17, 0x14d, 0xb, 0x17, 0x3, 0x17, 0x2, 0x3, 0x2c, 0x18, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 
    0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2, 0xa, 0x3, 
    0x2, 0x3, 0x5, 0x3, 0x2, 0x2f, 0x30, 0x3, 0x2, 0x1a, 0x1b, 0x3, 0x2, 
    0x1c, 0x1e, 0x3, 0x2, 0x28, 0x29, 0x3, 0x2, 0x1f, 0x20, 0x3, 0x2, 0x23, 
    0x24, 0x3, 0x2, 0x21, 0x22, 0x2, 0x179, 0x2, 0x31, 0x3, 0x2, 0x2, 0x2, 
    0x4, 0x39, 0x3, 0x2, 0x2, 0x2, 0x6, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x8, 0x45, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x47, 0x3, 0x2, 0x2, 0x2, 0xc, 0x49, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x10, 0x53, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x14, 0x71, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x79, 0x3, 0x2, 0x2, 0x2, 0x18, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x87, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x89, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x8e, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x22, 0xa2, 0x3, 
    0x2, 0x2, 0x2, 0x24, 0xc0, 0x3, 0x2, 0x2, 0x2, 0x26, 0xcb, 0x3, 0x2, 
    0x2, 0x2, 0x28, 0xf9, 0x3, 0x2, 0x2, 0x2, 0x2a, 0xff, 0x3, 0x2, 0x2, 
    0x2, 0x2c, 0x113, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x30, 0x5, 0x4, 0x3, 0x2, 
    0x2f, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x30, 0x33, 0x3, 0x2, 0x2, 0x2, 0x31, 
    0x2f, 0x3, 0x2, 0x2, 0x2, 0x31, 0x32, 0x3, 0x2, 0x2, 0x2, 0x32, 0x34, 
    0x3, 0x2, 0x2, 0x2, 0x33, 0x31, 0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x7, 
    0x2, 0x2, 0x3, 0x35, 0x3, 0x3, 0x2, 0x2, 0x2, 0x36, 0x3a, 0x5, 0x10, 
    0x9, 0x2, 0x37, 0x3a, 0x5, 0x12, 0xa, 0x2, 0x38, 0x3a, 0x5, 0xe, 0x8, 
    0x2, 0x39, 0x36, 0x3, 0x2, 0x2, 0x2, 0x39, 0x37, 0x3, 0x2, 0x2, 0x2, 
    0x39, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x5, 0x3, 0x2, 0x2, 0x2, 0x3b, 
    0x40, 0x5, 0x8, 0x5, 0x2, 0x3c, 0x3d, 0x7, 0x16, 0x2, 0x2, 0x3d, 0x3f, 
    0x7, 0x17, 0x2, 0x2, 0x3e, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x42, 0x3, 
    0x2, 0x2, 0x2, 0x40, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x3, 0x2, 
    0x2, 0x2, 0x41, 0x7, 0x3, 0x2, 0x2, 0x2, 0x42, 0x40, 0x3, 0x2, 0x2, 
    0x2, 0x43, 0x46, 0x5, 0xa, 0x6, 0x2, 0x44, 0x46, 0x5, 0xc, 0x7, 0x2, 
    0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 0x45, 0x44, 0x3, 0x2, 0x2, 0x2, 0x46, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x9, 0x2, 0x2, 0x2, 0x48, 0xb, 
    0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0x7, 0x35, 0x2, 0x2, 0x4a, 0xd, 0x3, 
    0x2, 0x2, 0x2, 0x4b, 0x4c, 0x5, 0x6, 0x4, 0x2, 0x4c, 0x4f, 0x7, 0x35, 
    0x2, 0x2, 0x4d, 0x4e, 0x7, 0x2e, 0x2, 0x2, 0x4e, 0x50, 0x5, 0x2c, 0x17, 
    0x2, 0x4f, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x3, 0x2, 0x2, 0x2, 
    0x50, 0x51, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x7, 0x18, 0x2, 0x2, 0x52, 
    0xf, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x7, 0x10, 0x2, 0x2, 0x54, 0x55, 
    0x7, 0x35, 0x2, 0x2, 0x55, 0x59, 0x7, 0x14, 0x2, 0x2, 0x56, 0x58, 0x5, 
    0x1a, 0xe, 0x2, 0x57, 0x56, 0x3, 0x2, 0x2, 0x2, 0x58, 0x5b, 0x3, 0x2, 
    0x2, 0x2, 0x59, 0x57, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x3, 0x2, 0x2, 
    0x2, 0x5a, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x59, 0x3, 0x2, 0x2, 0x2, 
    0x5c, 0x5d, 0x7, 0x15, 0x2, 0x2, 0x5d, 0x11, 0x3, 0x2, 0x2, 0x2, 0x5e, 
    0x5f, 0x5, 0x6, 0x4, 0x2, 0x5f, 0x60, 0x7, 0x35, 0x2, 0x2, 0x60, 0x62, 
    0x7, 0x12, 0x2, 0x2, 0x61, 0x63, 0x5, 0x14, 0xb, 0x2, 0x62, 0x61, 0x3, 
    0x2, 0x2, 0x2, 0x62, 0x63, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 
    0x2, 0x2, 0x64, 0x65, 0x7, 0x13, 0x2, 0x2, 0x65, 0x66, 0x5, 0x1e, 0x10, 
    0x2, 0x66, 0x70, 0x3, 0x2, 0x2, 0x2, 0x67, 0x68, 0x7, 0x7, 0x2, 0x2, 
    0x68, 0x69, 0x7, 0x35, 0x2, 0x2, 0x69, 0x6b, 0x7, 0x12, 0x2, 0x2, 0x6a, 
    0x6c, 0x5, 0x14, 0xb, 0x2, 0x6b, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 
    0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x7, 
    0x13, 0x2, 0x2, 0x6e, 0x70, 0x5, 0x1e, 0x10, 0x2, 0x6f, 0x5e, 0x3, 0x2, 
    0x2, 0x2, 0x6f, 0x67, 0x3, 0x2, 0x2, 0x2, 0x70, 0x13, 0x3, 0x2, 0x2, 
    0x2, 0x71, 0x76, 0x5, 0x16, 0xc, 0x2, 0x72, 0x73, 0x7, 0x19, 0x2, 0x2, 
    0x73, 0x75, 0x5, 0x16, 0xc, 0x2, 0x74, 0x72, 0x3, 0x2, 0x2, 0x2, 0x75, 
    0x78, 0x3, 0x2, 0x2, 0x2, 0x76, 0x74, 0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 
    0x3, 0x2, 0x2, 0x2, 0x77, 0x15, 0x3, 0x2, 0x2, 0x2, 0x78, 0x76, 0x3, 
    0x2, 0x2, 0x2, 0x79, 0x7a, 0x5, 0x6, 0x4, 0x2, 0x7a, 0x7b, 0x7, 0x35, 
    0x2, 0x2, 0x7b, 0x17, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x81, 0x5, 0x2c, 0x17, 
    0x2, 0x7d, 0x7e, 0x7, 0x19, 0x2, 0x2, 0x7e, 0x80, 0x5, 0x2c, 0x17, 0x2, 
    0x7f, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x80, 0x83, 0x3, 0x2, 0x2, 0x2, 0x81, 
    0x7f, 0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 0x3, 0x2, 0x2, 0x2, 0x82, 0x19, 
    0x3, 0x2, 0x2, 0x2, 0x83, 0x81, 0x3, 0x2, 0x2, 0x2, 0x84, 0x88, 0x5, 
    0xe, 0x8, 0x2, 0x85, 0x88, 0x5, 0x12, 0xa, 0x2, 0x86, 0x88, 0x5, 0x1c, 
    0xf, 0x2, 0x87, 0x84, 0x3, 0x2, 0x2, 0x2, 0x87, 0x85, 0x3, 0x2, 0x2, 
    0x2, 0x87, 0x86, 0x3, 0x2, 0x2, 0x2, 0x88, 0x1b, 0x3, 0x2, 0x2, 0x2, 
    0x89, 0x8a, 0x7, 0x35, 0x2, 0x2, 0x8a, 0x8b, 0x7, 0x12, 0x2, 0x2, 0x8b, 
    0x8c, 0x7, 0x13, 0x2, 0x2, 0x8c, 0x8d, 0x5, 0x1e, 0x10, 0x2, 0x8d, 0x1d, 
    0x3, 0x2, 0x2, 0x2, 0x8e, 0x92, 0x7, 0x14, 0x2, 0x2, 0x8f, 0x91, 0x5, 
    0x20, 0x11, 0x2, 0x90, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x91, 0x94, 0x3, 0x2, 
    0x2, 0x2, 0x92, 0x90, 0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 0x3, 0x2, 0x2, 
    0x2, 0x93, 0x95, 0x3, 0x2, 0x2, 0x2, 0x94, 0x92, 0x3, 0x2, 0x2, 0x2, 
    0x95, 0x96, 0x7, 0x15, 0x2, 0x2, 0x96, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x97, 
    0xa1, 0x5, 0x1e, 0x10, 0x2, 0x98, 0xa1, 0x5, 0xe, 0x8, 0x2, 0x99, 0x9a, 
    0x5, 0x2c, 0x17, 0x2, 0x9a, 0x9b, 0x7, 0x18, 0x2, 0x2, 0x9b, 0xa1, 0x3, 
    0x2, 0x2, 0x2, 0x9c, 0xa1, 0x5, 0x22, 0x12, 0x2, 0x9d, 0xa1, 0x5, 0x24, 
    0x13, 0x2, 0x9e, 0xa1, 0x5, 0x26, 0x14, 0x2, 0x9f, 0xa1, 0x7, 0x18, 
    0x2, 0x2, 0xa0, 0x97, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x98, 0x3, 0x2, 0x2, 
    0x2, 0xa0, 0x99, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x9c, 0x3, 0x2, 0x2, 0x2, 
    0xa0, 0x9d, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa0, 
    0x9f, 0x3, 0x2, 0x2, 0x2, 0xa1, 0x21, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 
    0x7, 0x8, 0x2, 0x2, 0xa3, 0xa4, 0x7, 0x12, 0x2, 0x2, 0xa4, 0xa5, 0x5, 
    0x2c, 0x17, 0x2, 0xa5, 0xa6, 0x7, 0x13, 0x2, 0x2, 0xa6, 0xa9, 0x5, 0x20, 
    0x11, 0x2, 0xa7, 0xa8, 0x7, 0x9, 0x2, 0x2, 0xa8, 0xaa, 0x5, 0x20, 0x11, 
    0x2, 0xa9, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xaa, 0x3, 0x2, 0x2, 0x2, 
    0xaa, 0x23, 0x3, 0x2, 0x2, 0x2, 0xab, 0xac, 0x7, 0xb, 0x2, 0x2, 0xac, 
    0xad, 0x7, 0x12, 0x2, 0x2, 0xad, 0xae, 0x5, 0x2c, 0x17, 0x2, 0xae, 0xaf, 
    0x7, 0x13, 0x2, 0x2, 0xaf, 0xb0, 0x5, 0x20, 0x11, 0x2, 0xb0, 0xc1, 0x3, 
    0x2, 0x2, 0x2, 0xb1, 0xb2, 0x7, 0xa, 0x2, 0x2, 0xb2, 0xb4, 0x7, 0x12, 
    0x2, 0x2, 0xb3, 0xb5, 0x5, 0x2c, 0x17, 0x2, 0xb4, 0xb3, 0x3, 0x2, 0x2, 
    0x2, 0xb4, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb6, 0x3, 0x2, 0x2, 0x2, 
    0xb6, 0xb8, 0x7, 0x18, 0x2, 0x2, 0xb7, 0xb9, 0x5, 0x2c, 0x17, 0x2, 0xb8, 
    0xb7, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xba, 
    0x3, 0x2, 0x2, 0x2, 0xba, 0xbc, 0x7, 0x18, 0x2, 0x2, 0xbb, 0xbd, 0x5, 
    0x2c, 0x17, 0x2, 0xbc, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x3, 0x2, 
    0x2, 0x2, 0xbd, 0xbe, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 0x7, 0x13, 0x2, 
    0x2, 0xbf, 0xc1, 0x5, 0x20, 0x11, 0x2, 0xc0, 0xab, 0x3, 0x2, 0x2, 0x2, 
    0xc0, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xc1, 0x25, 0x3, 0x2, 0x2, 0x2, 0xc2, 
    0xc4, 0x7, 0xe, 0x2, 0x2, 0xc3, 0xc5, 0x5, 0x2c, 0x17, 0x2, 0xc4, 0xc3, 
    0x3, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 0x3, 
    0x2, 0x2, 0x2, 0xc6, 0xcc, 0x7, 0x18, 0x2, 0x2, 0xc7, 0xc8, 0x7, 0xc, 
    0x2, 0x2, 0xc8, 0xcc, 0x7, 0x18, 0x2, 0x2, 0xc9, 0xca, 0x7, 0xd, 0x2, 
    0x2, 0xca, 0xcc, 0x7, 0x18, 0x2, 0x2, 0xcb, 0xc2, 0x3, 0x2, 0x2, 0x2, 
    0xcb, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xcc, 
    0x27, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xd2, 0x5, 0x8, 0x5, 0x2, 0xce, 0xcf, 
    0x7, 0x16, 0x2, 0x2, 0xcf, 0xd0, 0x5, 0x2c, 0x17, 0x2, 0xd0, 0xd1, 0x7, 
    0x17, 0x2, 0x2, 0xd1, 0xd3, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xce, 0x3, 0x2, 
    0x2, 0x2, 0xd3, 0xd4, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xd2, 0x3, 0x2, 0x2, 
    0x2, 0xd4, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xd8, 0x3, 0x2, 0x2, 0x2, 
    0xd6, 0xd7, 0x7, 0x16, 0x2, 0x2, 0xd7, 0xd9, 0x7, 0x17, 0x2, 0x2, 0xd8, 
    0xd6, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x3, 0x2, 0x2, 0x2, 0xda, 0xd8, 
    0x3, 0x2, 0x2, 0x2, 0xda, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xe0, 0x3, 
    0x2, 0x2, 0x2, 0xdc, 0xdd, 0x7, 0x16, 0x2, 0x2, 0xdd, 0xde, 0x5, 0x2c, 
    0x17, 0x2, 0xde, 0xdf, 0x7, 0x17, 0x2, 0x2, 0xdf, 0xe1, 0x3, 0x2, 0x2, 
    0x2, 0xe0, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe2, 0x3, 0x2, 0x2, 0x2, 
    0xe2, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe3, 0x3, 0x2, 0x2, 0x2, 0xe3, 
    0xfa, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe9, 0x5, 0x8, 0x5, 0x2, 0xe5, 0xe6, 
    0x7, 0x16, 0x2, 0x2, 0xe6, 0xe7, 0x5, 0x2c, 0x17, 0x2, 0xe7, 0xe8, 0x7, 
    0x17, 0x2, 0x2, 0xe8, 0xea, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xe5, 0x3, 0x2, 
    0x2, 0x2, 0xea, 0xeb, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xe9, 0x3, 0x2, 0x2, 
    0x2, 0xeb, 0xec, 0x3, 0x2, 0x2, 0x2, 0xec, 0xf1, 0x3, 0x2, 0x2, 0x2, 
    0xed, 0xee, 0x7, 0x16, 0x2, 0x2, 0xee, 0xf0, 0x7, 0x17, 0x2, 0x2, 0xef, 
    0xed, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xef, 
    0x3, 0x2, 0x2, 0x2, 0xf1, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xfa, 0x3, 
    0x2, 0x2, 0x2, 0xf3, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf7, 0x5, 0x8, 
    0x5, 0x2, 0xf5, 0xf6, 0x7, 0x12, 0x2, 0x2, 0xf6, 0xf8, 0x7, 0x13, 0x2, 
    0x2, 0xf7, 0xf5, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xf8, 0x3, 0x2, 0x2, 0x2, 
    0xf8, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xf9, 
    0xe4, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xf4, 0x3, 0x2, 0x2, 0x2, 0xfa, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0xfb, 0x100, 0x7, 0x32, 0x2, 0x2, 0xfc, 0x100, 0x7, 
    0x33, 0x2, 0x2, 0xfd, 0x100, 0x7, 0x34, 0x2, 0x2, 0xfe, 0x100, 0x7, 
    0x6, 0x2, 0x2, 0xff, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfc, 0x3, 0x2, 
    0x2, 0x2, 0xff, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfe, 0x3, 0x2, 0x2, 
    0x2, 0x100, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x101, 0x102, 0x8, 0x17, 0x1, 
    0x2, 0x102, 0x103, 0x9, 0x3, 0x2, 0x2, 0x103, 0x114, 0x5, 0x2c, 0x17, 
    0x17, 0x104, 0x105, 0x9, 0x4, 0x2, 0x2, 0x105, 0x114, 0x5, 0x2c, 0x17, 
    0x16, 0x106, 0x107, 0x7, 0x26, 0x2, 0x2, 0x107, 0x114, 0x5, 0x2c, 0x17, 
    0x15, 0x108, 0x109, 0x7, 0x2a, 0x2, 0x2, 0x109, 0x114, 0x5, 0x2c, 0x17, 
    0x14, 0x10a, 0x10b, 0x7, 0xf, 0x2, 0x2, 0x10b, 0x114, 0x5, 0x28, 0x15, 
    0x2, 0x10c, 0x114, 0x5, 0x2a, 0x16, 0x2, 0x10d, 0x114, 0x7, 0x35, 0x2, 
    0x2, 0x10e, 0x114, 0x7, 0x11, 0x2, 0x2, 0x10f, 0x110, 0x7, 0x12, 0x2, 
    0x2, 0x110, 0x111, 0x5, 0x2c, 0x17, 0x2, 0x111, 0x112, 0x7, 0x13, 0x2, 
    0x2, 0x112, 0x114, 0x3, 0x2, 0x2, 0x2, 0x113, 0x101, 0x3, 0x2, 0x2, 
    0x2, 0x113, 0x104, 0x3, 0x2, 0x2, 0x2, 0x113, 0x106, 0x3, 0x2, 0x2, 
    0x2, 0x113, 0x108, 0x3, 0x2, 0x2, 0x2, 0x113, 0x10a, 0x3, 0x2, 0x2, 
    0x2, 0x113, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x113, 0x10d, 0x3, 0x2, 0x2, 
    0x2, 0x113, 0x10e, 0x3, 0x2, 0x2, 0x2, 0x113, 0x10f, 0x3, 0x2, 0x2, 
    0x2, 0x114, 0x14b, 0x3, 0x2, 0x2, 0x2, 0x115, 0x116, 0xc, 0x12, 0x2, 
    0x2, 0x116, 0x117, 0x9, 0x5, 0x2, 0x2, 0x117, 0x14a, 0x5, 0x2c, 0x17, 
    0x13, 0x118, 0x119, 0xc, 0x11, 0x2, 0x2, 0x119, 0x11a, 0x9, 0x4, 0x2, 
    0x2, 0x11a, 0x14a, 0x5, 0x2c, 0x17, 0x12, 0x11b, 0x11c, 0xc, 0x10, 0x2, 
    0x2, 0x11c, 0x11d, 0x9, 0x6, 0x2, 0x2, 0x11d, 0x14a, 0x5, 0x2c, 0x17, 
    0x11, 0x11e, 0x11f, 0xc, 0xf, 0x2, 0x2, 0x11f, 0x120, 0x9, 0x7, 0x2, 
    0x2, 0x120, 0x14a, 0x5, 0x2c, 0x17, 0x10, 0x121, 0x122, 0xc, 0xe, 0x2, 
    0x2, 0x122, 0x123, 0x9, 0x8, 0x2, 0x2, 0x123, 0x14a, 0x5, 0x2c, 0x17, 
    0xf, 0x124, 0x125, 0xc, 0xd, 0x2, 0x2, 0x125, 0x126, 0x9, 0x9, 0x2, 
    0x2, 0x126, 0x14a, 0x5, 0x2c, 0x17, 0xe, 0x127, 0x128, 0xc, 0xc, 0x2, 
    0x2, 0x128, 0x129, 0x7, 0x2d, 0x2, 0x2, 0x129, 0x14a, 0x5, 0x2c, 0x17, 
    0xd, 0x12a, 0x12b, 0xc, 0xb, 0x2, 0x2, 0x12b, 0x12c, 0x7, 0x2c, 0x2, 
    0x2, 0x12c, 0x14a, 0x5, 0x2c, 0x17, 0xc, 0x12d, 0x12e, 0xc, 0xa, 0x2, 
    0x2, 0x12e, 0x12f, 0x7, 0x2b, 0x2, 0x2, 0x12f, 0x14a, 0x5, 0x2c, 0x17, 
    0xb, 0x130, 0x131, 0xc, 0x9, 0x2, 0x2, 0x131, 0x132, 0x7, 0x25, 0x2, 
    0x2, 0x132, 0x14a, 0x5, 0x2c, 0x17, 0xa, 0x133, 0x134, 0xc, 0x8, 0x2, 
    0x2, 0x134, 0x135, 0x7, 0x27, 0x2, 0x2, 0x135, 0x14a, 0x5, 0x2c, 0x17, 
    0x9, 0x136, 0x137, 0xc, 0x7, 0x2, 0x2, 0x137, 0x138, 0x7, 0x2e, 0x2, 
    0x2, 0x138, 0x14a, 0x5, 0x2c, 0x17, 0x7, 0x139, 0x13a, 0xc, 0x1b, 0x2, 
    0x2, 0x13a, 0x14a, 0x9, 0x3, 0x2, 0x2, 0x13b, 0x13c, 0xc, 0x1a, 0x2, 
    0x2, 0x13c, 0x13e, 0x7, 0x12, 0x2, 0x2, 0x13d, 0x13f, 0x5, 0x18, 0xd, 
    0x2, 0x13e, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x13e, 0x13f, 0x3, 0x2, 0x2, 
    0x2, 0x13f, 0x140, 0x3, 0x2, 0x2, 0x2, 0x140, 0x14a, 0x7, 0x13, 0x2, 
    0x2, 0x141, 0x142, 0xc, 0x19, 0x2, 0x2, 0x142, 0x143, 0x7, 0x16, 0x2, 
    0x2, 0x143, 0x144, 0x5, 0x2c, 0x17, 0x2, 0x144, 0x145, 0x7, 0x17, 0x2, 
    0x2, 0x145, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x146, 0x147, 0xc, 0x18, 0x2, 
    0x2, 0x147, 0x148, 0x7, 0x31, 0x2, 0x2, 0x148, 0x14a, 0x7, 0x35, 0x2, 
    0x2, 0x149, 0x115, 0x3, 0x2, 0x2, 0x2, 0x149, 0x118, 0x3, 0x2, 0x2, 
    0x2, 0x149, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x149, 0x11e, 0x3, 0x2, 0x2, 
    0x2, 0x149, 0x121, 0x3, 0x2, 0x2, 0x2, 0x149, 0x124, 0x3, 0x2, 0x2, 
    0x2, 0x149, 0x127, 0x3, 0x2, 0x2, 0x2, 0x149, 0x12a, 0x3, 0x2, 0x2, 
    0x2, 0x149, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x149, 0x130, 0x3, 0x2, 0x2, 
    0x2, 0x149, 0x133, 0x3, 0x2, 0x2, 0x2, 0x149, 0x136, 0x3, 0x2, 0x2, 
    0x2, 0x149, 0x139, 0x3, 0x2, 0x2, 0x2, 0x149, 0x13b, 0x3, 0x2, 0x2, 
    0x2, 0x149, 0x141, 0x3, 0x2, 0x2, 0x2, 0x149, 0x146, 0x3, 0x2, 0x2, 
    0x2, 0x14a, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x14b, 0x149, 0x3, 0x2, 0x2, 
    0x2, 0x14b, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14c, 0x2d, 0x3, 0x2, 0x2, 0x2, 
    0x14d, 0x14b, 0x3, 0x2, 0x2, 0x2, 0x23, 0x31, 0x39, 0x40, 0x45, 0x4f, 
    0x59, 0x62, 0x6b, 0x6f, 0x76, 0x81, 0x87, 0x92, 0xa0, 0xa9, 0xb4, 0xb8, 
    0xbc, 0xc0, 0xc4, 0xcb, 0xd4, 0xda, 0xe2, 0xeb, 0xf1, 0xf7, 0xf9, 0xff, 
    0x113, 0x13e, 0x149, 0x14b, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

MxParser::Initializer MxParser::_init;
