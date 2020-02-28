
// Generated from Mx.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  MxLexer : public antlr4::Lexer {
public:
  enum {
    BOOL = 1, INT = 2, STRING = 3, NONE = 4, VOID = 5, IF = 6, ELSE = 7, 
    FOR = 8, WHILE = 9, BREAK = 10, CONTINUE = 11, RETURN = 12, NEW = 13, 
    CLASS = 14, THIS = 15, LPAREN = 16, RPAREN = 17, LBRACE = 18, RBRACE = 19, 
    LBRACK = 20, RBRACK = 21, SEMI = 22, COMMA = 23, ADD = 24, SUB = 25, 
    MUL = 26, DIV = 27, MOD = 28, LT = 29, GT = 30, EQ = 31, NEQ = 32, GE = 33, 
    LE = 34, AND = 35, NOT = 36, OR = 37, LSFT = 38, RSFT = 39, BITNOT = 40, 
    BITOR = 41, BITXOR = 42, BITAND = 43, ASSIGN = 44, INC = 45, DEC = 46, 
    DOT = 47, BoolConstant = 48, IntConstant = 49, StringConstant = 50, 
    Identifier = 51, LINE_COMMENT = 52, BLOCK_COMMENT = 53, WS = 54
  };

  MxLexer(antlr4::CharStream *input);
  ~MxLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

