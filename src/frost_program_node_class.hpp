#ifndef src_frost_program_node_class_hpp
#define src_frost_program_node_class_hpp

// src/frost_program_node_class.hpp

#include "misc_includes.hpp"

#include "symbol_class.hpp"
#include "scoped_table_classes.hpp"


namespace frost_hdl
{

class FrostProgramNode : public HasSrcCodePosBase
{
protected:		// variables
	//FrostProgramNode* _parent = nullptr;

	//std::vector<FrostProgramNode> _children;
	//std::list<FrostProgramNode*> _children;

public:		// functions
	FrostProgramNode();

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(FrostProgramNode);

	virtual ~FrostProgramNode();

	bool is_expr() const;
	bool is_constant_expr() const;
};

} // namespace frost_hdl

#endif		// src_frost_program_node_class_hpp
