#ifndef src_frost_generate_block_classes_hpp
#define src_frost_generate_block_classes_hpp

// src/frost_generate_block_classes.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
//#include "table_types.hpp"

#include "has_src_code_pos_base_classes.hpp"
#include "generate_block_header_classes.hpp"

#include "module_scope_class.hpp"
//#include "interface_scope_class.hpp"


namespace frost_hdl
{

class FrostGenerateBlockInModule : public HasSrcCodePosAndIdentBase
{
private:		// variables
	ModuleScope _module_scope;

	AnyGenerateBlockHeader _header;

public:		// functions
	FrostGenerateBlockInModule(const SrcCodePos& s_src_code_pos,
		SavedString s_ident);

	//template<typename ParentType, typename HeaderType>
	//inline FrostGenerateBlockInModule(const SrcCodePos& s_src_code_pos,
	//	SavedString s_ident, ParentType* s_parent,
	//	const HeaderType& s_header)
	//	: FrostGenerateBlockInModule(s_src_code_pos, s_ident)
	//{
	//	_parent = s_parent;
	//	_header = s_header;
	//}
	//template<typename HeaderType>
	//inline FrostGenerateBlockInModule(const SrcCodePos& s_src_code_pos,
	//	SavedString s_ident, const HeaderType& s_header)
	//	: FrostGenerateBlockInModule(s_src_code_pos, s_ident)
	//{
	//	_header = s_header;
	//}

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostGenerateBlockInModule);

	virtual ~FrostGenerateBlockInModule();

	inline auto parent() const
	{
		return _module_scope.parent();
	}

	template<typename HeaderType>
	inline void set_header(const HeaderType& n_header)
	{
		_header = n_header;
	}

	GEN_GETTERS_BY_CON_REF_AND_REF(module_scope)
	//GEN_GETTER_BY_CON_REF(parent)
	GEN_GETTER_BY_CON_REF(header)
};

//class FrostGenerateBlockInInterface : public HasSrcCodePosAndIdentBase
//{
//private:		// variables
//	InterfaceScope _interface_scope;
//
//	AnyGenerateBlockHeader _header;
//
//public:		// functions
//	FrostGenerateBlockInInterface(const SrcCodePos& s_src_code_pos,
//		SavedString s_ident);
//
//	//template<typename ParentType, typename HeaderType>
//	//inline FrostGenerateBlockInInterface(const SrcCodePos& s_src_code_pos,
//	//	SavedString s_ident, ParentType* s_parent,
//	//	const HeaderType& s_header)
//	//	: FrostGenerateBlockInInterface(s_src_code_pos, s_ident)
//	//{
//	//	_parent = s_parent;
//	//	_header = s_header;
//	//}
//	//template<typename HeaderType>
//	//inline FrostGenerateBlockInInterface(const SrcCodePos& s_src_code_pos,
//	//	SavedString s_ident, const HeaderType& s_header)
//	//	: FrostGenerateBlockInInterface(s_src_code_pos, s_ident)
//	//{
//	//	_header = s_header;
//	//}
//
//	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostGenerateBlockInInterface);
//
//	virtual ~FrostGenerateBlockInInterface();
//
//	inline auto parent() const
//	{
//		return _interface_scope.parent();
//	}
//
//	template<typename HeaderType>
//	inline void set_header(const HeaderType& n_header)
//	{
//		_header = n_header;
//	}
//
//	GEN_GETTERS_BY_CON_REF_AND_REF(interface_scope)
//	//GEN_GETTER_BY_CON_REF(parent)
//	GEN_GETTER_BY_CON_REF(header)
//};

} // namespace frost_hdl


#endif		// src_frost_generate_block_classes_hpp
