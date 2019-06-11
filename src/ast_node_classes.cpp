#include "ast_node_classes.hpp"
#include "ast_visitor_class.hpp"


namespace frost_hdl
{

AstNodeBase::AstNodeBase(const SrcCodeChunk& s_src_code_chunk)
	: _src_code_chunk(s_src_code_chunk)
{
}


void AstNodeBase::accept(AstVisitor& visitor)
{
}


AstNodeExprBase::AstNodeExprBase(const SrcCodeChunk& s_src_code_chunk)
	: AstNodeBase(s_src_code_chunk)
{
}

void AstNodeExprBase::eval()
{
}


AstNodeBinopBase::AstNodeBinopBase(const SrcCodeChunk& s_src_code_chunk,
	unique_ptr<AstNodeBase>&& s_left, unique_ptr<AstNodeBase>&& s_right)
	: AstNodeExprBase(s_src_code_chunk)
{
	append_child(std::move(s_left));
	append_child(std::move(s_right));
}


} // namespace frost_hdl
