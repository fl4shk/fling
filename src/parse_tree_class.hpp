#ifndef src_parse_tree_class_hpp
#define src_parse_tree_class_hpp

// src/parse_tree_class.hpp

#include "misc_includes.hpp"
#include "lexer_class.hpp"

namespace frost_hdl
{

class ParseTree final : public ParseTreeBase<SrcCodeChunk, Tok>
{
public:		// functions
	inline ParseTree(const SrcCodeChunk& s_src_code_chunk)
		: ParseTreeBase<SrcCodeChunk, Tok>(s_src_code_chunk)
	{
	}
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ParseTree);
	inline ~ParseTree() = default;
};

} // namespace frost_hdl


#endif		// src_parse_tree_class_hpp
