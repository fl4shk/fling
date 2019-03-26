#include "frost_function_class.hpp"

namespace frost_hdl
{

FrostFunction::FrostFunction()
{
}

FrostFunction::FrostFunction(const SrcCodePos& s_src_code_pos,
	SavedString s_ident, bool s_is_task, bool s_is_constexpr,
	FrostStatementTable&& s_frost_statement_table, FrostModule* s_context)
{
	_src_code_pos = s_src_code_pos;
	_ident = s_ident;
	_is_task = s_is_task;
	_is_constexpr = s_is_constexpr;
	_frost_statement_table = std::move(s_frost_statement_table);
}
FrostFunction::FrostFunction(const SrcCodePos& s_src_code_pos,
	SavedString s_ident, bool s_is_task, bool s_is_constexpr,
	FrostStatementTable&& s_frost_statement_table, FrostPackage* s_context)
{
	_src_code_pos = s_src_code_pos;
	_ident = s_ident;
	_is_task = s_is_task;
	_is_constexpr = s_is_constexpr;
	_frost_statement_table = std::move(s_frost_statement_table);
}
FrostFunction::FrostFunction(const SrcCodePos& s_src_code_pos,
	SavedString s_ident, bool s_is_task, bool s_is_constexpr,
	FrostStatementTable&& s_frost_statement_table, FrostLhsType* s_context)
{
	_src_code_pos = s_src_code_pos;
	_ident = s_ident;
	_is_task = s_is_task;
	_is_constexpr = s_is_constexpr;
	_frost_statement_table = std::move(s_frost_statement_table);
}

FrostFunction::~FrostFunction()
{
}

} // namespace frost_hdl
