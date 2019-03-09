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
	typedef typename ScopedUnnamedTable<HdlStatement>::Node TableNode;


	// How a "Symbol" is driven
	enum class DriverType
	{
		None,
		ContAssign,
		BehavBlockInitial,
		BehavBlockAlwaysComb,
		BehavBlockAlwaysSeq,
	};

	// Pretty much only relevant for "always_seq"
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
	//virtual EdgeSensType edge_sens_type() const;


	//// Only some classes derived from "HdlStatement" need for this to
	//// sometimes return a message other than "nullptr".
	//// The returned message will be used as (part of?) an error message if
	//// it is not a "nullptr".
	//virtual SavedString is_valid() const;


	// This function takes the "top" parameter so that assignments inside
	// of behavioral blocks can know whether to output blocking assignments
	// ("=") or non-blocking assignments ("<=").
	virtual SavedString to_hdl_source(TableNode* top) const;


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

// Continuous assignment ("assign")
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

	SavedString to_hdl_source(TableNode* top) const;


	GEN_EXPR_GETTER(ident_expr, 0)
	GEN_EXPR_GETTER(rhs, 1)
};

// Base class for "initial", "always_comb", and "always_seq".
class HdlStmtBaseBehavBlock : public HdlStatement
{
public:		// functions
	HdlStmtBaseBehavBlock() = default;

	virtual ~HdlStmtBaseBehavBlock() = default;

	SavedString to_hdl_source(TableNode* top) const;

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
		Expression* s_ident_expr);

	virtual ~HdlStmtBehavBlockAlwaysSeq() = default;

	virtual DriverType driver_type() const
	{
		return DriverType::BehavBlockAlwaysSeq;
	}

	//virtual EdgeSensType edge_sens_type() const
	//{
	//	return _edge_sens_type;
	//}


	GEN_EXPR_GETTER(ident_expr, 0)

protected:		// functions
	virtual SavedString _output_behav_block_str() const;
};


// Behavioral assignment operator.  Can become either a blocking or a
// non-blocking assignment depending on whether it was in an "initial",
// "always_comb", or "always_seq" block.
//
// This is *not* used for the statements inside the parentheses of an
// "HdlStmtForLoop"!  For that, you'll want "HdlStmtForLoopAssign".
//
// This is also *not* used for the insides of a non-task "HdlFunction".
class HdlStmtBehavAssign : public HdlStatement
{
public:		// functions
	HdlStmtBehavAssign(Expression* s_ident_expr, Expression* s_rhs);

	virtual ~HdlStmtBehavAssign() = default;

	virtual SavedString to_hdl_source(TableNode* top);

	GEN_EXPR_GETTER(ident_expr, 0)
	GEN_EXPR_GETTER(rhs, 1)
};

//// "if" statement.
//class HdlStmtBehavIf : public HdlStatement
//{
//public:		// functions
//	HdlStmtBehavIf(Expression* s_condition_expr);
//};
//
//// "else" statement.

//// "if-elseif-else chain" 



class HdlStatementTable : public ScopedUnnamedTable<HdlStatement>
{
public:		// functions
	HdlStatementTable() = default;
	virtual ~HdlStatementTable() = default;
};

#undef GEN_EXPR_GETTER

} // namespace frost_hdl


#endif		// src_hdl_statement_table_class_hpp
