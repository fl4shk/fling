
// Generated from CompilerGrammar.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "CompilerGrammarParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CompilerGrammarParser.
 */
class  CompilerGrammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CompilerGrammarParser.
   */
    virtual antlrcpp::Any visitProgram(CompilerGrammarParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitSubProgram(CompilerGrammarParser::SubProgramContext *context) = 0;

    virtual antlrcpp::Any visitDeclModule(CompilerGrammarParser::DeclModuleContext *context) = 0;

    virtual antlrcpp::Any visitDeclStruct(CompilerGrammarParser::DeclStructContext *context) = 0;

    virtual antlrcpp::Any visitDeclVarList(CompilerGrammarParser::DeclVarListContext *context) = 0;

    virtual antlrcpp::Any visitDeclParameters(CompilerGrammarParser::DeclParametersContext *context) = 0;

    virtual antlrcpp::Any visitTypeName(CompilerGrammarParser::TypeNameContext *context) = 0;

    virtual antlrcpp::Any visitSlice(CompilerGrammarParser::SliceContext *context) = 0;

    virtual antlrcpp::Any visitScopedOuterStatements(CompilerGrammarParser::ScopedOuterStatementsContext *context) = 0;

    virtual antlrcpp::Any visitOuterStatement(CompilerGrammarParser::OuterStatementContext *context) = 0;

    virtual antlrcpp::Any visitListIdentNames(CompilerGrammarParser::ListIdentNamesContext *context) = 0;

    virtual antlrcpp::Any visitMultiListModulePorts(CompilerGrammarParser::MultiListModulePortsContext *context) = 0;

    virtual antlrcpp::Any visitListModulePorts(CompilerGrammarParser::ListModulePortsContext *context) = 0;

    virtual antlrcpp::Any visitListPortParams(CompilerGrammarParser::ListPortParamsContext *context) = 0;

    virtual antlrcpp::Any visitPortParam(CompilerGrammarParser::PortParamContext *context) = 0;

    virtual antlrcpp::Any visitExpr(CompilerGrammarParser::ExprContext *context) = 0;

    virtual antlrcpp::Any visitExprLogical(CompilerGrammarParser::ExprLogicalContext *context) = 0;

    virtual antlrcpp::Any visitExprCompare(CompilerGrammarParser::ExprCompareContext *context) = 0;

    virtual antlrcpp::Any visitExprAddSub(CompilerGrammarParser::ExprAddSubContext *context) = 0;

    virtual antlrcpp::Any visitExprMulDivModEtc(CompilerGrammarParser::ExprMulDivModEtcContext *context) = 0;

    virtual antlrcpp::Any visitExprUnary(CompilerGrammarParser::ExprUnaryContext *context) = 0;

    virtual antlrcpp::Any visitExprBitInvert(CompilerGrammarParser::ExprBitInvertContext *context) = 0;

    virtual antlrcpp::Any visitExprNegate(CompilerGrammarParser::ExprNegateContext *context) = 0;

    virtual antlrcpp::Any visitExprLogNot(CompilerGrammarParser::ExprLogNotContext *context) = 0;

    virtual antlrcpp::Any visitNumExpr(CompilerGrammarParser::NumExprContext *context) = 0;

    virtual antlrcpp::Any visitIdentExpr(CompilerGrammarParser::IdentExprContext *context) = 0;

    virtual antlrcpp::Any visitIdentName(CompilerGrammarParser::IdentNameContext *context) = 0;

    virtual antlrcpp::Any visitIdentSliced(CompilerGrammarParser::IdentSlicedContext *context) = 0;


};

