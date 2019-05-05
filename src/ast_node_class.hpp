#ifndef src_ast_node_class_hpp
#define src_ast_node_class_hpp

// src/ast_node_class.hpp

#include "misc_includes.hpp"
//#include "table_types.hpp"

#include "has_src_code_chunk_base_classes.hpp"

//#include "symbol_class.hpp"
//#include "scoped_table_classes.hpp"
#include "expr_value_class.hpp"
#include "symbol_class.hpp"


namespace frost_hdl
{

class AstNode final : public HasSrcCodeChunkBase
{
public:		// types
	typedef std::unique_ptr<AstNode> Child;
	typedef CircLinkedList<Child> ChildrenList;

	// Node type
	enum class Type
	{
		Bad,

		//--------
		// `package`
		Package,

		// `interface`
		Interface,

		// `module`
		Module,

		// `generate`
		Generate,

		// `range`
		Range,
		//--------


		//--------
		// `function`
		Function,

		// `task`
		Task,
		//--------

		//--------
		ModStmtContAssign,

		ModStmtInitial,
		ModStmtAlwaysComb,
		ModStmtAlwaysSeq,
		//--------


		//--------
		BehavNonBlkAssign,
		BehavBlkAssign,

		BehavIf,
		BehavElseIf,
		BehavElse,

		BehavSwitch,
		BehavSwitchz,
		BehavCase,
		BehavDefault,

		BehavFor,
		BehavWhile,
		//--------

		//--------
		// Can be combined with another `BehavIdentAccess`, `Slice`,
		// `BehavCallTask`, etc.
		BehavIdentAccess,
		BehavCallTask,
		//--------


		//--------
		IdentName,
		LhsTypeName,
		BuiltinTypeLogic,
		//--------

		//--------
		ParameterVarList,
		ParameterVarInst,

		LocalparamVarList,
		LocalparamVarInst,

		PortVarList,
		PortVarInst,

		NonPortVarList,
		NonPortVarInst,
		//--------

		//--------
		Expression,
		//--------

		//--------
		ExprBinOpLogAnd,
		ExprBinOpLogOr,

		ExprBinOpCmpEq,
		ExprBinOpCmpNe,
		ExprBinOpCmpLt,
		ExprBinOpCmpGt,
		ExprBinOpCmpLe,
		ExprBinOpCmpGe,

		ExprBinOpPlus,
		ExprBinOpMinus,

		ExprBinOpMul,
		ExprBinOpDiv,
		ExprBinOpMod,

		ExprBinOpBitAnd,
		ExprBinOpBitOr,
		ExprBinOpBitXor,

		ExprBinOpBitLsl,
		ExprBinOpBitLsr,
		ExprBinOpBitAsr,
		//--------

		//--------
		ExprUnOpPlus,
		ExprUnOpMinus,
		ExprUnOpLogNot,
		ExprUnOpBitNot,

		ExprUnOpCastUnsgn,
		ExprUnOpCastSgn,
		ExprUnOpClog2,
		//--------

		//--------
		// Can be combined with another `ExprIdentAccess`, `Slice`,
		// `ExprCallFunc`, etc.
		ExprIdentAccess,

		ExprCallFunc,
		//--------

		//--------
		// [i]
		// [left:right]
		Slice,

		// [expr +: width]
		SlicePlus,

		// [expr -: width]
		SliceMinus,
		//--------
	};


protected:		// variables
	Type _type = Type::Bad;

	AstNode * _parent = nullptr,
		* _actual_scope = nullptr;

	ChildrenList _children;
	size_t _num_children = 0;

	ExprValue _expr_value;


public:		// functions
	//--------
	AstNode();

	AstNode(const SrcCodeChunk& s_src_code_chunk, Type s_type,
		AstNode* s_parent);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(AstNode);

	~AstNode();
	//--------

	//--------
	inline bool is_scope() const
	{
		return (_actual_scope == this);
	}
	//--------

	//--------
	void push_child_back(Child&& to_push);
	void push_child_front(Child&& to_push);

	void insert_child_after(ChildrenList::Node* where, Child&& to_insert);
	void insert_child_before(ChildrenList::Node* where, Child&& to_insert);

	void remove_child_after(ChildrenList::Node* where);
	void remove_child_before(ChildrenList::Node* where);
	void remove_child(ChildrenList::Node* where);

	inline auto begin()
	{
		return _children.begin();
	}
	inline auto end()
	{
		return _children.end();
	}
	inline auto cbegin() const
	{
		return _children.cbegin();
	}
	inline auto cend() const
	{
		return _children.cend();
	}
	//--------

	//--------
	inline const auto& text() const
	{
		return src_code_chunk().text();
	}

	GEN_GETTER_BY_VAL(type)
	GEN_GETTER_BY_VAL(parent)
	GEN_GETTER_BY_VAL(actual_scope)
	GEN_GETTER_BY_CON_REF(children)
	GEN_GETTER_BY_VAL(num_children)
	//--------

private:		// functions
	inline void _finish_child_insert(ChildrenList::Node* inserted)
	{
		inserted->data->_parent = this;
		inserted->data->_actual_scope = _actual_scope;
	}
};

} // namespace frost_hdl

#endif		// src_ast_node_class_hpp
