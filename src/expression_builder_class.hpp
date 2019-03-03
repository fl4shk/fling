#ifndef src_expression_builder_class_hpp
#define src_expression_builder_class_hpp

// src/expression_builder_class.hpp

#include "misc_includes.hpp"
#include "expression_classes.hpp"

namespace frost_hdl
{

class ExpressionBuilder
{
public:		// static functions
	template<typename NumType>
	static inline Expression* make_expr_hc_num(const NumType& s_data,
		size_t s_data_size, bool s_is_signed)
	{
		return save_expr(ExprHardCodedNum(ExprNum(BigNum(s_data),
			s_data_size, s_is_signed)));
	}
	template<typename NumType>
	static inline Expression* make_expr_hc_num(const NumType& s_data)
	{
		static_assert(std::is_integral<NumType>(),
			"NumType must be an integral type.");
		if constexpr (std::is_integral<NumType>())
		{
			if constexpr (std::is_same<NumType, bool>())
			{
				return make_expr_hc_num(s_data, 1,
					std::is_signed<NumType>());
			}
			else
			{
				return make_expr_hc_num(s_data,
					(sizeof(NumType) * sizeof(u8)),
					std::is_signed<NumType>());
			}
		}
		// Eek!
		return nullptr;
	}

	template<typename ExprType>
	static inline Expression* make_expr_unop(Expression* only_child)
	{
		return save_expr(ExprType(only_child));
	}

	template<typename ExprType>
	static inline Expression* make_expr_binop(Expression* left_child,
		Expression* right_child)
	{
		return save_expr(ExprType(left_child, right_child));
	}

protected:		// static functions
	template<typename FirstType, typename... RemArgTypes>
	static void _inner_make_expr_concat
		(Expression::ChildrenList& s_children, FirstType&& first_child,
		RemArgTypes&&... rem_children)
	{
		if constexpr (sizeof...(rem_children) > 0)
		{
			_inner_make_expr_concat(s_children, rem_children...);
		}

		s_children.push_back(first_child);
	}

public:		// static functions

	// Require at least one child
	template<typename FirstType, typename... RemArgTypes>
	static inline Expression* make_expr_concat(FirstType&& first_child,
		RemArgTypes&&... rem_children)
	{
		Expression::ChildrenList s_children;

		_inner_make_expr_concat(s_children, first_child, rem_children...);

		return save_expr(ExprConcat(std::move(s_children)));
	}

	static inline Expression* make_expr_concat
		(Expression::ChildrenList&& s_children)
	{
		return save_expr(ExprConcat(std::move(s_children)));
	}

	static inline std::ostream& show_expr(std::ostream& os,
		Expression* to_show)
	{
		return osprintout(os, to_show->value().size(), " ",
			to_show->value().is_signed(), ":  ", BigNum(to_show->value()),
			"\n");
	}
};


} // namespace frost_hdl


#endif		// src_expression_builder_class_hpp
