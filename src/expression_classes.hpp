#ifndef src_expression_classes_hpp
#define src_expression_classes_hpp

// src/expression_classes.hpp

#include "misc_includes.hpp"
#include "expr_num_class.hpp"
#include "general_allocator_class.hpp"

namespace frost_hdl
{

//inline BigNum max(const BigNum& a, const BigNum& b)
//{
//	return (a > b) ? a : b;
//}
//
//typedef BigNum* ExprNum;

class Expression
{
public:		// types
	//typedef SavedString OpStr;
	typedef SavedString Ident;

	typedef std::set<Expression*> DescendantsList;

	//enum class Category
	//{
	//	UnOp,
	//	BinOp,
	//	Ternary,

	//	IdentSliced,
	//	HardCodedConstant,
	//};

	//enum class Type
	//{
	//	BinOpLogAnd,
	//	BinOpLogOr,

	//	BinOpCmpEq,
	//	BinOpCmpNe,
	//	BinOpCmpLt,
	//	BinOpCmpGt,
	//	BinOpCmpLe,
	//	BinOpCmpGe,

	//	BinOpPlus,
	//	BinOpMinus,

	//	UnOpPlus,
	//	UnOpMinus,
	//	UnOpBitInvert,

	//	BinOpMul,
	//	BinOpDiv,
	//	BinOpMod,

	//	BinOpBitAnd,
	//	BinOpBitOr,
	//	BinOpBitXor,

	//	BinOpBitLsl,
	//	BinOpBitLsr,
	//	BinOpBitAsr,

	//	Ternary,

	//	Ident,
	//	IdentSliced,
	//	HardCodedConstant,

	//	Lim,
	//};


protected:		// variables
	std::vector<Expression*> _children;

	Ident _ident;
	ExprNum _value;
	bool _is_self_determined;

public:		// functions
	Expression();


	// Don't want copies of raw Expression's
	Expression(const Expression& to_copy) = delete;

	// Moves are okay, though
	Expression(Expression&& to_move) = default;


	virtual ~Expression() = default;


	// Don't want copies of raw Expression's
	Expression& operator = (const Expression& to_copy) = delete;

	// Moves are okay, though
	Expression& operator = (Expression&& to_move) = default;






	inline size_t num_children() const
	{
		return children().size();
	}
	inline bool is_leaf() const
	{
		return (num_children() == 0);
	}


	inline const auto& ident() const
	{
		return (*_ident);
	}

	inline void set_value(const ExprNum& n_value)
	{
		_value = n_value;
	}


	//inline void set_value(const BigNum& n_value_data,
	//	size_t n_value_data_size, bool n_value_is_signed)
	//{
	//	set_value(ExprNum(n_value_data, n_value_data_size,
	//		n_value_is_signed));
	//}


	// This doesn't *need* to be stored anywhere.
	inline bool is_constant() const
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


protected:		// functions
	// Don't call "_evaluate()" until after the size of the expression has
	// been determined and the children have been modified.
	virtual void _evaluate();

	virtual bool _children_affect_length() const;

	// The length of the expression before (possibly) being casted to a
	// larger one.
	virtual size_t _starting_length() const;

	virtual bool _is_always_constant() const;



	inline void _set_ident(const std::string& n_ident)
	{
		_ident = dup_str(n_ident);
	}

	// Stuff for evaluating constant expressions.
	void _full_evaluate(bool is_real_top);

	void _inner_full_evaluate();
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
public:		// functions
	ExprBaseUnOp(Expression* only_child);


protected:		// functions
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


protected:		// functions
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
	size_t _starting_length() const final
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

	bool _children_affect_length() const final
	{
		return false;
	}

	size_t _starting_length() const final
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
	size_t _starting_length() const final
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
	size_t _starting_length() const final
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
	size_t _starting_length() const final
	{
		// Bit shifts take the size of the thing to be shifted as their
		// size.
		return _left_child()->value().size();
	}
};


// Finally, here are the "most derived" "Expression" classes, the ones at
// the bottom of the class hierarchy.

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

protected:		// functions
	void _evaluate() final
	{
		set_value(_only_child_value());
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

protected:		// functions
	void _evaluate() final
	{
		set_value(_only_child_value());
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
	void _evaluate() final
	{
		//ExprNum left_expr_num, right_expr_num;
		//_get_resized_child_expr_nums(left_expr_num, right_expr_num);

		//_value.copy_from_bignum(static_cast<BigNum>(left_expr_num)
		//	&& static_cast<BigNum>(right_expr_num));
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			&& static_cast<BigNum>(_right_child_value()));
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
	void _evaluate() final
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			|| static_cast<BigNum>(_right_child_value()));
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
	void _evaluate() final
	{
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				return (left == right);
			});
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
	void _evaluate() final
	{
		//_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
		//	!= static_cast<BigNum>(_right_child_value()));
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				return (left != right);
			});
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
	void _evaluate() final
	{
		//_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
		//	< static_cast<BigNum>(_right_child_value()));
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				return (left < right);
			});
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
	void _evaluate() final
	{
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				return (left > right);
			});
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
	void _evaluate() final
	{
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				return (left <= right);
			});
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
	void _evaluate() final
	{
		_perf_compare([](const BigNum& left, const BigNum& right) -> BigNum
			{
				return (left >= right);
			});
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
	void _evaluate() final
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			+ static_cast<BigNum>(_right_child_value()));
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
	void _evaluate() final
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			- static_cast<BigNum>(_right_child_value()));
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
	void _evaluate() final
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			* static_cast<BigNum>(_right_child_value()));
	}
};

// "/"
class ExprBinOpDiv : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpDiv(Expression* left_child, Expression* right_child)
		: ExprBaseArithBinOp(left_child, right_child)
	{
	}

protected:		// functions
	void _evaluate() final
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			/ static_cast<BigNum>(_right_child_value()));
	}
};

// "%"
class ExprBinOpMod : public ExprBaseArithBinOp
{
public:		// functions
	ExprBinOpMod(Expression* left_child, Expression* right_child)
		: ExprBaseArithBinOp(left_child, right_child)
	{
	}

protected:		// functions
	void _evaluate() final
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			% static_cast<BigNum>(_right_child_value()));
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
	void _evaluate() final
	{
		// This may not match the Verilog standard due to zero-extension
		// being dictated....
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			& static_cast<BigNum>(_right_child_value()));
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
	void _evaluate() final
	{
		// This may not match the Verilog standard due to zero-extension
		// being dictated....
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			| static_cast<BigNum>(_right_child_value()));
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
	void _evaluate() final
	{
		// This may not match the Verilog standard due to zero-extension
		// being dictated....
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			^ static_cast<BigNum>(_right_child_value()));
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
	void _evaluate() final;
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
	void _evaluate() final;
};

// ">>>"
class ExprBinOpBitAsr : public ExprBaseBitShiftBinOp
{
public:		// functions
	ExprBinOpBitAsr(Expression* left_child, Expression* right_child)
		: ExprBaseBitShiftBinOp(left_child, right_child)
	{
	}

protected:		// functions
	void _evaluate() final;
};


class ExprHardCodedNum : public Expression
{
public:		// functions
	ExprHardCodedNum(const ExprNum& n_value)
	{
		set_value(n_value);
	}



protected:		// functions

	// Hard-coded numbers don't really evaluate to anything.
	void _evaluate() final
	{
	}

	bool _children_affect_length() const final
	{
		return false;
	}
	size_t _starting_length() const final
	{
		return value().size();
	}

	bool _is_always_constant() const final
	{
		return true;
	}
};

} // namespace frost_hdl


#endif		// src_expression_classes_hpp
