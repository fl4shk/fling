#ifndef src_frost_module_instance_class_hpp
#define src_frost_module_instance_class_hpp

// src/frost_module_instance_class.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
#include "misc_types.hpp"

namespace frost_hdl
{

class FrostModuleInstance
{
private:		// variables
	SrcCodePos _src_code_pos;
	SavedString _ident = nullptr;

	// What is the mapping from variables to ports going to look like?

public:		// functions
	FrostModuleInstance(const SrcCodePos& s_src_code_pos,
		SavedString s_ident);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostModuleInstance);

	virtual ~FrostModuleInstance();

	GEN_GETTER_BY_CON_REF(src_code_pos)
	GEN_GETTER_BY_VAL(ident)
};

} // namespace frost_hdl


#endif		// src_frost_module_instance_class_hpp
