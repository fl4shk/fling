#include "../parse_tree_visitor_class.hpp"
#include "../general_allocator_class.hpp"
#include "../expression_builder_class.hpp"
#include <sstream>

#include "dot_cpp_defines.hpp"


namespace frost_hdl
{

// Expression parsing
auto ParseTreeVisitor::visitExpr
	(Parser::ExprContext *ctx)
	-> VisitorRetType
{
	//DEBUG_EXPR(visitExprAddSub, TokOpLogical);
	//printout("\n");

	if (ctx->TokOpLogical())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprLogical());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->expr());
		auto right = _stacks.pop_expr();

		auto tok = TOK_TO_DUPPED_STR(ctx->TokOpLogical());

		if (tok == dup_str("&&"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpLogAnd>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("||"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpLogOr>(_make_src_code_pos(ctx), left, right));
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitExpr():  Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprLogical());
	}
	return nullptr;
}

auto ParseTreeVisitor::visitExprLogical
	(Parser::ExprLogicalContext *ctx)
	-> VisitorRetType
{
	//DEBUG_EXPR(visitExprAddSub, TokOpCompare);
	//printout("\n");

	if (ctx->TokOpCompare())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprLogical());
		auto right = _stacks.pop_expr();

		auto tok = TOK_TO_DUPPED_STR(ctx->TokOpCompare());

		if (tok == dup_str("=="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpEq>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("!="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpNe>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("<"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpLt>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str(">"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpGt>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("<="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpLe>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str(">="))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpCmpGe>(_make_src_code_pos(ctx), left, right));
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitExprLogical():  Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
	}
	return nullptr;
}
auto ParseTreeVisitor::visitExprCompare
	(Parser::ExprCompareContext *ctx)
	-> VisitorRetType
{
	//DEBUG_EXPR(visitExprAddSub, TokPlus);
	//DEBUG_EXPR(visitExprAddSub, TokMinus);
	//printout("\n");

	if (ctx->TokPlus())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
		auto right = _stacks.pop_expr();

		_stacks.push_expr(ExpressionBuilder::make_expr_binop
			<ExprBinOpPlus>(_make_src_code_pos(ctx), left, right));
	}
	else if (ctx->TokMinus())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
		auto right = _stacks.pop_expr();

		_stacks.push_expr(ExpressionBuilder::make_expr_binop
			<ExprBinOpMinus>(_make_src_code_pos(ctx), left, right));
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
	}
	return nullptr;
}

auto ParseTreeVisitor::visitExprAddSub
	(Parser::ExprAddSubContext *ctx)
	-> VisitorRetType
{
	//DEBUG_EXPR(visitExprAddSub, TokOpMulDivMod);
	//DEBUG_EXPR(visitExprAddSub, TokOpBitwise);
	//printout("\n");

	if (ctx->TokOpMulDivMod())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprMulDivModEtc());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto right = _stacks.pop_expr();

		auto tok = TOK_TO_DUPPED_STR(ctx->TokOpMulDivMod());

		if (tok == dup_str("*"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpMul>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("/"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpDiv>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("%"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpMod>(_make_src_code_pos(ctx), left, right));
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitExprAddSub():  "
				"TokOpMulDivMod() "
				"Eek!");
		}
	}
	else if (ctx->TokOpBitwise())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprMulDivModEtc());
		auto left = _stacks.pop_expr();

		ANY_JUST_ACCEPT_BASIC(ctx->exprAddSub());
		auto right = _stacks.pop_expr();

		auto tok = TOK_TO_DUPPED_STR(ctx->TokOpBitwise());

		if (tok == dup_str("&"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitAnd>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("|"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitOr>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("^"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitXor>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str("<<"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitLsl>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str(">>"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitLsr>(_make_src_code_pos(ctx), left, right));
		}
		else if (tok == dup_str(">>>"))
		{
			_stacks.push_expr(ExpressionBuilder::make_expr_binop
				<ExprBinOpBitAsr>(_make_src_code_pos(ctx), left, right));
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitExprAddSub():  "
				"TokOpBitwise() Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprMulDivModEtc());
	}
	return nullptr;
}
auto ParseTreeVisitor::visitExprMulDivModEtc
	(Parser::ExprMulDivModEtcContext *ctx)
	-> VisitorRetType
{
	ANY_ACCEPT_IF_BASIC(ctx->exprPlusUnary())
	else ANY_ACCEPT_IF_BASIC(ctx->exprMinusUnary())
	else ANY_ACCEPT_IF_BASIC(ctx->exprLogNot())
	else ANY_ACCEPT_IF_BASIC(ctx->exprBitNot())
	else ANY_ACCEPT_IF_BASIC(ctx->exprCastUnsgn())
	else ANY_ACCEPT_IF_BASIC(ctx->exprCastSgn())
	else ANY_ACCEPT_IF_BASIC(ctx->exprClog2())
	else ANY_ACCEPT_IF_BASIC(ctx->numExpr())
	else ANY_ACCEPT_IF_BASIC(ctx->identExpr())
	else ANY_ACCEPT_IF_BASIC(ctx->expr())
	else
	{
		_err(ctx, "ParseTreeVisitor::visitExprMulDivModEtc():  Eek!");
	}
	return nullptr;
}


auto ParseTreeVisitor::visitExprPlusUnary
	(Parser::ExprPlusUnaryContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpPlus>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
auto ParseTreeVisitor::visitExprMinusUnary
	(Parser::ExprMinusUnaryContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpMinus>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
auto ParseTreeVisitor::visitExprLogNot
	(Parser::ExprLogNotContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpLogNot>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
auto ParseTreeVisitor::visitExprBitNot
	(Parser::ExprBitNotContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpBitNot>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
auto ParseTreeVisitor::visitExprCastUnsgn
	(Parser::ExprCastUnsgnContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop
		<ExprUnOpCastUnsigned>(_make_src_code_pos(ctx),
		_stacks.pop_expr()));

	return nullptr;
}
auto ParseTreeVisitor::visitExprCastSgn
	(Parser::ExprCastSgnContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop
		<ExprUnOpCastSigned>(_make_src_code_pos(ctx),
		_stacks.pop_expr()));

	return nullptr;
}
auto ParseTreeVisitor::visitExprClog2
	(Parser::ExprClog2Context *ctx)
	-> VisitorRetType
{
	const auto arg_src_code_pos = _make_src_code_pos(ctx->expr());
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	auto expr = _stacks.pop_expr();

	if (!expr->is_constant())
	{
		//_in_scope_thing()->in_scope_err(arg_src_code_pos, sconcat("This ",
		//	"value must be constant."));
		_err(arg_src_code_pos, sconcat("This value must be constant."));
	}

	_stacks.push_expr(ExpressionBuilder::make_expr_unop
		<ExprUnOpClog2>(_make_src_code_pos(ctx), expr));

	return nullptr;
}

// I'm pretty sure this works.
auto ParseTreeVisitor::visitNumExpr
	(Parser::NumExprContext *ctx)
	-> VisitorRetType
{
	if (ctx->rawNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->rawNumExpr());
		const auto s_data = _stacks.pop_big_num();

		_stacks.push_expr(ExpressionBuilder::make_expr_hc_num_from_expr_num
			(_make_src_code_pos(ctx), ExprNum(s_data, false)));
	}
	else if (ctx->rawSizedNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->rawSizedNumExpr());
		const auto value = _stacks.pop_big_num();
		const auto size = _stacks.pop_big_num();

		_stacks.push_expr(ExpressionBuilder::make_expr_hc_num
			(_make_src_code_pos(ctx), value, size.get_ui(), false));
	}
	else if (ctx->identSizedNumExpr())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identSizedNumExpr());
		const auto s_size_expr = _stacks.pop_expr();
		const auto s_temp_value = _stacks.pop_big_num();

		if (!s_size_expr->is_constant())
		{
			//_in_scope_thing()->in_scope_err(s_size_expr->src_code_pos(),
			//	"Hard-coded constants must have constant widths.");
			_err(s_size_expr->src_code_pos(), "Hard-coded constants "
				"must have constant widths.");
		}

		_stacks.push_expr(ExpressionBuilder::make_expr_ident_sized_hc_num
			(_make_src_code_pos(ctx), s_size_expr, s_temp_value));
	}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitNumExpr():  Eek!");
	}

	return nullptr;
}

// I'm pretty sure this works.
auto ParseTreeVisitor::visitRawNumExpr
	(Parser::RawNumExprContext *ctx)
	-> VisitorRetType
{
	BigNum to_push(0);
	if (ctx->TokDecNum())
	{
		for (auto c : ctx->TokDecNum()->toString())
		{
			to_push = (to_push * 10) + (c - '0');
		}

		_stacks.push_big_num(to_push);
	}
	else if (ctx->TokHexNum())
	{
		const auto& as_string = ctx->TokHexNum()->toString();
		for (size_t i=0; i<as_string.size(); ++i)
		{
			// Skip the prefix of "0x"
			if (i < 2)
			{
				continue;
			}

			const auto c = as_string.at(i);
			if ((c >= 'A') && (c <= 'F'))
			{
				to_push = (to_push * 0x10) + (c - 'A' + 0xA);
			}
			else if ((c >= 'a') && (c <= 'f'))
			{
				to_push = (to_push * 0x10) + (c - 'a' + 0xa);
			}
			else // if ((c >= '0') && (c <= '9'))
			{
				to_push = (to_push * 0x10) + (c - '0' + 0x0);
			}
		}

		_stacks.push_big_num(to_push);
	}
	else if (ctx->TokBinNum())
	{
		const auto& as_string = ctx->TokBinNum()->toString();
		for (size_t i=0; i<as_string.size(); ++i)
		{
			// Skip the prefix of "0b"
			if (i < 2)
			{
				continue;
			}

			const auto c = as_string.at(i);
			to_push = (to_push * 0b10) + (c - '0');
		}

		_stacks.push_big_num(to_push);
	}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitRawNumExpr():  Eek!");
	}

	return nullptr;
}
auto ParseTreeVisitor::visitRawSizedNumExpr
	(Parser::RawSizedNumExprContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_LOOPED(raw_num_expr, ctx->rawNumExpr())

	return nullptr;
}
auto ParseTreeVisitor::visitIdentSizedNumExpr
	(Parser::IdentSizedNumExprContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->pureIdentExpr());
	ANY_JUST_ACCEPT_BASIC(ctx->rawNumExpr());
	return nullptr;
}

auto ParseTreeVisitor::visitIdentExpr
	(Parser::IdentExprContext *ctx)
	-> VisitorRetType
{
	ANY_ACCEPT_IF_BASIC(ctx->pureIdentExpr())
	else ANY_ACCEPT_IF_BASIC(ctx->slicedPureIdentExpr())
	//else if (ctx->identConcatExpr())
	//{
	//	ANY_JUST_ACCEPT_BASIC(ctx->identConcatExpr());


	//}
	//else if (ctx->identSliced())
	//{
	//	ANY_JUST_ACCEPT_BASIC(ctx->identSliced());


	//}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitIdentExpr():  Eek!");
	}

	return nullptr;
}
auto ParseTreeVisitor::visitPureIdentExpr
	(Parser::PureIdentExprContext *ctx)
	-> VisitorRetType
{
	if (ctx->identName())
	{
		ANY_JUST_ACCEPT_BASIC(ctx->identName());
		auto ident = _stacks.pop_str();


		// Here we check to see whether or not the symbol actually exists
		// in the current scope.

		if (_in_package_pass())
		{
			auto package = _frost_program.curr_frost_package;
			if (package->symbol_table().contains(ident))
			{
				_stacks.push_expr(save_expr(ExprIdentName
					(_make_src_code_pos(ctx),
					package->symbol_table().at(ident))));
			}
			else
			{
				//package->in_scope_err(_make_src_code_pos(ctx), sconcat
				//	("Unknown symbol called \"", *ident, "\" at this ",
				//	"point."));
				_err(ctx, sconcat("Unknown symbol called \"", *ident,
					"\" at this point."));
			}
		}

		//else if (_in_interface_pass())
		//{
		//	auto interface = _frost_program.curr_frost_interface;
		//	if (interface->symbol_table().contains(ident))
		//	{
		//		_stacks.push_expr(save_expr(ExprIdentName
		//			(_make_src_code_pos(ctx),
		//			interface->symbol_table().at(ident))));
		//	}
		//	else
		//	{
		//		//interface->in_scope_err(_make_src_code_pos(ctx), sconcat
		//		//	("Unknown symbol called \"", *ident, "\" at this ",
		//		//	"point."));
		//		_err(ctx, sconcat("Unknown symbol called \"", *ident,
		//			"\" at this point."));
		//	}
		//}

		else if (_in_module_pass())
		{
			//auto module = _frost_program.curr_frost_module;
			auto module_scope = _stacks.get_top_module_scope();
			if (module_scope->contains_symbol(ident))
			{
				//auto symbol = module->find_symbol(ident);

				//if (!symbol->is_incomplete())
				//{
				//	_stacks.push_expr(save_expr(ExprIdentName
				//		(_make_src_code_pos(ctx), symbol)));
				//}
				//else // if (symbol->is_incomplete())
				//{
				//	_stacks.push_expr(save_expr(ExprSubpassIdentName
				//		(_make_src_code_pos(ctx), symbol)));
				//}
				_stacks.push_expr(save_expr(ExprIdentName
					(_make_src_code_pos(ctx),
					module_scope->find_symbol(ident))));
			}
			else
			{
				//module->in_scope_err(_make_src_code_pos(ctx), sconcat
				//	("Unknown symbol called \"", *ident, "\" at this ",
				//	"point."));
				_err(ctx, sconcat("Unknown symbol called \"", *ident,
					"\" at this point."));
			}
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitPureIdentExpr():  "
				"identName() pass() Eek!");
		}
	}

	else if (ctx->scopedIdentName())
	{
		//_err(ctx, "ParseTreeVisitor::visitPureIdentExpr():  "
		//	"scopedIdentName() not implemented Eek!");
		ANY_JUST_ACCEPT_BASIC(ctx->scopedIdentName());
	
		const auto num_scopes = _stacks.pop_small_num();

		if (num_scopes == 2)
		{
			auto most_inner_ident = _stacks.pop_str();
			auto which_scope = _stacks.pop_str();

			// Local enums come before packages because local symbols
			// override global ones.  Perhaps a warning should be spat out
			// if a local symbol overrides a global one?
			auto& frost_package_table = _frost_program.frost_package_table;

			//InScopeErrWarnBase<SrcCodePos>* in_scope_thing = nullptr;

			//if (_in_package_pass())
			//{
			//	in_scope_thing = _frost_program.curr_frost_package;
			//}
			////else if (_in_interface_pass())
			////{
			////	in_scope_thing = _frost_program.curr_frost_interface;
			////}
			//else if (_in_module_pass())
			//{
			//	in_scope_thing = _frost_program.curr_frost_module;
			//}

			if (!frost_package_table.contains(which_scope))
			{
				//_in_scope_thing()->in_scope_err(_make_src_code_pos(ctx),
				//	sconcat("Unknown package called \"", *which_scope,
				//	"\"."));
				_err(ctx, sconcat("Unknown package called \"",
					*which_scope, "\"."));
			}

			auto package = frost_package_table.at(which_scope);

			if (!package->symbol_table().contains(most_inner_ident))
			{
				//_in_scope_thing()->in_scope_err(_make_src_code_pos(ctx),
				//	sconcat("Package \"", *package->ident(), "\" does ",
				//	"not contain a symbol called \"", *most_inner_ident,
				//	"\"."));
				_err(ctx, sconcat("Package \"", *package->ident(), "\" ",
					"does not contain a symbol called \"",
					*most_inner_ident, "\"."));
			}

			//auto symbol = package->symbol_table().at(most_inner_ident);


			//if (symbol->is_incomplete())
			//{
			//	//printout("test:  ", *symbol->ident(), "\n");
			//	//in_scope_thing->in_scope_warn(_make_src_code_pos(ctx),
			//	//	sconcat("test:  ", *symbol->ident()));
			//	//_needs_another_subpass = true;
			//	_stacks.push_expr(save_expr(ExprSubpassIdentName
			//		(_make_src_code_pos(ctx), symbol)));
			//}
			//else // if (symbol->frost_full_type() != nullptr)
			//{
			//	_stacks.push_expr(save_expr(ExprIdentName
			//		(_make_src_code_pos(ctx), symbol)));
			//}
			_stacks.push_expr(save_expr(ExprIdentName
				(_make_src_code_pos(ctx), package->symbol_table()
				.at(most_inner_ident))));
		}
		else if (num_scopes == 3)
		{
			// This is a reference to a particular value of an enum that is
			// inside of a package.
			// Since enums aren't fully implemented yet, this is being
			// skipped for now.
			_err(ctx, "ParseTreeVisitor::visitPureIdentExpr():  "
				"scopedIdentName() (num_scopes == 3) not implemented "
				"Eek!");
		}
		else
		{
			_err(ctx, "ParseTreeVisitor::visitPureIdentExpr():  "
				"scopedIdentName() num_scopes Eek!");
		}
	}
	else
	{
		_err(ctx, "ParseTreeVisitor::visitPureIdentExpr():  Eek!");
	}
	return nullptr;
}
//auto ParseTreeVisitor::visitMemberAccessIdentExpr
//	(Parser::MemberAccessIdentExprContext *ctx)
//	-> VisitorRetType
//{
//	return nullptr;
//}
auto ParseTreeVisitor::visitSlicedPureIdentExpr
	(Parser::SlicedPureIdentExprContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->pureIdentExpr());
	auto ident_expr = _stacks.pop_expr();
	auto symbol = ident_expr->symbol();

	Expression* first_slice_with_one_expr = nullptr;

	if (ctx->sliceWithOne())
	{
		// Ban array indexing into a non-array.
		if (!symbol->frost_full_type()->is_array())
		{
			_err(ctx->sliceWithOne(), sconcat("Variable with identifier ",
				"\"", *symbol->ident(), "\" is sliced too many times"));
		}

		ANY_JUST_ACCEPT_BASIC(ctx->sliceWithOne());
		first_slice_with_one_expr = _stacks.pop_expr();
	}

	ANY_JUST_ACCEPT_BASIC(ctx->sliceWithAny());

	const auto num_exprs_in_slice_with_any = _stacks.pop_small_num();
	if (num_exprs_in_slice_with_any == 1)
	{
		auto second_slice_with_one_expr = _stacks.pop_expr();
	}
	else if (num_exprs_in_slice_with_any == 2)
	{
		auto slice_with_range_left_expr = _stacks.pop_expr();
		auto slice_with_range_right_expr = _stacks.pop_expr();
	}
	else
	{
		_err(ctx->sliceWithAny(), "ParseTreeVisitor"
			"::visitSlicedPureIdentExpr():  Eek!");
	}

	return nullptr;
}

auto ParseTreeVisitor::visitSliceWithOne
	(Parser::SliceWithOneContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	return nullptr;
}
auto ParseTreeVisitor::visitSliceWithRange
	(Parser::SliceWithRangeContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_LOOPED(iter, ctx->expr());
	return nullptr;
}
auto ParseTreeVisitor::visitSliceWithAny
	(Parser::SliceWithAnyContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto ParseTreeVisitor::visitIdentConcatExpr
	(Parser::IdentConcatExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto ParseTreeVisitor::visitIdentName
	(Parser::IdentNameContext *ctx)
	-> VisitorRetType
{
	_stacks.push_str(TOK_TO_DUPPED_STR(ctx->TokIdent()));
	//auto ident = TOK_TO_DUPPED_STR(ctx->TokIdent());

	return nullptr;
}

auto ParseTreeVisitor::visitScopedIdentName
	(Parser::ScopedIdentNameContext *ctx)
	-> VisitorRetType
{
	SmallNum num_scopes = 0;
	for (auto iter : ctx->identName())
	{
		ANY_JUST_ACCEPT_BASIC(iter);
		++num_scopes;
	}

	_stacks.push_small_num(num_scopes);
	return nullptr;
}

} // namespace frost_hdl
