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
	ChildrenList _children;

	Symbol* _symbol = nullptr;
	bool _is_self_determined = false;
	bool _handles_children_eval = false;
	ExprNum _value;


public:		// functions
	Expression() = default;


	// Don't want copies of raw Expression's
	// Moves are okay, though
	GEN_CM_CONSTRUCTORS_AND_ASSIGN(Expression, delete, default);
	virtual ~Expression() = default;



	// I didn't want this made public, but...
	void inner_full_evaluate();


	virtual SavedString to_hdl_source() const;



	inline size_t num_children() const
	{
		return children().size();
	}
	inline bool is_leaf() const
	{
		return (num_children() == 0);
	}

	//inline Symbol* symbol() const
	//{
	//	return _symbol_table->at(_ident);
	//}



	//inline const auto& ident() const
	//{
	//	return (*_ident);
	//}



	//inline void set_value(const BigNum& n_value_data,
	//	size_t n_value_data_size, bool n_value_is_signed)
	//{
	//	set_value(ExprNum(n_value_data, n_value_data_size,
	//		n_value_is_signed));
	//}


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

	//Symbol* symbol() const
	//{
	//	return _symbol;
	//}
	//Symbol* set_symbol(Symbol* n_symbol)
	//{
	//	_symbol = n_symbol;
	//	return _symbol;
	//}

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
	enum class HdlSourceType
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
	virtual HdlSourceType _hdl_source_type() const
	{
		return HdlSourceType::DollarFunction;
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
	SavedString _binop_str() const
	{
		return dup_str("/");
	}
	void _evaluate()
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
	SavedString _binop_str() const
	{
		return dup_str("%");
	}
	void _evaluate()
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
};

// "$concat(...)"
class ExprConcat : public Expression
{
public:		// functions
	ExprConcat(ChildrenList&& s_children);

	virtual SavedString to_hdl_source() const;

protected:		// functions
	void _evaluate();
	size_t _starting_length() const;
};

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
};

// Non-sliced reference to an identifier of some sort.
class ExprIdentName : public Expression
{
public:		// functions
	ExprIdentName(Symbol* s_symbol);

	//bool is_constant() const
	//{
	//	return (Expression::is_constant() || symbol()->is_constant());
	//}

	virtual SavedString to_hdl_source() const;
	bool is_constant() const;

protected:		// functions
	void _evaluate();
	size_t _starting_length() const;
};

#undef TO_HDL_SOURCE

} // namespace frost_hdl


#endif		// src_expression_classes_hpp
