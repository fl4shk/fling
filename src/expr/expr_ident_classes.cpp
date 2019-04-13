#include "../expression_class.hpp"
#include "../symbol_class.hpp"
#include "../frost_full_type_class.hpp"
#include "expr_ident_classes.hpp"
#include "dot_cpp_defines.hpp"

namespace frost_hdl
{

//--------
ExprIdentRefBase::ExprIdentRefBase(const SrcCodePos& s_src_code_pos,
	Symbol* s_symbol)
	: Expression(s_src_code_pos)
{
	_symbol = s_symbol;
}
//--------

// Non-sliced reference to an identifier of some sort.
//--------
ExprIdentName::ExprIdentName(const SrcCodePos& s_src_code_pos,
	Symbol* s_symbol)
	: ExprIdentRefBase(s_src_code_pos, s_symbol)
{
	//_symbol = s_symbol;

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
//--------



// vector[one_bit_index]
//--------
ExprIdentOneBitSlicedVector::ExprIdentOneBitSlicedVector
	(const SrcCodePos& s_src_code_pos, Symbol* s_symbol,
	Expression* s_one_bit_index_expr)
	: ExprIdentRefBase(s_src_code_pos, s_symbol)
{
	_set_semi_hidden_children(s_one_bit_index_expr);

	if (!_one_bit_index_expr()->is_constant())
	{
		_one_bit_index_expr()->src_code_pos().err("One-bit slice index is "
			"not constant.");
	}
}

SavedString ExprIdentOneBitSlicedVector::to_hdl_source() const
{
	return dup_str(sconcat(*symbol()->ident(), "[",
		*_one_bit_index_expr()->to_hdl_source(), "]"));
}

bool ExprIdentOneBitSlicedVector::is_constant() const
{
	return symbol()->is_constant();
}

void ExprIdentOneBitSlicedVector::_inner_finish_init_value()
{
	// Verilog dictates that slices are *always* unsigned.  I will do the
	// same because that is required for compatibility.  You can just use
	// "$sgn(...)" if you need to make it signed.
	//
	// Note that this does *not* apply to array indexing, but I have (or
	// will have) a separate class ("ExprIdentArrayIndex") for that anyway.
	_value.set_is_signed(false);

	// Require the one-bit index to have a non-negative value
	_one_bit_index_expr()->full_evaluate_if_constant();

	if (BigNum(_one_bit_index_expr()->value()) < BigNum(0))
	{
		_one_bit_index_expr()->src_code_pos().err("One-bit slice index "
			"expression evaluates to a negative number");
	}
}
void ExprIdentOneBitSlicedVector::_evaluate()
{
	symbol()->value()->full_evaluate_if_constant();
	const auto unsliced_value = symbol()->value()->value();

	_value.perf_slice_with_range(unsliced_value,
		_one_bit_index_expr()->value(), _one_bit_index_expr()->value());
}
size_t ExprIdentOneBitSlicedVector::_starting_length() const
{
	// Well, that was easy.
	return 1;
}
//--------

// vector[left:right]
//--------
ExprIdentSlicedVector::ExprIdentSlicedVector
	(const SrcCodePos& s_src_code_pos, Symbol* s_symbol,
	Expression* s_range_left_expr, Expression* s_range_right_expr)
	: ExprIdentRefBase(s_src_code_pos, s_symbol)
{
	_set_semi_hidden_children(s_range_left_expr, s_range_right_expr);

	if (!_pseudo_func_call_range().is_constant())
	{
		const u32 temp = ((_range_left_child()->is_constant() << 1)
			| _range_right_child()->is_constant());

		// Produce a better error message than just the whole range isn't
		// constant.
		switch (temp)
		{
		default:
			_range_left_child()->src_code_pos().err("ExprIdentSlicedVector"
				"::ExprIdentSlicedVector():  Eek!  Eek!  Eek!");
			break;

		case 0b01:
			_range_right_child()->src_code_pos().err("Right-hand side of "
				"\":\" in range is not constant.");
			break;

		case 0b10:
			_range_left_child()->src_code_pos().err("Left-hand side of "
				"\":\" in range is not constant.");
			break;

		case 0b11:
			_range_left_child()->src_code_pos().err("Both left and right "
				"hand sides of \":\" in range are not constant.");
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

SavedString ExprIdentSlicedVector::to_hdl_source() const
{
	return dup_str(sconcat(*symbol()->ident(), "[",
		*_range_left_child()->to_hdl_source(), ":",
		*_range_right_child()->to_hdl_source(), "]"));
	//return dup_str(sconcat(*_ident_expr->to_hdl_source(), "[",
	//	*_pseudo_func_call_range.left()->to_hdl_source(), ":",
	//	*_pseudo_func_call_range.right()->to_hdl_source(), "]"));
}

bool ExprIdentSlicedVector::is_constant() const
{
	//return (symbol()->is_constant() && _range_left_child()->is_constant()
	//	&& _range_right_child()->is_constant());
	return symbol()->is_constant();
	//return _ident_expr->is_constant();
}

void ExprIdentSlicedVector::_inner_finish_init_value()
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
	_range_left_child()->full_evaluate_if_constant();
	_range_right_child()->full_evaluate_if_constant();

	if (BigNum(_range_left_child()->value()) < BigNum(0))
	{
		_range_left_child()->src_code_pos().err("range left expression "
			"evaluates to negative number");
	}
	if (BigNum(_range_right_child()->value()) < BigNum(0))
	{
		_range_right_child()->src_code_pos().err("range right expression "
			"evaluates to negative number");
	}
}

void ExprIdentSlicedVector::_evaluate()
{
	symbol()->value()->full_evaluate_if_constant();
	const auto unsliced_value = symbol()->value()->value();

	_value.perf_slice_with_range(unsliced_value,
		_range_left_child()->value(),
		_range_right_child()->value());
}

size_t ExprIdentSlicedVector::_starting_length() const
{
	return _pseudo_func_call_range().size();
}
//--------

//// array[array_index]
////--------
//ExprIdentIndexedArray::ExprIdentIndexedArray
//	(const SrcCodePos& s_src_code_pos, Symbol* s_symbol,
//	Expression* s_array_index_expr)
//	: ExprIdentRefBase(s_src_code_pos, s_symbol)
//{
//	// This index expression doesn't have to be constant.
//	_array_index_expr = s_array_index_expr;
//}
////--------

} // namespace frost_hdl
