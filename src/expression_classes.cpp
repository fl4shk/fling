#include "expression_classes.hpp"

namespace frost_hdl
{

//typedef Expression::OpStr OpStr;
//typedef Expression::Type ExprType;

Expression::Expression()
{
	//for (auto& iter : _children)
	//{
	//	iter = nullptr;
	//}

	_ident = nullptr;
	set_is_self_determined(false);

}



//OpStr Expression::op_str() const
//{
//	return dup_str("INVALID_EXPRESSION");
//}

void Expression::_evaluate()
{
	set_value(ExprNum(0, 1, false));
}

bool Expression::_children_affect_length() const
{
	// Most types of expression use this definition.
	return true;
}

size_t Expression::_starting_length() const
{
	return 0;
}

bool Expression::_is_always_constant() const
{
	return false;
}

void Expression::_full_evaluate()
{
	// The expression evaluation algorithm:
	// * Determine the expression size using standard rules.
	// * Determine the sign of the expression using standard rules.
	// * Coerce the type of every operand of the expression, not counting
	// those that are self-determined, to the type of the expression.
	// * Extend the size of every operand of the expression, not counting
	// those that are self-determined, to the type of the expression.
	// Perform sign extension if and only if the operand type (after type
	// coercion) is signed.
	// * Finally, evaluate everything.


	// The descendants of an "Expression" already know their size and their
	// type.
	DescendantsList ptln_descs;
	_get_first_layer_ptln_descs(ptln_descs);

	for (auto iter : ptln_descs)
	{
		iter->_full_evaluate();
	}


	//for (auto iter : pseudo_top_level_descs)
	//{
	//	//printout(BigNum(iter->value()), "\n");
	//	iter->_full_evaluate();
	//}


	//_inner_full_evaluate(pseudo_top_level_descs);
}

//void Expression::_inner_full_evaluate
//	(const DescendantsList& pseudo_top_level_descs)
//{
//	for (auto iter : _children)
//	{
//		iter->_inner_full_evaluate(pseudo_top_level_descs);
//		iter->_evaluate();
//	}
//	_evaluate();
//}

// Get pseudo top-level node descendants, but only the ones in the first
// "layer" of descendants, relative to this "Expression".
void Expression::_get_first_layer_ptln_descs(DescendantsList& ret) const
{
	for (auto iter : _children)
	{
		// It's a bug if any descendants appear twice....
		if (ret.count(iter) != 0)
		{
			printout("Expression::_get_pseudo_top_level_descs():",
				"  Eek!\n");
			exit(1);
		}

		if (iter->_is_pseudo_top_level_node())
		{
			ret.insert(iter);
		}
		else // if (!iter->_is_pseudo_top_level_node())
		{
			iter->_get_first_layer_ptln_descs(ret);
		}
	}
}

//// Find the highest size of a descendant of this "Expression" that can
//// affect the size of this "Expression".
//size_t Expression::_highest_desc_size_with_effect() const
//{
//	size_t ret = 0;
//
//	for (const auto& child : _children)
//	{
//		if (!child->is_self_determined())
//		{
//			if (child->_is_pseudo_top_level_node())
//			{
//				ret = max_va(ret, child->value().size());
//			}
//			else // if (!child->_is_pseudo_top_level_node())
//			{
//				ret = max_va(ret, child->_highest_desc_size_with_effect());
//				ret = max_va(ret, child->value().size());
//			}
//		}
//	}
//
//	return ret;
//}

//// I'm pretty sure this is unnecessary because the Expression itself will
//// already know its signedness via "_value.is_signed()".
//bool Expression::_has_any_unsigned_non_sd_children() const
//{
//	for (const auto& child : _children)
//	{
//		if ((!child->value().is_signed())
//			&& (!child->is_self_determined()))
//		{
//			return true;
//		}
//	}
//
//	return false;
//}

bool Expression::_has_only_constant_children() const
{
	if (is_leaf())
	{
		return false;
	}

	for (const auto& child : _children)
	{
		if (!child->is_constant())
		{
			return false;
		}
	}

	return true;
}

ExprBaseUnOp::ExprBaseUnOp(Expression* only_child)
{
	_set_children(only_child);
}

ExprBaseBinOp::ExprBaseBinOp(Expression* left_child,
	Expression* right_child)
{
	_set_children(left_child, right_child);
}

void ExprBinOpBitLsl::_evaluate()
{
	RawExprNumData n_value_data;
	n_value_data.resize(_left_child_value().size(), false);


	for (BigNum i=0;
		i<_right_child_value().convert_to_unsigned_bignum();
		++i)
	{
		const auto write_index = BigNum(i + _right_child_value()
			.convert_to_unsigned_bignum()).get_ui();
		const auto read_index = i.get_ui();

		n_value_data.at(write_index) = _left_child_value().data()
			.at(read_index);
	}

	_value.set_data(std::move(n_value_data));
}

void ExprBinOpBitLsr::_evaluate()
{
	RawExprNumData n_value_data;
	n_value_data.resize(_left_child_value().size(), false);


	for (BigNum i=0;
		i<_right_child_value().convert_to_unsigned_bignum();
		++i)
	{
		const auto write_index = i.get_ui();
		const auto read_index = BigNum(i + _right_child_value()
			.convert_to_unsigned_bignum()).get_ui();

		n_value_data.at(write_index) = _left_child_value().data()
			.at(read_index);
	}

	_value.set_data(std::move(n_value_data));
}

void ExprBinOpBitAsr::_evaluate()
{
	RawExprNumData n_value_data;

	// ">>>" only acts as an arithmetic right shift when thing to shift is
	// signed.
	if (_left_child_value().is_signed())
	{
		n_value_data.resize(_left_child_value().size(),
			_left_child_value().data().back());
	}
	else // if (!_left_child_value().is_signed())
	{
		n_value_data.resize(_left_child_value().size(), false);
	}


	for (BigNum i=0;
		i<_right_child_value().convert_to_unsigned_bignum();
		++i)
	{
		const auto write_index = i.get_ui();
		const auto read_index = BigNum(i + _right_child_value()
			.convert_to_unsigned_bignum()).get_ui();

		n_value_data.at(write_index) = _left_child_value().data()
			.at(read_index);
	}

	_value.set_data(std::move(n_value_data));
}

} // namespace frost_hdl
