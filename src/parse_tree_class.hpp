#ifndef src_parse_tree_class_hpp
#define src_parse_tree_class_hpp

// src/parse_tree_class.hpp

#include "misc_includes.hpp"
#include "lexer_class.hpp"

namespace frost_hdl
{

class ParseTree : public ParseTreeBase<SrcCodeChunk, Tok>
{
public:		// functions
};

} // namespace frost_hdl


#endif		// src_parse_tree_class_hpp
