#include "ast_node_classes.hpp"
#include "ast_visitor_class.hpp"

#include "list_of_ast_node_classes_define.hpp"

namespace frost_hdl
{

namespace ast
{

#define GEN_ACCEPT(AstNodeType) \
	void AstNodeType::accept(Visitor& visitor) \
	{ \
		visitor.visit##AstNodeType(*this); \
	}

LIST_OF_AST_NODE_CLASSES(GEN_ACCEPT)

#undef GEN_ACCEPT

} // namespace ast

} // namespace frost_hdl
