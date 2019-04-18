#ifndef src_scope_parent_classes_hpp
#define src_scope_parent_classes_hpp

// src/scope_parent_classes.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

//typedef std::variant<FrostModule*, FrostGenerateBlockInModule*>
//	ModuleScopeParent;
//typedef std::variant<FrostInterface*, FrostGenerateBlockInInterface*>
//	InterfaceScopeParent;

class ModuleScopeParent
{
public:		// variables
	bool holds_generate_block_in_module = false;
	FrostModule* frost_module = nullptr;
	FrostGenerateBlockInModule* frost_generate_block_in_module = nullptr;

public:		// functions
	inline ModuleScopeParent& operator = (FrostModule* n_parent)
	{
		holds_generate_block_in_module = false;
		frost_module = n_parent;
		frost_generate_block_in_module = nullptr; 
		return *this;
	}
	inline ModuleScopeParent& operator =
		(FrostGenerateBlockInModule* n_parent)
	{
		holds_generate_block_in_module = true;
		frost_module = nullptr;
		frost_generate_block_in_module = n_parent; 
		return *this;
	}
};
} // namespace frost_hdl

#endif		// src_scope_parent_classes_hpp
