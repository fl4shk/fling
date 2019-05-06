#include "ptvisitor_class.hpp"
//#include "general_allocator_class.hpp"
//#include "expression_builder_class.hpp"

#include <sstream>
//#include "ptvisitor/dot_cpp_defines.hpp"
//
//#include "ptvisitor/list_for_gen_stack_defines.hpp"



namespace frost_hdl
{

//typedef PTVisitor::VisitorRetType VisitorRetType;


PTVisitor::PTVisitor
	(ListParsedSrcCode&& s_list_parsed_src_code)
	: _list_parsed_src_code(std::move(s_list_parsed_src_code))
{
}
PTVisitor::~PTVisitor()
{
}

int PTVisitor::run()
{
	for (const auto& parsed_src_code : _list_parsed_src_code)
	{
		_curr_filename = parsed_src_code->filename();
		visitProgram(parsed_src_code->parser()->program());
	}

	return 0;
}


} // namespace frost_hdl

#undef LIST_FOR_GEN_STACK
