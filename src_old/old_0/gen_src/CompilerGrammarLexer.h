
// Generated from CompilerGrammar.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  CompilerGrammarLexer : public antlr4::Lexer {
public:
  enum {
    LexWhitespace = 1, LexLineComment = 2, TokOpLogical = 3, TokOpCompare = 4, 
    TokPlus = 5, TokMinus = 6, TokOpMulDivMod = 7, TokOpBitwise = 8, TokBitInvert = 9, 
    TokDecNum = 10, TokHexNum = 11, TokBinNum = 12, TokBlockingAssign = 13, 
    TokNonBlockingAssign = 14, TokPeriod = 15, TokComma = 16, TokColon = 17, 
    TokScope = 18, TokApostrophe = 19, TokQuote = 20, TokSemicolon = 21, 
    TokExclamPoint = 22, TokLParen = 23, TokRParen = 24, TokLBracket = 25, 
    TokRBracket = 26, TokLBrace = 27, TokRBrace = 28, TokNumber = 29, TokKwModule = 30, 
    TokKwParameter = 31, TokKwLocalparam = 32, TokKwInput = 33, TokKwOutput = 34, 
    TokKwLogic = 35, TokKwInterface = 36, TokKwStruct = 37, TokKwPublic = 38, 
    TokKwPrivate = 39, TokKwEnum = 40, TokKwUnion = 41, TokKwTask = 42, 
    TokKwFunction = 43, TokKwPackage = 44, TokKwDollarConcat = 45, TokKwDollarReplicate = 46, 
    TokKwAssign = 47, TokKwInitial = 48, TokKwAlwaysComb = 49, TokKwAlwaysSeq = 50, 
    TokKwPosedge = 51, TokKwNegedge = 52, TokKwIf = 53, TokKwElse = 54, 
    TokKwFor = 55, TokKwWhile = 56, TokKwDo = 57, TokKwSwitch = 58, TokKwSwitchx = 59, 
    TokKwSwitchz = 60, TokKwCase = 61, TokKwDefault = 62, TokIdent = 63, 
    TokOther = 64
  };

  CompilerGrammarLexer(antlr4::CharStream *input);
  ~CompilerGrammarLexer();

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

