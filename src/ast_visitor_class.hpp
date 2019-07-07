#ifndef src_ast_visitor_class_hpp
#define src_ast_visitor_class_hpp

// src/ast_visitor_class.hpp

#include "misc_includes.hpp"

#include "ast_node_classes.hpp"

namespace frost_hdl
{

namespace ast
{

#include "list_of_ast_node_classes_define.hpp"

// Base class for a visitor of the abstract syntax tree
class Visitor
{
public:		// functions
	Visitor();
	virtual ~Visitor();

	virtual void visitBase(NodeBase* node) = 0;
	virtual void visitList(NodeList* node) = 0;
	#include "ast_visitor_visit_funcs.hpp"

};

#undef LIST_OF_AST_NODE_CLASSES

} // namespace ast

} // namespace frost_hdl

#endif		// src_ast_visitor_class_hpp
