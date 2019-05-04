#include "symbol_class.hpp"

namespace frost_hdl
{


Symbol::Symbol()
{
}

Symbol::Symbol(const Ident& s_ident, AstNode* s_decl_ast_node)
	: _ident(s_ident), _decl_ast_node(s_decl_ast_node)
{
}

Symbol::~Symbol()
{
}


} // namespace frost_hdl
