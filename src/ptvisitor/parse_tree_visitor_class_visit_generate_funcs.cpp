#include "../parse_tree_visitor_class.hpp"
#include "../general_allocator_class.hpp"
#include "../expression_builder_class.hpp"
#include <sstream>

#include "dot_cpp_defines.hpp"


namespace frost_hdl
{

auto ParseTreeVisitor::visitGenerateBlockInModule
	(Parser::GenerateBlockInModuleContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto ParseTreeVisitor::visitGenerateBlockAnyHeader
	(Parser::GenerateBlockAnyHeaderContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto ParseTreeVisitor::visitGenerateBlockHeaderForLoop
	(Parser::GenerateBlockHeaderForLoopContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}
auto ParseTreeVisitor::visitGenerateBlockHeaderIf
	(Parser::GenerateBlockHeaderIfContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

auto ParseTreeVisitor::visitPseudoFuncCallRange
	(Parser::PseudoFuncCallRangeContext *ctx)
	-> VisitorRetType
{
	return nullptr;
}

} // namespace frost_hdl
