#ifndef src_parameter_vars_type_hpp
#define src_parameter_vars_type_hpp

// src/parameter_vars_type.hpp

#include "misc_includes.hpp"
#include "ident_table_classes.hpp"

namespace frost_hdl
{

class Symbol;

typedef OrderedIdentToPointerTable<Symbol> ParameterVars;

} // namespace frost_hdl


#endif		// src_parameter_vars_type_hpp
