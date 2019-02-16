#ifndef src_expr_num_class_hpp
#define src_expr_num_class_hpp

// src/expr_num_class.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

class ExprNum
{
protected:		// variables
	std::vector<bool> _data;
	bool _is_signed = false;

public:		// functions
	ExprNum() = default;

	ExprNum(const std::vector<bool>& s_data, bool s_is_signed=false)
		: _data(s_data), _is_signed(s_is_signed)
	{
	}

	ExprNum(std::vector<bool>&& s_data, bool s_is_signed=false)
		: _data(std::move(s_data)), _is_signed(s_is_signed)
	{
	}

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
	bool operator && (const ExprNum& other) const;
	bool operator || (const ExprNum& other) const;
	bool operator == (const ExprNum& other) const;
	bool operator != (const ExprNum& other) const;
	bool operator < (const ExprNum& other) const;
	bool operator > (const ExprNum& other) const;
	bool operator <= (const ExprNum& other) const;
	bool operator >= (const ExprNum& other) const;

	ExprNum operator + (const ExprNum& other) const;
	ExprNum operator - (const ExprNum& other) const;

	// unary -
	inline ExprNum operator - () const
	{
		ExprNum ret = ~(*this);
		return ((~(*this)) + ExprNum(BigNum(1), size(), is_signed()));
	}

	inline ExprNum operator ~ () const
	{
		decltype(_data) ret_data;
		ret_data = _data;
		ret_data.flip();

		return ExprNum(ret_data, _is_signed);
	}

	ExprNum operator * (const ExprNum& other) const;
	ExprNum operator / (const ExprNum& other) const;
	ExprNum operator % (const ExprNum& other) const;

	ExprNum operator & (const ExprNum& other) const;
	ExprNum operator | (const ExprNum& other) const;
	ExprNum operator ^ (const ExprNum& other) const;

	ExprNum operator << (const ExprNum& other) const;

	// An arithmetic shift right will be performed if the expression is
	// signed.
	ExprNum operator >> (const ExprNum& other) const;

	inline size_t size() const
	{
		return data().size();
	}


	GEN_GETTER_BY_CON_REF(data)
	GEN_GETTER_AND_SETTER_BY_VAL(is_signed)
};

} // namespace frost_hdl


#endif		// src_expr_num_class_hpp
