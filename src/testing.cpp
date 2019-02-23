#include "testing.hpp"
#include "expr_num_class.hpp"
#include "expression_classes.hpp"
#include "general_allocator_class.hpp"


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

//template<typename ExprType>
//static inline Expression* _show_expr_binop(std::ostream& os,
//	Expression* left_child, Expression* right_child)
//{
//	ExprType ret(left_child, right_child);
//	ret.full_evaluate_if_constant();
//	osprintout(os, ret.value().size(), " ", ret.value().is_signed(),
//		":  ", BigNum(ret.value()), "\n");
//	return save_expr(std::move(ret));
//}

static inline std::ostream& _show_expr(std::ostream& os,
	Expression* to_show)
{
	return osprintout(os, to_show->value().size(), " ",
		to_show->value().is_signed(), ":  ", BigNum(to_show->value()),
		"\n");
}
static inline auto& _show_expr(Expression* to_show)
{
	return _show_expr(std::cout, to_show);
}

template<typename NumType>
static inline auto _make_expr_hc_num(const NumType& s_data,
	size_t s_data_size, bool s_is_signed)
{
	return save_expr(ExprHardCodedNum(ExprNum(BigNum(s_data), s_data_size,
		s_is_signed)));
}

template<typename ExprType>
static inline Expression* _make_expr_unop(Expression* only_child)
{
	return save_expr(ExprType(only_child));
}

template<typename ExprType>
static inline Expression* _make_expr_binop(Expression* left_child,
	Expression* right_child)
{
	return save_expr(ExprType(left_child, right_child));
}



void test_implemented_expressions(std::ostream& os)
{
	auto a_u = _make_expr_hc_num(1, 1, false);
	auto b_u = _make_expr_hc_num(1, 1, false);
	auto c_u = _make_expr_hc_num(5, 5, false);
	auto d_u = _make_expr_binop<ExprBinOpPlus>(a_u, b_u);
	auto e_u = _make_expr_binop<ExprBinOpPlus>(d_u, c_u);

	auto a_s = _make_expr_hc_num(1, 1, true);
	auto b_s = _make_expr_hc_num(1, 1, true);
	auto c_s = _make_expr_hc_num(5, 5, true);
	auto d_s = _make_expr_binop<ExprBinOpPlus>(a_s, b_s);
	auto e_s = _make_expr_binop<ExprBinOpPlus>(d_s, c_s);

	e_u->full_evaluate_if_constant();
	e_s->full_evaluate_if_constant();

	_show_expr(e_u);
	_show_expr(e_s);
}

} // namespace frost_hdl
