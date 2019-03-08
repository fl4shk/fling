#include "hdl_statement_table_class.hpp"

#include <sstream>

namespace frost_hdl
{

//SavedString HdlStatement::is_valid() const
//{
//	return nullptr;
//}
SavedString HdlStatement::to_hdl_source() const
{
	return nullptr;
}

HdlStmtContAssign::HdlStmtContAssign(Expression* s_ident_expr,
	Expression* s_rhs)
{
	_set_exprs(s_ident_expr, s_rhs);
}

//SavedString HdlStmtContAssign::is_valid() const
//{
//}
//SavedString HdlStmtContAssign::to_hdl_source() const
//{
//}

} // namespace frost_hdl
