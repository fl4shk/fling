#ifndef src_hdl_function_table_class_hpp
#define src_hdl_function_table_class_hpp

// src/hdl_function_table_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "general_allocator_class.hpp"
#include "ident_table_classes.hpp"
#include "hdl_statement_table_class.hpp"

namespace frost_hdl
{

class HdlModule;
//class HdlPackage;
class HdlLhsType;

// Barebones for now...
class HdlFunction
{
private:		// variables
	SavedString _ident = nullptr;
	bool _is_task = false;

	HdlStatementTable _hdl_statement_table;

	//std::variant<HdlModule*, HdlPackage*, HdlLhsType*> _context;


public:		// functions
	HdlFunction() = default;

	HdlFunction(SavedString s_ident, bool s_is_task,
		HdlStatementTable&& s_hdl_statement_table, HdlModule* s_context);
	//HdlFunction(SavedString s_ident, bool s_is_task,
	//	HdlStatementTable&& s_hdl_statement_table, HdlPackage* s_context);
	HdlFunction(SavedString s_ident, bool s_is_task,
		HdlStatementTable&& s_hdl_statement_table, HdlLhsType* s_context);

	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlFunction, delete, default);
	virtual ~HdlFunction();

	//bool in_hdl_module() const;
	//bool in_hdl_package() const;
	//bool in_hdl_lhs_type() const;


	GEN_GETTER_BY_VAL(ident)
	GEN_GETTER_BY_VAL(is_task)
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
