#include "hdl_module_table_class.hpp"

namespace frost_hdl
{

// Stick this in here so that things don't get inlined.
HdlModule::HdlModule()
{
}

HdlModule::~HdlModule()
{
}



Symbol* HdlModule::find_non_param_symbol(SavedString some_name) const
{
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


} // namespace frost_hdl
