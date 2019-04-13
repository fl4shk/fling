#include "../parse_tree_visitor_class.hpp"
#include "../general_allocator_class.hpp"
#include "../expression_builder_class.hpp"
#include <sstream>

#include "dot_cpp_defines.hpp"


namespace frost_hdl
{

// Variable declaration stuff
auto ParseTreeVisitor::visitLhsTypeName
	(Parser::LhsTypeNameContext *ctx)
	-> VisitorRetType
{
	ANY_ACCEPT_IF_BASIC(ctx->lhsBuiltinTypeName())
	//else ANY_ACCEPT_IF_BASIC(ctx->lhsUnscopedCstmTypeName())
	//else ANY_ACCEPT_IF_BASIC(ctx->lhsScopedCstmTypeName())
	else
	{
		_err(ctx, "ParseTreeVisitor::visitLhsTypeName():  Eek!");
	}
	return nullptr;
}

auto ParseTreeVisitor::visitLhsBuiltinTypeName
	(Parser::LhsBuiltinTypeNameContext *ctx)
	-> VisitorRetType
{
	// only call this when pass() == Pass::ListModuleIdentifiers

	Expression* s_left_dim_expr = nullptr;
	if (ctx->expr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->expr());
		s_left_dim_expr = _stacks.pop_expr();

		//// Helpful warning
		//if (static_cast<BigNum>(s_left_dim_expr->value())
		//	< static_cast<BigNum>(0))
		//{
		//	_warn(ctx, "Dimensions of vector are signed and evaluate to less"
		//		" than zero.  They will be treated as an unsigned value."
		//		"  This is might not be what you want.");
		//}

		if (!s_left_dim_expr->is_constant())
		{
			//_in_scope_thing()->in_scope_err(_make_src_code_pos
			//	(ctx->expr()), "Vectors must have constant dimensions.");
			_err(ctx->expr(), "Vectors must have constant dimensions.");
		}
	}

	auto s_ident = FrostLhsType::construct_initial_builtin_type_ident
		((ctx->TokKwSigned() != nullptr), s_left_dim_expr);


	// "ctx->TokKwUnsigned()" is only for those who want to be pedantic.

	_stacks.push_lhs_type(save_frost_lhs_type(FrostLhsType
		(_make_src_code_pos(ctx), s_ident,
		(ctx->TokKwSigned() != nullptr), s_left_dim_expr)));
	return nullptr;
}

// custom type name from the current scope, be it a module or a package.
// (FUTURE)
auto ParseTreeVisitor::visitLhsUnscopedCstmTypeName
	(Parser::LhsUnscopedCstmTypeNameContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

// custom type name from a package.
// (FUTURE)
auto ParseTreeVisitor::visitLhsScopedCstmTypeName
	(Parser::LhsScopedCstmTypeNameContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

} // namespace frost_hdl
