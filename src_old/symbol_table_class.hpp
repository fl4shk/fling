#ifndef src_symbol_table_class_hpp
#define src_symbol_table_class_hpp

// src/symbol_table_class.hpp

#include "misc_includes.hpp"

#include "scoped_table_base_class.hpp"
#include "symbol_class.hpp"

namespace frost_hdl
{

class SymbolTable : public ScopedTableBase<Symbol>
{
public:		// functions
	SymbolTable();
	virtual ~SymbolTable();
};

} // namespace frost_hdl


#endif		// src_symbol_table_class_hpp
