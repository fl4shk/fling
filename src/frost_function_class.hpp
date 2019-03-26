#ifndef src_frost_function_class_hpp
#define src_frost_function_class_hpp

// src/frost_function_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "general_allocator_class.hpp"
#include "ident_table_classes.hpp"
#include "frost_statement_table_class.hpp"

namespace frost_hdl
{

class FrostModule;
class FrostPackage;
class FrostLhsType;

// Barebones for now...
// This will eventually be used for both "function"s and "task"s.
class FrostFunction
{
private:		// variables
	SrcCodePos _src_code_pos;
	SavedString _ident = nullptr;
	bool _is_task = false;
	bool _is_constexpr = false;

	FrostStatementTable _frost_statement_table;

	std::variant<FrostModule*, FrostPackage*, FrostLhsType*> _context;


public:		// functions
	FrostFunction();

	FrostFunction(const SrcCodePos& s_src_code_pos, SavedString s_ident,
		bool s_is_task, bool s_is_constexpr,
		FrostStatementTable&& s_frost_statement_table,
		FrostModule* s_context);
	FrostFunction(const SrcCodePos& s_src_code_pos, SavedString s_ident,
		bool s_is_task, bool s_is_constexpr,
		FrostStatementTable&& s_frost_statement_table,
		FrostPackage* s_context);
	FrostFunction(const SrcCodePos& s_src_code_pos, SavedString s_ident,
		bool s_is_task, bool s_is_constexpr,
		FrostStatementTable&& s_frost_statement_table,
		FrostLhsType* s_context);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostFunction);
	virtual ~FrostFunction();

	inline bool in_frost_module() const
	{
		return std::holds_alternative<FrostModule*>(_context);
	}
	inline bool in_frost_package() const
	{
		return std::holds_alternative<FrostPackage*>(_context);
	}
	inline bool in_frost_lhs_type() const
	{
		return std::holds_alternative<FrostLhsType*>(_context);
	}



	GEN_GETTER_BY_CON_REF(src_code_pos)
	GEN_GETTER_BY_VAL(ident)
	GEN_GETTER_BY_VAL(is_task)
	GEN_GETTER_BY_VAL(is_constexpr)
};

//// "FrostFunctionTable" isn't scoped because scoping information is
//// stored in the "FrostScopeTable" class.
//class FrostFunctionTable : public IdentToPointerTable<FrostFunction>
//{
//public:		// functions
//	FrostFunctionTable() = default;
//	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostFunctionTable);
//	virtual ~FrostFunctionTable() = default;
//};

} // namespace frost_hdl


#endif		// src_frost_function_class_hpp
