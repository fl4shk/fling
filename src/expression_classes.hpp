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
	typedef SavedString OpStr;
	typedef SavedString Ident;

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




	// Don't call "evaluate()" until after the size of the expression has
	// been determined and the children have been modified.
	virtual void evaluate();


	inline auto num_children() const
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


	inline void set_ident(const std::string& n_ident)
	{
		_ident = dup_str(n_ident);
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

	inline bool is_constant() const
	{
		return (_has_only_constant_children() || _is_always_constant());
	}
	//inline bool is_pseudo_top_node() const
	//{
	//}

	GEN_GETTER_BY_CON_REF(children)
	GEN_GETTER_BY_CON_REF(value)

	GEN_GETTER_AND_SETTER_BY_VAL(is_self_determined)


protected:		// functions
	virtual bool _children_affect_length() const;

	// The length of the expression before being possibly casted to a
	// larger type
	virtual size_t _starting_length() const;

	virtual bool _is_always_constant() const;

	bool _has_only_constant_children() const;

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

// "&&", "||", "==", "!=", "<", ">", "<=", ">="
class ExprBaseLogCmpBinOp : public ExprBaseBinOp
{
public:		// functions
	ExprBaseLogCmpBinOp(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

protected:		// functions
	inline void _get_resized_child_expr_nums(ExprNum& left_ret,
		ExprNum& right_ret) const
	{
		left_ret = _left_child_value();
		right_ret = _right_child_value();

		if (left_ret.size() < right_ret.size())
		{
			left_ret.set_size(right_ret.size());
		}
		else // if (left_ret.size() >= right_ret.size())
		{
			right_ret.set_size(left_ret.size());
		}
	}

	size_t _starting_length() const final
	{
		return 1;
	}

	bool _children_affect_length() const final
	{
		return false;
	}

};

// "+", "-", "*", "/", "%", "&", "|", "^"
class ExprBaseLengthTwoMaxBinOp : public ExprBaseBinOp
{
public:		// functions
	ExprBaseLengthTwoMaxBinOp(Expression* left_child,
		Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

protected:		// functions
	size_t _starting_length() const final
	{
		// max(sizeof(left_child), sizeof(right_child))
		return max_va(_left_child()->value().size(),
			_right_child()->value().size());
	}

	bool _children_affect_length() const final
	{
		return true;
	}
};

// "<<", ">>", ">>>"
class ExprBaseBitShiftBinOp : public ExprBaseBinOp
{
public:		// functions
	ExprBaseBitShiftBinOp(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
		_right_child()->set_is_self_determined(true);
	}

protected:		// functions
	size_t _starting_length() const final
	{
		return _left_child()->value().size();
	}

	bool _children_affect_length() const final
	{
		return true;
	}
};


// Finally, here are the "most derived" "Expression" classes, the ones at
// the bottom of the class hierarchy.


// "Expression" classes derived from "ExprBaseLogCmpBinOp"

// "&&"
class ExprLogAnd : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprLogAnd(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		ExprNum left_expr_num, right_expr_num;
		_get_resized_child_expr_nums(left_expr_num, right_expr_num);

		_value.copy_from_bignum(static_cast<BigNum>(left_expr_num)
			&& static_cast<BigNum>(right_expr_num));
	}
};

// "||"
class ExprLogOr : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprLogOr(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		ExprNum left_expr_num, right_expr_num;
		_get_resized_child_expr_nums(left_expr_num, right_expr_num);

		_value.copy_from_bignum(static_cast<BigNum>(left_expr_num)
			|| static_cast<BigNum>(right_expr_num));
	}
};

// "=="
class ExprCmpEq : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprCmpEq(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		ExprNum left_expr_num, right_expr_num;
		_get_resized_child_expr_nums(left_expr_num, right_expr_num);

		_value.copy_from_bignum(static_cast<BigNum>(left_expr_num)
			== static_cast<BigNum>(right_expr_num));
	}
};

// "!="
class ExprCmpNe : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprCmpNe(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		ExprNum left_expr_num, right_expr_num;
		_get_resized_child_expr_nums(left_expr_num, right_expr_num);

		_value.copy_from_bignum(static_cast<BigNum>(left_expr_num)
			!= static_cast<BigNum>(right_expr_num));
	}
};

// "<"
class ExprCmpLt : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprCmpLt(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		ExprNum left_expr_num, right_expr_num;
		_get_resized_child_expr_nums(left_expr_num, right_expr_num);

		_value.copy_from_bignum(static_cast<BigNum>(left_expr_num)
			< static_cast<BigNum>(right_expr_num));
	}
};

// ">"
class ExprCmpGt : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprCmpGt(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		ExprNum left_expr_num, right_expr_num;
		_get_resized_child_expr_nums(left_expr_num, right_expr_num);

		_value.copy_from_bignum(static_cast<BigNum>(left_expr_num)
			> static_cast<BigNum>(right_expr_num));
	}
};

// "<="
class ExprCmpLe : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprCmpLe(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		ExprNum left_expr_num, right_expr_num;
		_get_resized_child_expr_nums(left_expr_num, right_expr_num);

		_value.copy_from_bignum(static_cast<BigNum>(left_expr_num)
			<= static_cast<BigNum>(right_expr_num));
	}
};

// ">="
class ExprCmpGe : public ExprBaseLogCmpBinOp
{
public:		// functions
	ExprCmpGe(Expression* left_child, Expression* right_child)
		: ExprBaseLogCmpBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		ExprNum left_expr_num, right_expr_num;
		_get_resized_child_expr_nums(left_expr_num, right_expr_num);

		_value.copy_from_bignum(static_cast<BigNum>(left_expr_num)
			>= static_cast<BigNum>(right_expr_num));
	}
};

// "Expression" classes derived from "ExprBaseLengthTwoMaxBinOp"

// Binop "+"
class ExprBinOpPlus : public ExprBaseLengthTwoMaxBinOp
{
public:		// functions
	ExprBinOpPlus(Expression* left_child, Expression* right_child)
		: ExprBaseLengthTwoMaxBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			+ static_cast<BigNum>(_right_child_value()));
	}
};

// Binop "-"
class ExprBinOpMinus : public ExprBaseLengthTwoMaxBinOp
{
public:		// functions
	ExprBinOpMinus(Expression* left_child, Expression* right_child)
		: ExprBaseLengthTwoMaxBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			- static_cast<BigNum>(_right_child_value()));
	}
};

// "*"
class ExprBinOpMul : public ExprBaseLengthTwoMaxBinOp
{
public:		// functions
	ExprBinOpMul(Expression* left_child, Expression* right_child)
		: ExprBaseLengthTwoMaxBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			* static_cast<BigNum>(_right_child_value()));
	}
};

// "/"
class ExprBinOpDiv : public ExprBaseLengthTwoMaxBinOp
{
public:		// functions
	ExprBinOpDiv(Expression* left_child, Expression* right_child)
		: ExprBaseLengthTwoMaxBinOp(left_child, right_child)
	{
	}

	void evaluate() final
	{
		_value.copy_from_bignum(static_cast<BigNum>(_left_child_value())
			/ static_cast<BigNum>(_right_child_value()));
	}
};

} // namespace frost_hdl


#endif		// src_expression_classes_hpp
