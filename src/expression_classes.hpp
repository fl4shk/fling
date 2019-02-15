#ifndef src_expression_classes_hpp
#define src_expression_classes_hpp

// src/expression_classes.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

class Expression
{
public:		// constants
	// If I recall correctly, only "?:" has three children.
	static constexpr size_t max_num_children = 3;

protected:		// variables
	std::array<Expression*, max_num_children> _children;
	BigNum _value, _size;
	bool _is_signed, _is_constant;

public:		// functions
	[[gnu::noinline]] Expression();


	// Don't want copies of raw Expression's
	Expression(const Expression& to_copy) = delete;


	virtual ~Expression();


	// Don't want copies of raw Expression's
	Expression& operator = (const Expression& to_copy) = default;

	virtual size_t num_children() const = 0;


	inline bool is_leaf() const
	{
		return (num_children() == 0);
	}


	GEN_GETTER_BY_CON_REF(children)

	GEN_GETTER_BY_CON_REF(value)
	GEN_GETTER_BY_CON_REF(size)
	GEN_GETTER_BY_VAL(is_constant)
	GEN_GETTER_BY_VAL(is_signed)

protected:		// functions
	bool _any_children_are_constant() const;

	template<typename FirstArgType, typename... RemArgTypes>
	void _inner_set_children(size_t index, FirstArgType&& first,
		RemArgTypes&&... rem_args)
	{
		_children.at(index) = first;

		if constexpr (sizeof...(rem_args) > 0)
		{
			_inner_set_children(index + 1, rem_args...);
		}
	}

	template<typename FirstArgType, typename... RemArgTypes>
	void _set_children(FirstArgType&& first, RemArgTypes&&... rem_args)
	{
		_inner_set_children(0, first, rem_args...);
	}
};



// "&&"
class ExprLogAnd : public Expression
{
public:		// functions
	ExprLogAnd(Expression* left, Expression* right);

	size_t num_children() const
	{
		return 2;
	}
};

} // namespace frost_hdl


#endif		// src_expression_classes_hpp
