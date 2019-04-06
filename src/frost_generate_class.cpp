#include "frost_generate_class.hpp"

namespace frost_hdl
{

FrostGenerate::FrostGenerate
	(const SrcCodePos& s_src_code_pos, SavedString s_ident)
	: _src_code_pos(s_src_code_pos), _ident(s_ident)
{
}

FrostGenerate::~FrostGenerate()
{
}

} // namespace frost_hdl
