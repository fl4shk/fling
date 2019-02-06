
// Generated from CompilerGrammar.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "CompilerGrammarVisitor.h"


/**
 * This class provides an empty implementation of CompilerGrammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CompilerGrammarBaseVisitor : public CompilerGrammarVisitor {
public:

  virtual antlrcpp::Any visitProgram(CompilerGrammarParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubProgram(CompilerGrammarParser::SubProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclModule(CompilerGrammarParser::DeclModuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclStruct(CompilerGrammarParser::DeclStructContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclVarList(CompilerGrammarParser::DeclVarListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclParameters(CompilerGrammarParser::DeclParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeName(CompilerGrammarParser::TypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSlice(CompilerGrammarParser::SliceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitScopedOuterStatements(CompilerGrammarParser::ScopedOuterStatementsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOuterStatement(CompilerGrammarParser::OuterStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitListIdentNames(CompilerGrammarParser::ListIdentNamesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMultiListModulePorts(CompilerGrammarParser::MultiListModulePortsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitListModulePorts(CompilerGrammarParser::ListModulePortsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitListPortParams(CompilerGrammarParser::ListPortParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPortParam(CompilerGrammarParser::PortParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr(CompilerGrammarParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprLogical(CompilerGrammarParser::ExprLogicalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprCompare(CompilerGrammarParser::ExprCompareContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprAddSub(CompilerGrammarParser::ExprAddSubContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprMulDivModEtc(CompilerGrammarParser::ExprMulDivModEtcContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprUnary(CompilerGrammarParser::ExprUnaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprBitInvert(CompilerGrammarParser::ExprBitInvertContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprNegate(CompilerGrammarParser::ExprNegateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprLogNot(CompilerGrammarParser::ExprLogNotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumExpr(CompilerGrammarParser::NumExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentExpr(CompilerGrammarParser::IdentExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentName(CompilerGrammarParser::IdentNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentSliced(CompilerGrammarParser::IdentSlicedContext *ctx) override {
    return visitChildren(ctx);
  }


};

