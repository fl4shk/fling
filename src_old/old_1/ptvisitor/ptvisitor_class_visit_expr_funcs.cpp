#include "../ptvisitor_class.hpp"
#include "../general_allocator_class.hpp"
#include "../expression_builder_class.hpp"
#include <sstream>

#include "dot_cpp_defines.hpp"


namespace frost_hdl
{

// Expression parsing
auto PTVisitor::visitExpr
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
			_err(ctx, "PTVisitor::visitExpr():  Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprLogical());
	}
	return nullptr;
}

auto PTVisitor::visitExprLogical
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
			_err(ctx, "PTVisitor::visitExprLogical():  Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprCompare());
	}
	return nullptr;
}
auto PTVisitor::visitExprCompare
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

auto PTVisitor::visitExprAddSub
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
			_err(ctx, "PTVisitor::visitExprAddSub():  "
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
			_err(ctx, "PTVisitor::visitExprAddSub():  "
				"TokOpBitwise() Eek!");
		}
	}
	else
	{
		ANY_JUST_ACCEPT_BASIC(ctx->exprMulDivModEtc());
	}
	return nullptr;
}
auto PTVisitor::visitExprMulDivModEtc
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
		_err(ctx, "PTVisitor::visitExprMulDivModEtc():  Eek!");
	}
	return nullptr;
}


auto PTVisitor::visitExprPlusUnary
	(Parser::ExprPlusUnaryContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpPlus>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
auto PTVisitor::visitExprMinusUnary
	(Parser::ExprMinusUnaryContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpMinus>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
auto PTVisitor::visitExprLogNot
	(Parser::ExprLogNotContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpLogNot>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
auto PTVisitor::visitExprBitNot
	(Parser::ExprBitNotContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop<ExprUnOpBitNot>
		(_make_src_code_pos(ctx), _stacks.pop_expr()));

	return nullptr;
}
auto PTVisitor::visitExprCastUnsgn
	(Parser::ExprCastUnsgnContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop
		<ExprUnOpCastUnsigned>(_make_src_code_pos(ctx),
		_stacks.pop_expr()));

	return nullptr;
}
auto PTVisitor::visitExprCastSgn
	(Parser::ExprCastSgnContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	_stacks.push_expr(ExpressionBuilder::make_expr_unop
		<ExprUnOpCastSigned>(_make_src_code_pos(ctx),
		_stacks.pop_expr()));

	return nullptr;
}
auto PTVisitor::visitExprClog2
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
auto PTVisitor::visitNumExpr
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
		_err(ctx, "PTVisitor::visitNumExpr():  Eek!");
	}

	return nullptr;
}

// I'm pretty sure this works.
auto PTVisitor::visitRawNumExpr
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
		_err(ctx, "PTVisitor::visitRawNumExpr():  Eek!");
	}

	return nullptr;
}
auto PTVisitor::visitRawSizedNumExpr
	(Parser::RawSizedNumExprContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_LOOPED(raw_num_expr, ctx->rawNumExpr())

	return nullptr;
}
auto PTVisitor::visitIdentSizedNumExpr
	(Parser::IdentSizedNumExprContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->nonSlicedPureIdentExpr());
	ANY_JUST_ACCEPT_BASIC(ctx->rawNumExpr());
	return nullptr;
}

auto PTVisitor::visitIdentExpr
	(Parser::IdentExprContext *ctx)
	-> VisitorRetType
{
	ANY_ACCEPT_IF_BASIC(ctx->nonSlicedPureIdentExpr())
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
		_err(ctx, "PTVisitor::visitIdentExpr():  Eek!");
	}

	return nullptr;
}
auto PTVisitor::visitPureIdent
	(Parser::PureIdentContext *ctx)
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
				//// This assumes that arrays can't be stored in packages.
				//_stacks.push_expr(save_expr(ExprIdentName
				//	(_make_src_code_pos(ctx),
				//	package->symbol_table().at(ident))));
				_stacks.push_sym(package->symbol_table().at(ident));
				_stacks.push_src_code_pos(_make_src_code_pos(ctx));
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
		//	if ()
		//	{
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
				_stacks.push_sym(module_scope->find_symbol(ident));
				_stacks.push_src_code_pos(_make_src_code_pos(ctx));
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
			_err(ctx, "PTVisitor::visitPureIdentExpr():  "
				"identName() pass() Eek!");
		}
	}

	else if (ctx->scopedIdentName())
	{
		//_err(ctx, "PTVisitor::visitPureIdentExpr():  "
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
				_err(ctx, sconcat("Package \"", *package->ident(), "\" ",
					"does not contain a symbol called \"",
					*most_inner_ident, "\"."));
			}

			_stacks.push_sym(package->symbol_table().at(most_inner_ident));
			_stacks.push_src_code_pos(_make_src_code_pos(ctx));
		}
		else if (num_scopes == 3)
		{
			// This is a reference to a particular value of an enum that is
			// inside of a package.
			// Since enums aren't fully implemented yet, this is being
			// skipped for now.
			_err(ctx, "PTVisitor::visitPureIdentExpr():  "
				"scopedIdentName() (num_scopes == 3) not implemented "
				"Eek!");
		}
		else
		{
			_err(ctx, "PTVisitor::visitPureIdentExpr():  "
				"scopedIdentName() num_scopes Eek!");
		}
	}
	else
	{
		_err(ctx, "PTVisitor::visitPureIdentExpr():  Eek!");
	}
	return nullptr;
}
//auto PTVisitor::visitMemberAccessIdentExpr
//	(Parser::MemberAccessIdentExprContext *ctx)
//	-> VisitorRetType
//{
//	return nullptr;
//}
auto PTVisitor::visitNonSlicedPureIdentExpr
	(Parser::NonSlicedPureIdentExprContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->pureIdent());

	auto symbol = _stacks.pop_sym();
	const auto src_code_pos = _stacks.pop_src_code_pos();

	if ((!symbol->is_constant())
		&& (symbol->frost_full_type()->is_array()))
	{
		_err(src_code_pos, "Can only reference one array element at a "
			"time");
	}

	_stacks.push_expr(save_expr(ExprIdentName(src_code_pos, symbol)));

	return nullptr;
};
auto PTVisitor::visitSlicedPureIdentExpr
	(Parser::SlicedPureIdentExprContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->pureIdent());
	//auto ident_expr = _stacks.pop_expr();
	//auto symbol = ident_expr->symbol();
	auto symbol = _stacks.pop_sym();
	const auto src_code_pos = _stacks.pop_src_code_pos();

	Expression* first_slice_with_one_expr = nullptr;

	if (ctx->sliceWithOne())
	{
		// Ban array indexing into a non-array.
		if (symbol->is_constant()
			|| (!symbol->frost_full_type()->is_array()))
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

		if (first_slice_with_one_expr == nullptr)
		{
			if (symbol->is_constant()
				|| (!symbol->frost_full_type()->is_array()))
			{
				// vector[one_bit_index]
				_stacks.push_expr(save_expr(ExprIdentOneBitSlicedVector
					(_make_src_code_pos(ctx), symbol,
					second_slice_with_one_expr)));
			}
			else // if (symbol->frost_full_type()->is_array())
			{
				// array[array_index]
				_stacks.push_expr(save_expr(ExprIdentIndexedArray
					(_make_src_code_pos(ctx), symbol,
					second_slice_with_one_expr)));
			}
		}
		else // if (first_slice_with_one_expr != nullptr)
		{
			// array[array_index][one_bit_index]
			_stacks.push_expr(save_expr
				(ExprIdentIndexedAndOneBitSlicedArray
				(_make_src_code_pos(ctx), symbol,
				first_slice_with_one_expr, second_slice_with_one_expr)));
		}
	}
	else if (num_exprs_in_slice_with_any == 2)
	{
		auto slice_with_range_left_expr = _stacks.pop_expr();
		auto slice_with_range_right_expr = _stacks.pop_expr();

		if (first_slice_with_one_expr == nullptr)
		{
			// vector[left:right]
			if ((!symbol->is_constant())
				&& symbol->frost_full_type()->is_array())
			{
				_err(ctx->sliceWithAny(), sconcat("Cannot perform ",
					"multiple element slice of entire array"));
			}

			_stacks.push_expr(save_expr(ExprIdentSlicedVector
				(_make_src_code_pos(ctx), symbol,
				slice_with_range_left_expr, slice_with_range_right_expr)));
		}
		else // if (first_slice_with_one_expr != nullptr)
		{
			// array[array_index][left:right]
			_stacks.push_expr(save_expr(ExprIdentIndexedAndSlicedArray
				(_make_src_code_pos(ctx), symbol,
				first_slice_with_one_expr, slice_with_range_left_expr,
				slice_with_range_right_expr)));
		}
	}
	else
	{
		_err(ctx->sliceWithAny(), "PTVisitor"
			"::visitSlicedPureIdentExpr():  Eek!");
	}

	return nullptr;
}

auto PTVisitor::visitSliceWithOne
	(Parser::SliceWithOneContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_BASIC(ctx->expr());
	return nullptr;
}
auto PTVisitor::visitSliceWithRange
	(Parser::SliceWithRangeContext *ctx)
	-> VisitorRetType
{
	ANY_JUST_ACCEPT_LOOPED(iter, ctx->expr());
	return nullptr;
}
auto PTVisitor::visitSliceWithAny
	(Parser::SliceWithAnyContext *ctx)
	-> VisitorRetType
{
	if (ctx->sliceWithOne())
	{
		_stacks.push_small_num(1);
		ANY_JUST_ACCEPT_BASIC(ctx->sliceWithOne());
	}
	else if (ctx->sliceWithRange())
	{
		_stacks.push_small_num(2);
		ANY_JUST_ACCEPT_BASIC(ctx->sliceWithRange());
	}
	else
	{
		_err(ctx, "PTVisitor::visitSliceWithAny():  Eek!");
	}

	return nullptr;
}
auto PTVisitor::visitIdentConcatExpr
	(Parser::IdentConcatExprContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto PTVisitor::visitIdentName
	(Parser::IdentNameContext *ctx)
	-> VisitorRetType
{
	_stacks.push_str(TOK_TO_DUPPED_STR(ctx->TokIdent()));
	//auto ident = TOK_TO_DUPPED_STR(ctx->TokIdent());

	return nullptr;
}

auto PTVisitor::visitScopedIdentName
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
