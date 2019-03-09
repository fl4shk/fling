#ifndef src_hdl_module_table_class_hpp
#define src_hdl_module_table_class_hpp

// src/hdl_module_table_class.hpp

#include "misc_includes.hpp"
//#include "hdl_statement_table_class.hpp"
#include "symbol_table_class.hpp"
#include "hdl_function_table_class.hpp"
#include "hdl_full_type_table_class.hpp"

namespace frost_hdl
{

// Class representing a module from HDL land (not a C++20 module).
class HdlModule
{
private:		// variables
	SavedString _ident = nullptr;
	ParameterVars _parameter_vars;
	SymbolTable _input_symbol_table, _output_symbol_table,
		_inout_symbol_table, _local_symbol_table;

	HdlLhsTypeTable _hdl_lhs_type_table;
	HdlFullTypeTable _hdl_full_type_table;

	HdlFunctionTable _hdl_function_table;

	HdlStatementTable _statement_table;

	//HdlPackageImportTable _hdl_package_import_table;

public:		// functions
	HdlModule();


	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlModule, delete, default);

	virtual ~HdlModule();


	Symbol* find_non_param_symbol(SavedString some_name) const;

	inline bool contains_non_param_symbol(SavedString some_name) const
	{
		return (find_non_param_symbol(some_name) != nullptr);
	}


	GEN_GETTER_AND_SETTER_BY_VAL(ident)

	GEN_GETTER_BY_CON_REF(input_symbol_table)
	GEN_GETTER_BY_REF(input_symbol_table)
	GEN_GETTER_BY_CON_REF(output_symbol_table)
	GEN_GETTER_BY_REF(output_symbol_table)
	GEN_GETTER_BY_CON_REF(inout_symbol_table)
	GEN_GETTER_BY_REF(inout_symbol_table)
	GEN_GETTER_BY_CON_REF(local_symbol_table)
	GEN_GETTER_BY_REF(local_symbol_table)


	GEN_GETTER_BY_CON_REF(hdl_lhs_type_table)
	GEN_GETTER_BY_REF(hdl_lhs_type_table)

	GEN_GETTER_BY_CON_REF(hdl_full_type_table)
	GEN_GETTER_BY_REF(hdl_full_type_table)

	GEN_GETTER_BY_CON_REF(hdl_function_table)
	GEN_GETTER_BY_REF(hdl_function_table)

	GEN_GETTER_BY_CON_REF(parameter_vars)
	GEN_GETTER_BY_REF(parameter_vars)

	GEN_GETTER_BY_CON_REF(statement_table)
	GEN_GETTER_BY_REF(statement_table)
};

// Nested "module"s are not permitted, and they are always at global scope.
// This class holds *only* the "module"s that were in the Frost HDL source
// code, and not the ones generated at compile time.
class HdlModuleTable : public IdentToPointerTable<HdlModule>
{
public:		// functions
	HdlModuleTable() = default;
	virtual ~HdlModuleTable() = default;
};

} // namespace frost_hdl

#endif		// src_hdl_module_table_class_hpp
