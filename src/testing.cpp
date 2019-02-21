#include "testing.hpp"
#include "expr_num_class.hpp"
#include "expression_classes.hpp"


namespace frost_hdl
{

using liborangepower::bignum::convert_bignum_to_str;

void test_expr_num_conversion(std::ostream& os, size_t test_data_width)
{
	for (BigNum iter=(-(1 << (test_data_width - 1)));
		iter<(1 << (test_data_width - 1));
		++iter)
	{
		const ExprNum test_expr_num(iter, test_data_width, true);

		const BigNum back_to_big_num = static_cast<BigNum>(test_expr_num);

		if (iter != back_to_big_num)
		{
			osprintout(os, "signed failure at ",
				convert_bignum_to_str(iter), " ",
				convert_bignum_to_str(back_to_big_num), "\n");
		}
	}

	for (BigNum iter=0; iter<(1 << test_data_width); ++iter)
	{
		const ExprNum test_expr_num(iter, test_data_width, false);

		const BigNum back_to_big_num = static_cast<BigNum>(test_expr_num);

		if (iter != back_to_big_num)
		{
			osprintout(os, "unsigned failure at ",
				convert_bignum_to_str(iter), " ",
				convert_bignum_to_str(back_to_big_num), "\n");
		}
	}
}

void test_expr_num_size_change(std::ostream& os)
{
	static constexpr size_t orig_size = 5, large_dst_size = 30,
		small_dst_size = 3;

	const ExprNum test_expr_num(-5, orig_size, true);

	//printout(BigNum(test_expr_num), "\n\n");
	//printout(test_expr_num, "\n");

	for (size_t j=test_expr_num.size(); j>0; --j)
	{
		osprintout(os, test_expr_num.one_bit(j - 1), " ");
	}
	osprintout(os, "\n\n");

	for (size_t i=small_dst_size; i<(large_dst_size + 1); ++i)
	{
		ExprNum resized_expr_num(test_expr_num, i, false);

		for (size_t j=resized_expr_num.size(); j>0; --j)
		{
			osprintout(os, resized_expr_num.one_bit(j - 1), " ");
		}
		osprintout(os, "\n");
	}

	osprintout(os, "\n");

	for (size_t i=small_dst_size; i<(large_dst_size + 1); ++i)
	{
		ExprNum resized_expr_num(test_expr_num, i);

		for (size_t j=resized_expr_num.size(); j>0; --j)
		{
			osprintout(os, resized_expr_num.one_bit(j - 1), " ");
		}
		osprintout(os, "\n");
	}
}

void test_cpp_expressions(std::ostream& os)
{
	static constexpr s32 a = -5;
	static constexpr s32 b = 2;

	osprintout(os, (a % b), "\n");

	const BigNum a_bignum(-5);
	const BigNum b_bignum(2);

	osprintout(os, (a_bignum % b_bignum), "\n");
}

void test_implemented_expressions(std::ostream& os)
{
	//static constexpr size_t width = 10;
	//// a + b
	//ExprHardCodedNum a(ExprNum(BigNum(3), width, false));
	//ExprHardCodedNum b(ExprNum(BigNum(5), width, false));

	//ExprBinOpPlus plus_of_a_comma_b(&a, &b);
	//plus_of_a_comma_b.evaluate();

	//printout(BigNum(plus_of_a_comma_b.value()), "\n");
}

} // namespace frost_hdl
