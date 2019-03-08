#include "hdl_function_table_class.hpp"

namespace frost_hdl
{

HdlFunction::HdlFunction(SavedString s_ident, bool s_is_task,
	HdlStatementTable&& s_hdl_statement_table, HdlModule* s_context)
{
	_ident = s_ident;
	_is_task = s_is_task;
	_hdl_statement_table = std::move(s_hdl_statement_table);
}
//HdlFunction::HdlFunction(SavedString s_ident, bool s_is_task,
//	HdlStatementTable&& s_hdl_statement_table, HdlPackage* s_context)
//{
//	_ident = s_ident;
//	_is_task = s_is_task;
//	_hdl_statement_table = std::move(s_hdl_statement_table);
//}
HdlFunction::HdlFunction(SavedString s_ident, bool s_is_task,
	HdlStatementTable&& s_hdl_statement_table, HdlLhsType* s_context)
{
	_ident = s_ident;
	_is_task = s_is_task;
	_hdl_statement_table = std::move(s_hdl_statement_table);
}

HdlFunction::~HdlFunction()
{
}

} // namespace frost_hdl
