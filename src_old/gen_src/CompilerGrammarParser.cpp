
// Generated from CompilerGrammar.g4 by ANTLR 4.7.1


#include "CompilerGrammarVisitor.h"

#include "CompilerGrammarParser.h"


using namespace antlrcpp;
using namespace antlr4;

CompilerGrammarParser::CompilerGrammarParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CompilerGrammarParser::~CompilerGrammarParser() {
  delete _interpreter;
}

std::string CompilerGrammarParser::getGrammarFileName() const {
  return "CompilerGrammar.g4";
}

const std::vector<std::string>& CompilerGrammarParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CompilerGrammarParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

CompilerGrammarParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CompilerGrammarParser::SubProgramContext *> CompilerGrammarParser::ProgramContext::subProgram() {
  return getRuleContexts<CompilerGrammarParser::SubProgramContext>();
}

CompilerGrammarParser::SubProgramContext* CompilerGrammarParser::ProgramContext::subProgram(size_t i) {
  return getRuleContext<CompilerGrammarParser::SubProgramContext>(i);
}


size_t CompilerGrammarParser::ProgramContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleProgram;
}

antlrcpp::Any CompilerGrammarParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::ProgramContext* CompilerGrammarParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, CompilerGrammarParser::RuleProgram);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CompilerGrammarParser::TokKwModule

    || _la == CompilerGrammarParser::TokKwStruct) {
      setState(56);
      subProgram();
      setState(61);
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

//----------------- SubProgramContext ------------------------------------------------------------------

CompilerGrammarParser::SubProgramContext::SubProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CompilerGrammarParser::DeclModuleContext* CompilerGrammarParser::SubProgramContext::declModule() {
  return getRuleContext<CompilerGrammarParser::DeclModuleContext>(0);
}

CompilerGrammarParser::DeclStructContext* CompilerGrammarParser::SubProgramContext::declStruct() {
  return getRuleContext<CompilerGrammarParser::DeclStructContext>(0);
}


size_t CompilerGrammarParser::SubProgramContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleSubProgram;
}

antlrcpp::Any CompilerGrammarParser::SubProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitSubProgram(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::SubProgramContext* CompilerGrammarParser::subProgram() {
  SubProgramContext *_localctx = _tracker.createInstance<SubProgramContext>(_ctx, getState());
  enterRule(_localctx, 2, CompilerGrammarParser::RuleSubProgram);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(64);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CompilerGrammarParser::TokKwModule: {
        enterOuterAlt(_localctx, 1);
        setState(62);
        declModule();
        break;
      }

      case CompilerGrammarParser::TokKwStruct: {
        enterOuterAlt(_localctx, 2);
        setState(63);
        declStruct();
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

//----------------- DeclModuleContext ------------------------------------------------------------------

CompilerGrammarParser::DeclModuleContext::DeclModuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::DeclModuleContext::TokKwModule() {
  return getToken(CompilerGrammarParser::TokKwModule, 0);
}

CompilerGrammarParser::IdentNameContext* CompilerGrammarParser::DeclModuleContext::identName() {
  return getRuleContext<CompilerGrammarParser::IdentNameContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::DeclModuleContext::TokLParen() {
  return getToken(CompilerGrammarParser::TokLParen, 0);
}

CompilerGrammarParser::MultiListModulePortsContext* CompilerGrammarParser::DeclModuleContext::multiListModulePorts() {
  return getRuleContext<CompilerGrammarParser::MultiListModulePortsContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::DeclModuleContext::TokRParen() {
  return getToken(CompilerGrammarParser::TokRParen, 0);
}

CompilerGrammarParser::ScopedOuterStatementsContext* CompilerGrammarParser::DeclModuleContext::scopedOuterStatements() {
  return getRuleContext<CompilerGrammarParser::ScopedOuterStatementsContext>(0);
}


size_t CompilerGrammarParser::DeclModuleContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleDeclModule;
}

antlrcpp::Any CompilerGrammarParser::DeclModuleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitDeclModule(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::DeclModuleContext* CompilerGrammarParser::declModule() {
  DeclModuleContext *_localctx = _tracker.createInstance<DeclModuleContext>(_ctx, getState());
  enterRule(_localctx, 4, CompilerGrammarParser::RuleDeclModule);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    match(CompilerGrammarParser::TokKwModule);
    setState(67);
    identName();
    setState(68);
    match(CompilerGrammarParser::TokLParen);
    setState(69);
    multiListModulePorts();
    setState(70);
    match(CompilerGrammarParser::TokRParen);
    setState(71);
    scopedOuterStatements();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclStructContext ------------------------------------------------------------------

CompilerGrammarParser::DeclStructContext::DeclStructContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::DeclStructContext::TokKwStruct() {
  return getToken(CompilerGrammarParser::TokKwStruct, 0);
}

CompilerGrammarParser::IdentNameContext* CompilerGrammarParser::DeclStructContext::identName() {
  return getRuleContext<CompilerGrammarParser::IdentNameContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::DeclStructContext::TokLBrace() {
  return getToken(CompilerGrammarParser::TokLBrace, 0);
}

tree::TerminalNode* CompilerGrammarParser::DeclStructContext::TokRBrace() {
  return getToken(CompilerGrammarParser::TokRBrace, 0);
}

std::vector<tree::TerminalNode *> CompilerGrammarParser::DeclStructContext::TokSemicolon() {
  return getTokens(CompilerGrammarParser::TokSemicolon);
}

tree::TerminalNode* CompilerGrammarParser::DeclStructContext::TokSemicolon(size_t i) {
  return getToken(CompilerGrammarParser::TokSemicolon, i);
}

std::vector<CompilerGrammarParser::DeclVarListContext *> CompilerGrammarParser::DeclStructContext::declVarList() {
  return getRuleContexts<CompilerGrammarParser::DeclVarListContext>();
}

CompilerGrammarParser::DeclVarListContext* CompilerGrammarParser::DeclStructContext::declVarList(size_t i) {
  return getRuleContext<CompilerGrammarParser::DeclVarListContext>(i);
}


size_t CompilerGrammarParser::DeclStructContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleDeclStruct;
}

antlrcpp::Any CompilerGrammarParser::DeclStructContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitDeclStruct(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::DeclStructContext* CompilerGrammarParser::declStruct() {
  DeclStructContext *_localctx = _tracker.createInstance<DeclStructContext>(_ctx, getState());
  enterRule(_localctx, 6, CompilerGrammarParser::RuleDeclStruct);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(73);
    match(CompilerGrammarParser::TokKwStruct);
    setState(74);
    identName();
    setState(75);
    match(CompilerGrammarParser::TokLBrace);
    setState(81);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CompilerGrammarParser::TokKwLogic

    || _la == CompilerGrammarParser::TokIdent) {
      setState(76);
      declVarList();
      setState(77);
      match(CompilerGrammarParser::TokSemicolon);
      setState(83);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(84);
    match(CompilerGrammarParser::TokRBrace);
    setState(85);
    match(CompilerGrammarParser::TokSemicolon);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclVarListContext ------------------------------------------------------------------

CompilerGrammarParser::DeclVarListContext::DeclVarListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CompilerGrammarParser::TypeNameContext* CompilerGrammarParser::DeclVarListContext::typeName() {
  return getRuleContext<CompilerGrammarParser::TypeNameContext>(0);
}

CompilerGrammarParser::ListIdentNamesContext* CompilerGrammarParser::DeclVarListContext::listIdentNames() {
  return getRuleContext<CompilerGrammarParser::ListIdentNamesContext>(0);
}


size_t CompilerGrammarParser::DeclVarListContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleDeclVarList;
}

antlrcpp::Any CompilerGrammarParser::DeclVarListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitDeclVarList(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::DeclVarListContext* CompilerGrammarParser::declVarList() {
  DeclVarListContext *_localctx = _tracker.createInstance<DeclVarListContext>(_ctx, getState());
  enterRule(_localctx, 8, CompilerGrammarParser::RuleDeclVarList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    typeName();
    setState(88);
    listIdentNames();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclParametersContext ------------------------------------------------------------------

CompilerGrammarParser::DeclParametersContext::DeclParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::DeclParametersContext::TokNumber() {
  return getToken(CompilerGrammarParser::TokNumber, 0);
}

tree::TerminalNode* CompilerGrammarParser::DeclParametersContext::TokLParen() {
  return getToken(CompilerGrammarParser::TokLParen, 0);
}

CompilerGrammarParser::ListPortParamsContext* CompilerGrammarParser::DeclParametersContext::listPortParams() {
  return getRuleContext<CompilerGrammarParser::ListPortParamsContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::DeclParametersContext::TokRParen() {
  return getToken(CompilerGrammarParser::TokRParen, 0);
}


size_t CompilerGrammarParser::DeclParametersContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleDeclParameters;
}

antlrcpp::Any CompilerGrammarParser::DeclParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitDeclParameters(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::DeclParametersContext* CompilerGrammarParser::declParameters() {
  DeclParametersContext *_localctx = _tracker.createInstance<DeclParametersContext>(_ctx, getState());
  enterRule(_localctx, 10, CompilerGrammarParser::RuleDeclParameters);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    match(CompilerGrammarParser::TokNumber);
    setState(91);
    match(CompilerGrammarParser::TokLParen);
    setState(92);
    listPortParams();
    setState(93);
    match(CompilerGrammarParser::TokRParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNameContext ------------------------------------------------------------------

CompilerGrammarParser::TypeNameContext::TypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::TypeNameContext::TokKwLogic() {
  return getToken(CompilerGrammarParser::TokKwLogic, 0);
}

CompilerGrammarParser::SliceContext* CompilerGrammarParser::TypeNameContext::slice() {
  return getRuleContext<CompilerGrammarParser::SliceContext>(0);
}

CompilerGrammarParser::IdentNameContext* CompilerGrammarParser::TypeNameContext::identName() {
  return getRuleContext<CompilerGrammarParser::IdentNameContext>(0);
}


size_t CompilerGrammarParser::TypeNameContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleTypeName;
}

antlrcpp::Any CompilerGrammarParser::TypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitTypeName(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::TypeNameContext* CompilerGrammarParser::typeName() {
  TypeNameContext *_localctx = _tracker.createInstance<TypeNameContext>(_ctx, getState());
  enterRule(_localctx, 12, CompilerGrammarParser::RuleTypeName);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(100);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CompilerGrammarParser::TokKwLogic: {
        enterOuterAlt(_localctx, 1);
        setState(95);
        match(CompilerGrammarParser::TokKwLogic);

        setState(97);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CompilerGrammarParser::TokLBrace) {
          setState(96);
          slice();
        }
        break;
      }

      case CompilerGrammarParser::TokIdent: {
        enterOuterAlt(_localctx, 2);
        setState(99);
        identName();
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

//----------------- SliceContext ------------------------------------------------------------------

CompilerGrammarParser::SliceContext::SliceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::SliceContext::TokLBrace() {
  return getToken(CompilerGrammarParser::TokLBrace, 0);
}

std::vector<CompilerGrammarParser::ExprContext *> CompilerGrammarParser::SliceContext::expr() {
  return getRuleContexts<CompilerGrammarParser::ExprContext>();
}

CompilerGrammarParser::ExprContext* CompilerGrammarParser::SliceContext::expr(size_t i) {
  return getRuleContext<CompilerGrammarParser::ExprContext>(i);
}

tree::TerminalNode* CompilerGrammarParser::SliceContext::TokColon() {
  return getToken(CompilerGrammarParser::TokColon, 0);
}

tree::TerminalNode* CompilerGrammarParser::SliceContext::TokRBrace() {
  return getToken(CompilerGrammarParser::TokRBrace, 0);
}


size_t CompilerGrammarParser::SliceContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleSlice;
}

antlrcpp::Any CompilerGrammarParser::SliceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitSlice(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::SliceContext* CompilerGrammarParser::slice() {
  SliceContext *_localctx = _tracker.createInstance<SliceContext>(_ctx, getState());
  enterRule(_localctx, 14, CompilerGrammarParser::RuleSlice);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(102);
    match(CompilerGrammarParser::TokLBrace);
    setState(103);
    expr(0);
    setState(104);
    match(CompilerGrammarParser::TokColon);
    setState(105);
    expr(0);
    setState(106);
    match(CompilerGrammarParser::TokRBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScopedOuterStatementsContext ------------------------------------------------------------------

CompilerGrammarParser::ScopedOuterStatementsContext::ScopedOuterStatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::ScopedOuterStatementsContext::TokLBrace() {
  return getToken(CompilerGrammarParser::TokLBrace, 0);
}

tree::TerminalNode* CompilerGrammarParser::ScopedOuterStatementsContext::TokRBrace() {
  return getToken(CompilerGrammarParser::TokRBrace, 0);
}

std::vector<CompilerGrammarParser::OuterStatementContext *> CompilerGrammarParser::ScopedOuterStatementsContext::outerStatement() {
  return getRuleContexts<CompilerGrammarParser::OuterStatementContext>();
}

CompilerGrammarParser::OuterStatementContext* CompilerGrammarParser::ScopedOuterStatementsContext::outerStatement(size_t i) {
  return getRuleContext<CompilerGrammarParser::OuterStatementContext>(i);
}


size_t CompilerGrammarParser::ScopedOuterStatementsContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleScopedOuterStatements;
}

antlrcpp::Any CompilerGrammarParser::ScopedOuterStatementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitScopedOuterStatements(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::ScopedOuterStatementsContext* CompilerGrammarParser::scopedOuterStatements() {
  ScopedOuterStatementsContext *_localctx = _tracker.createInstance<ScopedOuterStatementsContext>(_ctx, getState());
  enterRule(_localctx, 16, CompilerGrammarParser::RuleScopedOuterStatements);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(108);
    match(CompilerGrammarParser::TokLBrace);
    setState(112);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CompilerGrammarParser::TokKwLogic)
      | (1ULL << CompilerGrammarParser::TokKwStruct)
      | (1ULL << CompilerGrammarParser::TokIdent))) != 0)) {
      setState(109);
      outerStatement();
      setState(114);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(115);
    match(CompilerGrammarParser::TokRBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OuterStatementContext ------------------------------------------------------------------

CompilerGrammarParser::OuterStatementContext::OuterStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CompilerGrammarParser::DeclVarListContext* CompilerGrammarParser::OuterStatementContext::declVarList() {
  return getRuleContext<CompilerGrammarParser::DeclVarListContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::OuterStatementContext::TokSemicolon() {
  return getToken(CompilerGrammarParser::TokSemicolon, 0);
}

CompilerGrammarParser::DeclStructContext* CompilerGrammarParser::OuterStatementContext::declStruct() {
  return getRuleContext<CompilerGrammarParser::DeclStructContext>(0);
}


size_t CompilerGrammarParser::OuterStatementContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleOuterStatement;
}

antlrcpp::Any CompilerGrammarParser::OuterStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitOuterStatement(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::OuterStatementContext* CompilerGrammarParser::outerStatement() {
  OuterStatementContext *_localctx = _tracker.createInstance<OuterStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, CompilerGrammarParser::RuleOuterStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(121);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CompilerGrammarParser::TokKwLogic:
      case CompilerGrammarParser::TokIdent: {
        enterOuterAlt(_localctx, 1);
        setState(117);
        declVarList();
        setState(118);
        match(CompilerGrammarParser::TokSemicolon);
        break;
      }

      case CompilerGrammarParser::TokKwStruct: {
        enterOuterAlt(_localctx, 2);
        setState(120);
        declStruct();
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

//----------------- ListIdentNamesContext ------------------------------------------------------------------

CompilerGrammarParser::ListIdentNamesContext::ListIdentNamesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CompilerGrammarParser::IdentNameContext *> CompilerGrammarParser::ListIdentNamesContext::identName() {
  return getRuleContexts<CompilerGrammarParser::IdentNameContext>();
}

CompilerGrammarParser::IdentNameContext* CompilerGrammarParser::ListIdentNamesContext::identName(size_t i) {
  return getRuleContext<CompilerGrammarParser::IdentNameContext>(i);
}

std::vector<tree::TerminalNode *> CompilerGrammarParser::ListIdentNamesContext::TokComma() {
  return getTokens(CompilerGrammarParser::TokComma);
}

tree::TerminalNode* CompilerGrammarParser::ListIdentNamesContext::TokComma(size_t i) {
  return getToken(CompilerGrammarParser::TokComma, i);
}


size_t CompilerGrammarParser::ListIdentNamesContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleListIdentNames;
}

antlrcpp::Any CompilerGrammarParser::ListIdentNamesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitListIdentNames(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::ListIdentNamesContext* CompilerGrammarParser::listIdentNames() {
  ListIdentNamesContext *_localctx = _tracker.createInstance<ListIdentNamesContext>(_ctx, getState());
  enterRule(_localctx, 20, CompilerGrammarParser::RuleListIdentNames);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(123);
    identName();
    setState(128);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(124);
        match(CompilerGrammarParser::TokComma);
        setState(125);
        identName(); 
      }
      setState(130);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiListModulePortsContext ------------------------------------------------------------------

CompilerGrammarParser::MultiListModulePortsContext::MultiListModulePortsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CompilerGrammarParser::ListModulePortsContext *> CompilerGrammarParser::MultiListModulePortsContext::listModulePorts() {
  return getRuleContexts<CompilerGrammarParser::ListModulePortsContext>();
}

CompilerGrammarParser::ListModulePortsContext* CompilerGrammarParser::MultiListModulePortsContext::listModulePorts(size_t i) {
  return getRuleContext<CompilerGrammarParser::ListModulePortsContext>(i);
}

std::vector<tree::TerminalNode *> CompilerGrammarParser::MultiListModulePortsContext::TokComma() {
  return getTokens(CompilerGrammarParser::TokComma);
}

tree::TerminalNode* CompilerGrammarParser::MultiListModulePortsContext::TokComma(size_t i) {
  return getToken(CompilerGrammarParser::TokComma, i);
}


size_t CompilerGrammarParser::MultiListModulePortsContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleMultiListModulePorts;
}

antlrcpp::Any CompilerGrammarParser::MultiListModulePortsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitMultiListModulePorts(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::MultiListModulePortsContext* CompilerGrammarParser::multiListModulePorts() {
  MultiListModulePortsContext *_localctx = _tracker.createInstance<MultiListModulePortsContext>(_ctx, getState());
  enterRule(_localctx, 22, CompilerGrammarParser::RuleMultiListModulePorts);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    listModulePorts();
    setState(136);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CompilerGrammarParser::TokComma) {
      setState(132);
      match(CompilerGrammarParser::TokComma);
      setState(133);
      listModulePorts();
      setState(138);
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

//----------------- ListModulePortsContext ------------------------------------------------------------------

CompilerGrammarParser::ListModulePortsContext::ListModulePortsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CompilerGrammarParser::DeclVarListContext* CompilerGrammarParser::ListModulePortsContext::declVarList() {
  return getRuleContext<CompilerGrammarParser::DeclVarListContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::ListModulePortsContext::TokKwInput() {
  return getToken(CompilerGrammarParser::TokKwInput, 0);
}

tree::TerminalNode* CompilerGrammarParser::ListModulePortsContext::TokKwOutput() {
  return getToken(CompilerGrammarParser::TokKwOutput, 0);
}


size_t CompilerGrammarParser::ListModulePortsContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleListModulePorts;
}

antlrcpp::Any CompilerGrammarParser::ListModulePortsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitListModulePorts(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::ListModulePortsContext* CompilerGrammarParser::listModulePorts() {
  ListModulePortsContext *_localctx = _tracker.createInstance<ListModulePortsContext>(_ctx, getState());
  enterRule(_localctx, 24, CompilerGrammarParser::RuleListModulePorts);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    _la = _input->LA(1);
    if (!(_la == CompilerGrammarParser::TokKwInput

    || _la == CompilerGrammarParser::TokKwOutput)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(140);
    declVarList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ListPortParamsContext ------------------------------------------------------------------

CompilerGrammarParser::ListPortParamsContext::ListPortParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CompilerGrammarParser::PortParamContext *> CompilerGrammarParser::ListPortParamsContext::portParam() {
  return getRuleContexts<CompilerGrammarParser::PortParamContext>();
}

CompilerGrammarParser::PortParamContext* CompilerGrammarParser::ListPortParamsContext::portParam(size_t i) {
  return getRuleContext<CompilerGrammarParser::PortParamContext>(i);
}

std::vector<tree::TerminalNode *> CompilerGrammarParser::ListPortParamsContext::TokComma() {
  return getTokens(CompilerGrammarParser::TokComma);
}

tree::TerminalNode* CompilerGrammarParser::ListPortParamsContext::TokComma(size_t i) {
  return getToken(CompilerGrammarParser::TokComma, i);
}


size_t CompilerGrammarParser::ListPortParamsContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleListPortParams;
}

antlrcpp::Any CompilerGrammarParser::ListPortParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitListPortParams(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::ListPortParamsContext* CompilerGrammarParser::listPortParams() {
  ListPortParamsContext *_localctx = _tracker.createInstance<ListPortParamsContext>(_ctx, getState());
  enterRule(_localctx, 26, CompilerGrammarParser::RuleListPortParams);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(142);
    portParam();
    setState(147);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CompilerGrammarParser::TokComma) {
      setState(143);
      match(CompilerGrammarParser::TokComma);
      setState(144);
      portParam();
      setState(149);
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

//----------------- PortParamContext ------------------------------------------------------------------

CompilerGrammarParser::PortParamContext::PortParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::PortParamContext::TokKwParameter() {
  return getToken(CompilerGrammarParser::TokKwParameter, 0);
}

CompilerGrammarParser::IdentNameContext* CompilerGrammarParser::PortParamContext::identName() {
  return getRuleContext<CompilerGrammarParser::IdentNameContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::PortParamContext::TokBlockingAssign() {
  return getToken(CompilerGrammarParser::TokBlockingAssign, 0);
}

CompilerGrammarParser::ExprContext* CompilerGrammarParser::PortParamContext::expr() {
  return getRuleContext<CompilerGrammarParser::ExprContext>(0);
}


size_t CompilerGrammarParser::PortParamContext::getRuleIndex() const {
  return CompilerGrammarParser::RulePortParam;
}

antlrcpp::Any CompilerGrammarParser::PortParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitPortParam(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::PortParamContext* CompilerGrammarParser::portParam() {
  PortParamContext *_localctx = _tracker.createInstance<PortParamContext>(_ctx, getState());
  enterRule(_localctx, 28, CompilerGrammarParser::RulePortParam);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(150);
    match(CompilerGrammarParser::TokKwParameter);
    setState(151);
    identName();
    setState(154);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CompilerGrammarParser::TokBlockingAssign) {
      setState(152);
      match(CompilerGrammarParser::TokBlockingAssign);
      setState(153);
      expr(0);
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

CompilerGrammarParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CompilerGrammarParser::ExprLogicalContext* CompilerGrammarParser::ExprContext::exprLogical() {
  return getRuleContext<CompilerGrammarParser::ExprLogicalContext>(0);
}

CompilerGrammarParser::ExprContext* CompilerGrammarParser::ExprContext::expr() {
  return getRuleContext<CompilerGrammarParser::ExprContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::ExprContext::TokOpLogical() {
  return getToken(CompilerGrammarParser::TokOpLogical, 0);
}


size_t CompilerGrammarParser::ExprContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleExpr;
}

antlrcpp::Any CompilerGrammarParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}


CompilerGrammarParser::ExprContext* CompilerGrammarParser::expr() {
   return expr(0);
}

CompilerGrammarParser::ExprContext* CompilerGrammarParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CompilerGrammarParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  CompilerGrammarParser::ExprContext *previousContext = _localctx;
  size_t startState = 30;
  enterRecursionRule(_localctx, 30, CompilerGrammarParser::RuleExpr, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(157);
    exprLogical(0);
    _ctx->stop = _input->LT(-1);
    setState(164);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpr);
        setState(159);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(160);
        match(CompilerGrammarParser::TokOpLogical);
        setState(161);
        exprLogical(0); 
      }
      setState(166);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprLogicalContext ------------------------------------------------------------------

CompilerGrammarParser::ExprLogicalContext::ExprLogicalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CompilerGrammarParser::ExprCompareContext* CompilerGrammarParser::ExprLogicalContext::exprCompare() {
  return getRuleContext<CompilerGrammarParser::ExprCompareContext>(0);
}

CompilerGrammarParser::ExprLogicalContext* CompilerGrammarParser::ExprLogicalContext::exprLogical() {
  return getRuleContext<CompilerGrammarParser::ExprLogicalContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::ExprLogicalContext::TokOpCompare() {
  return getToken(CompilerGrammarParser::TokOpCompare, 0);
}


size_t CompilerGrammarParser::ExprLogicalContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleExprLogical;
}

antlrcpp::Any CompilerGrammarParser::ExprLogicalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitExprLogical(this);
  else
    return visitor->visitChildren(this);
}


CompilerGrammarParser::ExprLogicalContext* CompilerGrammarParser::exprLogical() {
   return exprLogical(0);
}

CompilerGrammarParser::ExprLogicalContext* CompilerGrammarParser::exprLogical(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CompilerGrammarParser::ExprLogicalContext *_localctx = _tracker.createInstance<ExprLogicalContext>(_ctx, parentState);
  CompilerGrammarParser::ExprLogicalContext *previousContext = _localctx;
  size_t startState = 32;
  enterRecursionRule(_localctx, 32, CompilerGrammarParser::RuleExprLogical, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(168);
    exprCompare(0);
    _ctx->stop = _input->LT(-1);
    setState(175);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExprLogicalContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExprLogical);
        setState(170);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(171);
        match(CompilerGrammarParser::TokOpCompare);
        setState(172);
        exprCompare(0); 
      }
      setState(177);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprCompareContext ------------------------------------------------------------------

CompilerGrammarParser::ExprCompareContext::ExprCompareContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CompilerGrammarParser::ExprAddSubContext* CompilerGrammarParser::ExprCompareContext::exprAddSub() {
  return getRuleContext<CompilerGrammarParser::ExprAddSubContext>(0);
}

CompilerGrammarParser::ExprCompareContext* CompilerGrammarParser::ExprCompareContext::exprCompare() {
  return getRuleContext<CompilerGrammarParser::ExprCompareContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::ExprCompareContext::TokPlus() {
  return getToken(CompilerGrammarParser::TokPlus, 0);
}

tree::TerminalNode* CompilerGrammarParser::ExprCompareContext::TokMinus() {
  return getToken(CompilerGrammarParser::TokMinus, 0);
}


size_t CompilerGrammarParser::ExprCompareContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleExprCompare;
}

antlrcpp::Any CompilerGrammarParser::ExprCompareContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitExprCompare(this);
  else
    return visitor->visitChildren(this);
}


CompilerGrammarParser::ExprCompareContext* CompilerGrammarParser::exprCompare() {
   return exprCompare(0);
}

CompilerGrammarParser::ExprCompareContext* CompilerGrammarParser::exprCompare(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CompilerGrammarParser::ExprCompareContext *_localctx = _tracker.createInstance<ExprCompareContext>(_ctx, parentState);
  CompilerGrammarParser::ExprCompareContext *previousContext = _localctx;
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, CompilerGrammarParser::RuleExprCompare, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(179);
    exprAddSub(0);
    _ctx->stop = _input->LT(-1);
    setState(189);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(187);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprCompareContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExprCompare);
          setState(181);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(182);
          match(CompilerGrammarParser::TokPlus);
          setState(183);
          exprAddSub(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprCompareContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExprCompare);
          setState(184);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(185);
          match(CompilerGrammarParser::TokMinus);
          setState(186);
          exprAddSub(0);
          break;
        }

        } 
      }
      setState(191);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprAddSubContext ------------------------------------------------------------------

CompilerGrammarParser::ExprAddSubContext::ExprAddSubContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CompilerGrammarParser::ExprMulDivModEtcContext* CompilerGrammarParser::ExprAddSubContext::exprMulDivModEtc() {
  return getRuleContext<CompilerGrammarParser::ExprMulDivModEtcContext>(0);
}

CompilerGrammarParser::ExprAddSubContext* CompilerGrammarParser::ExprAddSubContext::exprAddSub() {
  return getRuleContext<CompilerGrammarParser::ExprAddSubContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::ExprAddSubContext::TokOpMulDivMod() {
  return getToken(CompilerGrammarParser::TokOpMulDivMod, 0);
}

tree::TerminalNode* CompilerGrammarParser::ExprAddSubContext::TokOpBitwise() {
  return getToken(CompilerGrammarParser::TokOpBitwise, 0);
}


size_t CompilerGrammarParser::ExprAddSubContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleExprAddSub;
}

antlrcpp::Any CompilerGrammarParser::ExprAddSubContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitExprAddSub(this);
  else
    return visitor->visitChildren(this);
}


CompilerGrammarParser::ExprAddSubContext* CompilerGrammarParser::exprAddSub() {
   return exprAddSub(0);
}

CompilerGrammarParser::ExprAddSubContext* CompilerGrammarParser::exprAddSub(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CompilerGrammarParser::ExprAddSubContext *_localctx = _tracker.createInstance<ExprAddSubContext>(_ctx, parentState);
  CompilerGrammarParser::ExprAddSubContext *previousContext = _localctx;
  size_t startState = 36;
  enterRecursionRule(_localctx, 36, CompilerGrammarParser::RuleExprAddSub, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(193);
    exprMulDivModEtc();
    _ctx->stop = _input->LT(-1);
    setState(203);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(201);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprAddSubContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExprAddSub);
          setState(195);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(196);
          match(CompilerGrammarParser::TokOpMulDivMod);
          setState(197);
          exprMulDivModEtc();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprAddSubContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExprAddSub);
          setState(198);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(199);
          match(CompilerGrammarParser::TokOpBitwise);
          setState(200);
          exprMulDivModEtc();
          break;
        }

        } 
      }
      setState(205);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExprMulDivModEtcContext ------------------------------------------------------------------

CompilerGrammarParser::ExprMulDivModEtcContext::ExprMulDivModEtcContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CompilerGrammarParser::ExprUnaryContext* CompilerGrammarParser::ExprMulDivModEtcContext::exprUnary() {
  return getRuleContext<CompilerGrammarParser::ExprUnaryContext>(0);
}

CompilerGrammarParser::NumExprContext* CompilerGrammarParser::ExprMulDivModEtcContext::numExpr() {
  return getRuleContext<CompilerGrammarParser::NumExprContext>(0);
}

CompilerGrammarParser::IdentExprContext* CompilerGrammarParser::ExprMulDivModEtcContext::identExpr() {
  return getRuleContext<CompilerGrammarParser::IdentExprContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::ExprMulDivModEtcContext::TokLParen() {
  return getToken(CompilerGrammarParser::TokLParen, 0);
}

CompilerGrammarParser::ExprContext* CompilerGrammarParser::ExprMulDivModEtcContext::expr() {
  return getRuleContext<CompilerGrammarParser::ExprContext>(0);
}

tree::TerminalNode* CompilerGrammarParser::ExprMulDivModEtcContext::TokRParen() {
  return getToken(CompilerGrammarParser::TokRParen, 0);
}


size_t CompilerGrammarParser::ExprMulDivModEtcContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleExprMulDivModEtc;
}

antlrcpp::Any CompilerGrammarParser::ExprMulDivModEtcContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitExprMulDivModEtc(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::ExprMulDivModEtcContext* CompilerGrammarParser::exprMulDivModEtc() {
  ExprMulDivModEtcContext *_localctx = _tracker.createInstance<ExprMulDivModEtcContext>(_ctx, getState());
  enterRule(_localctx, 38, CompilerGrammarParser::RuleExprMulDivModEtc);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(213);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CompilerGrammarParser::TokMinus:
      case CompilerGrammarParser::TokBitInvert:
      case CompilerGrammarParser::TokExclamPoint: {
        enterOuterAlt(_localctx, 1);
        setState(206);
        exprUnary();
        break;
      }

      case CompilerGrammarParser::TokDecNum:
      case CompilerGrammarParser::TokHexNum:
      case CompilerGrammarParser::TokBinNum: {
        enterOuterAlt(_localctx, 2);
        setState(207);
        numExpr();
        break;
      }

      case CompilerGrammarParser::TokIdent: {
        enterOuterAlt(_localctx, 3);
        setState(208);
        identExpr();
        break;
      }

      case CompilerGrammarParser::TokLParen: {
        enterOuterAlt(_localctx, 4);
        setState(209);
        match(CompilerGrammarParser::TokLParen);
        setState(210);
        expr(0);
        setState(211);
        match(CompilerGrammarParser::TokRParen);
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

//----------------- ExprUnaryContext ------------------------------------------------------------------

CompilerGrammarParser::ExprUnaryContext::ExprUnaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CompilerGrammarParser::ExprBitInvertContext* CompilerGrammarParser::ExprUnaryContext::exprBitInvert() {
  return getRuleContext<CompilerGrammarParser::ExprBitInvertContext>(0);
}

CompilerGrammarParser::ExprNegateContext* CompilerGrammarParser::ExprUnaryContext::exprNegate() {
  return getRuleContext<CompilerGrammarParser::ExprNegateContext>(0);
}

CompilerGrammarParser::ExprLogNotContext* CompilerGrammarParser::ExprUnaryContext::exprLogNot() {
  return getRuleContext<CompilerGrammarParser::ExprLogNotContext>(0);
}


size_t CompilerGrammarParser::ExprUnaryContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleExprUnary;
}

antlrcpp::Any CompilerGrammarParser::ExprUnaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitExprUnary(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::ExprUnaryContext* CompilerGrammarParser::exprUnary() {
  ExprUnaryContext *_localctx = _tracker.createInstance<ExprUnaryContext>(_ctx, getState());
  enterRule(_localctx, 40, CompilerGrammarParser::RuleExprUnary);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(218);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CompilerGrammarParser::TokBitInvert: {
        enterOuterAlt(_localctx, 1);
        setState(215);
        exprBitInvert();
        break;
      }

      case CompilerGrammarParser::TokMinus: {
        enterOuterAlt(_localctx, 2);
        setState(216);
        exprNegate();
        break;
      }

      case CompilerGrammarParser::TokExclamPoint: {
        enterOuterAlt(_localctx, 3);
        setState(217);
        exprLogNot();
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

//----------------- ExprBitInvertContext ------------------------------------------------------------------

CompilerGrammarParser::ExprBitInvertContext::ExprBitInvertContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::ExprBitInvertContext::TokBitInvert() {
  return getToken(CompilerGrammarParser::TokBitInvert, 0);
}

CompilerGrammarParser::ExprContext* CompilerGrammarParser::ExprBitInvertContext::expr() {
  return getRuleContext<CompilerGrammarParser::ExprContext>(0);
}


size_t CompilerGrammarParser::ExprBitInvertContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleExprBitInvert;
}

antlrcpp::Any CompilerGrammarParser::ExprBitInvertContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitExprBitInvert(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::ExprBitInvertContext* CompilerGrammarParser::exprBitInvert() {
  ExprBitInvertContext *_localctx = _tracker.createInstance<ExprBitInvertContext>(_ctx, getState());
  enterRule(_localctx, 42, CompilerGrammarParser::RuleExprBitInvert);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(220);
    match(CompilerGrammarParser::TokBitInvert);
    setState(221);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprNegateContext ------------------------------------------------------------------

CompilerGrammarParser::ExprNegateContext::ExprNegateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::ExprNegateContext::TokMinus() {
  return getToken(CompilerGrammarParser::TokMinus, 0);
}

CompilerGrammarParser::ExprContext* CompilerGrammarParser::ExprNegateContext::expr() {
  return getRuleContext<CompilerGrammarParser::ExprContext>(0);
}


size_t CompilerGrammarParser::ExprNegateContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleExprNegate;
}

antlrcpp::Any CompilerGrammarParser::ExprNegateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitExprNegate(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::ExprNegateContext* CompilerGrammarParser::exprNegate() {
  ExprNegateContext *_localctx = _tracker.createInstance<ExprNegateContext>(_ctx, getState());
  enterRule(_localctx, 44, CompilerGrammarParser::RuleExprNegate);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    match(CompilerGrammarParser::TokMinus);
    setState(224);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprLogNotContext ------------------------------------------------------------------

CompilerGrammarParser::ExprLogNotContext::ExprLogNotContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::ExprLogNotContext::TokExclamPoint() {
  return getToken(CompilerGrammarParser::TokExclamPoint, 0);
}

CompilerGrammarParser::ExprContext* CompilerGrammarParser::ExprLogNotContext::expr() {
  return getRuleContext<CompilerGrammarParser::ExprContext>(0);
}


size_t CompilerGrammarParser::ExprLogNotContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleExprLogNot;
}

antlrcpp::Any CompilerGrammarParser::ExprLogNotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitExprLogNot(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::ExprLogNotContext* CompilerGrammarParser::exprLogNot() {
  ExprLogNotContext *_localctx = _tracker.createInstance<ExprLogNotContext>(_ctx, getState());
  enterRule(_localctx, 46, CompilerGrammarParser::RuleExprLogNot);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(226);
    match(CompilerGrammarParser::TokExclamPoint);
    setState(227);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumExprContext ------------------------------------------------------------------

CompilerGrammarParser::NumExprContext::NumExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::NumExprContext::TokDecNum() {
  return getToken(CompilerGrammarParser::TokDecNum, 0);
}

tree::TerminalNode* CompilerGrammarParser::NumExprContext::TokHexNum() {
  return getToken(CompilerGrammarParser::TokHexNum, 0);
}

tree::TerminalNode* CompilerGrammarParser::NumExprContext::TokBinNum() {
  return getToken(CompilerGrammarParser::TokBinNum, 0);
}


size_t CompilerGrammarParser::NumExprContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleNumExpr;
}

antlrcpp::Any CompilerGrammarParser::NumExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitNumExpr(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::NumExprContext* CompilerGrammarParser::numExpr() {
  NumExprContext *_localctx = _tracker.createInstance<NumExprContext>(_ctx, getState());
  enterRule(_localctx, 48, CompilerGrammarParser::RuleNumExpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(229);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CompilerGrammarParser::TokDecNum)
      | (1ULL << CompilerGrammarParser::TokHexNum)
      | (1ULL << CompilerGrammarParser::TokBinNum))) != 0))) {
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

//----------------- IdentExprContext ------------------------------------------------------------------

CompilerGrammarParser::IdentExprContext::IdentExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CompilerGrammarParser::IdentNameContext* CompilerGrammarParser::IdentExprContext::identName() {
  return getRuleContext<CompilerGrammarParser::IdentNameContext>(0);
}

CompilerGrammarParser::IdentSlicedContext* CompilerGrammarParser::IdentExprContext::identSliced() {
  return getRuleContext<CompilerGrammarParser::IdentSlicedContext>(0);
}


size_t CompilerGrammarParser::IdentExprContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleIdentExpr;
}

antlrcpp::Any CompilerGrammarParser::IdentExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitIdentExpr(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::IdentExprContext* CompilerGrammarParser::identExpr() {
  IdentExprContext *_localctx = _tracker.createInstance<IdentExprContext>(_ctx, getState());
  enterRule(_localctx, 50, CompilerGrammarParser::RuleIdentExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(233);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(231);
      identName();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(232);
      identSliced();
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

//----------------- IdentNameContext ------------------------------------------------------------------

CompilerGrammarParser::IdentNameContext::IdentNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::IdentNameContext::TokIdent() {
  return getToken(CompilerGrammarParser::TokIdent, 0);
}


size_t CompilerGrammarParser::IdentNameContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleIdentName;
}

antlrcpp::Any CompilerGrammarParser::IdentNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitIdentName(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::IdentNameContext* CompilerGrammarParser::identName() {
  IdentNameContext *_localctx = _tracker.createInstance<IdentNameContext>(_ctx, getState());
  enterRule(_localctx, 52, CompilerGrammarParser::RuleIdentName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(235);
    match(CompilerGrammarParser::TokIdent);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentSlicedContext ------------------------------------------------------------------

CompilerGrammarParser::IdentSlicedContext::IdentSlicedContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CompilerGrammarParser::IdentSlicedContext::TokIdent() {
  return getToken(CompilerGrammarParser::TokIdent, 0);
}

CompilerGrammarParser::SliceContext* CompilerGrammarParser::IdentSlicedContext::slice() {
  return getRuleContext<CompilerGrammarParser::SliceContext>(0);
}


size_t CompilerGrammarParser::IdentSlicedContext::getRuleIndex() const {
  return CompilerGrammarParser::RuleIdentSliced;
}

antlrcpp::Any CompilerGrammarParser::IdentSlicedContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CompilerGrammarVisitor*>(visitor))
    return parserVisitor->visitIdentSliced(this);
  else
    return visitor->visitChildren(this);
}

CompilerGrammarParser::IdentSlicedContext* CompilerGrammarParser::identSliced() {
  IdentSlicedContext *_localctx = _tracker.createInstance<IdentSlicedContext>(_ctx, getState());
  enterRule(_localctx, 54, CompilerGrammarParser::RuleIdentSliced);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(237);
    match(CompilerGrammarParser::TokIdent);
    setState(238);
    slice();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool CompilerGrammarParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 15: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);
    case 16: return exprLogicalSempred(dynamic_cast<ExprLogicalContext *>(context), predicateIndex);
    case 17: return exprCompareSempred(dynamic_cast<ExprCompareContext *>(context), predicateIndex);
    case 18: return exprAddSubSempred(dynamic_cast<ExprAddSubContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CompilerGrammarParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CompilerGrammarParser::exprLogicalSempred(ExprLogicalContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CompilerGrammarParser::exprCompareSempred(ExprCompareContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 2);
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CompilerGrammarParser::exprAddSubSempred(ExprAddSubContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> CompilerGrammarParser::_decisionToDFA;
atn::PredictionContextCache CompilerGrammarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CompilerGrammarParser::_atn;
std::vector<uint16_t> CompilerGrammarParser::_serializedATN;

std::vector<std::string> CompilerGrammarParser::_ruleNames = {
  "program", "subProgram", "declModule", "declStruct", "declVarList", "declParameters", 
  "typeName", "slice", "scopedOuterStatements", "outerStatement", "listIdentNames", 
  "multiListModulePorts", "listModulePorts", "listPortParams", "portParam", 
  "expr", "exprLogical", "exprCompare", "exprAddSub", "exprMulDivModEtc", 
  "exprUnary", "exprBitInvert", "exprNegate", "exprLogNot", "numExpr", "identExpr", 
  "identName", "identSliced"
};

std::vector<std::string> CompilerGrammarParser::_literalNames = {
  "", "", "", "", "", "'+'", "'-'", "", "", "'~'", "", "", "", "'='", "'<-'", 
  "'.'", "','", "':'", "'::'", "'''", "'\"'", "';'", "'!'", "'('", "')'", 
  "'['", "']'", "'{'", "'}'", "'#'", "'module'", "'parameter'", "'localparam'", 
  "'input'", "'output'", "'logic'", "'interface'", "'struct'", "'public'", 
  "'private'", "'enum'", "'union'", "'task'", "'function'", "'package'", 
  "'$concat'", "'$replicate'", "'assign'", "'initial'", "'always_comb'", 
  "'always_seq'", "'posedge'", "'negedge'", "'if'", "'else'", "'for'", "'while'", 
  "'do'", "'switch'", "'switchx'", "'switchz'", "'case'", "'default'"
};

std::vector<std::string> CompilerGrammarParser::_symbolicNames = {
  "", "LexWhitespace", "LexLineComment", "TokOpLogical", "TokOpCompare", 
  "TokPlus", "TokMinus", "TokOpMulDivMod", "TokOpBitwise", "TokBitInvert", 
  "TokDecNum", "TokHexNum", "TokBinNum", "TokBlockingAssign", "TokNonBlockingAssign", 
  "TokPeriod", "TokComma", "TokColon", "TokScope", "TokApostrophe", "TokQuote", 
  "TokSemicolon", "TokExclamPoint", "TokLParen", "TokRParen", "TokLBracket", 
  "TokRBracket", "TokLBrace", "TokRBrace", "TokNumber", "TokKwModule", "TokKwParameter", 
  "TokKwLocalparam", "TokKwInput", "TokKwOutput", "TokKwLogic", "TokKwInterface", 
  "TokKwStruct", "TokKwPublic", "TokKwPrivate", "TokKwEnum", "TokKwUnion", 
  "TokKwTask", "TokKwFunction", "TokKwPackage", "TokKwDollarConcat", "TokKwDollarReplicate", 
  "TokKwAssign", "TokKwInitial", "TokKwAlwaysComb", "TokKwAlwaysSeq", "TokKwPosedge", 
  "TokKwNegedge", "TokKwIf", "TokKwElse", "TokKwFor", "TokKwWhile", "TokKwDo", 
  "TokKwSwitch", "TokKwSwitchx", "TokKwSwitchz", "TokKwCase", "TokKwDefault", 
  "TokIdent", "TokOther"
};

dfa::Vocabulary CompilerGrammarParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CompilerGrammarParser::_tokenNames;

CompilerGrammarParser::Initializer::Initializer() {
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
    0x3, 0x42, 0xf3, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 
    0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 
    0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x3, 0x2, 0x7, 0x2, 0x3c, 0xa, 
    0x2, 0xc, 0x2, 0xe, 0x2, 0x3f, 0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 
    0x43, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x7, 0x5, 0x52, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x55, 0xb, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x64, 
    0xa, 0x8, 0x3, 0x8, 0x5, 0x8, 0x67, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x71, 
    0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x74, 0xb, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x7c, 0xa, 0xb, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x81, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x84, 
    0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x7, 0xd, 0x89, 0xa, 0xd, 0xc, 
    0xd, 0xe, 0xd, 0x8c, 0xb, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 
    0x3, 0xf, 0x3, 0xf, 0x7, 0xf, 0x94, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0x97, 
    0xb, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x9d, 
    0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x7, 0x11, 0xa5, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 0xa8, 0xb, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x7, 
    0x12, 0xb0, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0xb3, 0xb, 0x12, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x7, 0x13, 0xbe, 0xa, 0x13, 0xc, 0x13, 0xe, 0x13, 0xc1, 
    0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 0xcc, 0xa, 0x14, 0xc, 
    0x14, 0xe, 0x14, 0xcf, 0xb, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 
    0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0xd8, 0xa, 0x15, 0x3, 
    0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0xdd, 0xa, 0x16, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0xec, 
    0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x2, 0x6, 0x20, 0x22, 0x24, 0x26, 0x1e, 0x2, 0x4, 0x6, 0x8, 0xa, 
    0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 
    0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x2, 
    0x4, 0x3, 0x2, 0x23, 0x24, 0x3, 0x2, 0xc, 0xe, 0x2, 0xed, 0x2, 0x3d, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x42, 0x3, 0x2, 0x2, 0x2, 0x6, 0x44, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x4b, 0x3, 0x2, 0x2, 0x2, 0xa, 0x59, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x5c, 0x3, 0x2, 0x2, 0x2, 0xe, 0x66, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0x68, 0x3, 0x2, 0x2, 0x2, 0x12, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x14, 0x7b, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x18, 0x85, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x90, 0x3, 0x2, 
    0x2, 0x2, 0x1e, 0x98, 0x3, 0x2, 0x2, 0x2, 0x20, 0x9e, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0xa9, 0x3, 0x2, 0x2, 0x2, 0x24, 0xb4, 0x3, 0x2, 0x2, 0x2, 
    0x26, 0xc2, 0x3, 0x2, 0x2, 0x2, 0x28, 0xd7, 0x3, 0x2, 0x2, 0x2, 0x2a, 
    0xdc, 0x3, 0x2, 0x2, 0x2, 0x2c, 0xde, 0x3, 0x2, 0x2, 0x2, 0x2e, 0xe1, 
    0x3, 0x2, 0x2, 0x2, 0x30, 0xe4, 0x3, 0x2, 0x2, 0x2, 0x32, 0xe7, 0x3, 
    0x2, 0x2, 0x2, 0x34, 0xeb, 0x3, 0x2, 0x2, 0x2, 0x36, 0xed, 0x3, 0x2, 
    0x2, 0x2, 0x38, 0xef, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3c, 0x5, 0x4, 0x3, 
    0x2, 0x3b, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3f, 0x3, 0x2, 0x2, 0x2, 
    0x3d, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3e, 
    0x3, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x40, 0x43, 
    0x5, 0x6, 0x4, 0x2, 0x41, 0x43, 0x5, 0x8, 0x5, 0x2, 0x42, 0x40, 0x3, 
    0x2, 0x2, 0x2, 0x42, 0x41, 0x3, 0x2, 0x2, 0x2, 0x43, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x44, 0x45, 0x7, 0x20, 0x2, 0x2, 0x45, 0x46, 0x5, 0x36, 0x1c, 
    0x2, 0x46, 0x47, 0x7, 0x19, 0x2, 0x2, 0x47, 0x48, 0x5, 0x18, 0xd, 0x2, 
    0x48, 0x49, 0x7, 0x1a, 0x2, 0x2, 0x49, 0x4a, 0x5, 0x12, 0xa, 0x2, 0x4a, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x7, 0x27, 0x2, 0x2, 0x4c, 0x4d, 
    0x5, 0x36, 0x1c, 0x2, 0x4d, 0x53, 0x7, 0x1d, 0x2, 0x2, 0x4e, 0x4f, 0x5, 
    0xa, 0x6, 0x2, 0x4f, 0x50, 0x7, 0x17, 0x2, 0x2, 0x50, 0x52, 0x3, 0x2, 
    0x2, 0x2, 0x51, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x52, 0x55, 0x3, 0x2, 0x2, 
    0x2, 0x53, 0x51, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x3, 0x2, 0x2, 0x2, 
    0x54, 0x56, 0x3, 0x2, 0x2, 0x2, 0x55, 0x53, 0x3, 0x2, 0x2, 0x2, 0x56, 
    0x57, 0x7, 0x1e, 0x2, 0x2, 0x57, 0x58, 0x7, 0x17, 0x2, 0x2, 0x58, 0x9, 
    0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x5, 0xe, 0x8, 0x2, 0x5a, 0x5b, 0x5, 
    0x16, 0xc, 0x2, 0x5b, 0xb, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x7, 0x1f, 
    0x2, 0x2, 0x5d, 0x5e, 0x7, 0x19, 0x2, 0x2, 0x5e, 0x5f, 0x5, 0x1c, 0xf, 
    0x2, 0x5f, 0x60, 0x7, 0x1a, 0x2, 0x2, 0x60, 0xd, 0x3, 0x2, 0x2, 0x2, 
    0x61, 0x63, 0x7, 0x25, 0x2, 0x2, 0x62, 0x64, 0x5, 0x10, 0x9, 0x2, 0x63, 
    0x62, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 0x2, 0x2, 0x64, 0x67, 
    0x3, 0x2, 0x2, 0x2, 0x65, 0x67, 0x5, 0x36, 0x1c, 0x2, 0x66, 0x61, 0x3, 
    0x2, 0x2, 0x2, 0x66, 0x65, 0x3, 0x2, 0x2, 0x2, 0x67, 0xf, 0x3, 0x2, 
    0x2, 0x2, 0x68, 0x69, 0x7, 0x1d, 0x2, 0x2, 0x69, 0x6a, 0x5, 0x20, 0x11, 
    0x2, 0x6a, 0x6b, 0x7, 0x13, 0x2, 0x2, 0x6b, 0x6c, 0x5, 0x20, 0x11, 0x2, 
    0x6c, 0x6d, 0x7, 0x1e, 0x2, 0x2, 0x6d, 0x11, 0x3, 0x2, 0x2, 0x2, 0x6e, 
    0x72, 0x7, 0x1d, 0x2, 0x2, 0x6f, 0x71, 0x5, 0x14, 0xb, 0x2, 0x70, 0x6f, 
    0x3, 0x2, 0x2, 0x2, 0x71, 0x74, 0x3, 0x2, 0x2, 0x2, 0x72, 0x70, 0x3, 
    0x2, 0x2, 0x2, 0x72, 0x73, 0x3, 0x2, 0x2, 0x2, 0x73, 0x75, 0x3, 0x2, 
    0x2, 0x2, 0x74, 0x72, 0x3, 0x2, 0x2, 0x2, 0x75, 0x76, 0x7, 0x1e, 0x2, 
    0x2, 0x76, 0x13, 0x3, 0x2, 0x2, 0x2, 0x77, 0x78, 0x5, 0xa, 0x6, 0x2, 
    0x78, 0x79, 0x7, 0x17, 0x2, 0x2, 0x79, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7a, 
    0x7c, 0x5, 0x8, 0x5, 0x2, 0x7b, 0x77, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7a, 
    0x3, 0x2, 0x2, 0x2, 0x7c, 0x15, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x82, 0x5, 
    0x36, 0x1c, 0x2, 0x7e, 0x7f, 0x7, 0x12, 0x2, 0x2, 0x7f, 0x81, 0x5, 0x36, 
    0x1c, 0x2, 0x80, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x81, 0x84, 0x3, 0x2, 0x2, 
    0x2, 0x82, 0x80, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x3, 0x2, 0x2, 0x2, 
    0x83, 0x17, 0x3, 0x2, 0x2, 0x2, 0x84, 0x82, 0x3, 0x2, 0x2, 0x2, 0x85, 
    0x8a, 0x5, 0x1a, 0xe, 0x2, 0x86, 0x87, 0x7, 0x12, 0x2, 0x2, 0x87, 0x89, 
    0x5, 0x1a, 0xe, 0x2, 0x88, 0x86, 0x3, 0x2, 0x2, 0x2, 0x89, 0x8c, 0x3, 
    0x2, 0x2, 0x2, 0x8a, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8b, 0x3, 0x2, 
    0x2, 0x2, 0x8b, 0x19, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8a, 0x3, 0x2, 0x2, 
    0x2, 0x8d, 0x8e, 0x9, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x5, 0xa, 0x6, 0x2, 
    0x8f, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x90, 0x95, 0x5, 0x1e, 0x10, 0x2, 0x91, 
    0x92, 0x7, 0x12, 0x2, 0x2, 0x92, 0x94, 0x5, 0x1e, 0x10, 0x2, 0x93, 0x91, 
    0x3, 0x2, 0x2, 0x2, 0x94, 0x97, 0x3, 0x2, 0x2, 0x2, 0x95, 0x93, 0x3, 
    0x2, 0x2, 0x2, 0x95, 0x96, 0x3, 0x2, 0x2, 0x2, 0x96, 0x1d, 0x3, 0x2, 
    0x2, 0x2, 0x97, 0x95, 0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x7, 0x21, 0x2, 
    0x2, 0x99, 0x9c, 0x5, 0x36, 0x1c, 0x2, 0x9a, 0x9b, 0x7, 0xf, 0x2, 0x2, 
    0x9b, 0x9d, 0x5, 0x20, 0x11, 0x2, 0x9c, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9c, 
    0x9d, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 
    0x8, 0x11, 0x1, 0x2, 0x9f, 0xa0, 0x5, 0x22, 0x12, 0x2, 0xa0, 0xa6, 0x3, 
    0x2, 0x2, 0x2, 0xa1, 0xa2, 0xc, 0x3, 0x2, 0x2, 0xa2, 0xa3, 0x7, 0x5, 
    0x2, 0x2, 0xa3, 0xa5, 0x5, 0x22, 0x12, 0x2, 0xa4, 0xa1, 0x3, 0x2, 0x2, 
    0x2, 0xa5, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa4, 0x3, 0x2, 0x2, 0x2, 
    0xa6, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa7, 0x21, 0x3, 0x2, 0x2, 0x2, 0xa8, 
    0xa6, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xaa, 0x8, 0x12, 0x1, 0x2, 0xaa, 0xab, 
    0x5, 0x24, 0x13, 0x2, 0xab, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xac, 0xad, 0xc, 
    0x3, 0x2, 0x2, 0xad, 0xae, 0x7, 0x6, 0x2, 0x2, 0xae, 0xb0, 0x5, 0x24, 
    0x13, 0x2, 0xaf, 0xac, 0x3, 0x2, 0x2, 0x2, 0xb0, 0xb3, 0x3, 0x2, 0x2, 
    0x2, 0xb1, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb2, 0x3, 0x2, 0x2, 0x2, 
    0xb2, 0x23, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb4, 
    0xb5, 0x8, 0x13, 0x1, 0x2, 0xb5, 0xb6, 0x5, 0x26, 0x14, 0x2, 0xb6, 0xbf, 
    0x3, 0x2, 0x2, 0x2, 0xb7, 0xb8, 0xc, 0x4, 0x2, 0x2, 0xb8, 0xb9, 0x7, 
    0x7, 0x2, 0x2, 0xb9, 0xbe, 0x5, 0x26, 0x14, 0x2, 0xba, 0xbb, 0xc, 0x3, 
    0x2, 0x2, 0xbb, 0xbc, 0x7, 0x8, 0x2, 0x2, 0xbc, 0xbe, 0x5, 0x26, 0x14, 
    0x2, 0xbd, 0xb7, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xba, 0x3, 0x2, 0x2, 0x2, 
    0xbe, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xbf, 
    0xc0, 0x3, 0x2, 0x2, 0x2, 0xc0, 0x25, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xbf, 
    0x3, 0x2, 0x2, 0x2, 0xc2, 0xc3, 0x8, 0x14, 0x1, 0x2, 0xc3, 0xc4, 0x5, 
    0x28, 0x15, 0x2, 0xc4, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 0xc, 0x4, 
    0x2, 0x2, 0xc6, 0xc7, 0x7, 0x9, 0x2, 0x2, 0xc7, 0xcc, 0x5, 0x28, 0x15, 
    0x2, 0xc8, 0xc9, 0xc, 0x3, 0x2, 0x2, 0xc9, 0xca, 0x7, 0xa, 0x2, 0x2, 
    0xca, 0xcc, 0x5, 0x28, 0x15, 0x2, 0xcb, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xcb, 
    0xc8, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xcb, 
    0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 0x3, 0x2, 0x2, 0x2, 0xce, 0x27, 0x3, 
    0x2, 0x2, 0x2, 0xcf, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xd8, 0x5, 0x2a, 
    0x16, 0x2, 0xd1, 0xd8, 0x5, 0x32, 0x1a, 0x2, 0xd2, 0xd8, 0x5, 0x34, 
    0x1b, 0x2, 0xd3, 0xd4, 0x7, 0x19, 0x2, 0x2, 0xd4, 0xd5, 0x5, 0x20, 0x11, 
    0x2, 0xd5, 0xd6, 0x7, 0x1a, 0x2, 0x2, 0xd6, 0xd8, 0x3, 0x2, 0x2, 0x2, 
    0xd7, 0xd0, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd7, 
    0xd2, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xd3, 0x3, 0x2, 0x2, 0x2, 0xd8, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0xd9, 0xdd, 0x5, 0x2c, 0x17, 0x2, 0xda, 0xdd, 0x5, 
    0x2e, 0x18, 0x2, 0xdb, 0xdd, 0x5, 0x30, 0x19, 0x2, 0xdc, 0xd9, 0x3, 
    0x2, 0x2, 0x2, 0xdc, 0xda, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdb, 0x3, 0x2, 
    0x2, 0x2, 0xdd, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xde, 0xdf, 0x7, 0xb, 0x2, 
    0x2, 0xdf, 0xe0, 0x5, 0x20, 0x11, 0x2, 0xe0, 0x2d, 0x3, 0x2, 0x2, 0x2, 
    0xe1, 0xe2, 0x7, 0x8, 0x2, 0x2, 0xe2, 0xe3, 0x5, 0x20, 0x11, 0x2, 0xe3, 
    0x2f, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe5, 0x7, 0x18, 0x2, 0x2, 0xe5, 0xe6, 
    0x5, 0x20, 0x11, 0x2, 0xe6, 0x31, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe8, 0x9, 
    0x3, 0x2, 0x2, 0xe8, 0x33, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xec, 0x5, 0x36, 
    0x1c, 0x2, 0xea, 0xec, 0x5, 0x38, 0x1d, 0x2, 0xeb, 0xe9, 0x3, 0x2, 0x2, 
    0x2, 0xeb, 0xea, 0x3, 0x2, 0x2, 0x2, 0xec, 0x35, 0x3, 0x2, 0x2, 0x2, 
    0xed, 0xee, 0x7, 0x41, 0x2, 0x2, 0xee, 0x37, 0x3, 0x2, 0x2, 0x2, 0xef, 
    0xf0, 0x7, 0x41, 0x2, 0x2, 0xf0, 0xf1, 0x5, 0x10, 0x9, 0x2, 0xf1, 0x39, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0x3d, 0x42, 0x53, 0x63, 0x66, 0x72, 0x7b, 
    0x82, 0x8a, 0x95, 0x9c, 0xa6, 0xb1, 0xbd, 0xbf, 0xcb, 0xcd, 0xd7, 0xdc, 
    0xeb, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

CompilerGrammarParser::Initializer CompilerGrammarParser::_init;
