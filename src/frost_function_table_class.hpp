#ifndef src_frost_function_table_class_hpp
#define src_frost_function_table_class_hpp

// src/frost_function_table_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "general_allocator_class.hpp"
#include "ident_table_classes.hpp"
#include "frost_statement_table_class.hpp"

namespace frost_hdl
{

class FrostModule;
//class FrostPackage;
class FrostLhsType;

// Barebones for now...
class FrostFunction
{
private:		// variables
	SavedString _ident = nullptr;
	bool _is_task = false;

	FrostStatementTable _frost_statement_table;

	//std::variant<FrostModule*, FrostPackage*, FrostLhsType*> _context;


public:		// functions
	FrostFunction() = default;

	FrostFunction(SavedString s_ident, bool s_is_task,
		FrostStatementTable&& s_frost_statement_table,
		FrostModule* s_context);
	//FrostFunction(SavedString s_ident, bool s_is_task,
	//	FrostStatementTable&& s_frost_statement_table,
	//	FrostPackage* s_context);
	FrostFunction(SavedString s_ident, bool s_is_task,
		FrostStatementTable&& s_frost_statement_table,
		FrostLhsType* s_context);

	GEN_CM_CONSTRUCTORS_AND_ASSIGN(FrostFunction, delete, default);
	virtual ~FrostFunction();

	//bool in_frost_module() const;
	//bool in_frost_package() const;
	//bool in_frost_lhs_type() const;


	GEN_GETTER_BY_VAL(ident)
	GEN_GETTER_BY_VAL(is_task)
};

// "FrostFunctionTable" isn't scoped because scoping information is
// stored in the "FrostScopeTable" class.
class FrostFunctionTable : public IdentToPointerTable<FrostFunction>
{
public:		// functions
	FrostFunctionTable() = default;
	GEN_CM_CONSTRUCTORS_AND_ASSIGN(FrostFunctionTable, delete, default);
	virtual ~FrostFunctionTable() = default;
};

} // namespace frost_hdl


#endif		// src_frost_function_table_class_hpp
