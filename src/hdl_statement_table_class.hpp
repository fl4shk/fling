#ifndef src_hdl_statement_table_class_hpp
#define src_hdl_statement_table_class_hpp

// src/hdl_statement_table_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "scoped_table_classes.hpp"
//#include "symbol_table_class.hpp"
#include "hdl_lhs_type_table_class.hpp"
#include "expression_classes.hpp"
#include "misc_utility_funcs.hpp"

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
public:		// types
	typedef typename ScopedUnnamedTable<HdlStatement>::Node* TableNode;

	enum class DriverType
	{
		None,
		ContAssign,
		BehavBlockInitial,
		BehavBlockAlwaysComb,
		BehavBlockAlwaysSeq,
	};

	enum class EdgeSensType
	{
		None,
		Posedge,
		Negedge
	};

protected:		// variables
	// Component "Expression"s.
	std::vector<Expression*> _exprs;

public:		// functions
	HdlStatement() = default;

	virtual ~HdlStatement() = default;

	virtual DriverType driver_type() const;
	virtual EdgeSensType edge_sens_type() const;


	//// Only some classes derived from "HdlStatement" need for this to
	//// sometimes return a message other than "nullptr".
	//// The returned message will be used as (part of?) an error message if
	//// it is not a "nullptr".
	//virtual SavedString is_valid() const;

	virtual SavedString to_hdl_source(TableNode top) const;


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

	virtual DriverType driver_type() const
	{
		return DriverType::ContAssign;
	}

	SavedString to_hdl_source(TableNode top) const
	{
		return dup_str("assign ", TO_HDL_SOURCE(ident_expr), " = ",
			TO_HDL_SOURCE(rhs), ";\n");
	}


	GEN_EXPR_GETTER(ident_expr, 0)
	GEN_EXPR_GETTER(rhs, 1)
};

class HdlStmtBaseBehavBlock : public HdlStatement
{
public:		// functions
	HdlStmtBaseBehavBlock() = default;

	virtual ~HdlStmtBaseBehavBlock() = default;

	SavedString to_hdl_source(TableNode top) const;

protected:		// functions
	virtual SavedString _output_behav_block_str() const
	{
		return nullptr;
	}
};

// "initial"
class HdlStmtBehavBlockInitial : public HdlStatement
{
public:		// functions
	HdlStmtBehavBlockInitial() = default;

	virtual ~HdlStmtBehavBlockInitial() = default;

	virtual DriverType driver_type() const
	{
		return DriverType::BehavBlockInitial;
	}

protected:		// functions
	virtual SavedString _output_behav_block_str() const
	{
		return dup_str("initial");
	}
};

// "always_comb"
class HdlStmtBehavBlockAlwaysComb : public HdlStatement
{
public:		// functions
	HdlStmtBehavBlockAlwaysComb() = default;

	virtual ~HdlStmtBehavBlockAlwaysComb() = default;

	virtual DriverType driver_type() const
	{
		return DriverType::BehavBlockAlwaysComb;
	}

protected:		// functions
	virtual SavedString _output_behav_block_str() const
	{
		return dup_str("always @(*)");
	}
};

// "always_seq"
class HdlStmtBehavBlockAlwaysSeq : public HdlStatement
{
private:		// variables
	EdgeSensType _edge_sens_type = EdgeSensType::None;

public:		// functions
	HdlStmtBehavBlockAlwaysSeq(EdgeSensType s_edge_sens_type,
		Expression* s_ident);

	virtual ~HdlStmtBehavBlockAlwaysSeq() = default;

	virtual DriverType driver_type() const
	{
		return DriverType::BehavBlockAlwaysSeq;
	}

	virtual EdgeSensType edge_sens_type() const
	{
		return _edge_sens_type;
	}


	GEN_EXPR_GETTER(ident_expr, 0)

protected:		// functions
	virtual SavedString _output_behav_block_str() const;
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
