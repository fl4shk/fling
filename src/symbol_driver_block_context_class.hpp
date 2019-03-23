#ifndef src_symbol_driver_block_context_class_hpp
#define src_symbol_driver_block_context_class_hpp

// src/symbol_driver_block_context_class.hpp

#include "misc_includes.hpp"
#include "frost_statement_table_class.hpp"

namespace frost_hdl
{

// This class covers keeping track of the drivers of a particular "Symbol",
// but not including the more complex case where the "Symbol" is a
// composite type.
//
// This is intended to be used *after* producing "Symbol"s that have
// non-composite types from the original source code.
class SymbolDriverBlockContext
{
private:		// variables
	Symbol* _symbol = nullptr;

};

} // namespace frost_hdl

#endif		// src_symbol_driver_block_context_class_hpp
