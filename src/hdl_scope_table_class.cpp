#include "hdl_scope_table_class.hpp"

namespace frost_hdl
{

SymbolTable* HdlScope::symbol_table() const
{
	return nullptr;
}
HdlTypeTable* HdlScope::hdl_type_table() const
{
	return nullptr;
}
HdlFunction* HdlScope::hdl_function_table() const
{
	return nullptr;
}
OrderedIdentToPointerTable<Symbol>* HdlScope::parameter_vars() const
{
	return nullptr;
}
HdlStatementTable* HdlScope::statement_table() const
{
	return nullptr;
}
HdlType* HdlScope::hdl_type() const
{
	return nullptr;
}

HdlModule::HdlModule()
{
}


} // namespace frost_hdl
