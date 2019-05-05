#ifndef src_ast_node_type_list_stuff_hpp
#define src_ast_node_type_list_stuff_hpp

// src/ast_node_type_list_stuff.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

#define LIST_OF_AST_NODE_TYPES(X) \
	/* -------- */ \
	X(Bad) \
	/* -------- */ \
	\
	/* -------- */ \
	X(Program) \
	/* -------- */ \
	\
	/* -------- */ \
	/* `package` */ \
	X(Package) \
	\
	/* `interface` */ \
	X(Interface) \
	\
	/* `module` */ \
	X(Module) \
	\
	/* `generate` */ \
	X(Generate) \
	\
	/* `range` */ \
	X(Range) \
	/* -------- */ \
	\
	\
	/* -------- */ \
	/* `struct` */ \
	X(Struct) \
	\
	/* `class` */ \
	X(Class) \
	\
	/* `function` */ \
	X(Function) \
	\
	/* `task` */ \
	X(Task) \
	/* -------- */ \
	\
	\
	/* -------- */ \
	X(IdentName) \
	X(LhsTypeName) \
	X(Logic) \
	X(Unsigned) \
	X(Signed) \
	/* -------- */ \
	\
	\
	/* -------- */ \
	X(ParameterVarList) \
	X(ParameterVarInst) \
	\
	X(LocalparamVarList) \
	X(LocalparamVarInst) \
	\
	X(PortVarList) \
	X(PortVarInst) \
	\
	X(NonPortVarList) \
	X(NonPortVarInst) \
	/* -------- */ \
	\
	/* -------- */ \
	X(ModStmtContAssign) \
	\
	X(ModStmtInitial) \
	X(ModStmtAlwaysComb) \
	X(ModStmtAlwaysSeq) \
	\
	X(ModStmtInstModule) \
	/* -------- */ \
	\
	/* -------- */ \
	X(InstModuleConnList) \
	X(InstModuleConnInst) \
	/* -------- */ \
	\
	\
	/* -------- */ \
	X(BehavNonBlkAssign) \
	X(BehavBlkAssign) \
	\
	X(BehavIf) \
	X(BehavElseIf) \
	X(BehavElse) \
	\
	X(BehavSwitch) \
	X(BehavSwitchz) \
	X(BehavCase) \
	X(BehavDefault) \
	\
	X(BehavFor) \
	X(BehavWhile) \
	/* -------- */ \
	\
	/* -------- */ \
	/* Can be combined with another `BehavIdentAccess`, `Slice`, */ \
	/* `BehavCallTask`, etc. */ \
	X(BehavIdentAccess) \
	X(BehavCallTask) \
	/* -------- */ \
	\
	\
	/* -------- */ \
	/* [i] */ \
	/* [left:right] */ \
	X(Slice) \
	\
	/* [expr +: width] */ \
	X(SlicePlus) \
	\
	/* [expr -: width] */ \
	X(SliceMinus) \
	/* -------- */ \
	\
	\
	/* -------- */ \
	X(Expression) \
	/* -------- */ \
	\
	/* -------- */ \
	X(ExprBinOpLogAnd) \
	X(ExprBinOpLogOr) \
	\
	X(ExprBinOpCmpEq) \
	X(ExprBinOpCmpNe) \
	X(ExprBinOpCmpLt) \
	X(ExprBinOpCmpGt) \
	X(ExprBinOpCmpLe) \
	X(ExprBinOpCmpGe) \
	\
	X(ExprBinOpPlus) \
	X(ExprBinOpMinus) \
	\
	X(ExprBinOpMul) \
	X(ExprBinOpDiv) \
	X(ExprBinOpMod) \
	\
	X(ExprBinOpBitAnd) \
	X(ExprBinOpBitOr) \
	X(ExprBinOpBitXor) \
	\
	X(ExprBinOpBitLsl) \
	X(ExprBinOpBitLsr) \
	X(ExprBinOpBitAsr) \
	/* -------- */ \
	\
	/* -------- */ \
	X(ExprUnOpPlus) \
	X(ExprUnOpMinus) \
	X(ExprUnOpLogNot) \
	X(ExprUnOpBitNot) \
	/* -------- */ \
	\
	/* -------- */ \
	X(ExprUnOpCastUnsgn) \
	X(ExprUnOpCastSgn) \
	X(ExprUnOpClog2) \
	/* -------- */ \
	\
	/* -------- */ \
	X(ExprUnOpPosedge) \
	X(ExprUnOpNegedge) \
	/* -------- */ \
	\
	/* -------- */ \
	/* Can be combined with another `ExprIdentAccess`, `Slice`, */ \
	/* `ExprCallFunc`, etc. */ \
	X(ExprIdentAccess) \
	\
	X(ExprCallFunc) \
	/* -------- */ \

enum class AstNodeType
{
	#define X(val) \
		val,

	LIST_OF_AST_NODE_TYPES(X)

	#undef X
};


} // namespace frost_hdl


#endif		// src_ast_node_type_list_stuff_hpp
