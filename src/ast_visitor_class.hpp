#ifndef src_ast_visitor_class_hpp
#define src_ast_visitor_class_hpp

// src/ast_visitor_class.hpp

#include "misc_includes.hpp"

#include "ast_node_classes.hpp"

namespace frost_hdl
{

// Base class for a visitor of the abstract syntax tree
class AstVisitor
{
public:		// functions
	AstVisitor();
	virtual ~AstVisitor();

	virtual void visit_plus(AstNodePlus* node) = 0;
};

} // namespace frost_hdl

#endif		// src_ast_visitor_class_hpp
