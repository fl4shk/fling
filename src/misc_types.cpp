#include "misc_types.hpp"
#include "gen_src/CompilerGrammarLexer.h"
#include "gen_src/CompilerGrammarParser.h"
#include "gen_src/CompilerGrammarVisitor.h"

#include "general_allocator_class.hpp"

namespace frost_hdl
{
SavedString construct_initial_type_ident_from_dim(SavedString base_ident,
	Expression* some_dim_expr)
{
	return dup_str(sconcat(*base_ident, "[",
		reinterpret_cast<uintptr_t>(some_dim_expr),
		"]"));
}

ReplaceSymsMap::ReplaceSymsMap()
{
}

ReplaceSymsMap::~ReplaceSymsMap()
{
}

SrcCodePos::SrcCodePos()
	: _ctx(nullptr)
{
}
SrcCodePos::SrcCodePos(antlr4::ParserRuleContext* s_ctx)
	: _ctx(s_ctx)
{
	auto tok = _ctx->getStart();
	_src_line = tok->getLine();
	_src_pos_in_line = tok->getCharPositionInLine();
}

SrcCodePos::~SrcCodePos()
{
}


} // namespace frost_hdl
