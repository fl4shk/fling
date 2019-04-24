#include "ptvisitor_class.hpp"
#include "general_allocator_class.hpp"
#include "expression_builder_class.hpp"

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
	while (pass() < Pass::Done)
	{
		//visitProgram(_program_ctx);
		for (const auto& parsed_src_code : _list_parsed_src_code)
		{
			//_curr_parsed_src_code = &parsed_src_code;
			_curr_filename = parsed_src_code->filename();
			//printout("*_curr_filename:  ", *_curr_filename, "\n");
			visitProgram(parsed_src_code->parser()->program());
		}

		//if (_needs_another_subpass)
		//{
		//	_needs_another_subpass = false;

		//	set_subpass(subpass() + static_cast<decltype(_subpass)>(1));

		//	if (subpass() >= MAX_SUBPASS)
		//	{
		//		_err(nullptr, sconcat("Too many subpasses (", 
		//			MAX_SUBPASS, " or more)"));
		//	}

		//	_reparse();

		//	continue;
		//}

		_reparse();
		set_pass(static_cast<Pass>(static_cast<PassUint>
			(pass()) + static_cast<PassUint>(1)));
		set_subpass(0);
	}

	//for (const auto& package_iter
	//	: _frost_program.frost_package_table.table())
	//{
	//	printout("package \"", *package_iter.first, "\":\n");
	//	for (const auto& symbol_iter
	//		: package_iter.second->symbol_table().table())
	//	{
	//		const auto& symbol = symbol_iter.second;

	//		symbol->value()->full_evaluate_if_constant();

	//		printout(*symbol->ident(), " ",
	//			symbol->value()->value().convert_to_bignum(), " ",
	//			symbol->value()->value().size(), "\n");
	//	}
	//}

	return 0;
}

void PTVisitor::_reparse()
{
	// ...This is a HORRIBLE solution to a problem I don't know the
	// actual cause of.
	for (auto& parsed_src_code : _list_parsed_src_code)
	{
		*parsed_src_code = ParsedSrcCode(*parsed_src_code->filename());
	}
}
//InScopeErrWarnBase<SrcCodePos>* PTVisitor::_in_scope_thing()
//{
//	if (_in_package_pass())
//	{
//		return _frost_program.curr_frost_package;
//	}
//	//else if (_in_interface_pass())
//	//{
//	//	return _frost_program.curr_frost_interface;
//	//}
//	else if (_in_module_pass())
//	{
//		return _frost_program.curr_frost_module;
//	}
//	else
//	{
//		_err(nullptr, "PTVisitor::_in_scope_thing():  Eek!");
//	}
//
//	return nullptr;
//}

FrostLhsType* PTVisitor::_make_for_loop_iter_lhs_type
	(const SrcCodePos& s_src_code_pos) const
{
	static constexpr size_t size = sizeof(intmax_t) * CHAR_BIT;

	auto s_left_dim_expr = ExpressionBuilder::make_expr_hc_num
		(s_src_code_pos, size);
	return save_frost_lhs_type(FrostLhsType(s_src_code_pos,
		FrostLhsType::construct_initial_builtin_type_ident(true,
		s_left_dim_expr), true, s_left_dim_expr));
}



// Ports can be arrays now!
void PTVisitor::_insert_module_port_var(const SrcCodePos& s_src_code_pos,
	SavedString s_ident, Symbol::PortType s_port_type,
	FrostFullType* s_frost_full_type)
{
	// Call this ONLY if (pass() == Pass::FrostListModules)
	if (pass() != Pass::ListModuleIdentifiers)
	{
		_err(s_src_code_pos, "PTVisitor::_insert_module_port_var():  "
			"pass() Eek!");
	}

	// I am lazy.
	auto module = _frost_program.curr_frost_module;

	if (module->contains_symbol_in_top_scope(s_ident))
	{
		auto&& errwarn_string = module->find_symbol_in_top_scope(s_ident)
			->src_code_pos().convert_to_errwarn_string();
		//module->in_scope_err(s_src_code_pos, sconcat("This module ",
		//	"already has a symbol called \"", *s_ident, "\", defined at ",
		//	errwarn_string, "."));
		_err(s_src_code_pos, sconcat("This module already has a symbol ",
			"called \"", *s_ident, "\", defined at ", errwarn_string,
			"."));
	}

	// Again, I am lazy.
	SymbolTable* symbol_table = nullptr;

	switch (s_port_type)
	{
	case Symbol::PortType::Input:
		symbol_table = &module->input_symbol_table();
		break;

	case Symbol::PortType::Output:
		symbol_table = &module->output_symbol_table();
		break;

	//case Symbol::PortType::Inout:
	//	symbol_table = &module->inout_symbol_table();
	//	break;

	default:
		_err(s_src_code_pos, "PTVisitor"
			"::_insert_module_port_var():  PortType Eek!");
		break;
	}

	//auto s_frost_full_type = save_frost_full_type(FrostFullType
	//	(s_src_code_pos, s_frost_lhs_type));

	symbol_table->insert_or_assign(save_symbol(Symbol(s_src_code_pos,
		s_ident, s_port_type, s_frost_full_type)));
}

} // namespace frost_hdl

#undef LIST_FOR_GEN_STACK
