#ifndef src_expr_expr_bin_op_classes_hpp
#define src_expr_expr_bin_op_classes_hpp

// src/expr/expr_bin_op_classes.hpp

#include "../misc_includes.hpp"

#include "dot_hpp_defines.hpp"

namespace frost_hdl
{

class ExprBaseBinOp : public Expression
{
public:		// functions
	ExprBaseBinOp(const SrcCodePos& s_src_code_pos, Expression* left_child,
		Expression* right_child);

	virtual SavedString to_hdl_source() const
	{
		return dup_str(TO_HDL_SOURCE(_left_child), " ", *_binop_str(), " ",
			TO_HDL_SOURCE(_right_child));
	}


protected:		// functions
	virtual SavedString _binop_str() const
	{
		return nullptr;
	}

	inline Expression* _left_child() const
	{
		return children().at(0);
	}

	inline Expression* _right_child() const
	{
		return children().at(1);
	}

	inline const ExprNum& _left_child_value() const
	{
		return _left_child()->value();
	}
	inline const ExprNum& _right_child_value() const
	{
		return _right_child()->value();
	}
};

// "&&", "||", "==", "!=", "<", ">", "<=", ">="
class ExprBaseLogCmpBinOp : public ExprBaseBinOp
{
public:		// types
	typedef BigNum (*CmpEvalFunc)(const BigNum& left, const BigNum& right);

public:		// functions
	ExprBaseLogCmpBinOp(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(s_src_code_pos, left_child, right_child)
	{
		// This *has* to be done in this class or later down the hierarchy,
		// and not in one of the classes this one is derived from, at least
		// if done in the *constructor* of one of the classes this one is
		// derived from.
		//_value.set_size(_starting_length());

		// Comparisons, "&&", and "||" produce an *unsigned*, 1-bit value.
		_value.set_is_signed(false);
	}


protected:		// functions
	//inline void _get_resized_child_expr_nums(ExprNum& left_ret,
	//	ExprNum& right_ret) const
	//{
	//	left_ret = _left_child_value();
	//	right_ret = _right_child_value();

	//	if (left_ret.size() < right_ret.size())
	//	{
	//		left_ret.set_size(right_ret.size());
	//	}
	//	else // if (left_ret.size() >= right_ret.size())
	//	{
	//		right_ret.set_size(left_ret.size());
	//	}
	//}
	void _perf_compare(CmpEvalFunc cmp_eval_func)
	{
		if (_left_child_value().is_signed()
			&& _right_child_value().is_signed())
		{
			_value.copy_from_bignum(cmp_eval_func
				(static_cast<BigNum>(_left_child_value()),
				static_cast<BigNum>(_right_child_value())));
		}
		else
		{
			// Verilog dictates that, unless *both* expressions in a
			// compare are signed, the compare will be an unsigned one, at
			// least if there are no "real"s involved.  In this HDL,
			// however, there are no "real"s, so the only numeric types are
			// "unsigned" and "signed".
			_value.copy_from_bignum(cmp_eval_func
				(_left_child_value().convert_to_unsigned_bignum(),
				_right_child_value().convert_to_unsigned_bignum()));
		}
	}

	bool _children_affect_length() const
	{
		return false;
	}

	size_t _starting_length() const
	{
		return 1;
	}
};

// "+", "-", "*", "/", "%"
class ExprBaseArithBinOp : public ExprBaseBinOp
{
public:		// functions
	ExprBaseArithBinOp(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(s_src_code_pos, left_child, right_child)
	{
		// This *has* to be done in this class or later down the hierarchy,
		// and not in one of the classes this one is derived from, at least
		// if done in the *constructor* of one of the classes this one is
		// derived from.
		//_value.set_size(_starting_length());

		_value.set_is_signed(_left_child_value().is_signed()
			&& _right_child_value().is_signed());
	}

protected:		// functions
	size_t _starting_length() const
	{
		// max(sizeof(left_child), sizeof(right_child))
		return max_va(_left_child()->value().size(),
			_right_child()->value().size());
	}

};

// "&", "|", "^"
class ExprBaseBitNonShiftBinOp : public ExprBaseBinOp
{
public:		// functions
	ExprBaseBitNonShiftBinOp(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(s_src_code_pos, left_child, right_child)
	{
		// This *has* to be done in this class or later down the hierarchy,
		// and not in one of the classes this one is derived from, at least
		// if done in the *constructor* of one of the classes this one is
		// derived from.
		//_value.set_size(_starting_length());

		// I'm not sure this is correct.
		// FIXME:  POSSIBLE BUG HERE
		_value.set_is_signed(_left_child_value().is_signed()
			&& _right_child_value().is_signed());
	}

protected:		// functions
	size_t _starting_length() const
	{
		// max(sizeof(left_child), sizeof(right_child))
		return max_va(_left_child()->value().size(),
			_right_child()->value().size());
	}
};

// "<<", ">>", ">>>"
class ExprBaseBitShiftBinOp : public ExprBaseBinOp
{
public:		// functions
	ExprBaseBitShiftBinOp(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(s_src_code_pos, left_child, right_child)
	{
		// This *has* to be done in this class or later down the hierarchy,
		// and not in one of the classes this one is derived from, at least
		// if done in the *constructor* of one of the classes this one is
		// derived from.
		//_value.set_size(_starting_length());

		// Also, all bit shifts have the amount to shift by be
		// self-determined.
		_right_child()->set_is_self_determined(true);

		_value.set_is_signed(_left_child_value().is_signed());
	}

protected:		// functions
	size_t _starting_length() const
	{
		// Bit shifts take the size of the thing to be shifted as their
		// size.
		return _left_child()->value().size();
	}
};

// "Expression" classes derived from "ExprBaseLogCmpBinOp"

// "&&"
class ExprBinOpLogAnd : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpLogAnd(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("&&");
	}
	void _evaluate()
	{
		//ExprNum left_expr_num, right_expr_num;
		//_get_resized_child_expr_nums(left_expr_num, right_expr_num);

		//_value.copy_from_bignum(static_cast<BigNum>(left_expr_num)
		//	&& static_cast<BigNum>(right_expr_num));
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			&& static_cast<BigNum>(_right_child_value()));
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpLogAnd(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "||"
class ExprBinOpLogOr : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpLogOr(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("||");
	}
	void _evaluate()
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			|| static_cast<BigNum>(_right_child_value()));
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpLogOr(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "=="
class ExprBinOpCmpEq : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpEq(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("==");
	}
	void _evaluate()
	{
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				return (left == right);
			});
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpCmpEq(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "!="
class ExprBinOpCmpNe : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpNe(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("!=");
	}
	void _evaluate()
	{
		//_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
		//	!= static_cast<BigNum>(_right_child_value()));
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				return (left != right);
			});
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpCmpNe(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "<"
class ExprBinOpCmpLt : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpLt(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("<");
	}
	void _evaluate()
	{
		//_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
		//	< static_cast<BigNum>(_right_child_value()));
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				//printout("ExprBinOpCmpLt:  ", strappcom2(left, right,
				//	left < right), "\n");
				return (left < right);
			});
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpCmpLt(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// ">"
class ExprBinOpCmpGt : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpGt(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str(">");
	}
	void _evaluate()
	{
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				return (left > right);
			});
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpCmpGt(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "<="
class ExprBinOpCmpLe : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpLe(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("<=");
	}
	void _evaluate()
	{
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				return (left <= right);
			});
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpCmpLe(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// ">="
class ExprBinOpCmpGe : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpGe(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(s_src_code_pos, left_child, right_child)
	{
	}


protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str(">=");
	}
	void _evaluate()
	{
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				return (left >= right);
			});
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpCmpGe(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "Expression" classes derived from "ExprBaseArithBinOp"

// Binop "+"
class ExprBinOpPlus : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpPlus(const SrcCodePos& s_src_code_pos, Expression* left_child,
		Expression* right_child)
		: ExprBaseArithBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("+");
	}
	void _evaluate()
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			+ static_cast<BigNum>(_right_child_value()));
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpPlus(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// Binop "-"
class ExprBinOpMinus : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpMinus(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseArithBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("-");
	}
	void _evaluate()
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			- static_cast<BigNum>(_right_child_value()));
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpMinus(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "*"
class ExprBinOpMul : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpMul(const SrcCodePos& s_src_code_pos, Expression* left_child,
		Expression* right_child)
		: ExprBaseArithBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("*");
	}
	void _evaluate()
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			* static_cast<BigNum>(_right_child_value()));
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpMul(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "/"
class ExprBinOpDiv : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpDiv(const SrcCodePos& s_src_code_pos, Expression* left_child,
		Expression* right_child)
		: ExprBaseArithBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("/");
	}
	void _evaluate()
	{
		if (static_cast<BigNum>(_right_child_value())
			== static_cast<BigNum>(0))
		{
			_err("Division by zero.");
		}

		// FIXME:  BUG HERE
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			/ static_cast<BigNum>(_right_child_value()));
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpDiv(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "%"
class ExprBinOpMod : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpMod(const SrcCodePos& s_src_code_pos, Expression* left_child,
		Expression* right_child)
		: ExprBaseArithBinOp(s_src_code_pos, left_child, right_child)
	{
		_value.set_is_signed(_left_child_value().is_signed());
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("%");
	}
	void _evaluate()
	{
		if (static_cast<BigNum>(_right_child_value())
			== static_cast<BigNum>(0))
		{
			_err("Modulo by zero.");
		}

		// FIXME:  BUG HERE
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			% static_cast<BigNum>(_right_child_value()));
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpMod(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "Expression" classes derived from "ExprBaseBitNonShiftBinOp"

// "&"
class ExprBinOpBitAnd : public ExprBaseBitNonShiftBinOp
{
public:		// functions
	ExprBinOpBitAnd(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseBitNonShiftBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("&");
	}
	void _evaluate()
	{
		// This may not match the Verilog standard due to zero-extension
		// being dictated....
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			& static_cast<BigNum>(_right_child_value()));
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpBitAnd(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "|"
class ExprBinOpBitOr : public ExprBaseBitNonShiftBinOp
{
public:		// functions
	ExprBinOpBitOr(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseBitNonShiftBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("|");
	}
	void _evaluate()
	{
		// This may not match the Verilog standard due to zero-extension
		// being dictated....
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			| static_cast<BigNum>(_right_child_value()));
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpBitOr(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "^"
class ExprBinOpBitXor : public ExprBaseBitNonShiftBinOp
{
public:		// functions
	ExprBinOpBitXor(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseBitNonShiftBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("^");
	}
	void _evaluate()
	{
		// This may not match the Verilog standard due to zero-extension
		// being dictated....
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			^ static_cast<BigNum>(_right_child_value()));
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpBitXor(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// "Expression" classes derived from "ExprBaseBitShiftBinOp"

// "<<"
class ExprBinOpBitLsl : public ExprBaseBitShiftBinOp
{
public:		// functions
	ExprBinOpBitLsl(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseBitShiftBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("<<");
	}
	inline void _evaluate()
	{
		_value.perf_lsl(_left_child_value(), _right_child_value());
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpBitLsl(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// ">>"
class ExprBinOpBitLsr : public ExprBaseBitShiftBinOp
{
public:		// functions
	ExprBinOpBitLsr(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseBitShiftBinOp(s_src_code_pos, left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str(">>");
	}
	inline void _evaluate()
	{
		_value.perf_lsr(_left_child_value(), _right_child_value());
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpBitLsr(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

// ">>>"
class ExprBinOpBitAsr : public ExprBaseBitShiftBinOp
{
public:		// functions
	ExprBinOpBitAsr(const SrcCodePos& s_src_code_pos,
		Expression* left_child, Expression* right_child)
		: ExprBaseBitShiftBinOp(s_src_code_pos, left_child, right_child)
	{
	}

	//// "ExprBaseBinOp"'s "to_hdl_source()" won't work here.
	//virtual SavedString to_hdl_source() const
	//{
	//	// Verilog always treats the right argument of ">>>" as unsigned.
	//	// Also, it will only perform an arithmetic shift right if the left
	//	// argument of ">>>" is signed.
	//	// For Frost HDL, all uses of ">>>" treat the left argument as
	//	// signed, and this is also how I think the operator should work in
	//	// Verilog.
	//	return dup_str("$signed(", TO_HDL_SOURCE(_left_child), ") >>> ",
	//		TO_HDL_SOURCE(_right_child));
	//}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str(">>>");
	}
	inline void _evaluate()
	{
		_value.perf_asr(_left_child_value(), _right_child_value());
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprBinOpBitAsr(src_code_pos(),
	//		DUP_CHILD(_left_child()), DUP_CHILD(_right_child())));
	//}
};

} // namespace frost_hdl

#include "dot_hpp_undefs.hpp"

#endif		// src_expr_expr_bin_op_classes_hpp
