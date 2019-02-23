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


//bool Expression::children_affect_length() const
//{
//	// Most types of expression use this definition.
//	return true;
//}

//OpStr Expression::op_str() const
//{
//	return dup_str("INVALID_EXPRESSION");
//}

void Expression::_evaluate()
{
	set_value(ExprNum(0, 1, false));
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


	DescendantsList pseudo_top_descendants;
	_get_pseudo_top_descendants(pseudo_top_descendants);

	//for (auto iter : pseudo_top_descendants)
	//{
	//	//printout(BigNum(iter->value()), "\n");
	//	iter->_full_evaluate();
	//}

	_inner_full_evaluate();
}

void Expression::_inner_full_evaluate()
{
	for (auto iter : _children)
	{
		iter->_inner_full_evaluate();
		iter->_evaluate();
	}
	_evaluate();
}

void Expression::_get_pseudo_top_descendants(DescendantsList& ret)
	const
{
	for (auto iter : _children)
	{
		// It's a bug if any descendants appear twice....
		if (ret.count(iter) != 0)
		{
			printout("Expression::_get_pseudo_top_descendants():",
				"  Eek!\n");
			exit(1);
		}

		if (iter->is_self_determined())
		{
			ret.insert(iter);
		}
		else // if (!iter->is_self_determined())
		{
			iter->_get_pseudo_top_descendants(ret);
		}
	}
}

bool Expression::_has_any_unsigned_non_self_determined_children() const
{
	for (const auto& child : _children)
	{
		if ((!child->value().is_signed())
			&& (!child->is_self_determined()))
		{
			return true;
		}
	}

	return false;
}

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
