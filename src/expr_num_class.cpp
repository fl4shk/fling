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
	set_size(1);
	set_bit(0, s_data);
	set_is_signed(s_is_signed);
}

ExprNum::ExprNum(const BigNum& s_data, size_t s_data_size,
	bool s_is_signed)
{
	set_is_signed(s_is_signed);
	copy_from_bignum(s_data, s_data_size);
}

ExprNum::ExprNum(const ExprNum& src, size_t s_data_size)
{
	*this = src;
	set_size(s_data_size);
}
ExprNum::ExprNum(const ExprNum& src, size_t s_data_size, bool s_is_signed)
{
	_data = src._data;
	set_is_signed(s_is_signed);

	// resizing needs to come *after* "_is_signed" is modified.
	set_size(s_data_size);
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

		if (is_negative())
		{
			ret |= !one_bit(i - 1);
		}
		else // if (!is_negative())
		{
			ret |= one_bit(i - 1);
		}
	}


	if (is_negative())
	{
		ret += 1;
		ret = -ret;
	}

	return ret;
}

void ExprNum::set_size(size_t n_size)
{
	if (_data == nullptr)
	{
		RawExprNumData n_data;
		n_data.resize(n_size, false);
		set_data(n_data);

		return;
	}
	RawExprNumData n_data(data());
	n_data.resize(n_size, false);

	if (n_size > size())
	{
		if (!is_signed())
		{
			for (size_t i=size(); i<n_data.size(); ++i)
			{
				n_data.at(i) = 0;
			}
		}
		else // if (is_signed())
		{
			if (size() > 0)
			{
				for (size_t i=size(); i<n_data.size(); ++i)
				{
					n_data.at(i) = one_bit(size() - 1);
				}
			}
			else // if (size() == 0)
			{
				for (size_t i=size(); i<n_data.size(); ++i)
				{
					n_data.at(i) = 0;
				}
			}
		}
	}

	set_data(n_data);
}

RawExprNumData ExprNum::multiple_bits(size_t start_index, size_t amount)
	const
{
	RawExprNumData ret;

	for (size_t i=start_index; i<(start_index + amount); ++i)
	{
		ret.push_back(one_bit(i));
	}

	return ret;
}
void ExprNum::set_multiple_bits(size_t start_index,
	const RawExprNumData& some_bits)
{
	auto n_data(data());

	for (size_t i=0; i<some_bits.size(); ++i)
	{
		n_data.at(start_index + i) = some_bits.at(i);
	}

	set_data(n_data);
}

} // namespace frost_hdl
