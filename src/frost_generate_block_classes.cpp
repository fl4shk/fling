#include "frost_generate_block_classes.hpp"

namespace frost_hdl
{
FrostGenerateBlockInModule::FrostGenerateBlockInModule
	(const SrcCodePos& s_src_code_pos, SavedString s_ident)
	: HasSrcCodePosAndIdentBase(s_src_code_pos, s_ident)
{
	_module_scope = ModuleScope(this);
}

FrostGenerateBlockInModule::~FrostGenerateBlockInModule()
{
}

//FrostGenerateBlockInInterface::FrostGenerateBlockInInterface
//	(const SrcCodePos& s_src_code_pos, SavedString s_ident)
//	: HasSrcCodePosAndIdentBase(s_src_code_pos, s_ident)
//{
//	_interface_scope = InterfaceScope(this);
//}
//
//FrostGenerateBlockInInterface::~FrostGenerateBlockInInterface()
//{
//}
} // namespace frost_hdl
