#ifndef src_allocation_stuff_hpp
#define src_allocation_stuff_hpp

// src/allocation_stuff.hpp

#include "misc_includes.hpp"
#include "expr_num_class.hpp"
#include "expr_chunk_class.hpp"
//#include "expr_symbol_ref_class.hpp"


#include <map>

namespace frost_hdl
{

BigNum* cstm_numdup(const BigNum& to_dup);
std::string* cstm_strdup(const std::string& to_dup);
ExprNum* cstm_expr_numdup(const ExprNum& to_dup);
ExprSymbolRef* cstm_expr_symbol_refdup(const ExprSymbolRef& to_dup);

} // namespace frost_hdl

#endif		// src_allocation_stuff_hpp
