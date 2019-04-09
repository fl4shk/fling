#ifndef src_generate_parent_classes_hpp
#define src_generate_parent_classes_hpp

// src/generate_parent_classes.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

typedef std::variant<FrostModule*, FrostGenerateBlockInModule*>
	GenerateBlockInModuleParent;
//typedef std::variant<FrostInterface*, FrostGenerateBlockInInterface*>
//	GenerateBlockInInterfaceParent;
} // namespace frost_hdl

#endif		// src_generate_parent_classes_hpp
