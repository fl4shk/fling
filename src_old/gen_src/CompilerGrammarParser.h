
// Generated from CompilerGrammar.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  CompilerGrammarParser : public antlr4::Parser {
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

  enum {
    RuleProgram = 0, RuleSubProgram = 1, RuleDeclModule = 2, RuleDeclStruct = 3, 
    RuleDeclVarList = 4, RuleDeclParameters = 5, RuleTypeName = 6, RuleSlice = 7, 
    RuleScopedOuterStatements = 8, RuleOuterStatement = 9, RuleListIdentNames = 10, 
    RuleMultiListModulePorts = 11, RuleListModulePorts = 12, RuleListPortParams = 13, 
    RulePortParam = 14, RuleExpr = 15, RuleExprLogical = 16, RuleExprCompare = 17, 
    RuleExprAddSub = 18, RuleExprMulDivModEtc = 19, RuleExprUnary = 20, 
    RuleExprBitInvert = 21, RuleExprNegate = 22, RuleExprLogNot = 23, RuleNumExpr = 24, 
    RuleIdentExpr = 25, RuleIdentName = 26, RuleIdentSliced = 27
  };

  CompilerGrammarParser(antlr4::TokenStream *input);
  ~CompilerGrammarParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ProgramContext;
  class SubProgramContext;
  class DeclModuleContext;
  class DeclStructContext;
  class DeclVarListContext;
  class DeclParametersContext;
  class TypeNameContext;
  class SliceContext;
  class ScopedOuterStatementsContext;
  class OuterStatementContext;
  class ListIdentNamesContext;
  class MultiListModulePortsContext;
  class ListModulePortsContext;
  class ListPortParamsContext;
  class PortParamContext;
  class ExprContext;
  class ExprLogicalContext;
  class ExprCompareContext;
  class ExprAddSubContext;
  class ExprMulDivModEtcContext;
  class ExprUnaryContext;
  class ExprBitInvertContext;
  class ExprNegateContext;
  class ExprLogNotContext;
  class NumExprContext;
  class IdentExprContext;
  class IdentNameContext;
  class IdentSlicedContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SubProgramContext *> subProgram();
    SubProgramContext* subProgram(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  SubProgramContext : public antlr4::ParserRuleContext {
  public:
    SubProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclModuleContext *declModule();
    DeclStructContext *declStruct();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SubProgramContext* subProgram();

  class  DeclModuleContext : public antlr4::ParserRuleContext {
  public:
    DeclModuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokKwModule();
    IdentNameContext *identName();
    antlr4::tree::TerminalNode *TokLParen();
    MultiListModulePortsContext *multiListModulePorts();
    antlr4::tree::TerminalNode *TokRParen();
    ScopedOuterStatementsContext *scopedOuterStatements();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclModuleContext* declModule();

  class  DeclStructContext : public antlr4::ParserRuleContext {
  public:
    DeclStructContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokKwStruct();
    IdentNameContext *identName();
    antlr4::tree::TerminalNode *TokLBrace();
    antlr4::tree::TerminalNode *TokRBrace();
    std::vector<antlr4::tree::TerminalNode *> TokSemicolon();
    antlr4::tree::TerminalNode* TokSemicolon(size_t i);
    std::vector<DeclVarListContext *> declVarList();
    DeclVarListContext* declVarList(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclStructContext* declStruct();

  class  DeclVarListContext : public antlr4::ParserRuleContext {
  public:
    DeclVarListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    ListIdentNamesContext *listIdentNames();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclVarListContext* declVarList();

  class  DeclParametersContext : public antlr4::ParserRuleContext {
  public:
    DeclParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokNumber();
    antlr4::tree::TerminalNode *TokLParen();
    ListPortParamsContext *listPortParams();
    antlr4::tree::TerminalNode *TokRParen();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclParametersContext* declParameters();

  class  TypeNameContext : public antlr4::ParserRuleContext {
  public:
    TypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokKwLogic();
    SliceContext *slice();
    IdentNameContext *identName();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeNameContext* typeName();

  class  SliceContext : public antlr4::ParserRuleContext {
  public:
    SliceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokLBrace();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *TokColon();
    antlr4::tree::TerminalNode *TokRBrace();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SliceContext* slice();

  class  ScopedOuterStatementsContext : public antlr4::ParserRuleContext {
  public:
    ScopedOuterStatementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokLBrace();
    antlr4::tree::TerminalNode *TokRBrace();
    std::vector<OuterStatementContext *> outerStatement();
    OuterStatementContext* outerStatement(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScopedOuterStatementsContext* scopedOuterStatements();

  class  OuterStatementContext : public antlr4::ParserRuleContext {
  public:
    OuterStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclVarListContext *declVarList();
    antlr4::tree::TerminalNode *TokSemicolon();
    DeclStructContext *declStruct();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OuterStatementContext* outerStatement();

  class  ListIdentNamesContext : public antlr4::ParserRuleContext {
  public:
    ListIdentNamesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentNameContext *> identName();
    IdentNameContext* identName(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TokComma();
    antlr4::tree::TerminalNode* TokComma(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ListIdentNamesContext* listIdentNames();

  class  MultiListModulePortsContext : public antlr4::ParserRuleContext {
  public:
    MultiListModulePortsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ListModulePortsContext *> listModulePorts();
    ListModulePortsContext* listModulePorts(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TokComma();
    antlr4::tree::TerminalNode* TokComma(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiListModulePortsContext* multiListModulePorts();

  class  ListModulePortsContext : public antlr4::ParserRuleContext {
  public:
    ListModulePortsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclVarListContext *declVarList();
    antlr4::tree::TerminalNode *TokKwInput();
    antlr4::tree::TerminalNode *TokKwOutput();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ListModulePortsContext* listModulePorts();

  class  ListPortParamsContext : public antlr4::ParserRuleContext {
  public:
    ListPortParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PortParamContext *> portParam();
    PortParamContext* portParam(size_t i);
    std::vector<antlr4::tree::TerminalNode *> TokComma();
    antlr4::tree::TerminalNode* TokComma(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ListPortParamsContext* listPortParams();

  class  PortParamContext : public antlr4::ParserRuleContext {
  public:
    PortParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokKwParameter();
    IdentNameContext *identName();
    antlr4::tree::TerminalNode *TokBlockingAssign();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PortParamContext* portParam();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprLogicalContext *exprLogical();
    ExprContext *expr();
    antlr4::tree::TerminalNode *TokOpLogical();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  ExprLogicalContext : public antlr4::ParserRuleContext {
  public:
    ExprLogicalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprCompareContext *exprCompare();
    ExprLogicalContext *exprLogical();
    antlr4::tree::TerminalNode *TokOpCompare();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprLogicalContext* exprLogical();
  ExprLogicalContext* exprLogical(int precedence);
  class  ExprCompareContext : public antlr4::ParserRuleContext {
  public:
    ExprCompareContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprAddSubContext *exprAddSub();
    ExprCompareContext *exprCompare();
    antlr4::tree::TerminalNode *TokPlus();
    antlr4::tree::TerminalNode *TokMinus();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprCompareContext* exprCompare();
  ExprCompareContext* exprCompare(int precedence);
  class  ExprAddSubContext : public antlr4::ParserRuleContext {
  public:
    ExprAddSubContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprMulDivModEtcContext *exprMulDivModEtc();
    ExprAddSubContext *exprAddSub();
    antlr4::tree::TerminalNode *TokOpMulDivMod();
    antlr4::tree::TerminalNode *TokOpBitwise();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprAddSubContext* exprAddSub();
  ExprAddSubContext* exprAddSub(int precedence);
  class  ExprMulDivModEtcContext : public antlr4::ParserRuleContext {
  public:
    ExprMulDivModEtcContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprUnaryContext *exprUnary();
    NumExprContext *numExpr();
    IdentExprContext *identExpr();
    antlr4::tree::TerminalNode *TokLParen();
    ExprContext *expr();
    antlr4::tree::TerminalNode *TokRParen();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprMulDivModEtcContext* exprMulDivModEtc();

  class  ExprUnaryContext : public antlr4::ParserRuleContext {
  public:
    ExprUnaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprBitInvertContext *exprBitInvert();
    ExprNegateContext *exprNegate();
    ExprLogNotContext *exprLogNot();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprUnaryContext* exprUnary();

  class  ExprBitInvertContext : public antlr4::ParserRuleContext {
  public:
    ExprBitInvertContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokBitInvert();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprBitInvertContext* exprBitInvert();

  class  ExprNegateContext : public antlr4::ParserRuleContext {
  public:
    ExprNegateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokMinus();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprNegateContext* exprNegate();

  class  ExprLogNotContext : public antlr4::ParserRuleContext {
  public:
    ExprLogNotContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokExclamPoint();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprLogNotContext* exprLogNot();

  class  NumExprContext : public antlr4::ParserRuleContext {
  public:
    NumExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokDecNum();
    antlr4::tree::TerminalNode *TokHexNum();
    antlr4::tree::TerminalNode *TokBinNum();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NumExprContext* numExpr();

  class  IdentExprContext : public antlr4::ParserRuleContext {
  public:
    IdentExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentNameContext *identName();
    IdentSlicedContext *identSliced();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentExprContext* identExpr();

  class  IdentNameContext : public antlr4::ParserRuleContext {
  public:
    IdentNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokIdent();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentNameContext* identName();

  class  IdentSlicedContext : public antlr4::ParserRuleContext {
  public:
    IdentSlicedContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TokIdent();
    SliceContext *slice();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentSlicedContext* identSliced();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);
  bool exprLogicalSempred(ExprLogicalContext *_localctx, size_t predicateIndex);
  bool exprCompareSempred(ExprCompareContext *_localctx, size_t predicateIndex);
  bool exprAddSubSempred(ExprAddSubContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

