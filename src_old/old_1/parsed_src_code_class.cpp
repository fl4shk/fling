#include "parsed_src_code_class.hpp"
#include <fstream>

namespace frost_hdl
{

ParsedSrcCode::ParsedSrcCode()
{
}

ParsedSrcCode::ParsedSrcCode(const std::string& s_filename)
{
	//antlr4::ANTLRInputStream input(from_stdin);
	//FrostHdlGrammarLexer lexer(&input);
	//antlr4::CommonTokenStream tokens(&lexer);
	//tokens.fill();

	//FrostHdlGrammarParser parser(&tokens);
	//parser.removeErrorListeners();
	//std::unique_ptr<frost_hdl::PTVisitorErrorListener>
	//	ptvisitor_error_listener
	//	(new frost_hdl::PTVisitorErrorListener());
	//parser.addErrorListener(ptvisitor_error_listener.get());

	_filename = dup_str(s_filename);

	std::ifstream fstm(*filename());

	//std::string&& raw_file_as_string = get_istream_as_str(fstm);
	//std::string file_as_string;

	//if (raw_file_as_string.at(raw_file_as_string.size() - 1) == EOF)
	//{
	//	for (size_t i=0; i<raw_file_as_string.size() - 1; ++i)
	//	{
	//		file_as_string += raw_file_as_string.at(i);
	//	}
	//}
	//else
	//{
	//	for (auto iter : raw_file_as_string)
	//	{
	//		file_as_string += iter;
	//	}
	//}


	_input_stream.reset(new antlr4::ANTLRInputStream(get_istream_as_str
		(fstm)));
	_lexer.reset(new FrostHdlGrammarLexer(&(*_input_stream)));
	_tokens.reset(new antlr4::CommonTokenStream(&(*_lexer)));
	_tokens->fill();

	_parser.reset(new FrostHdlGrammarParser(&(*_tokens)));
	_parser->removeErrorListeners();
	_ptvisitor_error_listener.reset
		(new PTVisitorErrorListener(_filename));
	_parser->addErrorListener(_ptvisitor_error_listener.get());
}

ParsedSrcCode::~ParsedSrcCode()
{
}

} // namespace frost_hdl
