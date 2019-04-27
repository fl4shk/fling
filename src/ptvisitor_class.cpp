#include "ptvisitor_class.hpp"
#include "general_allocator_class.hpp"
//#include "expression_builder_class.hpp"

#include <sstream>
#include "ptvisitor/dot_cpp_defines.hpp"

#include "ptvisitor/list_for_gen_stack_defines.hpp"



namespace frost_hdl
{

//typedef PTVisitor::VisitorRetType VisitorRetType;


PTVisitor::PTVisitor
	(ListParsedSrcCode&& s_list_parsed_src_code)
	: _list_parsed_src_code(std::move(s_list_parsed_src_code))
{
	//_program_ctx = parser.program();
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

	//while (pass() < Pass::Done)
	//{
	//	//visitProgram(_program_ctx);
	//	for (const auto& parsed_src_code : _list_parsed_src_code)
	//	{
	//		//_curr_parsed_src_code = &parsed_src_code;
	//		_curr_filename = parsed_src_code->filename();
	//		//printout("*_curr_filename:  ", *_curr_filename, "\n");
	//		visitProgram(parsed_src_code->parser()->program());
	//	}

	//	//if (_needs_another_subpass)
	//	//{
	//	//	_needs_another_subpass = false;

	//	//	set_subpass(subpass() + static_cast<decltype(_subpass)>(1));

	//	//	if (subpass() >= MAX_SUBPASS)
	//	//	{
	//	//		_err(nullptr, sconcat("Too many subpasses (", 
	//	//			MAX_SUBPASS, " or more)"));
	//	//	}

	//	//	_reparse();

	//	//	continue;
	//	//}

	//	_reparse();
	//	set_pass(static_cast<Pass>(static_cast<PassUint>
	//		(pass()) + static_cast<PassUint>(1)));
	//	set_subpass(0);
	//}

	////for (const auto& package_iter
	////	: _frost_program.frost_package_table.table())
	////{
	////	printout("package \"", *package_iter.first, "\":\n");
	////	for (const auto& symbol_iter
	////		: package_iter.second->symbol_table().table())
	////	{
	////		const auto& symbol = symbol_iter.second;

	////		symbol->value()->full_evaluate_if_constant();

	////		printout(*symbol->ident(), " ",
	////			symbol->value()->value().convert_to_bignum(), " ",
	////			symbol->value()->value().size(), "\n");
	////	}
	////}

	return 0;
}


} // namespace frost_hdl

#undef LIST_FOR_GEN_STACK
