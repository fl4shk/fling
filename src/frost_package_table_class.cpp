#include "frost_package_table_class.hpp"

namespace frost_hdl
{

FrostPackage::FrostPackage(const SrcCodePos& s_src_code_pos,
	SavedString s_ident)
{
	_src_code_pos = s_src_code_pos;
	_ident = s_ident;
}

FrostPackage::~FrostPackage()
{
}

} // namespace frost_hdl
