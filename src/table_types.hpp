#ifndef src_table_types_hpp
#define src_table_types_hpp

// src/table_types.hpp

#include "misc_includes.hpp"
#include "scoped_table_classes.hpp"
//#include "misc_types.hpp"

namespace frost_hdl
{

class Symbol;
class FrostLhsType;


typedef IdentToPointerTable<Symbol> SymbolTable;
typedef IdentToPointerTable<FrostLhsType> FrostLhsTypeTable;
//typedef ScopedUnnamedTable<FrostStatement> FrostStatementTable;

//typedef PointerVector<FrostGenerateBlockInModule>
//	FrostGenerateBlockInModuleTable;

} // namespace frost_hdl

#endif		// src_table_types_hpp
