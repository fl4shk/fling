#include "../expression_class.hpp"
#include "expr_un_op_classes.hpp"
#include "dot_cpp_defines.hpp"

namespace frost_hdl
{

ExprBaseUnOp::ExprBaseUnOp(const SrcCodePos& s_src_code_pos,
	Expression* only_child)
	: Expression(s_src_code_pos)
{
	_set_children(only_child);
}

SavedString ExprBaseUnOp::to_hdl_source() const
{
	switch (_frost_source_type())
	{
	case FrostSourceType::UnOp:
		return dup_str(*_unop_str(), TO_HDL_SOURCE(_only_child));
		break;
	case FrostSourceType::DollarFunction:
		return dup_str(*_unop_str(), "(", TO_HDL_SOURCE(_only_child), ")");
		break;
	default:
		// Eek!
		printerr("ExprBaseUnOp::to_hdl_source():  Eek!\n");
		exit(1);
		return nullptr;
		break;
	}
}


void ExprUnOpClog2::_evaluate()
{
	const auto only_child_data_as_binary_str = _only_child_value()
		.convert_to_unsigned_bignum().get_str(2);
	//const BigNum n_value_data
	//	= (only_child_data_as_binary_str.front() == '-')
	//	? BigNum(only_child_data_as_binary_str.size() - 1)
	//	: BigNum(only_child_data_as_binary_str.size());
	const BigNum n_value_data
		= BigNum(only_child_data_as_binary_str.size()) - BigNum(1);
	_set_value(ExprNum((n_value_data - BigNum(1)), value().size(),
		value().is_signed()));
}

} // namespace frost_hdl
