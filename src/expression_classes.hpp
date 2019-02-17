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
	//typedef std::string* MemberName;

	enum class Category
	{
		UnOp,
		BinOp,
		Ternary,

		IdentName,
		IdentSliced,
		HardCodedConstant,
	};

protected:		// variables
	std::vector<Expression*> _children;

	Ident _ident;
	ExprNum _value;

	//ExprNum _size;
	//bool _is_signed, _is_constant;
	//bool _is_signed;
	bool _is_constant;

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

	virtual void evaluate();
	virtual OpStr op_str() const;


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



	GEN_GETTER_BY_CON_REF(children)
	GEN_GETTER_BY_CON_REF(value)

	//GEN_GETTER_BY_VAL(is_signed)
	GEN_GETTER_BY_VAL(is_constant)

protected:		// functions

	inline void set_ident(const std::string& n_ident)
	{
		_ident = dup_str(n_ident);
	}
	//inline void set_value(const BigNum& n_value)
	//{
	//	_value = cstm_num_dup(n_value);
	//}
	//inline void set_size(const BigNum& n_size)
	//{
	//	_size = cstm_num_dup(n_size);
	//}

	bool _has_only_constant_children() const;

	template<typename FirstArgType, typename... RemArgTypes>
	inline bool _has_only_constant_children(FirstArgType&& first_child,
		RemArgTypes&&... rem_children)
	{
		_set_children(first_child, rem_children...);
		return _has_only_constant_children();
	}

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
	Expression* _left_child() const
	{
		return children().at(0);
	}

	Expression* _right_child() const
	{
		return children().at(1);
	}
};


// "&&"
class ExprLogAnd : public ExprBaseBinOp
{
public:		// functions
	inline ExprLogAnd(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "||"
class ExprLogOr : public ExprBaseBinOp
{
public:		// functions
	inline ExprLogOr(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "=="
class ExprCmpEq : public ExprBaseBinOp
{
public:		// functions
	inline ExprCmpEq(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "!="
class ExprCmpNe : public ExprBaseBinOp
{
public:		// functions
	inline ExprCmpNe(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "<"
class ExprCmpLt : public ExprBaseBinOp
{
public:		// functions
	inline ExprCmpLt(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// ">"
class ExprCmpGt : public ExprBaseBinOp
{
public:		// functions
	inline ExprCmpGt(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "<="
class ExprCmpLe : public ExprBaseBinOp
{
public:		// functions
	inline ExprCmpLe(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// ">="
class ExprCmpGe : public ExprBaseBinOp
{
public:		// functions
	inline ExprCmpGe(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "+" binop
class ExprBinOpPlus : public ExprBaseBinOp
{
public:		// functions
	inline ExprBinOpPlus(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};
// "-" binop
class ExprBinOpMinus : public ExprBaseBinOp
{
public:		// functions
	inline ExprBinOpMinus(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "*" binop
class ExprBinOpMul : public ExprBaseBinOp
{
public:		// functions
	inline ExprBinOpMul(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "/" binop
class ExprBinOpDiv : public ExprBaseBinOp
{
public:		// functions
	inline ExprBinOpDiv(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "%" binop
class ExprBinOpMod : public ExprBaseBinOp
{
public:		// functions
	inline ExprBinOpMod(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "&" binop
class ExprBinOpBitAnd : public ExprBaseBinOp
{
public:		// functions
	inline ExprBinOpBitAnd(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "|" binop
class ExprBinOpBitOr : public ExprBaseBinOp
{
public:		// functions
	inline ExprBinOpBitOr(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "^" binop
class ExprBinOpBitXor : public ExprBaseBinOp
{
public:		// functions
	inline ExprBinOpBitXor(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// "<<" binop
class ExprBinOpBitLsl : public ExprBaseBinOp
{
public:		// functions
	inline ExprBinOpBitLsl(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// ">>" binop
class ExprBinOpBitLsr : public ExprBaseBinOp
{
public:		// functions
	inline ExprBinOpBitLsr(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

// ">>>" binop
class ExprBinOpBitAsr : public ExprBaseBinOp
{
public:		// functions
	inline ExprBinOpBitAsr(Expression* left_child, Expression* right_child)
		: ExprBaseBinOp(left_child, right_child)
	{
	}

	void evaluate() final;
	OpStr op_str() const final;
};

} // namespace frost_hdl


#endif		// src_expression_classes_hpp
