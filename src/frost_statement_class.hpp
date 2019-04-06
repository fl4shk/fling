#ifndef src_frost_statement_class_hpp
#define src_frost_statement_class_hpp

// src/frost_statement_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "src_code_pos_class.hpp"
#include "scoped_table_classes.hpp"
//#include "symbol_class.hpp"
#include "frost_lhs_type_class.hpp"
#include "expression_classes.hpp"
#include "misc_utility_funcs.hpp"

namespace frost_hdl
{

#define GEN_EXPR_GETTER(name, index) \
	inline Expression* name() const \
	{ \
		return _exprs.at(index); \
	}

// Base class for a statement (primarily for the insides of an
// "FrostModule", but also intended for use inside of an "FrostFunction"),
// to be processed into a direct equivalent of the destination HDL
// (probably Verilog-2001).
class FrostStatement : public HasSrcCodePosBase
{
public:		// types
	//typedef typename ScopedUnnamedTable<FrostStatement>::Node TableNode;


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
		//None,
		Posedge,
		Negedge
	};

	typedef std::vector<Expression*> ExprsList;

protected:		// variables
	// Component "Expression"s.
	ExprsList _exprs;

public:		// functions
	FrostStatement(const SrcCodePos& s_src_code_pos);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostStatement);

	virtual ~FrostStatement() = default;

	virtual DriverType driver_type() const
	{
		return DriverType::None;
	}


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
class FrostStmtContAssign : public FrostStatement
{
public:		// functions
	FrostStmtContAssign(const SrcCodePos& s_src_code_pos,
		Expression* s_lhs_expr, Expression* s_rhs_expr);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostStmtContAssign);

	virtual ~FrostStmtContAssign() = default;

	virtual DriverType driver_type() const
	{
		return DriverType::ContAssign;
	}


	GEN_EXPR_GETTER(lhs_expr, 0)
	GEN_EXPR_GETTER(rhs_expr, 1)
};

//// Base class for "initial", "always_comb", and "always_seq".
//class FrostStmtBaseBehavBlock : public FrostStatement
//{
//public:		// functions
//	FrostStmtBaseBehavBlock() = default;
//
//	virtual ~FrostStmtBaseBehavBlock() = default;
//
//	SavedString to_hdl_source(TableNode* top) const;
//};

// "initial"
class FrostStmtBehavBlockInitial : public FrostStatement
{
public:		// functions
	inline FrostStmtBehavBlockInitial(const SrcCodePos& s_src_code_pos)
		: FrostStatement(s_src_code_pos)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostStmtBehavBlockInitial);

	virtual ~FrostStmtBehavBlockInitial() = default;

	virtual DriverType driver_type() const
	{
		return DriverType::BehavBlockInitial;
	}
};

// "always_comb"
class FrostStmtBehavBlockAlwaysComb : public FrostStatement
{
public:		// functions
	inline FrostStmtBehavBlockAlwaysComb(const SrcCodePos& s_src_code_pos)
		: FrostStatement(s_src_code_pos)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostStmtBehavBlockAlwaysComb);

	virtual ~FrostStmtBehavBlockAlwaysComb() = default;

	virtual DriverType driver_type() const
	{
		return DriverType::BehavBlockAlwaysComb;
	}
};

// "always_seq"
class FrostStmtBehavBlockAlwaysSeq : public FrostStatement
{
private:		// variables
	EdgeSensType _edge_sens_type = EdgeSensType::Posedge;

public:		// functions
	FrostStmtBehavBlockAlwaysSeq(const SrcCodePos& s_src_code_pos,
		EdgeSensType s_edge_sens_type, Expression* s_ident_expr);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostStmtBehavBlockAlwaysSeq);

	virtual ~FrostStmtBehavBlockAlwaysSeq() = default;

	virtual DriverType driver_type() const
	{
		return DriverType::BehavBlockAlwaysSeq;
	}


	GEN_EXPR_GETTER(ident_expr, 0)
};


// Behavioral assignment operator.  Can become either a blocking or a
// non-blocking assignment depending on whether it was in an "initial",
// "always_comb", or "always_seq" block.
//
// This is *not* used for the statements inside the parentheses of an
// "FrostStmtForLoop"!  For that, you'll want
// "FrostStmtForLoopAssign".
//
// This is also *not* used for the insides of a non-task
// "FrostFunction".
class FrostStmtBehavAssign : public FrostStatement
{
public:		// functions
	FrostStmtBehavAssign(const SrcCodePos& s_src_code_pos,
		Expression* s_lhs_expr, Expression* s_rhs_expr);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostStmtBehavAssign);

	virtual ~FrostStmtBehavAssign() = default;

	//virtual DstHdlStatement* to_dst_hdl_statement() const;

	GEN_EXPR_GETTER(lhs_expr, 0)
	GEN_EXPR_GETTER(rhs_expr, 1)
};

// "if" statement by itself.
class FrostStmtBehavIf : public FrostStatement
{
public:		// functions
	FrostStmtBehavIf(const SrcCodePos& s_src_code_pos,
		Expression* s_condition_expr);
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostStmtBehavIf);
};

// "else" statement.

// "if-elseif-else chain" 



#undef GEN_EXPR_GETTER

} // namespace frost_hdl


#endif		// src_frost_statement_class_hpp
