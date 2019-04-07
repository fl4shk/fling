#ifndef src_expr_expr_ident_classes_hpp
#define src_expr_expr_ident_classes_hpp

// src/expr/expr_ident_classes.hpp

#include "../misc_includes.hpp"

#include "dot_hpp_defines.hpp"

namespace frost_hdl
{


// Non-sliced reference to an identifier of some sort.
class ExprIdentName : public Expression
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

//// Used by "ParseTreeVisitor" when constant "Symbol"s are defined in terms
//// of other, potentially unknown "Symbol"s.
////
//// Please do not touch the "_value" of one of these!
//class ExprSubpassIdentName : public Expression
//{
//public:		// functions
//	ExprSubpassIdentName(const SrcCodePos& s_src_code_pos,
//		Symbol* s_symbol);
//
//	virtual LhsCategory lhs_category() const
//	{
//		return LhsCategory::NonSliced;
//	}
//
//	bool is_constant() const;
//};

class ExprIdentSlicedWithRange : public Expression
{
public:		// functions
	ExprIdentSlicedWithRange(const SrcCodePos& s_src_code_pos,
		Symbol* s_symbol, Expression* range_left_child,
		Expression* range_right_child);

	virtual SavedString to_hdl_source() const;
	virtual LhsCategory lhs_category() const
	{
		return LhsCategory::Sliced;
	}

	bool is_constant() const;

	//SavedString is_valid() const;

protected:		// functions
	void _inner_finish_init_value();
	void _evaluate();
	size_t _starting_length() const;

	Expression* _range_left_child() const
	{
		return _children.at(0);
	}
	Expression* _range_right_child() const
	{
		return _children.at(1);
	}
};

} // namespace frost_hdl

#include "dot_hpp_undefs.hpp"

#endif		// src_expr_expr_ident_classes_hpp
