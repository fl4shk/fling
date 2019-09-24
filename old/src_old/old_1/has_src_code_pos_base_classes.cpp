#include "has_src_code_pos_base_classes.hpp"

namespace frost_hdl
{

HasSrcCodePosBase::HasSrcCodePosBase()
{
}
HasSrcCodePosBase::HasSrcCodePosBase(const SrcCodePos& s_src_code_pos)
	: _src_code_pos(s_src_code_pos)
{
}
HasSrcCodePosBase::~HasSrcCodePosBase()
{
}


HasSrcCodePosAndIdentBase::HasSrcCodePosAndIdentBase()
{
}
HasSrcCodePosAndIdentBase::HasSrcCodePosAndIdentBase
	(const SrcCodePos& s_src_code_pos, SavedString s_ident)
	: HasSrcCodePosBase(s_src_code_pos), _ident(s_ident)
{
}
HasSrcCodePosAndIdentBase::~HasSrcCodePosAndIdentBase()
{
}

} // namespace frost_hdl
