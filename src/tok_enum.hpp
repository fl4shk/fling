#ifndef src_tok_enum_hpp
#define src_tok_enum_hpp

// src/tok_enum.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

#include "list_of_tok_defines.hpp"

enum class Tok
{
	#define X(ident, str) ident,
	LIST_OF_TOK(X)
	#undef X
};


extern const std::map<Tok, string> kw_dollar_tok_ident_map;
extern const std::map<Tok, string> kw_tok_ident_map;
extern const std::map<Tok, string> tok_ident_map;

} // namespace frost_hdl


#endif		// src_tok_enum_hpp
