#include "frost_module_table_class.hpp"

namespace frost_hdl
{

// Stick this in here so that things don't get inlined.
FrostModule::FrostModule(const SrcCodePos& s_src_code_pos,
	SavedString s_ident)
{
	_src_code_pos = s_src_code_pos;
	_ident = s_ident;
}

FrostModule::~FrostModule()
{
}

Symbol* FrostModule::find_symbol(SavedString some_name) const
{
	if (parameter_vars().contains(some_name))
	{
		return parameter_vars().find(some_name);
	}
	if (input_symbol_table().contains(some_name))
	{
		return input_symbol_table().at(some_name);
	}
	if (output_symbol_table().contains(some_name))
	{
		return output_symbol_table().at(some_name);
	}
	if (inout_symbol_table().contains(some_name))
	{
		return inout_symbol_table().at(some_name);
	}
	if (local_symbol_table().contains(some_name))
	{
		return local_symbol_table().at(some_name);
	}

	return nullptr;
}


//Symbol* FrostModule::find_non_param_symbol(SavedString some_name) const
//{
//	if (input_symbol_table().contains(some_name))
//	{
//		return input_symbol_table().at(some_name);
//	}
//	if (output_symbol_table().contains(some_name))
//	{
//		return output_symbol_table().at(some_name);
//	}
//	if (inout_symbol_table().contains(some_name))
//	{
//		return inout_symbol_table().at(some_name);
//	}
//	if (local_symbol_table().contains(some_name))
//	{
//		return local_symbol_table().at(some_name);
//	}
//
//	return nullptr;
//}


} // namespace frost_hdl
