#include "frost_module_instance_class.hpp"

namespace frost_hdl
{

ModuleInstConnection::ModuleInstConnection
	(const SrcCodePos& s_src_code_pos, Symbol* s_symbol,
	Expression* s_ident_expr)
	: HasSrcCodePosBase(s_src_code_pos), _symbol(s_symbol),
	_ident_expr(s_ident_expr)
{
}
ModuleInstConnection::~ModuleInstConnection()
{
}

FrostModuleInstance::FrostModuleInstance
	(const SrcCodePos& s_src_code_pos, SavedString s_ident,
	ModuleScope* s_where, FrostModule* s_what)
	: HasSrcCodePosBase(s_src_code_pos), _ident(s_ident), _where(s_where),
	_what(s_what)
{
}

FrostModuleInstance::~FrostModuleInstance()
{
}

SavedString FrostModuleInstance::ident() const
{
	if (_ident == nullptr)
	{
		std::string to_dup;

		return dup_str(sconcat("\\", *construct_str_from_pointer(_what),
			".", *construct_str_from_pointer(_where)));
	}
	else
	{
		return _ident;
	}
}

} // namespace frost_hdl
