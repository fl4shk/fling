#ifndef src_frost_module_class_hpp
#define src_frost_module_class_hpp

// src/frost_module_class.hpp

#include "misc_includes.hpp"
//#include "frost_statement_class.hpp"
#include "symbol_class.hpp"
#include "frost_function_class.hpp"
#include "frost_full_type_class.hpp"
//#include "in_scope_errwarn_base_class.hpp"

#include "has_src_code_pos_base_classes.hpp"
#include "inside_mod_or_gen_class.hpp"

namespace frost_hdl
{

// Class representing a module from HDL land (not a C++20 module).
// Nested "module"s are not permitted, and they are always at global scope.
class FrostModule : public HasSrcCodePosAndIdentBase
{
private:		// variables
	SymbolTable _parameter_symbol_table, _input_symbol_table,
		_output_symbol_table;

	InsideModOrGen _inside_mod_or_gen;

	//FrostLhsTypeTable _frost_lhs_type_table;
	//FrostFullTypeTable _frost_full_type_table;

	//FrostFunctionTable _frost_function_table;

	//FrostStatementTable _frost_statement_table;

	//// Used by the "ParseTreeVisitor" purely to determine whether or not
	//// this "module" is defined in terms of itself.
	//std::set<FrostModule*> _contained_module_instance_types;


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


	//std::string scope_type_str() const
	//{
	//	return std::string("module");
	//}

	GEN_GETTERS_BY_CON_REF_AND_REF(parameter_symbol_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(input_symbol_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(output_symbol_table)
	////GEN_GETTERS_BY_CON_REF_AND_REF(inout_symbol_table)
	//GEN_GETTERS_BY_CON_REF_AND_REF(local_symbol_table)


	//GEN_GETTERS_BY_CON_REF_AND_REF(frost_lhs_type_table)
	//GEN_GETTERS_BY_CON_REF_AND_REF(frost_full_type_table)
	//GEN_GETTERS_BY_CON_REF_AND_REF(frost_function_table)
	//GEN_GETTERS_BY_CON_REF_AND_REF(frost_statement_table)
	////GEN_GETTERS_BY_CON_REF_AND_REF(contained_module_instance_types)
};


} // namespace frost_hdl

#endif		// src_frost_module_class_hpp
