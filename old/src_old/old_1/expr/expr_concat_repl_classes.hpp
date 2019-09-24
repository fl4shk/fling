#ifndef src_expr_expr_concat_repl_classes_hpp
#define src_expr_expr_concat_repl_classes_hpp

// src/expr/expr_concat_repl_classes.hpp

#include "../misc_includes.hpp"

#include "dot_hpp_defines.hpp"

namespace frost_hdl
{

// "concat(...)"
class ExprConcat : public Expression
{
public:		// functions
	ExprConcat(const SrcCodePos& s_src_code_pos,
		ChildrenList&& s_children);

	virtual SavedString to_hdl_source() const;
	virtual LhsCategory lhs_category() const
	{
		return LhsCategory::Concat;
	}


protected:		// functions
	void _evaluate();
	size_t _starting_length() const;
	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	ChildrenList dupped_children;

	//	for (auto iter : dupped_children)
	//	{
	//		dupped_children.push_back(DUP_CHILD(iter));
	//	}

	//	return SAFE_SAVE_EXPR(ExprConcat(src_code_pos(),
	//		std::move(dupped_children)));
	//}
};

// "repl(...)"
class ExprRepl : public Expression
{
public:		// functions
	ExprRepl(const SrcCodePos& s_src_code_pos, Expression* s_width_child,
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

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	//return SAFE_SAVE_EXPR(ExprTernary(DUP_CHILD(_condition_child()),
	//	//	DUP_CHILD(_when_true_child()),
	//	//	DUP_CHILD(_when_false_child())));
	//	ChildrenList dupped_non_width_children;

	//	for (size_t i=0; i<_width_child_index(); ++i)
	//	{
	//		dupped_non_width_children.push_back
	//			(DUP_CHILD(_children.at(i)));
	//	}

	//	return SAFE_SAVE_EXPR(ExprRepl(src_code_pos(),
	//		DUP_CHILD(_width_child()),
	//		std::move(dupped_non_width_children)));
	//}
};

} // namespace frost_hdl

#include "dot_hpp_undefs.hpp"

#endif		// src_expr_expr_concat_repl_classes_hpp
