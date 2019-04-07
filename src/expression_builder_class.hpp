#ifndef src_expression_builder_class_hpp
#define src_expression_builder_class_hpp

// src/expression_builder_class.hpp

#include "misc_includes.hpp"
#include "expression_class.hpp"
#include "expr/expr_derived_classes.hpp"

namespace frost_hdl
{

class ExpressionBuilder
{
public:		// static functions
	static inline Expression* make_expr_hc_num_from_expr_num
		(const SrcCodePos& s_src_code_pos, const ExprNum& to_copy)
	{
		return save_expr(ExprHardCodedNum(s_src_code_pos, to_copy));
	}
	template<typename NumType>
	static inline Expression* make_expr_hc_num
		(const SrcCodePos& s_src_code_pos, const NumType& s_data,
		size_t s_data_size, bool s_is_signed)
	{
		return save_expr(ExprHardCodedNum(s_src_code_pos,
			ExprNum(BigNum(s_data), s_data_size, s_is_signed)));
	}
	template<typename NumType>
	static inline Expression* make_expr_hc_num
		(const SrcCodePos& s_src_code_pos, const NumType& s_data)
	{
		static_assert(std::is_integral<NumType>(),
			"NumType must be an integral type.");

		if constexpr (std::is_integral<NumType>())
		{
			if constexpr (std::is_same<NumType, bool>())
			{
				return make_expr_hc_num(s_src_code_pos, s_data, 1,
					std::is_signed<NumType>());
			}
			else
			{
				return make_expr_hc_num(s_src_code_pos, s_data,
					(sizeof(NumType) * sizeof(u8)),
					std::is_signed<NumType>());
			}
		}
		// Eek!
		return nullptr;
	}
	static inline Expression* make_expr_ident_sized_hc_num
		(const SrcCodePos& s_src_code_pos, Expression* s_size_expr,
		const BigNum& s_temp_value)
	{
		return save_expr(ExprIdentSizedHardCodedNum(s_src_code_pos,
			s_size_expr, s_temp_value));
	}

	template<typename ExprType>
	static inline Expression* make_expr_unop
		(const SrcCodePos& s_src_code_pos, Expression* only_child)
	{
		return save_expr(ExprType(s_src_code_pos, only_child));
	}

	template<typename ExprType>
	static inline Expression* make_expr_binop
		(const SrcCodePos& s_src_code_pos, Expression* left_child,
		Expression* right_child)
	{
		return save_expr(ExprType(s_src_code_pos, left_child,
			right_child));
	}

protected:		// static functions
	template<typename FirstArgType, typename... RemArgTypes>
	static void _inner_make_expr_concat
		(Expression::ChildrenList& s_children, FirstArgType&& first_child,
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
	template<typename FirstArgType, typename... RemArgTypes>
	static inline Expression* make_expr_concat
		(const SrcCodePos& s_src_code_pos, FirstArgType&& first_child,
		RemArgTypes&&... rem_children)
	{
		Expression::ChildrenList s_children;

		_inner_make_expr_concat(s_children, first_child, rem_children...);

		return save_expr(ExprConcat(s_src_code_pos,
			std::move(s_children)));
	}

	static inline Expression* make_expr_concat
		(const SrcCodePos& s_src_code_pos,
		Expression::ChildrenList&& s_children)
	{
		return save_expr(ExprConcat(s_src_code_pos,
			std::move(s_children)));
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
