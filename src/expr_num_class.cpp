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

// this calls "copy_from_bignum_with_smallest_size()"
ExprNum::ExprNum(const BigNum& s_data, bool s_is_signed)
{
	copy_from_bignum_with_smallest_size(s_data, s_is_signed);
}

// size/signedness changing constructors
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

void ExprNum::copy_from_bignum_with_smallest_size(const BigNum& n_data,
	bool n_is_signed)
{
	set_is_signed(n_is_signed);

	// I wish I'd known about this earlier, haha.
	const auto n_data_as_binary_str = n_data.get_str(2);

	if (n_data < BigNum(0))
	{
		copy_from_bignum(n_data, n_data_as_binary_str.size() - 1);
	}
	else // if (n_data > BigNum(0))
	{
		copy_from_bignum(n_data, n_data_as_binary_str.size());
	}
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
std::string ExprNum::convert_to_verilog_literal() const
{
	std::string ret;

	if (is_negative())
	{
		ret += "(-";
	}

	ret += sconcat(size(), "'");

	if (is_signed())
	{
		ret += "s";
	}

	ret += sconcat("d", convert_to_bignum());

	if (is_negative())
	{
		ret += ")";
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

// Logical Shift Left
void ExprNum::perf_lsl(const ExprNum& to_shift, const ExprNum& amount)
{
	RawExprNumData n_value_data;
	n_value_data.resize(to_shift.size(), false);

	const auto& old_data = to_shift.data();
	const auto amount_as_ui = amount.convert_to_unsigned_bignum().get_ui();

	if (amount_as_ui < n_value_data.size())
	{
		for (size_t i=0; i<(n_value_data.size() - amount_as_ui); ++i)
		{
			const auto write_index = i + amount_as_ui;
			const auto read_index = i;

			n_value_data.at(write_index) = old_data.at(read_index);
		}
	}

	set_data(std::move(n_value_data));
}

// Logical Shift Right
void ExprNum::perf_lsr(const ExprNum& to_shift, const ExprNum& amount)
{
	RawExprNumData n_data;
	n_data.resize(to_shift.size(), false);

	const auto& old_data = to_shift.data();
	const auto amount_as_ui = amount.convert_to_unsigned_bignum().get_ui();

	if (amount_as_ui < n_data.size())
	{
		for (size_t i=0; i<(n_data.size() - amount_as_ui); ++i)
		{
			const auto write_index = i;
			const auto read_index = i + amount_as_ui;

			n_data.at(write_index) = old_data.at(read_index);
		}
	}

	set_data(std::move(n_data));
}

// Arithmetic Shift Right
void ExprNum::perf_asr(const ExprNum& to_shift, const ExprNum& amount)
{
	RawExprNumData n_data;

	const auto& old_data = to_shift.data();
	const auto amount_as_ui = amount.convert_to_unsigned_bignum().get_ui();

	// ">>>" only acts as an arithmetic right shift when thing to shift is
	// signed.
	if (to_shift.is_signed())
	{
		n_data.resize(to_shift.size(), old_data.back());
	}
	else // if (!_left_child_value().is_signed())
	{
		n_data.resize(to_shift.size(), false);
	}


	if (amount_as_ui < n_data.size())
	{
		for (size_t i=0; i<(n_data.size() - amount_as_ui); ++i)
		{
			const auto write_index = i;
			const auto read_index = i + amount_as_ui;

			n_data.at(write_index) = old_data.at(read_index);
		}
	}

	set_data(std::move(n_data));
}

} // namespace frost_hdl
