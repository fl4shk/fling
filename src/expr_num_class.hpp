#ifndef src_expr_num_class_hpp
#define src_expr_num_class_hpp

// src/expr_num_class.hpp

#include "misc_includes.hpp"
//#include "general_allocator_class.hpp"

namespace frost_hdl
{

class ExprNum
{
public:		// types
	typedef std::vector<bool> ExprNumData;

protected:		// variables
	ExprNumData _data;
	bool _is_signed = false;

public:		// functions
	ExprNum() = default;

	ExprNum(const ExprNumData& s_data, bool s_is_signed=false);
	ExprNum(ExprNumData&& s_data, bool s_is_signed=false);
	explicit ExprNum(bool s_data, bool s_is_signed=false);


	explicit ExprNum(const BigNum& s_data, size_t s_data_size,
		bool s_is_signed);

	// this calls "copy_from_bignum_with_smallest_size()"
	explicit ExprNum(const BigNum& s_data, bool s_is_signed);

	// size/signedness changing constructors
	ExprNum(const ExprNum& src, size_t s_data_size);
	ExprNum(const ExprNum& src, size_t s_data_size, bool s_is_signed);


	ExprNum(const ExprNum& to_copy) = default;


	virtual ~ExprNum() = default;


	ExprNum& operator = (const ExprNum& to_copy) = default;

	inline bool operator == (const ExprNum& other) const
	{
		return (static_cast<BigNum>(*this) == static_cast<BigNum>(other));
	}



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

	void copy_from_bignum_with_smallest_size(const BigNum& n_data,
		bool n_is_signed);

	BigNum convert_to_bignum() const;

	// For when we need this "ExprNum" to be treated as unsigned.
	inline BigNum convert_to_unsigned_bignum() const
	{
		return BigNum(ExprNum(*this, size(), false));
	}
	inline std::string convert_to_string() const
	{
		return liborangepower::bignum::convert_bignum_to_str
			(convert_to_bignum());
	}

	std::string convert_to_verilog_literal() const;

	inline operator BigNum() const
	{
		return convert_to_bignum();
	}

	explicit inline operator std::string() const
	{
		return convert_to_string();
	}



	//inline const auto& data() const
	//{
	//	return *_data;
	//}

	inline size_t size() const
	{
		return data().size();
	}
	// When n_size is greater than size(), "set_size()", zero extension or
	// sign extension will be performed (with the appropriate type of
	// extension being determined by the value of _is_signed)
	void set_size(size_t n_size);

	// "change_full_type()" is intended to be used only by whoever is
	// evaluating the expression (which is probably the "Expression" class
	// itself).
	inline void change_full_type(size_t n_size, bool n_is_signed)
	{
		set_is_signed(n_is_signed);
		set_size(n_size);
	}

	inline auto one_bit(size_t index) const
	{
		return data().at(index);
	}
	ExprNumData multiple_bits(size_t start_index, size_t amount) const;

	inline void set_bit(size_t index, bool val)
	{
		auto n_data(data());
		n_data.at(index) = val;
		set_data(n_data);
	}
	void set_multiple_bits(size_t start_index,
		const ExprNumData& some_bits);


	//inline void set_data(const ExprNumData& n_data)
	//{
	//	_data = dup_expr_num_data(n_data);
	//}
	//inline void set_data(ExprNumData&& n_data)
	//{
	//	_data = dup_expr_num_data(std::move(n_data));
	//}

	inline bool is_negative() const
	{
		return (is_signed() && one_bit(size() - 1));
	}

	// Logical Shift Left
	void perf_lsl(const ExprNum& to_shift, const ExprNum& amount);

	// Logical Shift Right
	void perf_lsr(const ExprNum& to_shift, const ExprNum& amount);

	// Arithmetic Shift Right
	void perf_asr(const ExprNum& to_shift, const ExprNum& amount);

	// Slice with a range
	void perf_slice_with_range(const ExprNum& to_slice,
		const ExprNum& range_left, const ExprNum& range_right);


	GEN_GETTER_AND_SETTER_BY_VAL(is_signed)

	GEN_GETTER_AND_SETTER_BY_CON_REF(data)
	GEN_SETTER_BY_RVAL_REF(data)
};

} // namespace frost_hdl


#endif		// src_expr_num_class_hpp
