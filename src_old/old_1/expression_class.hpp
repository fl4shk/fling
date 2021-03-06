#ifndef src_expression_class_hpp
#define src_expression_class_hpp

// src/expression_class.hpp

#include "misc_includes.hpp"
//#include "misc_types.hpp"
#include "table_types.hpp"
#include "src_code_pos_class.hpp"
#include "expr_num_class.hpp"
//#include "general_allocator_class.hpp"
//#include "symbol_class.hpp"

#include "expr/dot_hpp_defines.hpp"

namespace frost_hdl
{


class Symbol;


class Expression
{
public:		// types
	//typedef SavedString OpStr;
	typedef SavedString Ident;

	typedef std::set<Expression*> DescendantsList;
	typedef std::vector<Expression*> ChildrenList;

	// Uses of identifiers that can be on the left-hand side of an
	// assignment.
	enum class LhsCategory
	{
		None,

		NonSliced,
		Sliced,

		MemberAccess,

		Concat,
	};

	// Concatenations and member accesses sometimes use this underneath.
	enum class SliceType
	{
		None,

		// vector[one_bit_index]
		OneBitSlicedVector,

		// vector[left:right]
		SlicedVector,

		// array[array_index]
		IndexedArray,

		// array[array_index][one_bit_index]
		IndexedAndOneBitSlicedArray,

		// array[array_index][left:right]
		IndexedAndSlicedArray,
	};

	//enum class Category
	//{
	//	UnOp,
	//	BinOp,
	//	Ternary,

	//	IdentSliced,
	//	HardCodedConstant,
	//};



protected:		// variables
	// Children!
	// Wave o'babies!
	ChildrenList _children;

	// This is used for "struct", "class" (if those even make it into the
	// language), and "interface" member accesses.
	// This is also used for "concat()", "repl()", and other things that
	// reference identifiers.
	// This (maybe?) makes it easier to change references to symbols when
	// re-building the internal representation.
	// Finally, this prevents children of the "Expression" from modified by
	// "_perf_mega_descs_cast()" and friends.
	ChildrenList _semi_hidden_children;

	Symbol* _symbol = nullptr;

	bool _is_self_determined = false;

	bool _handles_children_eval = false;
	bool _handles_value_set_size = false;


	ExprNum _value;

	SrcCodePos _src_code_pos;


public:		// functions
	//Expression() = default;

	Expression(const SrcCodePos& s_src_code_pos);


	// Don't want copies of raw Expression's
	// Moves are okay, though
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Expression);
	virtual ~Expression() = default;





	// I didn't want this made public, but...
	void inner_full_evaluate();
	void finish_init_value();

	// Recursively search the tree for a reference to a particular
	// "Symbol".  This is (exclusively?) used to prevent defining a
	// "parameter" in terms of itself.
	bool references_symbol(Symbol* to_check) const;

	//// Duplicate this expression *before* calling _evaluate()
	//Expression* pure_dup() const;
	//Expression* dupped_size_expr() const;

	//bool defined_in_terms_of_any_incomplete_symbol() const;



	inline bool is_valid_lhs() const
	{
		return (lhs_category() != LhsCategory::None);
	}



	inline size_t num_children() const
	{
		return children().size();
	}
	inline bool is_leaf() const
	{
		return (num_children() == 0);
	}

	//// Unfortunately, replacing the references to "Symbol"s has come down
	//// to this.  Each most-derived "Expression" class will now have to
	//// implement this.  It's a pain.
	//Expression* dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const;
	virtual SavedString to_hdl_source() const;
	virtual LhsCategory lhs_category() const;
	virtual SliceType slice_type() const;



	// This doesn't *need* to be stored anywhere.
	virtual bool is_constant() const
	{
		//printout("Debug:  is_constant():  ", _has_only_constant_children(),
		//	" ", _is_always_constant(), "\n");
		return (_has_only_constant_children() || _is_always_constant());
	}

	//virtual SavedString is_valid() const
	//{
	//	return nullptr;
	//}

	inline void full_evaluate_if_constant()
	{
		if (is_constant())
		{
			return _full_evaluate(true);
		}
	}




	GEN_GETTER_BY_CON_REF(children)
	GEN_GETTER_BY_CON_REF(semi_hidden_children)
	GEN_GETTER_BY_CON_REF(value)

	GEN_GETTER_AND_SETTER_BY_VAL(is_self_determined)
	GEN_GETTER_AND_SETTER_BY_VAL(handles_children_eval)
	GEN_GETTER_AND_SETTER_BY_VAL(handles_value_set_size)

	GEN_GETTER_AND_SETTER_BY_VAL(symbol)

	GEN_GETTER_BY_CON_REF(src_code_pos)


protected:		// functions
	void _err(const std::string& msg) const;
	inline void _set_value(const ExprNum& n_value)
	{
		_value = n_value;
	}


	virtual void _inner_finish_init_value();

	// Don't call "_evaluate()" until after the size of the expression has
	// been determined and the children have been modified.
	virtual void _evaluate();

	virtual bool _children_affect_length() const;

	// The length of the expression before (possibly) being casted to a
	// larger one.
	virtual size_t _starting_length() const;

	virtual bool _is_always_constant() const;

	virtual bool _extra_check_for_references_symbol(Symbol* to_check)
		const;

	//virtual Expression* _inner_pure_dup() const;
	//virtual Expression* _inner_dupped_size_expr() const;
	//virtual Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const;



	//inline void _set_ident(const std::string& n_ident)
	//{
	//	_ident = dup_str(n_ident);
	//}

	// Stuff for evaluating constant expressions.
	void _full_evaluate(bool is_real_top);

	void _get_first_layer_ptln_descs(DescendantsList& ret) const;

	size_t _highest_desc_size_with_effect() const;
	bool _has_any_unsigned_first_layer_non_sd_descs() const;

	void _perf_mega_descs_cast(size_t n_size, bool n_is_signed) const;

	bool _has_only_constant_children() const;

	inline bool _is_pseudo_top_level_node() const
	{
		const bool non_sd_thing = (!_is_always_constant())
			&& (!_children_affect_length());
		return (non_sd_thing || is_self_determined());
	}

	//template<typename FirstArgType, typename... RemArgTypes>
	//inline bool _has_only_constant_children(FirstArgType&& first_child,
	//	RemArgTypes&&... rem_children)
	//{
	//	_set_children(first_child, rem_children...);
	//	return _has_only_constant_children();
	//}

	inline ChildrenList _all_children() const
	{
		ChildrenList ret;

		for (auto iter : _children)
		{
			ret.push_back(iter);
		}

		for (auto iter : _semi_hidden_children)
		{
			ret.push_back(iter);
		}
		return ret;
	}

	// Require at LEAST one argument.
	template<typename FirstArgType, typename... RemArgTypes>
	inline void _set_children(FirstArgType&& first_child,
		RemArgTypes&&... rem_children)
	{
		_children.push_back(first_child);

		// Oh hey, an actual use for "if constexpr" that actually CAN'T be
		// written as a plain old "if"!
		if constexpr (sizeof...(rem_children) > 0)
		{
			_set_children(rem_children...);
		}

		// (Don't uncomment this if "_set_children()" is called too early
		// in the class hierarchy!)
		//else 
		//{
		//	_value.set_size(_starting_length());
		//}
	}

	// Require at LEAST one argument.
	template<typename FirstArgType, typename... RemArgTypes>
	inline void _set_semi_hidden_children
		(FirstArgType&& first_ident_access_child,
		RemArgTypes&&... rem_semi_hidden_children)
	{
		_semi_hidden_children.push_back(first_ident_access_child);

		// Oh hey, an actual use for "if constexpr" that actually CAN'T be
		// written as a plain old "if"!
		if constexpr (sizeof...(rem_semi_hidden_children) > 0)
		{
			_set_semi_hidden_children(rem_semi_hidden_children...);
		}
	}
};





// "most derived" "Expression" classes that derive only from "Expression"




//#undef TO_HDL_SOURCE
//#undef DUP_CHILD
//#undef SAFE_SAVE_EXPR
//#undef REMOVE_CONST_REF
#include "expr/dot_hpp_undefs.hpp"


} // namespace frost_hdl


#endif		// src_expression_class_hpp
