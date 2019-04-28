#ifndef src_frost_program_node_class_hpp
#define src_frost_program_node_class_hpp

// src/frost_program_node_class.hpp

#include "misc_includes.hpp"

#include "symbol_class.hpp"
#include "scoped_table_classes.hpp"


namespace frost_hdl
{

class FrostProgramNode : public HasSrcCodeChunkAndIdentBase
{
protected:		// variables
	//FrostProgramNode* _parent = nullptr;

	//std::vector<FrostProgramNode> _children;
	//std::list<FrostProgramNode*> _children;
	FrostProgramNode* _actual_scope_fpn = nullptr;

public:		// functions
	FrostProgramNode();

	FrostProgramNode(const SrcCodeChunk& s_src_code_chunk,
		SavedString s_ident);
	FrostProgramNode(const SrcCodeChunk& s_src_code_chunk,
		SavedString s_ident, FrostProgramNode* s_actual_scope_fpn);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostProgramNode);

	virtual ~FrostProgramNode();

	virtual bool is_expr() const;
	virtual bool is_constant_expr() const;

	GEN_GETTER_BY_VAL(actual_scope_fpn)
};

} // namespace frost_hdl

#endif		// src_frost_program_node_class_hpp
