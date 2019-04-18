#include "frost_module_class.hpp"

namespace frost_hdl
{

// Stick this in a .cpp file so that the large member variables don't have
// their constructor calls inlined.
FrostModule::FrostModule(const SrcCodePos& s_src_code_pos,
	SavedString s_ident)
	: HasSrcCodePosAndIdentBase(s_src_code_pos, s_ident)
{
	// This caused the "_module_scope" to think this was on the stack
	//_module_scope = ModuleScope(this);
}

FrostModule::~FrostModule()
{
}

Symbol* FrostModule::find_symbol_in_top_scope(SavedString some_name) const
{
	//if (parameter_symbol_table().contains(some_name))
	//{
	//	return parameter_symbol_table().find(some_name);
	//}
	if (parameter_symbol_table().contains(some_name))
	{
		return parameter_symbol_table().at(some_name);
	}
	if (input_symbol_table().contains(some_name))
	{
		return input_symbol_table().at(some_name);
	}
	if (output_symbol_table().contains(some_name))
	{
		return output_symbol_table().at(some_name);
	}
	//if (inout_symbol_table().contains(some_name))
	//{
	//	return inout_symbol_table().at(some_name);
	//}
	if (_module_scope.local_symbol_table.contains(some_name))
	{
		return _module_scope.local_symbol_table.at(some_name);
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
