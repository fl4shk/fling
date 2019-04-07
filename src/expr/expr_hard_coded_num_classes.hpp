#ifndef src_expr_expr_hard_coded_num_classes_hpp
#define src_expr_expr_hard_coded_num_classes_hpp

// src/expr/expr_hard_coded_num_classes.hpp

#include "../misc_includes.hpp"

#include "dot_hpp_defines.hpp"

namespace frost_hdl
{

// A hard-coded number (not a named constant) whose value is fully known
// by the "ParseTreeVisitor".
class ExprHardCodedNum : public Expression
{
public:		// functions
	ExprHardCodedNum(const SrcCodePos& s_src_code_pos,
		const ExprNum& s_value)
		: Expression(s_src_code_pos)
	{
		_set_value(s_value);
	}

	virtual SavedString to_hdl_source() const
	{
		//return dup_str(static_cast<std::string>(value()));
		return dup_str(value().convert_to_verilog_literal());
	}


protected:		// functions

	// Hard-coded numbers whose values are fully known by the
	// "ParseTreeVisitor" don't really evaluate to anything.
	void _evaluate()
	{
	}

	bool _children_affect_length() const
	{
		return false;
	}
	size_t _starting_length() const
	{
		return value().size();
	}

	bool _is_always_constant() const
	{
		return true;
	}

	//inline Expression* _inner_dup_with_changed_symbols
	//	(const ReplaceSymsMap& replace_syms_map) const
	//{
	//	return SAFE_SAVE_EXPR(ExprHardCodedNum(src_code_pos(), value()));
	//}
};

// A hard-coded number that uses a "parameter" or "localparam" for its
// width (and thus whose value is not fully known by the
// "ParseTreeVisitor")
class ExprIdentSizedHardCodedNum : public Expression
{
private:		// variables
	// Don't want to store this as part of "_children".
	Expression* _size_expr = nullptr;
	BigNum _temp_value;

public:		// functions
	ExprIdentSizedHardCodedNum(const SrcCodePos& s_src_code_pos,
		Expression* s_size_expr, const BigNum& s_temp_value);

	virtual SavedString to_hdl_source() const
	{
		return dup_str(value().convert_to_verilog_literal());
	}


protected:		// functions
	void _inner_finish_init_value();

	// Even for this type of hard-coded number, we still don't need to have
	// "_evaluate()" do anything because "_inner_finish_init_value()" does
	// this for us.
	void _evaluate()
	{
	}

	bool _children_affect_length() const
	{
		return false;
	}
	size_t _starting_length() const;
	bool _is_always_constant() const
	{
		return true;
	}
};

} // namespace frost_hdl

#include "dot_hpp_undefs.hpp"


#endif		// src_expr_expr_hard_coded_num_classes_hpp
