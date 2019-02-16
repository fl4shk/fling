#include "expr_num_class.hpp"

namespace frost_hdl
{

ExprNum::ExprNum(const RawExprNumData& s_data, bool s_is_signed)
{
	set_data(s_data);

	set_is_signed(s_is_signed);
}
ExprNum::ExprNum(RawExprNumData&& s_data, bool s_is_signed)
{
	set_data(std::move(s_data));

	set_is_signed(s_is_signed);
}
ExprNum::ExprNum(bool s_data, bool s_is_signed)
{
	RawExprNumData temp;
	temp.push_back(s_data);
	set_data(std::move(temp));

	set_is_signed(s_is_signed);
}

ExprNum::ExprNum(const BigNum& s_data, size_t s_data_size,
	bool s_is_signed)
{
	copy_from_bignum(s_data, s_data_size);

	set_is_signed(s_is_signed);
}

void ExprNum::copy_from_bignum(const BigNum& n_data, size_t n_data_size)
{
	BigNum mask = 1;

	RawExprNumData temp_data;

	for (size_t i=0; i<n_data_size; ++i)
	{
		//_data.push_back((n_data & mask) != BigNum(0));
		temp_data.push_back((n_data & mask) != BigNum(0));
		mask *= 2;
	}

	set_data(temp_data);
}

BigNum ExprNum::convert_to_bignum() const
{
	BigNum ret = 0;

	for (size_t i=size(); i>0; --i)
	{
		ret *= 2;
		ret |= data().at(i - 1);
	}

	return ret;
}

// non-assignment operators
// "&&", "||"
ExprNum ExprNum::op_log_and(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_log_or(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}

// "==", "!=", "<", ">", "<=", ">="
ExprNum ExprNum::op_cmp_eq(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_cmp_ne(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_cmp_lt(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_cmp_gt(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_cmp_le(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_cmp_ge(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}

// Unop "+", "-", "~"
ExprNum ExprNum::op_unop_plus(ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_unop_minus(ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_unop_bit_invert(ExprNum* assignment_lhs) const
{
}

// Binop "*", "/", "%", "&", "|", "^", "<<", ">>", ">>>"
ExprNum ExprNum::op_binop_mul(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_binop_div(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_binop_mod(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_binop_bit_and(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_binop_bit_or(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_binop_bit_xor(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_binop_bit_lsl(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_binop_bit_lsr(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}
ExprNum ExprNum::op_binop_bit_asr(const ExprNum& other,
	ExprNum* assignment_lhs) const
{
}

} // namespace frost_hdl
