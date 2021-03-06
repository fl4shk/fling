#ifndef src_pseudo_func_call_range_class_hpp
#define src_pseudo_func_call_range_class_hpp

// src/pseudo_func_call_range_class.hpp

#include "misc_includes.hpp"
#include "expression_class.hpp"

namespace frost_hdl
{

// This is not an expression because it doesn't make sense for this to have
// one singular value.
class PseudoFuncCallRange
{
private:		// variables
	Expression* _left = nullptr;
	Expression* _right = nullptr;

public:		// functions
	PseudoFuncCallRange() = default;
	inline PseudoFuncCallRange(Expression* s_left, Expression* s_right)
		: _left(s_left), _right(s_right)
	{
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(PseudoFuncCallRange);
	virtual ~PseudoFuncCallRange() = default;

	// As far as I can tell, it doesn't really matter whether we use "<" or
	// "<=" in "is_ascending()", but I am biased towards "<" because
	// descending ranges are far more my thing than ascending ones.
	inline bool is_ascending() const
	{
		return (static_cast<BigNum>(left()->value())
			< static_cast<BigNum>(right()->value()));
	}
	inline bool is_descending() const
	{
		return (!is_ascending());
	}
	//inline bool is_constant() const
	//{
	//	return (left()->is_constant() && right()->is_constant());
	//}
	inline bool is_constant() const
	{
		return (left()->is_constant() && right()->is_constant());
	}
	inline void evaluate() const
	{
		_left->full_evaluate_if_constant();
		_right->full_evaluate_if_constant();
	}

	size_t size() const;

	GEN_GETTER_BY_VAL(left)
	GEN_GETTER_BY_VAL(right)
};

} // namespace frost_hdl


#endif		// src_pseudo_func_call_range_class_hpp
