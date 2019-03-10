#include "frost_function_table_class.hpp"

namespace frost_hdl
{

FrostFunction::FrostFunction(SavedString s_ident, bool s_is_task,
	FrostStatementTable&& s_frost_statement_table, FrostModule* s_context)
{
	_ident = s_ident;
	_is_task = s_is_task;
	_frost_statement_table = std::move(s_frost_statement_table);
}
FrostFunction::FrostFunction(SavedString s_ident, bool s_is_task,
	FrostStatementTable&& s_frost_statement_table, FrostPackage* s_context)
{
	_ident = s_ident;
	_is_task = s_is_task;
	_frost_statement_table = std::move(s_frost_statement_table);
}
FrostFunction::FrostFunction(SavedString s_ident, bool s_is_task,
	FrostStatementTable&& s_frost_statement_table, FrostLhsType* s_context)
{
	_ident = s_ident;
	_is_task = s_is_task;
	_frost_statement_table = std::move(s_frost_statement_table);
}

FrostFunction::~FrostFunction()
{
}

} // namespace frost_hdl
