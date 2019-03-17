#ifndef src_frost_package_table_class_hpp
#define src_frost_package_table_class_hpp

// src/frost_package_table_class.hpp

#include "misc_includes.hpp"
#include "symbol_table_class.hpp"
#include "frost_function_table_class.hpp"
#include "frost_full_type_table_class.hpp"

namespace frost_hdl
{

class FrostPackage
{
private:		// variables
	SavedString _ident = nullptr;

	SymbolTable _symbol_table;
	FrostLhsTypeTable _frost_lhs_type_table;
	FrostFullTypeTable _frost_full_type_table;
	FrostFunctionTable _frost_function_table;

public:		// functions
	FrostPackage(SavedString s_ident);


	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostPackage);
	virtual ~FrostPackage();


	GEN_GETTER_BY_VAL(ident)

	GEN_GETTERS_BY_CON_REF_AND_REF(symbol_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(frost_lhs_type_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(frost_full_type_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(frost_function_table)
};

// "FrostPackage"s can't be nested.
class FrostPackageTable : public IdentToPointerTable<FrostPackage>
{
public:		// functions
	FrostPackageTable() = default;
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostPackageTable);
	virtual ~FrostPackageTable() = default;
};

} // namespace frost_hdl


#endif		// src_frost_package_table_class_hpp
