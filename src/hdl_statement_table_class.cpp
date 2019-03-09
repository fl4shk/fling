#include "hdl_statement_table_class.hpp"

#include <sstream>

namespace frost_hdl
{

SavedString HdlStatement::to_hdl_source(TableNode* top) const
{
	return nullptr;
}

auto HdlStatement::driver_type() const -> DriverType
{
	return DriverType::None;
}
//auto HdlStatement::edge_sens_type() const -> EdgeSensType
//{
//	return EdgeSensType::None;
//}

HdlStmtContAssign::HdlStmtContAssign(Expression* s_ident_expr,
	Expression* s_rhs)
{
	_set_exprs(s_ident_expr, s_rhs);
}

SavedString HdlStmtBaseBehavBlock::to_hdl_source(TableNode* top) const
{
	std::string non_dupped_ret;

	non_dupped_ret += pretabbed("\n");
	non_dupped_ret += pretabbed(*_output_behav_block_str(), "\n");
	non_dupped_ret += pretabbed("begin\n");

	for (auto child : top->children)
	{
		//non_dupped_ret += dblpretabbed(*child->to_hdl_source(top));
		for (auto iter : child->table)
		{
			non_dupped_ret += *iter->to_hdl_source(top);
		}
	}

	non_dupped_ret += pretabbed("end\n");

	return dup_str(non_dupped_ret);
}



// "always_seq"
HdlStmtBehavBlockAlwaysSeq::HdlStmtBehavBlockAlwaysSeq
	(EdgeSensType s_edge_sens_type, Expression* s_ident)
{
	_edge_sens_type = s_edge_sens_type;
	_set_exprs(s_ident);
}

SavedString HdlStmtBehavBlockAlwaysSeq::_output_behav_block_str() const
{
	std::string non_dupped_ret;

	non_dupped_ret += "always @(";

	//switch (edge_sens_type())
	switch (_edge_sens_type)
	{
	case EdgeSensType::Posedge:
		non_dupped_ret += "posedge";
		break;
	case EdgeSensType::Negedge:
		non_dupped_ret += "negedge";
		break;
	default:
		printerr("HdlStmtBehavBlockAlwaysSeq",
			"::_output_behav_block_str():  Eek!");
		exit(1);
		return nullptr;
		break;
	}

	non_dupped_ret += sconcat(" ", *ident_expr()->to_hdl_source());
	non_dupped_ret += ")";

	return dup_str(non_dupped_ret);
}

} // namespace frost_hdl
