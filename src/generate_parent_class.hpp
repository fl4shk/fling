#ifndef src_generate_parent_class_hpp
#define src_generate_parent_class_hpp

// src/generate_parent_class.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

typedef std::variant<FrostModule*, FrostGenerate*> GenerateParent;

} // namespace frost_hdl

#endif		// src_generate_parent_class_hpp
