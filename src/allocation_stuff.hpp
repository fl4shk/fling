#ifndef src__slash__allocation_stuff_hpp
#define src__slash__allocation_stuff_hpp

// src/allocation_stuff.hpp

#include "misc_includes.hpp"
#include "expr_num_class.hpp"
#include "expr_chunk_class.hpp"


#include <map>

namespace frost_hdl
{

BigNum* cstm_numdup(const BigNum& to_dup);
std::string* cstm_strdup(const std::string& to_dup);
ExprNum* alloc_expr_num(size_t s_size, BigNum* s_val);

} // namespace frost_hdl

#endif		// src__slash__allocation_stuff_hpp
