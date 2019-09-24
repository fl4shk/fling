#ifndef src_expr_expr_ternary_class_hpp
#define src_expr_expr_ternary_class_hpp

// src/expr/expr_ternary_class.hpp

#include "../misc_includes.hpp"

#include "dot_hpp_defines.hpp"

namespace frost_hdl
{

// "condition ? when_true : when_false"
class ExprTernary : public Expression
{
public:		// functions
	ExprTernary(const SrcCodePos& s_src_code_pos,
		Expression* condition_child, Expression* when_true_child,
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

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprTernary(src_code_pos(),
	//		DUP_CHILD(_condition_child()), DUP_CHILD(_when_true_child()),
	//		DUP_CHILD(_when_false_child())));
	//}
};


} // namespace frost_hdl

#include "dot_hpp_undefs.hpp"


#endif		// src_expr_expr_ternary_class_hpp
