#ifndef src_expr_num_class_hpp
#define src_expr_num_class_hpp

// src/expr_num_class.hpp

#include "misc_includes.hpp"
#include "general_allocator_class.hpp"

namespace frost_hdl
{

class ExprNum
{
protected:		// variables
	ExprNumData _data = nullptr;
	bool _is_signed = false;

public:		// functions
	ExprNum() = default;

	ExprNum(const RawExprNumData& s_data, bool s_is_signed=false);
	ExprNum(RawExprNumData&& s_data, bool s_is_signed=false);
	ExprNum(bool s_data, bool s_is_signed=false);


	ExprNum(const BigNum& s_data, size_t s_data_size,
		bool s_is_signed=false);



	ExprNum(const ExprNum& to_copy) = default;
	ExprNum(ExprNum&& to_move) = default;


	virtual ~ExprNum() = default;


	ExprNum& operator = (const ExprNum& to_copy) = default;
	ExprNum& operator = (ExprNum&& to_move) = default;

	void copy_from_bignum(const BigNum& n_data, size_t n_data_size);
	BigNum convert_to_bignum() const;


	// non-assignment operators
	// "&&", "||"
	ExprNum op_log_and(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_log_or(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;

	// "==", "!=", "<", ">", "<=", ">="
	ExprNum op_cmp_eq(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_cmp_ne(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_cmp_lt(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_cmp_gt(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_cmp_le(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_cmp_ge(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;


	// Binop "+", "-"
	ExprNum op_binop_plus(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_binop_minus(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;

	// Unop "+", "-"

	//// unary -
	//inline ExprNum operator - () const
	//{
	//	ExprNum ret = ~(*this);
	//	return ((~(*this)) + ExprNum(BigNum(1), size(), is_signed()));
	//}

	//inline ExprNum operator ~ () const
	//{
	//	decltype(_data) ret_data;
	//	ret_data = _data;
	//	ret_data.flip();

	//	return ExprNum(ret_data, _is_signed);
	//}

	// Unop "+", "-", "~"
	ExprNum op_unop_plus(ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_unop_minus(ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_unop_bit_invert(ExprNum* assignment_lhs=nullptr) const;

	// Binop "*", "/", "%", "&", "|", "^", "<<", ">>", ">>>"
	ExprNum op_binop_mul(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_binop_div(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_binop_mod(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_binop_bit_and(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_binop_bit_or(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_binop_bit_xor(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_binop_bit_lsl(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_binop_bit_lsr(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;
	ExprNum op_binop_bit_asr(const ExprNum& other,
		ExprNum* assignment_lhs=nullptr) const;



	inline const auto& data() const
	{
		return *_data;
	}

	inline size_t size() const
	{
		return data().size();
	}

	inline void set_data(const RawExprNumData& n_data)
	{
		_data = dup_expr_num_data(n_data);
	}
	inline void set_data(RawExprNumData&& n_data)
	{
		_data = dup_expr_num_data(std::move(n_data));
	}

	GEN_GETTER_AND_SETTER_BY_VAL(is_signed)
};

} // namespace frost_hdl


#endif		// src_expr_num_class_hpp
