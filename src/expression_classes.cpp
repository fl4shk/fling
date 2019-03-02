#include "expression_classes.hpp"
#include "symbol_table_class.hpp"
#include "hdl_type_table_class.hpp"

namespace frost_hdl
{

//typedef Expression::OpStr OpStr;
//typedef Expression::Type ExprType;

//Expression::Expression()
//{
//	//for (auto& iter : _children)
//	//{
//	//	iter = nullptr;
//	//}
//
//	//_ident = nullptr;
//	set_symbol(nullptr);
//	set_is_self_determined(false);
//	set_handles_children_eval(false);
//
//}



//OpStr Expression::op_str() const
//{
//	return dup_str("INVALID_EXPRESSION");
//}

void Expression::inner_full_evaluate()
{
	if (!handles_children_eval())
	{
		for (auto iter : _children)
		{
			iter->inner_full_evaluate();
			iter->_evaluate();
		}
	}
	_evaluate();
}

void Expression::_evaluate()
{
	_set_value(ExprNum(0, 1, false));
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

void Expression::_full_evaluate(bool is_real_top)
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
		iter->_full_evaluate(false);
	}

	if (!_is_pseudo_top_level_node())
	{
		_perf_mega_descs_cast(value().size(), value().is_signed());
	}
	else // if (_is_pseudo_top_level_node())
	{
		if (is_self_determined())
		{
			_perf_mega_descs_cast(value().size(), value().is_signed());
		}
		else // if (!is_self_determined())
		{
			_perf_mega_descs_cast(_highest_desc_size_with_effect(),
				!_has_any_unsigned_first_layer_non_sd_descs());
		}
	}


	if (is_real_top)
	{
		inner_full_evaluate();
	}
}


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

// Find the highest size of a descendant of this "Expression" that can
// affect the size of this "Expression".  This is used for 
size_t Expression::_highest_desc_size_with_effect() const
{
	size_t ret = 0;

	for (const auto& child : _children)
	{
		if (!child->is_self_determined())
		{
			if (child->_is_pseudo_top_level_node())
			{
				ret = max_va(ret, child->value().size());
			}
			else // if (!child->_is_pseudo_top_level_node())
			{
				ret = max_va(ret, child->_highest_desc_size_with_effect());
				ret = max_va(ret, child->value().size());
			}
			//ret = max_va(ret, child->_highest_desc_size_with_effect());
			//ret = max_va(ret, child->value().size());
		}
	}

	return ret;
}

bool Expression::_has_any_unsigned_first_layer_non_sd_descs() const
{
	for (const auto& child : _children)
	{
		if (!child->is_self_determined())
		{
			if (!child->value().is_signed())
			{
				return true;
			}

			if (!child->_is_pseudo_top_level_node())
			{
				if (child->_has_any_unsigned_first_layer_non_sd_descs())
				{
					return true;
				}
			}
		}
	}

	return false;
}

void Expression::_perf_mega_descs_cast(size_t n_size, bool n_is_signed)
	const
{
	for (auto child : _children)
	{
		// We don't want to cast self-determined nodes.
		if (!child->is_self_determined())
		{
			child->_value.change_full_type(n_size, n_is_signed);

			// We don't want to cast the *descendants* of a pseudo
			// top-level node.
			if (!child->_is_pseudo_top_level_node())
			{
				child->_perf_mega_descs_cast(n_size, n_is_signed);
			}
		}
	}
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
	_value.perf_lsl(_left_child_value(), _right_child_value());
}

void ExprBinOpBitLsr::_evaluate()
{
	_value.perf_lsr(_left_child_value(), _right_child_value());
}

void ExprBinOpBitAsr::_evaluate()
{
	_value.perf_asr(_left_child_value(), _right_child_value());
}

ExprConcat::ExprConcat(ChildrenList&& s_children)
{
	_children = std::move(s_children);

	for (auto child : _children)
	{
		child->set_is_self_determined(true);
	}

	_value.set_size(_starting_length());
	_value.set_is_signed(false);
}

void ExprConcat::_evaluate()
{
	RawExprNumData n_value_data;
	//n_value_data.reserve(_value.size());

	for (auto child : _children)
	{
		for (size_t i=0; i<child->value().size(); ++i)
		{
			n_value_data.push_back(child->value().one_bit(i));
		}
	}

	_value.set_data(std::move(n_value_data));
}

size_t ExprConcat::_starting_length() const
{
	size_t ret = 0;

	for (auto child : _children)
	{
		ret += child->value().size();
	}

	return ret;
}

ExprTernary::ExprTernary(Expression* condition_child,
	Expression* when_true_child, Expression* when_false_child)
{
	_set_children(condition_child, when_true_child, when_false_child);
	//_value.set_size(_starting_length());
	//_value.set_is_signed(_when_true_child_value().is_signed()
	//	&& _when_false_child_value().is_signed());
	set_handles_children_eval(true);
}

void ExprTernary::_evaluate()
{
	_condition_child()->inner_full_evaluate();

	if (static_cast<BigNum>(_condition_child_value()))
	{
		_when_true_child()->inner_full_evaluate();
		//_value.copy_from_bignum(static_cast<BigNum>
		//	(_when_true_child_value()));
		_value = _when_true_child_value();
	}
	else // if (!static_cast<BigNum>(_condition_child_value()))
	{
		_when_false_child()->inner_full_evaluate();
		_value = _when_false_child_value();
	}
}

//ExprIdentName::ExprIdentName(const std::string& s_ident,
//	SymbolTable* s_symbol_table)
//{
//	_set_ident(s_ident);
//	_symbol_table = s_symbol_table;
//}
ExprIdentName::ExprIdentName(Symbol* s_symbol)
{
	_symbol = s_symbol;
}

bool ExprIdentName::is_constant() const
{
	return (Expression::is_constant() || symbol()->is_constant());
}

void ExprIdentName::_evaluate()
{
}

// This should only ever be called for non-composite identifiers
size_t ExprIdentName::_starting_length() const
{
	//if (symbol()->hdl_type()->is_packed_composite())
	//{
	//}
	return symbol()->hdl_type()->left_dim();
}

} // namespace frost_hdl
