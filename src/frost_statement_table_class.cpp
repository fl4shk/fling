#include "frost_statement_table_class.hpp"

#include <sstream>

namespace frost_hdl
{

#define EXPR_TO_HDL_SOURCE(expr) (*expr()->to_hdl_source())

SavedString FrostStatement::to_hdl_source(TableNode* top) const
{
	return nullptr;
}

// Continuous assignment ("assign")
FrostStmtContAssign::FrostStmtContAssign(Expression* s_ident_expr,
	Expression* s_rhs)
{
	_set_exprs(s_ident_expr, s_rhs);
}
SavedString FrostStmtContAssign::to_hdl_source(TableNode* top)
	const
{
	return dup_str("assign ", EXPR_TO_HDL_SOURCE(ident_expr), " = ",
		EXPR_TO_HDL_SOURCE(rhs), ";\n");
}


// "initial", "always_comb", "always_seq"
SavedString FrostStmtBaseBehavBlock::to_hdl_source(TableNode* top)
	const
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
FrostStmtBehavBlockAlwaysSeq::FrostStmtBehavBlockAlwaysSeq
	(EdgeSensType s_edge_sens_type, Expression* s_ident_expr)
{
	_edge_sens_type = s_edge_sens_type;
	_set_exprs(s_ident_expr);
}

SavedString FrostStmtBehavBlockAlwaysSeq::_output_behav_block_str()
	const
{
	std::string non_dupped_ret;

	non_dupped_ret += "always @(";

	switch (_edge_sens_type)
	{
	case EdgeSensType::Posedge:
		non_dupped_ret += "posedge";
		break;
	case EdgeSensType::Negedge:
		non_dupped_ret += "negedge";
		break;
	default:
		printerr("FrostStmtBehavBlockAlwaysSeq",
			"::_output_behav_block_str():  Eek!");
		exit(1);
		return nullptr;
		break;
	}

	non_dupped_ret += sconcat(" ", *ident_expr()->to_hdl_source());
	non_dupped_ret += ")";

	return dup_str(non_dupped_ret);
}

// Behavioral assignment operator.  Can become either a blocking or a
// non-blocking assignment depending on whether it was in an "initial",
// "always_comb", or "always_seq" block.
FrostStmtBehavAssign::FrostStmtBehavAssign(Expression* s_ident_expr,
	Expression* s_rhs)
{
	_set_exprs(s_ident_expr, s_rhs);
}

SavedString FrostStmtBehavAssign::to_hdl_source(TableNode* top)
{
	std::string non_dupped_ret;

	non_dupped_ret += sconcat(EXPR_TO_HDL_SOURCE(ident_expr), " ");

	switch (top->table.front()->driver_type())
	{
	case DriverType::BehavBlockInitial:
	case DriverType::BehavBlockAlwaysComb:
		// blocking assignment
		non_dupped_ret += "=";
		break;

	case DriverType::BehavBlockAlwaysSeq:
		// non-blocking assignment
		non_dupped_ret += "<=";
		break;

	default:
		printerr("FrostStmtBehavAssign::to_hdl_source():  Eek!\n");
		exit(1);
		return nullptr;
		break;
	}

	non_dupped_ret += sconcat(" ", EXPR_TO_HDL_SOURCE(rhs), ";\n");

	return dup_str(non_dupped_ret);
}

#undef EXPR_TO_HDL_SOURCE

} // namespace frost_hdl
