#include "expression_class.hpp"
#include "symbol_class.hpp"
#include "frost_lhs_type_class.hpp"
#include "frost_full_type_class.hpp"

#include "expr/dot_cpp_defines.hpp"
#include "expr/expr_derived_classes.hpp"

#include "general_allocator_class.hpp"

namespace frost_hdl
{


//typedef Expression::OpStr OpStr;
//typedef Expression::Type ExprType;

//Expression::Expression()
//{
//	//for (auto& iter : _children)
//	//{
//	//	iter = nullptr;
//	//}
//
//	//_ident = nullptr;
//	set_symbol(nullptr);
//	set_is_self_determined(false);
//	set_handles_children_eval(false);
//
//}

Expression::Expression(const SrcCodePos& s_src_code_pos)
{
	_src_code_pos = s_src_code_pos;
	set_symbol(nullptr);
	set_is_self_determined(false);
	set_handles_children_eval(false);
}



//OpStr Expression::op_str() const
//{
//	return dup_str("INVALID_EXPRESSION");
//}

void Expression::inner_full_evaluate()
{
	if (!handles_children_eval())
	{
		for (auto iter : _children)
		{
			iter->inner_full_evaluate();
			iter->_evaluate();
		}
	}
	_evaluate();
}
void Expression::finish_init_value()
{
	for (auto child : _children)
	{
		child->finish_init_value();
	}
	_inner_finish_init_value();

	if (!_handles_value_set_size)
	{
		_value.set_size(_starting_length());
	}
}


bool Expression::references_symbol(Symbol* to_check) const
{
	//printout("Expression::references_symbol():  ", *to_check->ident(),
	//	"\n");
	if (_symbol == to_check)
	{
		return true;
	}

	if ((_symbol != nullptr)
		&& (_symbol->value() != nullptr)
		&& _symbol->value()->references_symbol(to_check))
	{
		return true;
	}

	// Here we execute the recursion into children.  This *only* works if
	// "Expression"s are truly trees.  I *really* hope there are no bugs
	// that can cause an "Expression" to have itself as a descendant, but I
	// think this is a low risk.
	for (auto iter : _children)
	{
		if (iter->references_symbol(to_check))
		{
			return true;
		}
	}

	return false;
}

bool Expression::defined_in_terms_of_any_incomplete_symbol() const
{
	if (_symbol != nullptr)
	{
		//if (_symbol->is_incomplete())
		//{
		//	printout("incomplete sym debug:  ", *_symbol->ident(), "\n");
		//}
		//else // if (!_symbol->is_incomplete())
		//{
		//	_symbol->value()->full_evaluate_if_constant();
		//	printout("!incomplete sym debug:  ", *_symbol->ident(), " ",
		//		_symbol->value()->value().convert_to_bignum(), "\n");
		//}

		if (_symbol->is_incomplete())
		{
			return true;
		}
	}

	for (auto iter : _children)
	{
		if (iter->defined_in_terms_of_any_incomplete_symbol())
		{
			return true;
		}
	}

	return false;
}

//Expression* Expression::dup_with_changed_symbols
//	(const ReplaceSymsMap& replace_syms_map) const
//{
//	return _inner_dup_with_changed_symbols(replace_syms_map);
//}

SavedString Expression::to_hdl_source() const
{
	//printerr("Expression::to_hdl_source():  Eek!");
	//exit(1);
	_err("Expression::to_hdl_source():  Eek!");
	return nullptr;
}

auto Expression::lhs_category() const -> LhsCategory
{
	return LhsCategory::None;
}

void Expression::_err(const std::string& msg) const
{
	src_code_pos().err(msg);
}

void Expression::_inner_finish_init_value()
{
}

void Expression::_evaluate()
{
	//printerr("Expression::_evaluate():  Eek!");
	//exit(1);
	_err("Expression::_evaluate():  Eek!");

	_set_value(ExprNum(0, 1, false));
}

bool Expression::_children_affect_length() const
{
	// Most types of expression use this definition.
	return true;
}

size_t Expression::_starting_length() const
{
	//printerr("Expression::_starting_length():  Eek!");
	//exit(1);
	_err("Expression::_starting_length():  Eek!");

	return 0;
}

bool Expression::_is_always_constant() const
{
	return false;
}


//Expression* Expression::_inner_dup_with_changed_symbols
//	(const ReplaceSymsMap& replace_syms_map) const
//{
//	printerr("Expression::_inner_dup_with_changed_symbols():  Eek!");
//	exit(1);
//
//	return nullptr;
//}


void Expression::_full_evaluate(bool is_real_top)
{
	// The expression evaluation algorithm:
	// * Determine the expression size using standard rules.
	// * Determine the sign of the expression using standard rules.
	// * Coerce the type of every operand of the expression, not counting
	// those that are self-determined, to the type of the expression.
	// * Extend the size of every operand of the expression, not counting
	// those that are self-determined, to the type of the expression.
	// Perform sign extension if and only if the operand type (after type
	// coercion) is signed.
	// * Finally, evaluate everything.

	if (is_real_top)
	{
		finish_init_value();
	}


	// The descendants of an "Expression" already know their size and their
	// type.
	DescendantsList ptln_descs;
	_get_first_layer_ptln_descs(ptln_descs);

	for (auto iter : ptln_descs)
	{
		iter->_full_evaluate(false);
	}

	// When does this happen?
	if (!_is_pseudo_top_level_node())
	{
		//printout("!_is_pseudo_top_level_node():  Test\n");
		_perf_mega_descs_cast(value().size(), value().is_signed());
	}
	else // if (_is_pseudo_top_level_node())
	{
		if (is_self_determined())
		{
			_perf_mega_descs_cast(value().size(), value().is_signed());
		}
		else // if (!is_self_determined())
		{
			_perf_mega_descs_cast(_highest_desc_size_with_effect(),
				!_has_any_unsigned_first_layer_non_sd_descs());
		}
	}


	if (is_real_top)
	{
		inner_full_evaluate();
	}

}


// Get pseudo top-level node descendants, but only the ones in the first
// "layer" of descendants, relative to this "Expression".
void Expression::_get_first_layer_ptln_descs(DescendantsList& ret) const
{
	for (auto iter : _children)
	{
		// It's a bug if any descendants appear twice....
		// This is comparing to NOT zero because we need an "Expression" to
		// be a tree (not a DAG or something).
		if (ret.count(iter) != 0)
		{
			printerr("Expression::_get_pseudo_top_level_descs():",
				"  Eek!\n");
			exit(1);
		}

		if (iter->_is_pseudo_top_level_node())
		{
			ret.insert(iter);
		}
		else // if (!iter->_is_pseudo_top_level_node())
		{
			iter->_get_first_layer_ptln_descs(ret);
		}
	}
}

// Find the highest size of a descendant of this "Expression" that can
// affect the size of this "Expression".  This is used for 
size_t Expression::_highest_desc_size_with_effect() const
{
	size_t ret = 0;

	for (const auto& child : _children)
	{
		if (!child->is_self_determined())
		{
			if (child->_is_pseudo_top_level_node())
			{
				ret = max_va(ret, child->value().size());
			}
			else // if (!child->_is_pseudo_top_level_node())
			{
				ret = max_va(ret, child->_highest_desc_size_with_effect());
				ret = max_va(ret, child->value().size());
			}
			//ret = max_va(ret, child->_highest_desc_size_with_effect());
			//ret = max_va(ret, child->value().size());
		}
	}

	return ret;
}

bool Expression::_has_any_unsigned_first_layer_non_sd_descs() const
{
	for (const auto& child : _children)
	{
		if (!child->is_self_determined())
		{
			if (!child->value().is_signed())
			{
				return true;
			}

			if (!child->_is_pseudo_top_level_node())
			{
				if (child->_has_any_unsigned_first_layer_non_sd_descs())
				{
					return true;
				}
			}
		}
	}

	return false;
}

void Expression::_perf_mega_descs_cast(size_t n_size, bool n_is_signed)
	const
{
	for (auto child : _children)
	{
		// We don't want to cast self-determined nodes.
		if (!child->is_self_determined())
		{
			child->_value.change_full_type(n_size, n_is_signed);

			// We don't want to cast the *descendants* of a pseudo
			// top-level node.
			if (!child->_is_pseudo_top_level_node())
			{
				child->_perf_mega_descs_cast(n_size, n_is_signed);
			}
		}
	}
}

bool Expression::_has_only_constant_children() const
{
	if (is_leaf())
	{
		return false;
	}

	for (const auto& child : _children)
	{
		if (!child->is_constant())
		{
			return false;
		}
	}

	return true;
}




} // namespace frost_hdl
