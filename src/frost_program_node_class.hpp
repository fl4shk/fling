#ifndef src_frost_program_node_class_hpp
#define src_frost_program_node_class_hpp

// src/frost_program_node_class.hpp

#include "misc_includes.hpp"
//#include "table_types.hpp"

#include "has_src_code_chunk_base_classes.hpp"

//#include "symbol_class.hpp"
//#include "scoped_table_classes.hpp"


namespace frost_hdl
{

// Base class for a node in the pseudo-AST internal representation.
class FrostProgramNode : public HasSrcCodeChunkAndIdentBase
{
public:		// types
	typedef CircLinkedList<FrostProgramNode> ChildrenList;
	//typedef std::map<Ident, FrostProgramNode*> SymbolTable;

	typedef IdentToPointerTable<FrostProgramNode> SymbolTable;

protected:		// variables
	FrostProgramNode * _parent = nullptr,
		* _actual_scope_fpn = nullptr;

	std::unique_ptr<ChildrenList> _children;

	SymbolTable _symbol_table;

	enum class ScopeType
	{
		None,
		Package,
		Interface,
		Module,
		Function,
		Task,
	};

	enum class SymbolType
	{
		None,
		Var,
		Function,
		LhsType,
		//TypedefOfLhsType,
	};

	enum class PortType
	{
		None,
		Input,
		Output,

		// This might only ever be used for `task` arguments.
		// I am unsure about permitting it for `module` ports.
		Inout,
	};

	//std::vector<FrostProgramNode> _children;
	//std::list<FrostProgramNode*> _children;

public:		// functions
	//--------
	FrostProgramNode();

	FrostProgramNode(const SrcCodeChunk& s_src_code_chunk,
		const Ident& s_ident);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostProgramNode);

	virtual ~FrostProgramNode();
	//--------



	//--------
	virtual bool is_expr() const;
	virtual bool is_constant_expr() const;

	virtual ScopeType scope_type() const;
	virtual SymbolType symbol_type() const;
	virtual PortType port_type() const;

	//virtual void insert_child(FrostProgramNode* to_insert_after,
	//	FrostProgramNode&& to_insert);
	//--------



	//--------
	inline ChildrenList& children()
	{
		return *_children;
	}
	inline const ChildrenList& children() const
	{
		return *_children;
	}

	GEN_GETTER_AND_SETTER_BY_VAL(parent)
	GEN_GETTER_AND_SETTER_BY_VAL(actual_scope_fpn)
	//GEN_GETTERS_BY_CON_REF_AND_REF(children)
	//GEN_GETTER_BY_CON_REF(children)
	//--------
};

} // namespace frost_hdl

#endif		// src_frost_program_node_class_hpp
