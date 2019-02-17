#include "compiler_error_listener_class.hpp"
#include "compiler_class.hpp"
#include "expr_num_class.hpp"


void test_expr_num_conversion(std::ostream& os, size_t test_data_width);
void test_expr_num_size_change(std::ostream& os);

int main(int argc, char** argv)
{
	//std::string from_stdin(get_stdin_as_str());

	//antlr4::ANTLRInputStream input(from_stdin);
	//CompilerGrammarLexer lexer(&input);
	//antlr4::CommonTokenStream tokens(&lexer);
	//tokens.fill();

	//CompilerGrammarParser parser(&tokens);
	//parser.removeErrorListeners();
	//std::unique_ptr<frost_hdl::CompilerErrorListener>
	//	compiler_error_listener(new frost_hdl::CompilerErrorListener());
	//parser.addErrorListener(compiler_error_listener.get());

	//frost_hdl::Compiler visitor(parser);
	//return visitor.run();

	//const frost_hdl::ExprNum test_egg(BigNum(-2003), 12, true);

	////ASM_COMMENT("test_egg constructed.");

	//printout(liborangepower::bignum::convert_bignum_to_str
	//	(static_cast<BigNum>(test_egg)), "\n");

	//test_expr_num_conversion(std::cout, 4);

	//test_expr_num_size_change(std::cout);
}

void test_expr_num_conversion(std::ostream& os, size_t test_data_width)
{
	using frost_hdl::ExprNum;
	using liborangepower::bignum::convert_bignum_to_str;

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
	using frost_hdl::ExprNum;

	static constexpr size_t orig_size = 5, large_dst_size = 30,
		small_dst_size = 3;

	const ExprNum test_expr_num(5, orig_size, true);

	printout(BigNum(test_expr_num), "\n\n");
	//printout(test_expr_num, "\n");

	for (size_t i=small_dst_size; i<(large_dst_size + 1); ++i)
	{
		ExprNum resized_expr_num(test_expr_num, i, false);

		for (size_t j=resized_expr_num.size(); j>0; --j)
		{
			printout(resized_expr_num.one_bit(j - 1), " ");
		}
		printout("\n");
	}

	printout("\n");

	for (size_t i=small_dst_size; i<(large_dst_size + 1); ++i)
	{
		ExprNum resized_expr_num(test_expr_num, i);

		for (size_t j=resized_expr_num.size(); j>0; --j)
		{
			printout(resized_expr_num.one_bit(j - 1), " ");
		}
		printout("\n");
	}
}
