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
class FrostFullType;
class FrostFunction;
class FrostPackage;
class FrostInterface;
class FrostModule;
class FrostInstModule;
class FrostStatement;
//class FrostGenerateBlockBase;
class FrostGenerateBlockInModule;
class FrostGenerateBlockInInterface;

class Expression;

class ModuleScope;
class InterfaceScope;

template<typename MostOuterScopeType, typename ContainedScopeType>
class FrostGenerateBlockBase;

//typedef OrderedIdentToPointerTable<Symbol> SymbolTable;
//typedef IdentToPointerTable<Symbol> SymbolTable;
typedef IdentToPointerTable<Symbol> SymbolTable;
typedef IdentToPointerTable<FrostLhsType> FrostLhsTypeTable;
typedef IdentToPointerTable<FrostFullType> FrostFullTypeTable;
typedef IdentToPointerTable<FrostFunction> FrostFunctionTable;
typedef IdentToPointerTable<FrostPackage> FrostPackageTable;
typedef IdentToPointerTable<FrostInterface> FrostInterfaceTable;
typedef IdentToPointerTable<FrostModule> FrostModuleTable;
typedef IdentToPointerTable<FrostInstModule> FrostInstModuleTable;
typedef ScopedUnnamedTable<FrostStatement> FrostStatementTable;
//typedef PointerVector<FrostGenerateBlockBase> FrostGenerateBlockBaseTable;

typedef PointerVector<FrostGenerateBlockInModule>
	FrostGenerateBlockInModuleTable;
typedef PointerVector<FrostGenerateBlockInInterface>
	FrostGenerateBlockInInterfaceTable;


} // namespace frost_hdl

#endif		// src_table_types_hpp
