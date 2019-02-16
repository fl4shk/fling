#include "expr_num_class.hpp"

namespace frost_hdl
{

ExprNum::ExprNum(const BigNum& s_data, size_t s_data_size,
	bool s_is_signed)
{
	_is_signed = s_is_signed;

	copy_from_bignum(s_data, s_data_size);
}
void ExprNum::copy_from_bignum(const BigNum& n_data, size_t n_data_size)
{
	BigNum mask = 1;

	for (size_t i=0; i<n_data_size; ++i)
	{
		_data.push_back((n_data & mask) != BigNum(0));
		mask *= 2;
	}
}

BigNum ExprNum::convert_to_bignum() const
{
	BigNum ret = 0;

	for (size_t i=_data.size(); i>0; --i)
	{
		ret *= 2;
		ret |= _data.at(i - 1);
	}

	return ret;
}

//bool ExprNum::operator && (const ExprNum& other) const
//{
//}
//bool ExprNum::operator || (const ExprNum& other) const
//{
//}
bool ExprNum::operator == (const ExprNum& other) const
{
	return (_data == other._data);
}
bool ExprNum::operator != (const ExprNum& other) const
{
	return (_data != other._data);
}
//bool ExprNum::operator < (const ExprNum& other) const
//{
//}
//bool ExprNum::operator > (const ExprNum& other) const
//{
//}
//bool ExprNum::operator <= (const ExprNum& other) const
//{
//}
//bool ExprNum::operator >= (const ExprNum& other) const
//{
//}
//
//ExprNum ExprNum::operator + (const ExprNum& other) const
//{
//}
//ExprNum ExprNum::operator - (const ExprNum& other) const
//{
//}
//
//ExprNum ExprNum::operator * (const ExprNum& other) const
//{
//}
//ExprNum ExprNum::operator / (const ExprNum& other) const
//{
//}
//ExprNum ExprNum::operator % (const ExprNum& other) const
//{
//}
//
//ExprNum ExprNum::operator & (const ExprNum& other) const
//{
//}
//ExprNum ExprNum::operator | (const ExprNum& other) const
//{
//}
//ExprNum ExprNum::operator ^ (const ExprNum& other) const
//{
//}
//
//ExprNum ExprNum::operator << (const ExprNum& other) const
//{
//}
//ExprNum ExprNum::operator >> (const ExprNum& other) const
//{
//}


} // namespace frost_hdl
