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

	inline operator BigNum () const
	{
		return convert_to_bignum();
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

	inline void set_bit(size_t index, bool val)
	{
		RawExprNumData n_data(data());
		n_data.at(index) = val;
		set_data(n_data);
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
