#include "../expression_class.hpp"
#include "../symbol_class.hpp"
#include "../frost_full_type_class.hpp"
#include "expr_ident_classes.hpp"
#include "dot_cpp_defines.hpp"

namespace frost_hdl
{

ExprIdentName::ExprIdentName(const SrcCodePos& s_src_code_pos,
	Symbol* s_symbol)
	: Expression(s_src_code_pos)
{
	_symbol = s_symbol;

	//_value.set_size(symbol()->frost_lhs_type()->left_dim());
	//_value.set_size(_starting_length());
	//_value.set_is_signed(symbol()->frost_full_type()->frost_lhs_type()
	//	->is_signed());
}

SavedString ExprIdentName::to_hdl_source() const
{
	return symbol()->ident();
}

bool ExprIdentName::is_constant() const
{
	// Why was this written this way?
	//return (Expression::is_constant() || symbol()->is_constant());
	return symbol()->is_constant();
}
void ExprIdentName::_inner_finish_init_value()
{
	//_value.set_size(_starting_length());
	_value.set_is_signed(symbol()->frost_full_type()->frost_lhs_type()
		->is_signed());
}

void ExprIdentName::_evaluate()
{
	//if (symbol()->is_constant())
	//{
	//	_value = symbol()->value_expr()->value();
	//}
	//else
	//{
	//	_value.copy_from_bignum(BigNum(0));
	//}

	//_value = symbol()->value_exprs().front()->value();
	symbol()->value()->full_evaluate_if_constant();
	_value = symbol()->value()->value();
}

// This should only ever be called for non-composite identifiers....  
// However, if that part of the language design changes, only *PACKED*
// composite identifiers should be allowed here.
size_t ExprIdentName::_starting_length() const
{
	////if (symbol()->frost_lhs_type()->is_packed_composite())
	////{
	////}
	//return symbol()->frost_lhs_type()->left_dim();
	return symbol()->frost_full_type()->frost_lhs_type()->left_dim();
}



//ExprSubpassIdentName::ExprSubpassIdentName
//	(const SrcCodePos& s_src_code_pos, Symbol* s_symbol)
//	: Expression(s_src_code_pos)
//{
//	_symbol = s_symbol;
//
//	//_value.set_size(1);
//}
//bool ExprSubpassIdentName::is_constant() const
//{
//	return symbol()->is_constant();
//}

ExprIdentSlicedWithRange::ExprIdentSlicedWithRange
	(const SrcCodePos& s_src_code_pos, Symbol* s_symbol,
	const PseudoFuncCallRange& s_pseudo_func_call_range)
	: Expression(s_src_code_pos)
{
	_symbol = s_symbol;
	_pseudo_func_call_range = s_pseudo_func_call_range;

	if (!_pseudo_func_call_range.is_constant())
	{
		const u32 temp = ((_pseudo_func_call_range.left()->is_constant()
			<< 1) | _pseudo_func_call_range.right()->is_constant());

		// Produce a better error message than just the whole range isn't
		// constant.
		switch (temp)
		{
		default:
			_pseudo_func_call_range.left()->src_code_pos().err
				("ExprIdentSlicedWithRange::ExprIdentSlicedWithRange():  "
				"Eek!  Eek!  Eek!");
			break;

		case 0b01:
			_pseudo_func_call_range.right()->src_code_pos().err
				("Right-hand side of \":\" in range is not constant.");
			break;

		case 0b10:
			_pseudo_func_call_range.left()->src_code_pos().err
				("Left-hand side of \":\" in range is not constant.");
			break;

		case 0b11:
			_pseudo_func_call_range.left()->src_code_pos().err
				("Both left and right hand sides of \":\" in range are "
				"not constant.");
			break;
		}
	}

	//_set_children(range_left_child, range_right_child);

	//// I'm pretty sure that ranges, which are constant, aren't affected by
	//// what variable they're applied to.
	//for (auto child : _children)
	//{
	//	child->set_is_self_determined(true);
	//}

	//set_handles_children_eval(true);
	//set_handles_value_set_size(true);
}

SavedString ExprIdentSlicedWithRange::to_hdl_source() const
{
	return dup_str(sconcat(*symbol()->ident(), "[",
		*_pseudo_func_call_range.left()->to_hdl_source(), ":",
		*_pseudo_func_call_range.right()->to_hdl_source(), "]"));
}

bool ExprIdentSlicedWithRange::is_constant() const
{
	//return (symbol()->is_constant() && _range_left_child()->is_constant()
	//	&& _range_right_child()->is_constant());
	return symbol()->is_constant();
}

void ExprIdentSlicedWithRange::_inner_finish_init_value()
{
	//_value.set_is_signed(symbol()->frost_full_type()->frost_lhs_type()
	//	->is_signed());

	// Verilog dictates that slices are *always* unsigned.  I will do the
	// same because that is required for compatibility.  You can just use
	// "$sgn(...)" if you need to make it signed.
	//
	// Note that this does *not* apply to array indexing, but I have (or
	// will have) a separate class ("ExprIdentArrayIndex") for that anyway.
	_value.set_is_signed(false);

	// Require ranges to have non-negative values
	_pseudo_func_call_range.evaluate();

	//if (_pseudo_func_call_range
}

void ExprIdentSlicedWithRange::_evaluate()
{
	symbol()->value()->full_evaluate_if_constant();
	const auto unsliced_value = symbol()->value()->value();

	_value.perf_slice_with_range(unsliced_value,
		_pseudo_func_call_range.left()->value(),
		_pseudo_func_call_range.right()->value());
}

size_t ExprIdentSlicedWithRange::_starting_length() const
{
	_pseudo_func_call_range.evaluate();
	return _pseudo_func_call_range.size();
}

} // namespace frost_hdl
