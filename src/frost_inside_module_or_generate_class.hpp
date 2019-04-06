#ifndef src_frost_inside_module_or_generate_class_hpp
#define src_frost_inside_module_or_generate_class_hpp

// src/frost_inside_module_or_generate_class.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
#include "frost_function_class.hpp"
#include "frost_full_type_class.hpp"

namespace frost_hdl
{

class FrostInsideModuleOrGenerate
{
public:		// variables
	SymbolTable local_symbol_table;
	FrostLhsTypeTable frost_lhs_type_table;
	FrostFullTypeTable frost_full_type_table;
	FrostFunctionTable frost_function_table;
	FrostStatementTable frost_statement_table;
	FrostGenerateTable frost_generate_table;

public:		// functions
	FrostInsideModuleOrGenerate();

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostInsideModuleOrGenerate)
	virtual ~FrostInsideModuleOrGenerate();
};

} // namespace frost_hdl

#endif		// src_frost_inside_module_or_generate_class_hpp
