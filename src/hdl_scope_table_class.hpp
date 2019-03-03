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

// Base class for (almost?) any type of scope in HDL source code, which
// includes "HdlDeclModule", "HdlDeclStruct", "HdlDeclClass",
// "HdlDeclPackage", etc.
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
	virtual SymbolTable* symbol_table();

	// One single "HdlTypeTable" per scope, if any.
	virtual HdlTypeTable* hdl_type_table();

	// One single "HdlFunctionTable" per scope, if any.
	virtual HdlFunctionTable* hdl_function_table();

	// Relevant for "HdlDeclModule", "HdlDeclStruct", and "HdlDeclClass".
	// Might eventually be relevant for "HdlDeclPackage", too.
	virtual ParameterVars* parameter_vars();

	// Relevant for "HdlDeclModule"
	virtual HdlStatementTable* statement_table();

	// Relevant for "HdlDeclStruct", "HdlDeclClass", and "HdlDeclEnum".
	virtual HdlType* hdl_type();

	// Relevant for "HdlDeclModule", "HdlDeclStruct", "HdlDeclClass",
	// "HdlDeclPackage", and "HdlDeclFunction"
	virtual HdlFunction* hdl_function();

	bool has_symbol_table();
	bool has_hdl_type_table();
	bool has_hdl_function_table();
	bool has_parameter_vars();
	bool has_statement_table();

	bool has_hdl_type();
	bool has_hdl_function();
};

class HdlDeclModule : public HdlScope
{
private:		// variables
	SymbolTable _symbol_table;
	HdlTypeTable _hdl_type_table;
	HdlFunctionTable _hdl_function_table;
	ParameterVars _parameter_vars;
	HdlStatementTable _statement_table;

public:		// functions
	HdlDeclModule();

	HdlDeclModule(SymbolTable&& s_symbol_table,
		HdlTypeTable&& s_hdl_type_table,
		HdlFunctionTable&& s_hdl_function_table,
		ParameterVars&& s_parameter_vars,
		HdlStatementTable&& s_statement_table);

	inline HdlDeclModule(const HdlDeclModule& to_copy) = delete;
	inline HdlDeclModule(HdlDeclModule&& to_move) = default;

	virtual ~HdlDeclModule() = default;

	inline HdlDeclModule& operator = (const HdlDeclModule& to_copy)
		= delete;
	inline HdlDeclModule& operator = (HdlDeclModule&& to_move) = default;

	virtual GEN_GETTER_AS_POINTER(symbol_table)
	virtual GEN_GETTER_AS_POINTER(hdl_type_table)
	virtual GEN_GETTER_AS_POINTER(hdl_function_table)
	virtual GEN_GETTER_AS_POINTER(parameter_vars)
	virtual GEN_GETTER_AS_POINTER(statement_table)
};

class HdlDeclStruct : public HdlScope
{
private:		// variables
	HdlType* _hdl_type = nullptr;

public:		// functions
	HdlDeclStruct() = default;

	HdlDeclStruct(HdlType&& s_hdl_type);

	inline HdlDeclStruct(const HdlDeclStruct& to_copy) = delete;
	inline HdlDeclStruct(HdlDeclStruct&& to_move) = default;

	virtual ~HdlDeclStruct() = default;

	inline HdlDeclStruct& operator = (const HdlDeclStruct& to_copy)
		= delete;
	inline HdlDeclStruct& operator = (HdlDeclStruct&& to_move) = default;

	virtual GEN_GETTER_BY_VAL(hdl_type)

};

class HdlDeclClass : public HdlScope
{
private:		// variables
	HdlType* _hdl_type = nullptr;

public:		// functions
	HdlDeclClass() = default;

	HdlDeclClass(HdlType&& s_hdl_type);

	inline HdlDeclClass(const HdlDeclClass& to_copy) = delete;
	inline HdlDeclClass(HdlDeclClass&& to_move) = default;

	virtual ~HdlDeclClass() = default;

	inline HdlDeclClass& operator = (const HdlDeclClass& to_copy) = delete;
	inline HdlDeclClass& operator = (HdlDeclClass&& to_move) = default;

	virtual GEN_GETTER_BY_VAL(hdl_type)

};

class HdlDeclEnum : public HdlScope
{
private:		// variables
	HdlType* _hdl_type = nullptr;

public:		// functions
	HdlDeclEnum();

	HdlDeclEnum(HdlType&& s_hdl_type);

	inline HdlDeclEnum(const HdlDeclEnum& to_copy) = delete;
	inline HdlDeclEnum(HdlDeclEnum&& to_move) = default;

	virtual ~HdlDeclEnum() = default;

	inline HdlDeclEnum& operator = (const HdlDeclEnum& to_copy) = delete;
	inline HdlDeclEnum& operator = (HdlDeclEnum&& to_move) = default;

	virtual GEN_GETTER_BY_VAL(hdl_type)

};

// It's probably a good idea to allow one "HdlDeclPackage" inside of
// another "HdlDeclPackage".  This is fascilitated via the "HdlScopeTable"
// class rather than being part of this one.
class HdlDeclPackage : public HdlScope
{
private:		// variables
	SymbolTable _symbol_table;
	HdlTypeTable _hdl_type_table;
	HdlFunctionTable _hdl_function_table;
	ParameterVars _parameter_vars;

public:		// functions
	HdlDeclPackage();

	HdlDeclPackage(SymbolTable&& s_symbol_table,
		HdlTypeTable&& s_hdl_type_table,
		HdlFunctionTable&& s_hdl_function_table,
		ParameterVars&& s_parameter_vars);

	inline HdlDeclPackage(const HdlDeclPackage& to_copy) = delete;
	inline HdlDeclPackage(HdlDeclPackage&& to_move) = default;

	virtual ~HdlDeclPackage() = default;

	inline HdlDeclPackage& operator = (const HdlDeclPackage& to_copy)
		= delete;
	inline HdlDeclPackage& operator = (HdlDeclPackage&& to_move) = default;

	virtual GEN_GETTER_AS_POINTER(symbol_table)
	virtual GEN_GETTER_AS_POINTER(hdl_type_table)
	virtual GEN_GETTER_AS_POINTER(hdl_function_table)
	virtual GEN_GETTER_AS_POINTER(parameter_vars)
};

class HdlDeclFunction : public HdlScope
{
private:		// variables
	HdlFunction* _hdl_function = nullptr;

public:		// functions
	HdlDeclFunction() = default;

	HdlDeclFunction(HdlFunction&& s_hdl_function);

	inline HdlDeclFunction(const HdlDeclFunction& to_copy) = delete;
	inline HdlDeclFunction(HdlDeclFunction&& to_move) = default;

	virtual ~HdlDeclFunction() = default;

	inline HdlDeclFunction& operator = (const HdlDeclFunction& to_copy)
		= delete;
	inline HdlDeclFunction& operator = (HdlDeclFunction&& to_move)
		= default;

	virtual GEN_GETTER_BY_VAL(hdl_function)
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
