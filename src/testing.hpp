#ifndef src_testing_hpp
#define src_testing_hpp

// src/testing.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

void test_expr_num_conversion(std::ostream& os, size_t test_data_width);
void test_expr_num_size_change(std::ostream& os);
void test_cpp_expressions(std::ostream& os);
void test_implemented_expressions(std::ostream& os);

} // namespace frost_hdl


#endif		// src_testing_hpp
