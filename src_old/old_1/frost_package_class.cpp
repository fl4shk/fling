#include "frost_package_class.hpp"

namespace frost_hdl
{

FrostPackage::FrostPackage(const SrcCodePos& s_src_code_pos,
	SavedString s_ident)
	: HasSrcCodePosAndIdentBase(s_src_code_pos, s_ident)
{
}

FrostPackage::~FrostPackage()
{
}

} // namespace frost_hdl
