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
ParameterVars* HdlScope::parameter_vars() const
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

// Force the constructors of the private variables to be inlined here.
HdlModule::HdlModule()
{
}
HdlModule::HdlModule(SymbolTable&& s_symbol_table,
	HdlTypeTable&& s_hdl_type_table,
	HdlFunctionTable&& s_hdl_function_table,
	ParameterVars&& s_parameter_vars,
	HdlStatementTable&& s_statement_table)
	: _symbol_table(std::move(s_symbol_table)),
	_hdl_type_table(std::move(s_hdl_type_table)),
	_hdl_function_table(std::move(s_hdl_function_table)),
	_parameter_vars(std::move(s_parameter_vars)),
	_statement_table(std::move(s_statement_table))
{
}

HdlStruct::HdlStruct()
{
}
HdlStruct::HdlStruct(HdlType&& s_hdl_type)
	: _hdl_type(std::move(s_hdl_type))
{
}

HdlClass::HdlClass()
{
}
HdlClass::HdlClass(HdlType&& s_hdl_type)
	: _hdl_type(std::move(s_hdl_type))
{
}

HdlEnum::HdlEnum()
{
}
HdlEnum::HdlEnum(HdlType&& s_hdl_type)
	: _hdl_type(std::move(s_hdl_type))
{
}

HdlPackage::HdlPackage()
{
}
HdlPackage::HdlPackage(SymbolTable&& s_symbol_table,
	HdlTypeTable&& s_hdl_type_table,
	HdlFunctionTable&& s_hdl_function_table,
	ParameterVars&& s_parameter_vars)
	: _symbol_table(std::move(s_symbol_table)),
	_hdl_type_table(std::move(s_hdl_type_table)),
	_hdl_function_table(std::move(s_hdl_function_table)),
	_parameter_vars(std::move(s_parameter_vars))
{
}

} // namespace frost_hdl
