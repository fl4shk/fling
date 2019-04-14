#ifndef src_scope_parent_classes_hpp
#define src_scope_parent_classes_hpp

// src/scope_parent_classes.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

typedef std::variant<FrostModule*, FrostGenerateBlockInModule*>
	ModuleScopeParent;
//typedef std::variant<FrostInterface*, FrostGenerateBlockInInterface*>
//	InterfaceScopeParent;
} // namespace frost_hdl

#endif		// src_scope_parent_classes_hpp
