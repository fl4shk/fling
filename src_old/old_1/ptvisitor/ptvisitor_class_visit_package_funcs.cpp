#include "../ptvisitor_class.hpp"
#include "../general_allocator_class.hpp"
#include "../expression_builder_class.hpp"
#include <sstream>

#include "dot_cpp_defines.hpp"


namespace frost_hdl
{

// "package" stuff
auto PTVisitor::visitDeclPackage
	(Parser::DeclPackageContext *ctx)
	-> VisitorRetType
{
	if (pass() == Pass::ListPackageIdentifiers)
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto s_ident = _stacks.pop_str();

		auto& frost_package_table = _frost_program.frost_package_table;
		auto& curr_frost_package = _frost_program.curr_frost_package;

		if (frost_package_table.contains(s_ident))
		{
			_err(ctx, sconcat("Duplicate package called \"", *s_ident,
				"\", previously declared at ", frost_package_table.at
				(s_ident)->src_code_pos().convert_to_errwarn_string(),
				"."));
		}

		curr_frost_package = save_frost_package(FrostPackage
			(_make_src_code_pos(ctx), s_ident));

		frost_package_table.insert_or_assign(curr_frost_package);
	}
	else if ((pass() == Pass::ListPackageInnerDecl)
		|| (pass() == Pass::FinishRawPackageConstruct))
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		_frost_program.curr_frost_package
			= _frost_program.frost_package_table.at(_stacks.pop_str());

		ANY_JUST_ACCEPT_BASIC(ctx->insidePackage());
	}
	else
	{
		_err(ctx, "PTVisitor::visitDeclPackage():  Eek!");
	}
	return nullptr;
}
auto PTVisitor::visitInsidePackage
	(Parser::InsidePackageContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_LOOPED(decl_localparam_list_iter,
		ctx->declLocalparamList())

	//ANY_JUST_ACCEPT_BASIC(ctx->declStruct())
	////ANY_JUST_ACCEPT_BASIC(ctx->declClass())
	//ANY_JUST_ACCEPT_BASIC(ctx->declEnum())
	//ANY_JUST_ACCEPT_BASIC(ctx->declFunction())
	//ANY_JUST_ACCEPT_BASIC(ctx->declTypedef())

	return nullptr;
}

} // namespace frost_hdl
