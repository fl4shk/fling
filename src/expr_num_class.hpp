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
	explicit ExprNum(bool s_data, bool s_is_signed=false);


	explicit ExprNum(const BigNum& s_data, size_t s_data_size,
		bool s_is_signed);

	ExprNum(const ExprNum& src, size_t s_data_size);
	ExprNum(const ExprNum& src, size_t s_data_size, bool s_is_signed);


	ExprNum(const ExprNum& to_copy) = default;


	virtual ~ExprNum() = default;


	ExprNum& operator = (const ExprNum& to_copy) = default;



	void copy_from_bignum(const BigNum& n_data, size_t n_data_size);
	inline void copy_from_bignum(const BigNum& n_data, size_t n_data_size,
		bool n_is_signed)
	{
		copy_from_bignum(n_data, n_data_size);
		set_is_signed(n_is_signed);
	}
	inline void copy_from_bignum(const BigNum& n_data)
	{
		copy_from_bignum(n_data, size(), is_signed());
	}

	BigNum convert_to_bignum() const;
	inline std::string convert_to_string() const
	{
		return liborangepower::bignum::convert_bignum_to_str
			(convert_to_bignum());
	}

	inline operator BigNum() const
	{
		return convert_to_bignum();
	}

	explicit inline operator std::string() const
	{
		return convert_to_string();
	}



	inline const auto& data() const
	{
		return *_data;
	}

	inline size_t size() const
	{
		return data().size();
	}
	void set_size(size_t n_size);

	inline auto one_bit(size_t index) const
	{
		return data().at(index);
	}
	RawExprNumData multiple_bits(size_t start_index, size_t amount) const;

	inline void set_bit(size_t index, bool val)
	{
		auto n_data(data());
		n_data.at(index) = val;
		set_data(n_data);
	}
	void set_multiple_bits(size_t start_index,
		const RawExprNumData& some_bits);


	inline void set_data(const RawExprNumData& n_data)
	{
		_data = dup_expr_num_data(n_data);
	}
	inline void set_data(RawExprNumData&& n_data)
	{
		_data = dup_expr_num_data(std::move(n_data));
	}

	inline bool is_negative() const
	{
		return (is_signed() && one_bit(size() - 1));
	}

	GEN_GETTER_AND_SETTER_BY_VAL(is_signed)
};

} // namespace frost_hdl


#endif		// src_expr_num_class_hpp
