#include "compiler_class.hpp"
#include "expr_num_class.hpp"
#include "expression_classes.hpp"
#include "testing.hpp"


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

	//frost_hdl::Compiler visitor(parsers);
	//return visitor.run();

	////frost_hdl::test_implemented_expressions(std::cout);

	auto usage = [&]() -> void
	{
		printerr("Usage:  ", argv[0], " <source_files>\n");
		exit(1);
	};

	if (argc < 2)
	{
		usage();
	}

}
