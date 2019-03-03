#ifndef src_hdl_scope_table_class_hpp
#define src_hdl_scope_table_class_hpp

// src/hdl_scope_table_class.hpp

#include "misc_includes.hpp"
#include "scoped_table_base_class.hpp"
#include "symbol_table_class.hpp"
#include "hdl_type_table_class.hpp"

namespace frost_hdl
{

//class Symbol;
//class SymbolTable;
//class HdlType;
//class HdlTypeTable;

// Base class for a scope in HDL source code, which includes "HdlModule",
// "HdlStruct", "HdlClass", "HdlPackage", "HdlForLoop", etc.
class HdlScope
{
public:		// types
	enum class Category
	{
		Module,
		Composite,
		Enum,
		Package,
	};

private:		// variables
	// One single "SymbolTable" per scope
	SymbolTable _symbol_table;

	// One single "HdlTypeTable" per scope
	HdlTypeTable _hdl_type_table;

	// Relevant for "HdlModule", "HdlStruct", and "HdlClass".
	// Might eventually be relevant for "HdlPackage", but that may change.
	OrderedIdentToPointerTable<Symbol> _parameter_vars;

	// Relevant for "HdlStruct" and "HdlClass".
	HdlType* _hdl_type = nullptr;

public:		// functions
	HdlScope() = default;

	// We don't want copies of "HdlScope"
	inline HdlScope(const HdlScope& to_copy) = default;
	inline HdlScope(HdlScope&& to_move) = default;

	virtual ~HdlScope() = default;

	// We don't want copies of "HdlScope"
	inline HdlScope& operator = (const HdlScope& to_copy) = default;
	inline HdlScope& operator = (HdlScope&& to_move) = default;


	GEN_GETTER_BY_REF(symbol_table)
	GEN_GETTER_BY_CON_REF(symbol_table)

	GEN_GETTER_BY_REF(hdl_type_table)
	GEN_GETTER_BY_CON_REF(hdl_type_table)

	GEN_GETTER_BY_REF(parameter_vars)
	GEN_GETTER_BY_CON_REF(parameter_vars)

	GEN_GETTER_AND_SETTER_BY_VAL(hdl_type)

};

// Scoping information is stored here.  The parse tree visitor ("Compiler")
// builds this and operates on it.
class HdlScopeTable : public ScopedTableBase<HdlScope>
{
public:		// functions
	HdlScopeTable() = default;
	virtual ~HdlScopeTable() = default;
};

} // namespace frost_hdl


#endif		// src_hdl_scope_table_class_hpp
