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

	// One single "SymbolTable" per scope, if any.
	virtual SymbolTable* symbol_table() const;

	// One single "HdlTypeTable" per scope, if any.
	virtual HdlTypeTable* hdl_type_table() const;

	// One single "HdlFunctionTable" per scope, if any.
	virtual HdlFunction* hdl_function_table() const;

	// Relevant for "HdlModule", "HdlStruct", and "HdlClass".
	// Might eventually be relevant for "HdlPackage", too.
	virtual ParameterVars* parameter_vars() const;

	// Relevant for "HdlModule"
	virtual HdlStatementTable* statement_table() const;

	// Relevant for "HdlStruct", "HdlClass", and "HdlEnum".
	virtual HdlType* hdl_type() const;

	bool has_symbol_table() const;
	bool has_hdl_type_table() const;
	bool has_hdl_function_table() const;
	bool has_parameter_vars() const;
	bool has_statement_table() const;
	bool has_hdl_type() const;
};

class HdlModule : public HdlScope
{
private:		// variables
	SymbolTable _symbol_table;
	HdlTypeTable _hdl_type_table;
	HdlFunctionTable _hdl_function_table;
	ParameterVars _parameter_vars;
	HdlStatementTable _statement_table;

public:		// functions
	HdlModule();

	HdlModule(SymbolTable&& s_symbol_table,
		HdlTypeTable&& s_hdl_type_table,
		HdlFunctionTable&& s_hdl_function_table,
		ParameterVars&& s_parameter_vars,
		HdlStatementTable&& s_statement_table);

	inline HdlModule(const HdlModule& to_copy) = delete;
	inline HdlModule(HdlModule&& to_move) = default;

	virtual ~HdlModule() = default;

	inline HdlModule& operator = (const HdlModule& to_copy) = delete;
	inline HdlModule& operator = (HdlModule&& to_move) = default;

	virtual GEN_GETTER_AS_POINTER(symbol_table)
	virtual GEN_GETTER_AS_POINTER(hdl_type_table)
	virtual GEN_GETTER_AS_POINTER(hdl_function_table)
	virtual GEN_GETTER_AS_POINTER(parameter_vars)
	virtual GEN_GETTER_AS_POINTER(statement_table)
};

class HdlStruct : public HdlScope
{
private:		// variables
	HdlType _hdl_type;

public:		// functions
	HdlStruct();

	HdlStruct(HdlType&& s_hdl_type);

	inline HdlStruct(const HdlStruct& to_copy) = delete;
	inline HdlStruct(HdlStruct&& to_move) = default;

	virtual ~HdlStruct() = default;

	inline HdlStruct& operator = (const HdlStruct& to_copy) = delete;
	inline HdlStruct& operator = (HdlStruct&& to_move) = default;

	virtual GEN_GETTER_AS_POINTER(hdl_type)

};
class HdlClass : public HdlScope
{
private:		// variables
	HdlType _hdl_type;

public:		// functions
	HdlClass();

	HdlClass(HdlType&& s_hdl_type);

	inline HdlClass(const HdlClass& to_copy) = delete;
	inline HdlClass(HdlClass&& to_move) = default;

	virtual ~HdlClass() = default;

	inline HdlClass& operator = (const HdlClass& to_copy) = delete;
	inline HdlClass& operator = (HdlClass&& to_move) = default;

	virtual GEN_GETTER_AS_POINTER(hdl_type)

};
class HdlEnum : public HdlScope
{
private:		// variables
	HdlType _hdl_type;

public:		// functions
	HdlEnum();

	HdlEnum(HdlType&& s_hdl_type);

	inline HdlEnum(const HdlEnum& to_copy) = delete;
	inline HdlEnum(HdlEnum&& to_move) = default;

	virtual ~HdlEnum() = default;

	inline HdlEnum& operator = (const HdlEnum& to_copy) = delete;
	inline HdlEnum& operator = (HdlEnum&& to_move) = default;

	virtual GEN_GETTER_AS_POINTER(hdl_type)

};

// It's probably a good idea to allow one "HdlPackage" inside of another
// "HdlPackage".  This is fascilitated via the "HdlScopeTable" class rather
// than being part of this one.
class HdlPackage : public HdlScope
{
private:		// variables
	SymbolTable _symbol_table;
	HdlTypeTable _hdl_type_table;
	HdlFunctionTable _hdl_function_table;
	ParameterVars _parameter_vars;

public:		// functions
	HdlPackage();

	HdlPackage(SymbolTable&& s_symbol_table,
		HdlTypeTable&& s_hdl_type_table,
		HdlFunctionTable&& s_hdl_function_table,
		ParameterVars&& s_parameter_vars);

	inline HdlPackage(const HdlPackage& to_copy) = delete;
	inline HdlPackage(HdlPackage&& to_move) = default;

	virtual ~HdlPackage() = default;

	inline HdlPackage& operator = (const HdlPackage& to_copy) = delete;
	inline HdlPackage& operator = (HdlPackage&& to_move) = default;

	virtual GEN_GETTER_AS_POINTER(symbol_table)
	virtual GEN_GETTER_AS_POINTER(hdl_type_table)
	virtual GEN_GETTER_AS_POINTER(hdl_function_table)
	virtual GEN_GETTER_AS_POINTER(parameter_vars)
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
