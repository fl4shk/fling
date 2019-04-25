#ifndef src_has_src_code_pos_base_classes_hpp
#define src_has_src_code_pos_base_classes_hpp

// src/has_src_code_pos_base_classes.hpp

#include "misc_includes.hpp"
#include "src_code_pos_class.hpp"
#include "general_allocator_class.hpp"

namespace frost_hdl
{

class HasSrcCodePosBase
{
protected:		// variables
	SrcCodePos _src_code_pos;

public:		// functions
	HasSrcCodePosBase();
	HasSrcCodePosBase(const SrcCodePos& s_src_code_pos);

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(HasSrcCodePosBase);

	virtual ~HasSrcCodePosBase();

	GEN_GETTER_BY_CON_REF(src_code_pos);
};

class HasSrcCodePosAndIdentBase : public HasSrcCodePosBase
{
protected:		// variables
	SavedString _ident = nullptr;

public:		// functions
	HasSrcCodePosAndIdentBase();
	HasSrcCodePosAndIdentBase(const SrcCodePos& s_src_code_pos,
		SavedString s_ident);

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(HasSrcCodePosAndIdentBase);

	virtual ~HasSrcCodePosAndIdentBase();

	GEN_GETTER_BY_VAL(ident);
};

} // namespace frost_hdl

#endif		// src_has_src_code_pos_base_classes_hpp
