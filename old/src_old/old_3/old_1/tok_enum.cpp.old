#include "tok_enum.hpp"

namespace frost_hdl
{

#define X(ident, str) {Tok::ident, str},

const std::map<Tok, string> kw_dollar_tok_ident_map
= {
	LIST_OF_KW_DOLLAR_TOK(X)
};

const std::map<Tok, string> kw_tok_ident_map
= {
	LIST_OF_KW_NON_DOLLAR_TOK(X)
};

const std::map<Tok, string> tok_ident_map
= {
	LIST_OF_TOK(X)
};

#undef X

} // namespace frost_hdl
