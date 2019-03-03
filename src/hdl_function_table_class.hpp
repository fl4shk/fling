#ifndef src_hdl_function_table_class_hpp
#define src_hdl_function_table_class_hpp

// src/hdl_function_table_class.hpp

#include "misc_includes.hpp"
#include "general_allocator_class.hpp"
#include "ident_table_classes.hpp"

namespace frost_hdl
{

// Barebones for now...
class HdlFunction
{
private:		// variables
	SavedString _ident = nullptr;

public:		// functions
	HdlFunction() = default;

	HdlFunction(SavedString s_ident);

	virtual ~HdlFunction() = default;


	GEN_GETTER_BY_VAL(ident)
};

// "HdlFunctionTable" isn't scoped because scoping information is stored
// in the "HdlScopeTable" class.
class HdlFunctionTable : public IdentToPointerTable<HdlFunction>
{
public:		// functions
	HdlFunctionTable() = default;
	virtual ~HdlFunctionTable() = default;
};

} // namespace frost_hdl


#endif		// src_hdl_function_table_class_hpp
