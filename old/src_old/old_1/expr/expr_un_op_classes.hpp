#ifndef src_expr_expr_un_op_classes_hpp
#define src_expr_expr_un_op_classes_hpp

// src/expr/expr_un_op_classes.hpp

#include "../misc_includes.hpp"

#include "dot_hpp_defines.hpp"

namespace frost_hdl
{

class ExprBaseUnOp : public Expression
{
public:		// types
	enum class FrostSourceType
	{
		// "!", "~", unary "-", etc.
		UnOp,

		// "$unsgn", "$sgn", etc.
		DollarFunction,
	};

public:		// functions
	ExprBaseUnOp(const SrcCodePos& s_src_code_pos,
		Expression* only_child);

	virtual SavedString to_hdl_source() const;

protected:		// functions
	virtual SavedString _unop_str() const
	{
		return nullptr;
	}

	// I'm *guessing* that this is a good default, but I'm not totally sure
	// yet.
	virtual FrostSourceType _frost_source_type() const
	{
		return FrostSourceType::DollarFunction;
	}

	Expression* _only_child() const
	{
		return children().at(0);
	}

	inline const ExprNum& _only_child_value() const
	{
		return _only_child()->value();
	}
};


// "+", "-", "!", "~"
class ExprBaseArithLogBitUnOp : public ExprBaseUnOp
{
public:		// functions
	ExprBaseArithLogBitUnOp(const SrcCodePos& s_src_code_pos,
		Expression* only_child)
		: ExprBaseUnOp(s_src_code_pos, only_child)
	{
		// This *has* to be done in this class or later down the hierarchy,
		// and not in one of the classes this one is derived from, at least
		// if done in the *constructor* of one of the classes this one is
		// derived from.
		//_value.set_size(_starting_length());

		_value.set_is_signed(_only_child_value().is_signed());
	}

protected:		// functions
	size_t _starting_length() const
	{
		return _only_child_value().size();
	}
};

// "$unsgn()", "$sgn()", "$clog2()"
// These are dollar functions that take only one argument.
class ExprBaseDollarFuncUnOp : public ExprBaseUnOp
{
public:		// functions
	ExprBaseDollarFuncUnOp(const SrcCodePos& s_src_code_pos,
		Expression* only_child)
		: ExprBaseUnOp(s_src_code_pos, only_child)
	{
		//_value.set_size(_starting_length());
	}

protected:		// functions
	size_t _starting_length() const
	{
		return _only_child_value().size();
	}
};




// Finally, here are the "most derived" "Expression" classes, the ones at
// the bottom of the class hierarchy.

// "Expression" classes derived from "ExprBaseArithLogBitUnOp"

// Unary "+"
class ExprUnOpPlus : public ExprBaseArithLogBitUnOp
{
public:		// functions
	ExprUnOpPlus(const SrcCodePos& s_src_code_pos, Expression* only_child)
		: ExprBaseArithLogBitUnOp(s_src_code_pos, only_child)
	{
	}

protected:		// functions
	SavedString _unop_str() const
	{
		return dup_str("+");
	}
	void _evaluate()
	{
		_value.copy_from_bignum(static_cast<BigNum>(_only_child_value()));
	}

	virtual FrostSourceType _frost_source_type() const
	{
		return FrostSourceType::UnOp;
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprUnOpPlus(src_code_pos(),
	//		DUP_CHILD(_only_child())));
	//}
};

// Unary "-"
class ExprUnOpMinus : public ExprBaseArithLogBitUnOp
{
public:		// functions
	ExprUnOpMinus(const SrcCodePos& s_src_code_pos, Expression* only_child)
		: ExprBaseArithLogBitUnOp(s_src_code_pos, only_child)
	{
	}

protected:		// functions
	SavedString _unop_str() const
	{
		return dup_str("-");
	}
	void _evaluate()
	{
		_value.copy_from_bignum(-static_cast<BigNum>(_only_child_value()));
	}

	virtual FrostSourceType _frost_source_type() const
	{
		return FrostSourceType::UnOp;
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprUnOpMinus(src_code_pos(),
	//		DUP_CHILD(_only_child())));
	//}
};

// "!"
class ExprUnOpLogNot : public ExprBaseArithLogBitUnOp
{
public:		// functions
	ExprUnOpLogNot(const SrcCodePos& s_src_code_pos,
		Expression* only_child)
		: ExprBaseArithLogBitUnOp(s_src_code_pos, only_child)
	{
	}

protected:		// functions
	SavedString _unop_str() const
	{
		return dup_str("!");
	}
	void _evaluate()
	{
		_value.copy_from_bignum(!static_cast<BigNum>(_only_child_value()));
	}

	virtual FrostSourceType _frost_source_type() const
	{
		return FrostSourceType::UnOp;
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprUnOpLogNot(src_code_pos(),
	//		DUP_CHILD(_only_child())));
	//}
};

// "~"
class ExprUnOpBitNot : public ExprBaseArithLogBitUnOp
{
public:		// functions
	ExprUnOpBitNot(const SrcCodePos& s_src_code_pos,
		Expression* only_child)
		: ExprBaseArithLogBitUnOp(s_src_code_pos, only_child)
	{
	}

protected:		// functions
	SavedString _unop_str() const
	{
		return dup_str("!");
	}
	void _evaluate()
	{
		_value.copy_from_bignum(~static_cast<BigNum>(_only_child_value()));
	}

	virtual FrostSourceType _frost_source_type() const
	{
		return FrostSourceType::UnOp;
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprUnOpBitNot(src_code_pos(),
	//		DUP_CHILD(_only_child())));
	//}
};

// "Expression" classes derived from "ExprBaseDollarFuncUnOp"

// "$unsgn()
class ExprUnOpCastUnsigned : public ExprBaseDollarFuncUnOp
{
public:		// functions
	ExprUnOpCastUnsigned(const SrcCodePos& s_src_code_pos,
		Expression* only_child)
		: ExprBaseDollarFuncUnOp(s_src_code_pos, only_child)
	{
		_value.set_is_signed(false);
	}

	//virtual SavedString to_hdl_source() const
	//{
	//	return dup_str("$unsgn(", TO_HDL_SOURCE(_only_child), ")");
	//}


protected:		// functions
	virtual SavedString _unop_str() const
	{
		return dup_str("$unsgn");
	}

	void _evaluate()
	{
		_set_value(_only_child_value());
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprUnOpCastUnsigned(src_code_pos(),
	//		DUP_CHILD(_only_child())));
	//}
};
// "$sgn()
class ExprUnOpCastSigned : public ExprBaseDollarFuncUnOp
{
public:		// functions
	ExprUnOpCastSigned(const SrcCodePos& s_src_code_pos,
		Expression* only_child)
		: ExprBaseDollarFuncUnOp(s_src_code_pos, only_child)
	{
		_value.set_is_signed(true);
	}

	//virtual SavedString to_hdl_source() const
	//{
	//	return dup_str("$sgn(", TO_HDL_SOURCE(_only_child), ")");
	//}

protected:		// functions
	virtual SavedString _unop_str() const
	{
		return dup_str("$sgn");
	}
	void _evaluate()
	{
		_set_value(_only_child_value());
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprUnOpCastSigned(src_code_pos(),
	//		DUP_CHILD(_only_child())));
	//}
};

// "$clog2()"
class ExprUnOpClog2 : public ExprBaseDollarFuncUnOp
{
public:		// functions
	ExprUnOpClog2(const SrcCodePos& s_src_code_pos,
		Expression* only_child)
		: ExprBaseDollarFuncUnOp(s_src_code_pos, only_child)
	{
		_value.set_is_signed(false);
	}

protected:		// functions
	virtual SavedString _unop_str() const
	{
		return dup_str("$clog2");
	}

	void _evaluate();
};

} // namespace frost_hdl

#include "dot_hpp_undefs.hpp"


#endif		// src_expr_expr_un_op_classes_hpp
