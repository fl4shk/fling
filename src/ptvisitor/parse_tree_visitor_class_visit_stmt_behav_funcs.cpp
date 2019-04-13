#include "../parse_tree_visitor_class.hpp"
#include "../general_allocator_class.hpp"
#include "../expression_builder_class.hpp"
#include <sstream>

#include "dot_cpp_defines.hpp"


namespace frost_hdl
{

auto ParseTreeVisitor::visitStmtBehavHeaderForLoop
	(Parser::StmtBehavHeaderForLoopContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto ParseTreeVisitor::visitStmtBehavHeaderIf
	(Parser::StmtBehavHeaderIfContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

} // namespace frost_hdl
