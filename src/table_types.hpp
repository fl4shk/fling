#ifndef src_table_types_hpp
#define src_table_types_hpp

// src/table_types.hpp

#include "misc_includes.hpp"
//#include "general_allocator_class.hpp"

//#include "scoped_table_classes.hpp"
//#include "misc_types.hpp"

namespace frost_hdl
{

//class Symbol;
//class FrostLhsType;
class FrostProgramNode;


//typedef IdentToPointerTable<Symbol> SymbolTable;
//typedef IdentToPointerTable<FrostLhsType> FrostLhsTypeTable;
//typedef ScopedUnnamedTable<FrostStatement> FrostStatementTable;

//typedef PointerVector<FrostGenerateBlockInModule>
//	FrostGenerateBlockInModuleTable;


typedef std::map<std::string, FrostProgramNode*> SymbolTable;

} // namespace frost_hdl

#endif		// src_table_types_hpp
