#ifndef src_ast_visitor_class_hpp
#define src_ast_visitor_class_hpp

// src/ast_visitor_class.hpp

#include "misc_includes.hpp"

#include "ast_node_classes.hpp"

namespace frost_hdl
{

namespace ast
{

// Base class for a visitor of the abstract syntax tree
class Visitor
{
public:		// functions
	Visitor();
	virtual ~Visitor();

	//virtual void visit_plus(NodePlus* node) = 0;
};

} // namespace ast

} // namespace frost_hdl

#endif		// src_ast_visitor_class_hpp
