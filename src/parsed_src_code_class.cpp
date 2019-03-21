#include "parsed_src_code_class.hpp"

namespace frost_hdl
{

ParsedSrcCode::ParsedSrcCode()
{
}

ParsedSrcCode::ParsedSrcCode(SavedString s_filename)
{
	//antlr4::ANTLRInputStream input(from_stdin);
	//CompilerGrammarLexer lexer(&input);
	//antlr4::CommonTokenStream tokens(&lexer);
	//tokens.fill();

	//CompilerGrammarParser parser(&tokens);
	//parser.removeErrorListeners();
	//std::unique_ptr<frost_hdl::CompilerErrorListener>
	//	compiler_error_listener(new frost_hdl::CompilerErrorListener());
	//parser.addErrorListener(compiler_error_listener.get());

	_filename = s_filename;

	_input_stream.reset(new antlr4::ANTLRInputStream(*filename()));
	_lexer.reset(new CompilerGrammarLexer(&(*_input_stream)));
	_tokens.reset(new antlr4::CommonTokenStream(&(*_lexer)));
	_tokens->fill();

	_parser.reset(new CompilerGrammarParser(&(*_tokens)));
	_parser->removeErrorListeners();
	_compiler_error_listener.reset(new CompilerErrorListener());
	_parser->addErrorListener(_compiler_error_listener.get());
}

ParsedSrcCode::~ParsedSrcCode()
{
}

} // namespace frost_hdl
