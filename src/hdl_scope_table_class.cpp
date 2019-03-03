#include "hdl_scope_table_class.hpp"
#include "general_allocator_class.hpp"

namespace frost_hdl
{

SymbolTable* HdlScope::symbol_table()
{
	return nullptr;
}
HdlTypeTable* HdlScope::hdl_type_table()
{
	return nullptr;
}
HdlFunctionTable* HdlScope::hdl_function_table()
{
	return nullptr;
}
ParameterVars* HdlScope::parameter_vars()
{
	return nullptr;
}
HdlStatementTable* HdlScope::statement_table()
{
	return nullptr;
}
HdlType* HdlScope::hdl_type()
{
	return nullptr;
}
HdlFunction* HdlScope::hdl_function()
{
	return nullptr;
}


bool HdlScope::has_symbol_table()
{
	return (symbol_table() != nullptr);
}
bool HdlScope::has_hdl_type_table()
{
	return (hdl_type_table() != nullptr);
}
bool HdlScope::has_hdl_function_table()
{
	return (hdl_function_table() != nullptr);
}
bool HdlScope::has_parameter_vars()
{
	return (parameter_vars() != nullptr);
}
bool HdlScope::has_statement_table()
{
	return (statement_table() != nullptr);
}
bool HdlScope::has_hdl_type()
{
	return (hdl_type() != nullptr);
}
bool HdlScope::has_hdl_function()
{
	return (hdl_function() != nullptr);
}

// Force the constructors of the private variables to be inlined here.
HdlDeclModule::HdlDeclModule()
{
}
HdlDeclModule::HdlDeclModule(SymbolTable&& s_symbol_table,
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

HdlDeclStruct::HdlDeclStruct(HdlType&& s_hdl_type)
	: _hdl_type(save_hdl_type(std::move(s_hdl_type)))
{
}

HdlDeclClass::HdlDeclClass(HdlType&& s_hdl_type)
	: _hdl_type(save_hdl_type(std::move(s_hdl_type)))
{
}

HdlDeclEnum::HdlDeclEnum(HdlType&& s_hdl_type)
	: _hdl_type(save_hdl_type(std::move(s_hdl_type)))
{
}

HdlDeclPackage::HdlDeclPackage()
{
}
HdlDeclPackage::HdlDeclPackage(SymbolTable&& s_symbol_table,
	HdlTypeTable&& s_hdl_type_table,
	HdlFunctionTable&& s_hdl_function_table,
	ParameterVars&& s_parameter_vars)
	: _symbol_table(std::move(s_symbol_table)),
	_hdl_type_table(std::move(s_hdl_type_table)),
	_hdl_function_table(std::move(s_hdl_function_table)),
	_parameter_vars(std::move(s_parameter_vars))
{
}

HdlDeclFunction::HdlDeclFunction(HdlFunction&& s_hdl_function)
	: _hdl_function(save_hdl_function(std::move(s_hdl_function)))
{
}

} // namespace frost_hdl
