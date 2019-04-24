#include "../ptvisitor_class.hpp"
#include "../general_allocator_class.hpp"
#include "../expression_builder_class.hpp"
#include <sstream>

#include "dot_cpp_defines.hpp"


namespace frost_hdl
{

// Basically just "module", "interface", and "package" declarations.
// There are no other things permitted at global scope.
auto PTVisitor::visitProgram
	(Parser::ProgramContext *ctx)
	-> VisitorRetType
{
	if (_in_package_pass())
	{
		ANY_JUST_ACCEPT_LOOPED(iter, ctx->declPackage());
	}

	//else if (_in_interface_pass())
	//{
	//	ANY_JUST_ACCEPT_LOOPED(iter, ctx->declInterface());
	//}

	else if (_in_module_pass())
	{
		ANY_JUST_ACCEPT_LOOPED(iter, ctx->declModule());
	}

	// else if (pass() == Pass::Done)
	else
	{
		_err(ctx, "PTVisitor::visitProgram():  Eek!");
	}

	return nullptr;
}

} // namespace frost_hdl
