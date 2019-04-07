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
	Expression* range_left_child, Expression* range_right_child)
	: Expression(s_src_code_pos)
{
	_symbol = s_symbol;

	_set_children(range_left_child, range_right_child);

	for (auto child : _children)
	{
		child->set_is_self_determined(true);
	}
}

SavedString ExprIdentSlicedWithRange::to_hdl_source() const
{
	return dup_str(sconcat(*symbol()->ident(), "[",
		*_range_left_child()->to_hdl_source(), ":",
		*_range_right_child()->to_hdl_source(), "]"));
}

bool ExprIdentSlicedWithRange::is_constant() const
{
	return (symbol()->is_constant() && _range_left_child()->is_constant()
		&& _range_right_child()->is_constant());
}

void ExprIdentSlicedWithRange::_inner_finish_init_value()
{
	//_value.set_is_signed(symbol()->frost_full_type()->frost_lhs_type()
	//	->is_signed());
	_value.set_is_signed(false);
}

void ExprIdentSlicedWithRange::_evaluate()
{
	symbol()->value()->full_evaluate_if_constant();
	const auto unsliced_value = symbol()->value()->value();

	//_value
	//ExprNum temp_value;
	//_value.set_size
}

size_t ExprIdentSlicedWithRange::_starting_length() const
{
}

} // namespace frost_hdl
