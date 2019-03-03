#ifndef src_hdl_scope_table_class_hpp
#define src_hdl_scope_table_class_hpp

// src/hdl_scope_table_class.hpp

#include "misc_includes.hpp"
#include "statement_table_class.hpp"
#include "hdl_function_table_class.hpp"

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
		// Nonexistent... don't use this!
		Bad,

		// "HdlModule"
		Module,

		// "HdlStruct", "HdlClass", "HdlEnum"
		CustomType,

		// "HdlPackage"
		Package,
	};

private:		// variables
	// One single "SymbolTable" per scope
	SymbolTable _symbol_table;

	// One single "HdlTypeTable" per scope
	HdlTypeTable _hdl_type_table;

	// One single "HdlFunctionTable" per scope
	HdlFunctionTable _hdl_function_table;

	// Relevant for "HdlModule", "HdlStruct", and "HdlClass".
	// Might eventually be relevant for "HdlPackage", but that may change.
	OrderedIdentToPointerTable<Symbol> _parameter_vars;

	// Relevant for "HdlModule"
	StatementTable _statement_table;


	// Relevant for "HdlStruct", "HdlClass", and "HdlEnum".
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

	virtual Category category() const;


	GEN_GETTER_BY_REF(symbol_table)
	GEN_GETTER_BY_CON_REF(symbol_table)

	GEN_GETTER_BY_REF(hdl_type_table)
	GEN_GETTER_BY_CON_REF(hdl_type_table)

	GEN_GETTER_BY_REF(parameter_vars)
	GEN_GETTER_BY_CON_REF(parameter_vars)

	GEN_GETTER_BY_REF(statement_table)
	GEN_GETTER_BY_CON_REF(statement_table)

	GEN_GETTER_AND_SETTER_BY_VAL(hdl_type)

};

class HdlModule : public HdlScope
{
public:		// functions
	virtual inline Category category() const
	{
		return Category::Module;
	}
};
class HdlStruct : public HdlScope
{
public:		// functions
	virtual inline Category category() const
	{
		return Category::CustomType;
	}
};
class HdlClass : public HdlScope
{
public:		// functions
	virtual inline Category category() const
	{
		return Category::CustomType;
	}
};
class HdlEnum : public HdlScope
{
public:		// functions
	virtual inline Category category() const
	{
		return Category::CustomType;
	}
};
class HdlPackage : public HdlScope
{
public:		// functions
	virtual inline Category category() const
	{
		return Category::Package;
	}
};

// Scoping information is stored here.  The parse tree visitor ("Compiler")
// builds this and operates on it.
class HdlScopeTable : public ScopedIdentTable<HdlScope>
{
public:		// functions
	HdlScopeTable() = default;
	virtual ~HdlScopeTable() = default;
};

} // namespace frost_hdl


#endif		// src_hdl_scope_table_class_hpp
