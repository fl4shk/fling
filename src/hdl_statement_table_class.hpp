#ifndef src_hdl_statement_table_class_hpp
#define src_hdl_statement_table_class_hpp

// src/hdl_statement_table_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "scoped_table_classes.hpp"
#include "symbol_table_class.hpp"
#include "hdl_lhs_type_table_class.hpp"
#include "expression_classes.hpp"

namespace frost_hdl
{

#define TO_HDL_SOURCE(expr) (*expr()->to_hdl_source())
#define GEN_EXPR_GETTER(name, index) \
	inline Expression* name() const \
	{ \
		return _exprs.at(index); \
	}

// Base class for a statement (primarily for the insides of an "HdlModule",
// but also intended for use inside of an "HdlFunction")
class HdlStatement
{
protected:		// variables
	// Component "Expression"s.
	std::vector<Expression*> _exprs;

public:		// functions
	HdlStatement() = default;

	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlStatement, delete, default);


	virtual ~HdlStatement() = default;


	//// Only some classes derived from "HdlStatement" need for this to
	//// sometimes return a message other than "nullptr".
	//// The returned message will be used as (part of?) an error message if
	//// it is not a "nullptr".
	//virtual SavedString is_valid() const;

	virtual SavedString to_hdl_source() const;

protected:		// functions
	// Require at LEAST one argument
	template<typename FirstArgType, typename... RemArgTypes>
	inline void _set_exprs(FirstArgType&& first_expr,
		RemArgTypes&&... rem_exprs)
	{
		_exprs.push_back(first_expr);

		if constexpr (sizeof...(rem_exprs) > 0)
		{
			_set_exprs(rem_exprs...);
		}
	}
};

// Continuous assignment
class HdlStmtContAssign : public HdlStatement
{
public:		// functions
	//HdlStmtContAssign() = default;
	HdlStmtContAssign(Expression* s_ident_expr, Expression* s_rhs);

	virtual ~HdlStmtContAssign() = default;

	//SavedString is_valid() const;
	SavedString to_hdl_source() const
	{
		return dup_str("assign ", TO_HDL_SOURCE(ident_expr), " = ",
			TO_HDL_SOURCE(rhs), ";");
	}
	GEN_EXPR_GETTER(ident_expr, 0)
	GEN_EXPR_GETTER(rhs, 1)

private:		// functions
	//inline Expression* _ident_expr() const
	//{
	//	return _exprs.at(0);
	//}

	//inline Expression* _rhs() const
	//{
	//	return _exprs.at(1);
	//}

};

class HdlStatementTable : public ScopedUnnamedTable<HdlStatement>
{
public:		// functions
	HdlStatementTable() = default;
	virtual ~HdlStatementTable() = default;
};

#undef TO_HDL_SOURCE
#undef GEN_EXPR_GETTER

} // namespace frost_hdl


#endif		// src_hdl_statement_table_class_hpp
