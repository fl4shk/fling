#include "expr_num_class.hpp"

namespace frost_hdl
{


//void ExprNum::copy_from_bignum(const BigNum& n_data, size_t n_data_size)
//{
//	BigNum mask = 1;
//
//	RawExprNumData temp_data;
//
//	for (size_t i=0; i<n_data_size; ++i)
//	{
//		//_data.push_back((n_data & mask) != BigNum(0));
//		temp_data.push_back((n_data & mask) != BigNum(0));
//		mask *= 2;
//	}
//
//	set_data(temp_data);
//}
//
//BigNum ExprNum::convert_to_bignum() const
//{
//	BigNum ret = 0;
//
//	for (size_t i=size(); i>0; --i)
//	{
//		ret *= 2;
//		ret |= one_bit(i - 1);
//	}
//
//	return ret;
//}

//void ExprNum::set_size(size_t n_size)
//{
//	//if (n_size > size())
//	//{
//	//	RawExprNumData 
//	//}
//}


} // namespace frost_hdl
