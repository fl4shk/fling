#include "module_scope_class.hpp"
#include "frost_module_class.hpp"
#include "frost_generate_block_classes.hpp"

namespace frost_hdl
{

ModuleScope::ModuleScope()
{
}

ModuleScope::~ModuleScope()
{
}

Symbol* ModuleScope::find_symbol(SavedString some_name) const
{
	if (std::holds_alternative<FrostGenerateBlockInModule*>(_parent))
	{
		// We only need to do this here because, if the "_parent" is a
		// "FrostModule*", the "_parent"'s "find_symbol_in_top_scope()"
		// member function will do this for us.
		if (local_symbol_table.contains(some_name))
		{
			return local_symbol_table.at(some_name);
		}

		auto parent_of_parent = std::get<FrostGenerateBlockInModule*>
			(_parent)->parent();

		// I think this is right?
		if (std::holds_alternative<FrostGenerateBlockInModule*>
			(parent_of_parent))
		{
			return std::get<FrostGenerateBlockInModule*>(parent_of_parent)
				->module_scope().find_symbol(some_name);
		}
		else if (std::holds_alternative<FrostModule*>(parent_of_parent))
		{
			return std::get<FrostModule*>(parent_of_parent)
				->module_scope().find_symbol(some_name);
		}

		// This should *never* happen.  If it does, we spit out an error.
		printerr("Error:  ModuleScope::find_symbol():  Eek 0!\n");
		exit(1);
	}
	else if (std::holds_alternative<FrostModule*>(_parent))
	{
		return std::get<FrostModule*>(_parent)->find_symbol_in_top_scope
			(some_name);
	}

	// This should *never* happen.  If it does, we spit out an error.
	printerr("Error:  ModuleScope::find_symbol():  Eek 1!\n");
	exit(1);

	return nullptr;
}

} // namespace frost_hdl
