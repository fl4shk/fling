#ifndef src_allocation_stuff_hpp
#define src_allocation_stuff_hpp

// src/allocation_stuff.hpp

#include "misc_includes.hpp"
//#include "expression_classes.hpp"


#include <map>

namespace frost_hdl
{

BigNum* cstm_num_dup(const BigNum& to_dup);
std::string* cstm_str_dup(const std::string& to_dup);

class Expression;

Expression* save_expr(Expression&& to_move);

} // namespace frost_hdl

#endif		// src_allocation_stuff_hpp
