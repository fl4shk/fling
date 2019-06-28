#ifndef src_parser_class_hpp
#define src_parser_class_hpp

// src/parser_class.hpp

#include "misc_includes.hpp"
#include "lexer_class.hpp"
#include "parser_base_class.hpp"
#include "err_warn_base_class.hpp"

namespace frost_hdl
{

class Parser final : public ParserBase<Lexer>
{
private:		// variables
	//string* _text = nullptr;

public:		// functions
	Parser(std::vector<string>&& s_filename_vec);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Parser)
	~Parser();

private:		// functions



	bool _parse_decl_package();
	bool _parse_decl_module();
	bool _parse_decl_enum();
	bool _parse_decl_class();
	bool _parse_generate();
	bool _parse_func();
	bool _parse_task();
	bool _parse_module_prefix();
	bool _parse_list_param();
	bool _parse_list_port();
};

} // namespace frost_hdl


#endif		// src_parser_class_hpp
