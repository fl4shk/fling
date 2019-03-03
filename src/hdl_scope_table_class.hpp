#ifndef src_hdl_scope_table_class_hpp
#define src_hdl_scope_table_class_hpp

// src/hdl_scope_table_class.hpp

#include "misc_includes.hpp"
#include "hdl_statement_table_class.hpp"
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
	//enum class Category
	//{
	//	// Nonexistent... don't use this!
	//	Bad,

	//	// "HdlModule"
	//	Module,

	//	// "HdlStruct", "HdlClass", "HdlEnum"
	//	CustomType,

	//	// "HdlPackage"
	//	Package,
	//};

private:		// variables
	//// One single "SymbolTable" per scope
	//SymbolTable _symbol_table;

	//// One single "HdlTypeTable" per scope
	//HdlTypeTable _hdl_type_table;

	//// One single "HdlFunctionTable" per scope
	//HdlFunctionTable _hdl_function_table;

	//// Relevant for "HdlModule", "HdlStruct", and "HdlClass".
	//// Might eventually be relevant for "HdlPackage", but that may change.
	//OrderedIdentToPointerTable<Symbol> _parameter_vars;

	//// Relevant for "HdlModule"
	//HdlStatementTable _statement_table;


	//// Relevant for "HdlStruct", "HdlClass", and "HdlEnum".
	//HdlType* _hdl_type = nullptr;

public:		// functions
	HdlScope() = default;

	// We don't want copies of "HdlScope"
	inline HdlScope(const HdlScope& to_copy) = default;
	inline HdlScope(HdlScope&& to_move) = default;

	virtual ~HdlScope() = default;

	// We don't want copies of "HdlScope"
	inline HdlScope& operator = (const HdlScope& to_copy) = default;
	inline HdlScope& operator = (HdlScope&& to_move) = default;


	//virtual bool is_module() const;
	//virtual bool is_package() const;
	//virtual bool is_custom_type() const;
	//virtual bool is_function() const;

	virtual SymbolTable* symbol_table() const;
	virtual HdlTypeTable* hdl_type_table() const;
	virtual HdlFunction* hdl_function_table() const;
	virtual OrderedIdentToPointerTable<Symbol>* parameter_vars() const;
	virtual HdlStatementTable* statement_table() const;
	virtual HdlType* hdl_type() const;

};

class HdlModule : public HdlScope
{
private:		// variables
	SymbolTable _symbol_table;
	HdlTypeTable _hdl_type_table;
	HdlFunctionTable _hdl_function_table;
	OrderedIdentToPointerTable<Symbol> _parameter_vars;

public:		// functions
	HdlModule();

	inline HdlModule(const HdlModule& to_copy) = delete;
	inline HdlModule(HdlModule&& to_move) = default;

	virtual ~HdlModule() = default;

	inline HdlModule& operator = (const HdlModule& to_copy) = delete;
	inline HdlModule& operator = (HdlModule&& to_move) = default;

	virtual GEN_GETTER_AS_POINTER(symbol_table)
	virtual GEN_GETTER_AS_POINTER(hdl_type_table)
	virtual GEN_GETTER_AS_POINTER(hdl_function_table)
	virtual GEN_GETTER_AS_POINTER(parameter_vars)

	//virtual SymbolTable* symbol_table() const
	//{
	//	return &_symbol_table;
	//}
};
class HdlStruct : public HdlScope
{
private:		// variables
	std::unique_ptr<HdlType> _hdl_type;
public:		// functions
};
class HdlClass : public HdlScope
{
public:		// functions
};
class HdlEnum : public HdlScope
{
public:		// functions
};
class HdlPackage : public HdlScope
{
public:		// functions
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
