#ifndef src_expression_classes_hpp
#define src_expression_classes_hpp

// src/expression_classes.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "expr_num_class.hpp"
//#include "general_allocator_class.hpp"
//#include "symbol_table_class.hpp"

namespace frost_hdl
{

#define REMOVE_CONST_REF(to_remove_from) \
	std::remove_const<std::remove_reference<to_remove_from>::type>::type

// Used to prevent accidentally doing a "save_expr" of the wrong type.
#define SAFE_SAVE_EXPR save_expr<REMOVE_CONST_REF(decltype(*this))>
#define DUP_CHILD(child) child->dup_with_changed_symbols(replace_syms_map)

//inline BigNum max(const BigNum& a, const BigNum& b)
//{
//	return (a > b) ? a : b;
//}
//
//typedef BigNum* ExprNum;
class Symbol;

#define TO_HDL_SOURCE(child) (*child()->to_hdl_source())

class Expression
{
public:		// types
	//typedef SavedString OpStr;
	typedef SavedString Ident;

	typedef std::set<Expression*> DescendantsList;
	typedef std::vector<Expression*> ChildrenList;

	// Uses of identifiers that can be on the left-hand side of an
	// assignment.
	enum class LhsCategory
	{
		None,

		Concat,
		IdentSliced,
		IdentNonSliced,
	};

	//enum class Category
	//{
	//	UnOp,
	//	BinOp,
	//	Ternary,

	//	IdentSliced,
	//	HardCodedConstant,
	//};



protected:		// variables
	ChildrenList _children;

	Symbol* _symbol = nullptr;
	bool _is_self_determined = false;
	bool _handles_children_eval = false;
	ExprNum _value;


public:		// functions
	Expression() = default;


	// Don't want copies of raw Expression's
	// Moves are okay, though
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Expression);
	virtual ~Expression() = default;





	// I didn't want this made public, but...
	void inner_full_evaluate();

	// Recursively search the tree for a reference to a particular
	// "Symbol".  This is (exclusively?) used to prevent defining a
	// "parameter" in terms of itself.
	bool references_symbol(Symbol* to_check) const;



	inline bool is_valid_lhs() const
	{
		return (lhs_category() != LhsCategory::None);
	}



	inline size_t num_children() const
	{
		return children().size();
	}
	inline bool is_leaf() const
	{
		return (num_children() == 0);
	}

	// Unfortunately, replacing the references to "Symbol"s has come down
	// to this.  Each most-derived "Expression" class will now have to
	// implement this.  It's a pain.
	Expression* dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const;
	virtual SavedString to_hdl_source() const;
	virtual LhsCategory lhs_category() const;



	// This doesn't *need* to be stored anywhere.
	virtual bool is_constant() const
	{
		//printout("Debug:  is_constant():  ", _has_only_constant_children(),
		//	" ", _is_always_constant(), "\n");
		return (_has_only_constant_children() || _is_always_constant());
	}

	inline void full_evaluate_if_constant()
	{
		if (is_constant())
		{
			_full_evaluate(true);
		}
	}



	GEN_GETTER_BY_CON_REF(children)
	GEN_GETTER_BY_CON_REF(value)

	GEN_GETTER_AND_SETTER_BY_VAL(is_self_determined)
	GEN_GETTER_AND_SETTER_BY_VAL(handles_children_eval)

	GEN_GETTER_AND_SETTER_BY_VAL(symbol)


protected:		// functions
	inline void _set_value(const ExprNum& n_value)
	{
		_value = n_value;
	}


	// Don't call "_evaluate()" until after the size of the expression has
	// been determined and the children have been modified.
	virtual void _evaluate();

	virtual bool _children_affect_length() const;

	// The length of the expression before (possibly) being casted to a
	// larger one.
	virtual size_t _starting_length() const;

	virtual bool _is_always_constant() const;
	virtual Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const;



	//inline void _set_ident(const std::string& n_ident)
	//{
	//	_ident = dup_str(n_ident);
	//}

	// Stuff for evaluating constant expressions.
	void _full_evaluate(bool is_real_top);

	void _get_first_layer_ptln_descs(DescendantsList& ret) const;

	size_t _highest_desc_size_with_effect() const;
	bool _has_any_unsigned_first_layer_non_sd_descs() const;

	void _perf_mega_descs_cast(size_t n_size, bool n_is_signed) const;

	bool _has_only_constant_children() const;

	inline bool _is_pseudo_top_level_node() const
	{
		const bool non_sd_thing = (!_is_always_constant())
			&& (!_children_affect_length());
		return (non_sd_thing || is_self_determined());
	}

	//template<typename FirstArgType, typename... RemArgTypes>
	//inline bool _has_only_constant_children(FirstArgType&& first_child,
	//	RemArgTypes&&... rem_children)
	//{
	//	_set_children(first_child, rem_children...);
	//	return _has_only_constant_children();
	//}

	// Require at LEAST one argument.
	template<typename FirstArgType, typename... RemArgTypes>
	inline void _set_children(FirstArgType&& first_child,
		RemArgTypes&&... rem_children)
	{
		_children.push_back(first_child);

		// Oh hey, an actual use for "if constexpr" that actually CAN'T be
		// written as a plain old "if"!
		if constexpr (sizeof...(rem_children) > 0)
		{
			_set_children(rem_children...);
		}

		// (Don't uncomment this if "_set_children()" is called too early
		// in the class hierarchy!)
		//else 
		//{
		//	_value.set_size(_starting_length());
		//}
	}
};

class ExprBaseUnOp : public Expression
{
public:		// types
	enum class FrostSourceType
	{
		// "!", "~", unary "-", etc.
		UnOp,

		// "$unsigned", "$signed", etc.
		DollarFunction,
	};

public:		// functions
	ExprBaseUnOp(Expression* only_child);

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

class ExprBaseBinOp : public Expression
{
public:		// functions
	ExprBaseBinOp(Expression* left_child, Expression* right_child);

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

// "+", "-"
class ExprBaseArithUnOp : public ExprBaseUnOp
{
public:		// functions
	ExprBaseArithUnOp(Expression* only_child)
		: ExprBaseUnOp(only_child)
	{
		// This *has* to be done in this class or later down the hierarchy,
		// and not in one of the classes this one is derived from, at least
		// if done in the *constructor* of one of the classes this one is
		// derived from.
		_value.set_size(_starting_length());

		_value.set_is_signed(_only_child_value().is_signed());
	}

protected:		// functions
	size_t _starting_length() const
	{
		return _only_child_value().size();
	}
};

// "$unsigned()", "$signed()"
class ExprBaseCastUnop : public ExprBaseUnOp
{
public:		// functions
	ExprBaseCastUnop(Expression* only_child)
		: ExprBaseUnOp(only_child)
	{
		_value.set_size(_starting_length());
	}

protected:		// functions
	size_t _starting_length() const
	{
		return _only_child_value().size();
	}
};

// "&&", "||", "==", "!=", "<", ">", "<=", ">="
class ExprBaseLogCmpBinOp : public ExprBaseBinOp
{
public:		// types
	typedef BigNum (*CmpEvalFunc)(const BigNum& left, const BigNum& right);

public:		// functions
	ExprBaseLogCmpBinOp(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
		// This *has* to be done in this class or later down the hierarchy,
		// and not in one of the classes this one is derived from, at least
		// if done in the *constructor* of one of the classes this one is
		// derived from.
		_value.set_size(_starting_length());

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
	ExprBaseArithBinOp(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
		// This *has* to be done in this class or later down the hierarchy,
		// and not in one of the classes this one is derived from, at least
		// if done in the *constructor* of one of the classes this one is
		// derived from.
		_value.set_size(_starting_length());

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
	ExprBaseBitNonShiftBinOp(Expression* left_child,
		Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
		// This *has* to be done in this class or later down the hierarchy,
		// and not in one of the classes this one is derived from, at least
		// if done in the *constructor* of one of the classes this one is
		// derived from.
		_value.set_size(_starting_length());

		// I'm not sure this is correct.
		// NOTE:  POSSIBLE BUG HERE
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
	ExprBaseBitShiftBinOp(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
		// This *has* to be done in this class or later down the hierarchy,
		// and not in one of the classes this one is derived from, at least
		// if done in the *constructor* of one of the classes this one is
		// derived from.
		_value.set_size(_starting_length());

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



// Finally, here are the "most derived" "Expression" classes, the ones at
// the bottom of the class hierarchy.

// "Expression" classes derived from "ExprBaseArithUnOp"

// Unary "+"
class ExprUnOpPlus : public ExprBaseArithUnOp
{
public:		// functions
	ExprUnOpPlus(Expression* only_child)
		: ExprBaseArithUnOp(only_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprUnOpPlus(DUP_CHILD(_only_child())));
	}
};

// Unary "-"
class ExprUnOpMinus : public ExprBaseArithUnOp
{
public:		// functions
	ExprUnOpMinus(Expression* only_child)
		: ExprBaseArithUnOp(only_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprUnOpMinus(DUP_CHILD(_only_child())));
	}
};

// "Expression" classes derived from "ExprBaseCastUnop"

// "$unsigned()
class ExprUnOpCastUnsigned : public ExprBaseCastUnop
{
public:		// functions
	ExprUnOpCastUnsigned(Expression* only_child)
		: ExprBaseCastUnop(only_child)
	{
		_value.set_is_signed(false);
	}

	//virtual SavedString to_hdl_source() const
	//{
	//	return dup_str("$unsigned(", TO_HDL_SOURCE(_only_child), ")");
	//}


protected:		// functions
	virtual SavedString _unop_str() const
	{
		return dup_str("$unsigned");
	}

	void _evaluate()
	{
		_set_value(_only_child_value());
	}
};
// "$signed()
class ExprUnOpCastSigned : public ExprBaseCastUnop
{
public:		// functions
	ExprUnOpCastSigned(Expression* only_child)
		: ExprBaseCastUnop(only_child)
	{
		_value.set_is_signed(true);
	}

	//virtual SavedString to_hdl_source() const
	//{
	//	return dup_str("$signed(", TO_HDL_SOURCE(_only_child), ")");
	//}

protected:		// functions
	virtual SavedString _unop_str() const
	{
		return dup_str("$signed");
	}
	void _evaluate()
	{
		_set_value(_only_child_value());
	}
};


// "Expression" classes derived from "ExprBaseLogCmpBinOp"

// "&&"
class ExprBinOpLogAnd : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpLogAnd(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpLogAnd(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "||"
class ExprBinOpLogOr : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpLogOr(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpLogOr(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "=="
class ExprBinOpCmpEq : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpEq(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpCmpEq(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "!="
class ExprBinOpCmpNe : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpNe(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpCmpNe(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "<"
class ExprBinOpCmpLt : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpLt(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpCmpLt(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// ">"
class ExprBinOpCmpGt : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpGt(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpCmpGt(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "<="
class ExprBinOpCmpLe : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpLe(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpCmpLe(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// ">="
class ExprBinOpCmpGe : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprBinOpCmpGe(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpCmpGe(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "Expression" classes derived from "ExprBaseArithBinOp"

// Binop "+"
class ExprBinOpPlus : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpPlus(Expression* left_child, Expression* right_child)
		: ExprBaseArithBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpPlus(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// Binop "-"
class ExprBinOpMinus : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpMinus(Expression* left_child, Expression* right_child)
		: ExprBaseArithBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpMinus(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "*"
class ExprBinOpMul : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpMul(Expression* left_child, Expression* right_child)
		: ExprBaseArithBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpMul(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "/"
// FUTURE:  add some way to detect division by zero.
class ExprBinOpDiv : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpDiv(Expression* left_child, Expression* right_child)
		: ExprBaseArithBinOp(left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("/");
	}
	void _evaluate()
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			/ static_cast<BigNum>(_right_child_value()));
	}

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpDiv(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "%"
// FUTURE:  add some way to detect division by zero.
class ExprBinOpMod : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpMod(Expression* left_child, Expression* right_child)
		: ExprBaseArithBinOp(left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("%");
	}
	void _evaluate()
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			% static_cast<BigNum>(_right_child_value()));
	}

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpMod(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "Expression" classes derived from "ExprBaseBitNonShiftBinOp"

// "&"
class ExprBinOpBitAnd : public ExprBaseBitNonShiftBinOp
{
public:		// functions
	ExprBinOpBitAnd(Expression* left_child, Expression* right_child)
		: ExprBaseBitNonShiftBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpBitAnd(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "|"
class ExprBinOpBitOr : public ExprBaseBitNonShiftBinOp
{
public:		// functions
	ExprBinOpBitOr(Expression* left_child, Expression* right_child)
		: ExprBaseBitNonShiftBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpBitOr(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "^"
class ExprBinOpBitXor : public ExprBaseBitNonShiftBinOp
{
public:		// functions
	ExprBinOpBitXor(Expression* left_child, Expression* right_child)
		: ExprBaseBitNonShiftBinOp(left_child, right_child)
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

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpBitXor(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// "Expression" classes derived from "ExprBaseBitShiftBinOp"

// "<<"
class ExprBinOpBitLsl : public ExprBaseBitShiftBinOp
{
public:		// functions
	ExprBinOpBitLsl(Expression* left_child, Expression* right_child)
		: ExprBaseBitShiftBinOp(left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str("<<");
	}
	void _evaluate();

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpBitLsl(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// ">>"
class ExprBinOpBitLsr : public ExprBaseBitShiftBinOp
{
public:		// functions
	ExprBinOpBitLsr(Expression* left_child, Expression* right_child)
		: ExprBaseBitShiftBinOp(left_child, right_child)
	{
	}

protected:		// functions
	SavedString _binop_str() const
	{
		return dup_str(">>");
	}
	void _evaluate();

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpBitLsr(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};

// ">>>"
class ExprBinOpBitAsr : public ExprBaseBitShiftBinOp
{
public:		// functions
	ExprBinOpBitAsr(Expression* left_child, Expression* right_child)
		: ExprBaseBitShiftBinOp(left_child, right_child)
	{
	}

	// "ExprBaseBinOp"'s "to_hdl_source()" won't work here.
	virtual SavedString to_hdl_source() const
	{
		// Verilog always treats the right argument of ">>>" as unsigned.
		// Also, it will only perform an arithmetic shift right if the left
		// argument of ">>>" is signed.
		// For Frost HDL, all uses of ">>>" treat the left argument as
		// signed, and this is also how I think the operator should work in
		// Verilog.
		return dup_str("$signed(", TO_HDL_SOURCE(_left_child), ") >>> ",
			TO_HDL_SOURCE(_right_child));
	}

protected:		// functions
	void _evaluate();

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprBinOpBitAsr(DUP_CHILD(_left_child()),
			DUP_CHILD(_right_child())));
	}
};


// "most derived" "Expression" classes that derive only from "Expression"

// Hard-coded numbers (not named constants)
class ExprHardCodedNum : public Expression
{
public:		// functions
	ExprHardCodedNum(const ExprNum& s_value)
	{
		_set_value(s_value);
	}

	virtual SavedString to_hdl_source() const
	{
		//return dup_str(static_cast<std::string>(value()));
		return dup_str(value().convert_to_verilog_literal());
	}


protected:		// functions

	// Hard-coded numbers don't really evaluate to anything.
	void _evaluate()
	{
	}

	bool _children_affect_length() const
	{
		return false;
	}
	size_t _starting_length() const
	{
		return value().size();
	}

	bool _is_always_constant() const
	{
		return true;
	}

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprHardCodedNum(value()));
	}
};

// "$concat(...)"
class ExprConcat : public Expression
{
public:		// functions
	ExprConcat(ChildrenList&& s_children);

	virtual SavedString to_hdl_source() const;
	virtual LhsCategory lhs_category() const
	{
		return LhsCategory::Concat;
	}


protected:		// functions
	void _evaluate();
	size_t _starting_length() const;
	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		ChildrenList dupped_children;

		for (auto iter : dupped_children)
		{
			dupped_children.push_back(DUP_CHILD(iter));
		}

		return SAFE_SAVE_EXPR(ExprConcat(std::move(dupped_children)));
	}
};

// "$repl(...)"
class ExprRepl : public Expression
{
public:		// functions
	ExprRepl(Expression* s_width_child,
		ChildrenList&& s_non_width_children);

	//inline Expression* dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//}
	virtual SavedString to_hdl_source() const;

protected:		// functions
	inline Expression* _width_child() const
	{
		return children().back();
	}

	inline size_t _width_child_index() const
	{
		return (children().size() - 1);
	}

	//// Intended for iteration
	//inline Expression* _last_non_width_child() const
	//{
	//	return children().at(children.size() - 2);
	//}

	void _evaluate();
	size_t _starting_length();

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		//return SAFE_SAVE_EXPR(ExprTernary(DUP_CHILD(_condition_child()),
		//	DUP_CHILD(_when_true_child()),
		//	DUP_CHILD(_when_false_child())));
		ChildrenList dupped_non_width_children;

		for (size_t i=0; i<_width_child_index(); ++i)
		{
			dupped_non_width_children.push_back
				(DUP_CHILD(_children.at(i)));
		}

		return SAFE_SAVE_EXPR(ExprRepl(DUP_CHILD(_width_child()),
			std::move(dupped_non_width_children)));
	}
};

// "condition ? when_true : when_false"
class ExprTernary : public Expression
{
public:		// functions
	ExprTernary(Expression* condition_child, Expression* when_true_child,
		Expression* when_false_child);


	virtual SavedString to_hdl_source() const
	{
		return dup_str(TO_HDL_SOURCE(_condition_child), " ? ",
			TO_HDL_SOURCE(_when_true_child), " : ",
			TO_HDL_SOURCE(_when_false_child));
	}

protected:		// functions
	inline Expression* _condition_child() const
	{
		return _children.at(0);
	}
	inline Expression* _when_true_child() const
	{
		return _children.at(1);
	}
	inline Expression* _when_false_child() const
	{
		return _children.at(2);
	}

	inline const ExprNum& _condition_child_value() const
	{
		return _condition_child()->value();
	}
	inline const ExprNum& _when_true_child_value() const
	{
		return _when_true_child()->value();
	}
	inline const ExprNum& _when_false_child_value() const
	{
		return _when_false_child()->value();
	}

	void _evaluate();
	size_t _starting_length() const
	{
		return max_va(_when_true_child()->value().size(),
			_when_false_child()->value().size());
	}

	inline Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		return SAFE_SAVE_EXPR(ExprTernary(DUP_CHILD(_condition_child()),
			DUP_CHILD(_when_true_child()),
			DUP_CHILD(_when_false_child())));
	}
};

// Non-sliced reference to an identifier of some sort.
class ExprIdentName : public Expression
{
public:		// functions
	ExprIdentName(Symbol* s_symbol);


	virtual SavedString to_hdl_source() const;
	virtual LhsCategory lhs_category() const
	{
		return LhsCategory::IdentNonSliced;
	}

	bool is_constant() const;

protected:		// functions
	void _evaluate();
	size_t _starting_length() const;

	virtual Expression* _inner_dup_with_changed_symbols
		(const ReplaceSymsMap& replace_syms_map) const
	{
		if (replace_syms_map.contains(_symbol))
		{
			return SAFE_SAVE_EXPR(ExprIdentName(replace_syms_map.at
				(_symbol)));
		}
		else
		{
			return SAFE_SAVE_EXPR(ExprIdentName(_symbol));
		}
	}
};

#undef TO_HDL_SOURCE
#undef DUP_CHILD
#undef SAFE_SAVE_EXPR
#undef REMOVE_CONST_REF

} // namespace frost_hdl


#endif		// src_expression_classes_hpp
