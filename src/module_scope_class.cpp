#include "module_scope_class.hpp"
#include "frost_module_class.hpp"
#include "frost_generate_class.hpp"

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
	if (std::holds_alternative<FrostGenerate*>(_parent))
	{
		// We only need to do this here because, if the "_parent" is a
		// "FrostModule*", the "_parent"'s "find_symbol_in_top_scope()"
		// member function will do this for us.
		if (local_symbol_table.contains(some_name))
		{
			return local_symbol_table.at(some_name);
		}

		const auto& parent_of_parent = std::get<FrostGenerate*>(_parent)
			->parent();

		// I think this is right?
		if (std::holds_alternative<FrostGenerate*>(parent_of_parent))
		{
			return std::get<FrostGenerate*>(parent_of_parent)
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