#include "../expression_class.hpp"
#include "expr_concat_repl_classes.hpp"
#include "dot_cpp_defines.hpp"

namespace frost_hdl
{

ExprConcat::ExprConcat(const SrcCodePos& s_src_code_pos,
	ChildrenList&& s_children)
	: Expression(s_src_code_pos)
{
	_children = std::move(s_children);

	for (auto child : _children)
	{
		child->set_is_self_determined(true);
	}

	//_value.set_size(_starting_length());
	_value.set_is_signed(false);
}

SavedString ExprConcat::to_hdl_source() const
{
	std::string non_dupped_ret;

	non_dupped_ret += "{";

	//for (auto child : _children)
	for (size_t i=0; i<children().size(); ++i)
	{
		//non_dupped_ret += "(";
		non_dupped_ret += *children().at(i)->to_hdl_source();
		//non_dupped_ret += ")";

		if ((i + 1) != children().size())
		{
			non_dupped_ret += ", ";
		}
	}

	non_dupped_ret += "}";

	return dup_str(non_dupped_ret);
}

//SavedString ExprConcat::to_hdl_source() const
//{
//	std::string ret;
//
//	ret += "{";
//
//	for (size_t i=0; i<children().size(); ++i)
//	{
//		//ret += TO_HDL_SOURCE(children.at(i));
//		ret += *children().at(i)->to_hdl_source();
//
//		if (i != children().size())
//		{
//			ret += ", ";
//		}
//	}
//
//	ret += "}";
//
//	return dup_str(ret);
//}

void ExprConcat::_evaluate()
{
	RawExprNumData n_value_data;
	//n_value_data.reserve(_value.size());

	for (auto child : _children)
	{
		for (size_t i=0; i<child->value().size(); ++i)
		{
			n_value_data.push_back(child->value().one_bit(i));
		}
	}

	_value.set_data(std::move(n_value_data));
}

size_t ExprConcat::_starting_length() const
{
	size_t ret = 0;

	for (auto child : _children)
	{
		ret += child->value().size();
	}

	return ret;
}

ExprRepl::ExprRepl(const SrcCodePos& s_src_code_pos,
	Expression* s_width_child, ChildrenList&& s_non_width_children)
	: Expression(s_src_code_pos)
{
	_children = std::move(s_non_width_children);
	_children.push_back(s_width_child);

	//_value.set_size(_starting_length());
	_value.set_is_signed(false);
}

SavedString ExprRepl::to_hdl_source() const
{
	std::string non_dupped_ret;

	non_dupped_ret += sconcat("{", *_width_child()->to_hdl_source(), "{");

	for (size_t i=0; i<_width_child_index(); ++i)
	{
		non_dupped_ret += *children().at(i)->to_hdl_source();

		if ((i + 1) != _width_child_index())
		{
			non_dupped_ret += ", ";
		}
	}

	non_dupped_ret += "}}";

	return dup_str(non_dupped_ret);
}

void ExprRepl::_evaluate()
{
	RawExprNumData n_value_data;

	for (auto child : _children)
	{
		for (size_t i=0;
			i<static_cast<BigNum>(_width_child()->value()).get_ui();
			++i)
		{
			for (size_t j=0; j<child->value().size(); ++j)
			{
				n_value_data.push_back(child->value().one_bit(j));
			}
		}
	}

	_value.set_data(std::move(n_value_data));
}

size_t ExprRepl::_starting_length()
{
	size_t ret = 0;

	for (auto child : _children)
	{
		ret += child->value().size();
	}

	ret *= _width_child()->value().size();

	return ret;
}

} // namespace frost_hdl
