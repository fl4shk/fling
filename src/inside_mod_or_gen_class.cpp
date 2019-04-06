#include "inside_mod_or_gen_class.hpp"
#include "frost_module_class.hpp"
#include "frost_generate_class.hpp"

namespace frost_hdl
{

InsideModOrGen::InsideModOrGen()
{
}

InsideModOrGen::~InsideModOrGen()
{
}

Symbol* InsideModOrGen::find_symbol(SavedString some_name) const
{
	if (local_symbol_table.contains(some_name))
	{
		return local_symbol_table.at(some_name);
	}

	if (std::holds_alternative<FrostGenerate*>(_parent))
	{
		const auto& parent_of_parent = std::get<FrostGenerate*>(_parent)
			->parent();

		if (std::holds_alternative<FrostGenerate*>(parent_of_parent))
		{
			return std::get<FrostGenerate*>(parent_of_parent)
				->inside_mod_or_gen().find_symbol(some_name);
		}
		else if (std::holds_alternative<FrostModule*>(parent_of_parent))
		{
			return std::get<FrostModule*>(parent_of_parent)
				->inside_mod_or_gen().find_symbol(some_name);
		}
	}
	else if (std::holds_alternative<FrostModule*>(_parent))
	{
		return std::get<FrostModule*>(_parent)->find_symbol_in_top_scope
			(some_name);
	}

	printerr("InsideModOrGen::find_symbol():  Eek!\n");

	return nullptr;
}

} // namespace frost_hdl
