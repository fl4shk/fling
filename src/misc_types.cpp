#include "misc_types.hpp"

#include "general_allocator_class.hpp"

namespace frost_hdl
{
SavedString construct_initial_type_ident_from_dim(SavedString base_ident,
	Expression* some_dim_expr)
{
	return dup_str(sconcat(*base_ident, "[",
		reinterpret_cast<uintptr_t>(some_dim_expr),
		"]"));
}



ReplaceSymsMap::ReplaceSymsMap()
{
}

ReplaceSymsMap::~ReplaceSymsMap()
{
}


} // namespace frost_hdl
