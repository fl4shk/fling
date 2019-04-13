#ifndef src_expr_expr_ident_classes_hpp
#define src_expr_expr_ident_classes_hpp

// src/expr/expr_ident_classes.hpp

#include "../misc_includes.hpp"
#include "../pseudo_func_call_range_class.hpp"

#include "dot_hpp_defines.hpp"

namespace frost_hdl
{

// Base class to help me be lazy and slightly reduce the chance of a
// specific bug.
//--------
class ExprIdentRefBase : public Expression
{
public:		// functions
	ExprIdentRefBase(const SrcCodePos& s_src_code_pos, Symbol* s_symbol);
};
//--------

// Non-sliced reference to an identifier of some sort.
//--------
class ExprIdentName : public ExprIdentRefBase
{
public:		// functions
	ExprIdentName(const SrcCodePos& s_src_code_pos, Symbol* s_symbol);


	virtual SavedString to_hdl_source() const;
	virtual LhsCategory lhs_category() const
	{
		return LhsCategory::NonSliced;
	}

	bool is_constant() const;

protected:		// functions
	void _inner_finish_init_value();
	void _evaluate();
	size_t _starting_length() const;

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	if (replace_syms_map.contains(_symbol))
	//	{
	//		return SAFE_SAVE_EXPR(ExprIdentName(src_code_pos(),
	//			replace_syms_map.at(_symbol)));
	//	}
	//	else
	//	{
	//		return SAFE_SAVE_EXPR(ExprIdentName(src_code_pos(), _symbol));
	//	}
	//}
};
//--------

// vector[one_bit_index]
//--------
class ExprIdentOneBitSlicedVector : public ExprIdentRefBase
{
public:		// functions
	ExprIdentOneBitSlicedVector(const SrcCodePos& s_src_code_pos,
		Symbol* s_symbol, Expression* s_one_bit_index_expr);

	virtual SavedString to_hdl_source() const;
	virtual LhsCategory lhs_category() const
	{
		return LhsCategory::Sliced;
	}
	virtual SliceType slice_type() const
	{
		return SliceType::OneBitSlicedVector;
	}

	bool is_constant() const;

protected:		// functions
	void _inner_finish_init_value();
	void _evaluate();
	size_t _starting_length() const;

	inline Expression* _one_bit_index_expr() const
	{
		return _semi_hidden_children.at(0);
	}
};
//--------

// vector[left:right]
//--------
class ExprIdentSlicedVector : public ExprIdentRefBase
{
public:		// functions
	ExprIdentSlicedVector(const SrcCodePos& s_src_code_pos,
		Symbol* s_symbol, Expression* s_range_left_expr,
		Expression* s_range_right_expr);

	virtual SavedString to_hdl_source() const;
	virtual LhsCategory lhs_category() const
	{
		return LhsCategory::Sliced;
	}
	virtual SliceType slice_type() const
	{
		return SliceType::SlicedVector;
	}

	bool is_constant() const;

	//SavedString is_valid() const;

protected:		// functions
	void _inner_finish_init_value();
	void _evaluate();
	size_t _starting_length() const;

	inline Expression* _range_left_child() const
	{
		return _semi_hidden_children.at(0);
	}
	inline Expression* _range_right_child() const
	{
		return _semi_hidden_children.at(1);
	}

	inline PseudoFuncCallRange _pseudo_func_call_range() const
	{
		return PseudoFuncCallRange(_range_left_child(),
			_range_right_child());
	}
};
//--------


// array[array_index]
//--------
class ExprIdentIndexedArray : public ExprIdentRefBase
{
public:		// functions
	ExprIdentIndexedArray(const SrcCodePos& s_src_code_pos,
		Symbol* s_symbol, Expression* s_array_index_expr);

	virtual SavedString to_hdl_source() const;
	virtual LhsCategory lhs_category() const
	{
		return LhsCategory::Sliced;
	}
	virtual SliceType slice_type() const
	{
		return SliceType::IndexedArray;
	}

	bool is_constant() const;

protected:		// functions
	inline Expression* _array_index_expr() const
	{
		return _semi_hidden_children.at(0);
	}
};
//--------

//// array[array_index][one_bit_index]
////--------
//class ExprIdentIndexedAndOneBitSlicedArray : public ExprIdentRefBase
//{
//
//protected:		// variables
//};
////--------
//
//
//// array[array_index][left:right]
////--------
//class ExprIdentIndexedAndSlicedArray : public ExprIdentRefBase
//{
//};
////--------


//// whatever.whatever.whatever
//// whatever.whatever_array[index].(...).whatever[left:right]
//// whatever.whatever_array[index].(...).whatever[one_bit_index]
//// whatever.whatever_array[index][left:right]
////--------
//class ExprIdentMemberAccess : public ExprIdentRefBase
//{
//public:		// functions
//protected:		// functions
//	void _inner_finish_init_value();
//	void _evaluate();
//	size_t _starting_length() const;
//};
////--------

} // namespace frost_hdl

#include "dot_hpp_undefs.hpp"

#endif		// src_expr_expr_ident_classes_hpp
