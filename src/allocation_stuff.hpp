#ifndef src_allocation_stuff_hpp
#define src_allocation_stuff_hpp

// src/allocation_stuff.hpp

#include "misc_includes.hpp"


#include <map>

namespace frost_hdl
{
class Expression;

std::string* cstm_str_dup(const std::string& to_dup);
Expression* save_expr(Expression&& to_save);

} // namespace frost_hdl

#endif		// src_allocation_stuff_hpp
