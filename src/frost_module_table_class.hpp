#ifndef src_frost_module_table_class_hpp
#define src_frost_module_table_class_hpp

// src/frost_module_table_class.hpp

#include "misc_includes.hpp"
//#include "frost_statement_table_class.hpp"
#include "symbol_table_class.hpp"
#include "frost_function_table_class.hpp"
#include "frost_full_type_table_class.hpp"
#include "in_scope_errwarn_base_class.hpp"

namespace frost_hdl
{

// Class representing a module from HDL land (not a C++20 module).
class FrostModule : public InScopeErrWarnBase<SrcCodePos>
{
private:		// variables
	SrcCodePos _src_code_pos;
	SavedString _ident = nullptr;
	ListVars _parameter_vars;
	SymbolTable _input_symbol_table, _output_symbol_table,
		_inout_symbol_table, _local_symbol_table;

	FrostLhsTypeTable _frost_lhs_type_table;
	FrostFullTypeTable _frost_full_type_table;

	FrostFunctionTable _frost_function_table;

	FrostStatementTable _frost_statement_table;

	//FrostPackageImportTable _frost_package_import_table;

public:		// functions
	FrostModule(const SrcCodePos& s_src_code_pos, SavedString s_ident);


	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostModule);

	virtual ~FrostModule();


	Symbol* find_symbol(SavedString some_name) const;
	inline bool contains_symbol(SavedString some_name) const
	{
		return (find_symbol(some_name) != nullptr);
	}
	//Symbol* find_non_param_symbol(SavedString some_name) const;

	//inline bool contains_non_param_symbol(SavedString some_name) const
	//{
	//	return (find_non_param_symbol(some_name) != nullptr);
	//}


	std::string scope_type_str() const
	{
		return std::string("module");
	}

	GEN_GETTER_BY_CON_REF(src_code_pos)
	GEN_GETTER_BY_VAL(ident)

	GEN_GETTERS_BY_CON_REF_AND_REF(parameter_vars)
	GEN_GETTERS_BY_CON_REF_AND_REF(input_symbol_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(output_symbol_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(inout_symbol_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(local_symbol_table)



	GEN_GETTERS_BY_CON_REF_AND_REF(frost_lhs_type_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(frost_full_type_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(frost_function_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(frost_statement_table)
};

// Nested "module"s are not permitted, and they are always at global scope.
class FrostModuleTable : public IdentToPointerTable<FrostModule>
{
public:		// functions
	FrostModuleTable() = default;
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostModuleTable);
	virtual ~FrostModuleTable() = default;
};

} // namespace frost_hdl

#endif		// src_frost_module_table_class_hpp
