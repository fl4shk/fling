#ifndef src_pseudo_func_call_range_class_hpp
#define src_pseudo_func_call_range_class_hpp

// src/pseudo_func_call_range_class.hpp

#include "misc_includes.hpp"
#include "expression_classes.hpp"

namespace frost_hdl
{

class PseudoFuncCallRange
{
private:		// variables
	Expression* _left = nullptr;
	Expression* _right = nullptr;

public:		// functions
	inline PseudoFuncCallRange() = default;
	inline PseudoFuncCallRange(Expression* s_left, Expression* s_right)
		: _left(s_left), _right(s_right)
	{
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(PseudoFuncCallRange);

	inline bool is_ascending() const
	{
		return (static_cast<BigNum>(left()->value())
			< static_cast<BigNum>(right()->value()));
	}
	inline bool is_descending() const
	{
		return (!is_ascending());
	}
	inline bool is_constant() const
	{
		return (left()->is_constant() && right()->is_constant());
	}

	GEN_GETTER_AND_SETTER_BY_VAL(left)
	GEN_GETTER_AND_SETTER_BY_VAL(right)
};

} // namespace frost_hdl


#endif		// src_pseudo_func_call_range_class_hpp
