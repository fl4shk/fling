#ifndef src_hdl_scope_table_class_hpp
#define src_hdl_scope_table_class_hpp

// src/hdl_scope_table_class.hpp

#include "misc_includes.hpp"
#include "hdl_statement_table_class.hpp"
#include "hdl_function_table_class.hpp"

namespace frost_hdl
{


// Base class for (almost?) any type of scope in HDL source code, which
// includes "HdlDeclModule", "HdlDeclStruct", "HdlDeclClass",
// "HdlDeclPackage", etc.
class HdlScope
{
public:		// functions
	HdlScope() = default;

	// We don't want copies of "HdlScope"
	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlScope, delete, default)
	virtual ~HdlScope() = default;


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

	// Relevant for "HdlDeclModule".
	// Might be relevant for "HdlDeclPackage", too.
	virtual ParameterVars* parameter_vars();

	// Relevant for "HdlDeclModule".
	virtual HdlStatementTable* statement_table();


	// Relevant for "HdlDeclStruct", "HdlDeclClass", and "HdlDeclEnum".
	virtual HdlType* hdl_type();

	// Relevant for "HdlDeclFunction"
	virtual HdlFunction* hdl_function();

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

	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlDeclModule, delete, default)

	virtual ~HdlDeclModule() = default;


	virtual GEN_GETTER_AS_POINTER(symbol_table)
	virtual GEN_GETTER_AS_POINTER(hdl_type_table)
	virtual GEN_GETTER_AS_POINTER(hdl_function_table)
	virtual GEN_GETTER_AS_POINTER(parameter_vars)
	virtual GEN_GETTER_AS_POINTER(statement_table)
};

// This class exists to provide temporary information about scope for
// "HdlType" instances that are structs.
class HdlDeclStruct : public HdlScope
{
private:		// variables
	HdlType* _hdl_type = nullptr;

public:		// functions
	HdlDeclStruct() = default;

	HdlDeclStruct(HdlType&& s_hdl_type);

	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlDeclStruct, delete, default)
	virtual ~HdlDeclStruct() = default;


	virtual GEN_GETTER_BY_VAL(hdl_type)

};

// This class exists to provide temporary information about scope for
// "HdlType" instances that are classes.
class HdlDeclClass : public HdlScope
{
private:		// variables
	HdlType* _hdl_type = nullptr;

public:		// functions
	HdlDeclClass() = default;

	HdlDeclClass(HdlType&& s_hdl_type);

	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlDeclClass, delete, default)

	virtual ~HdlDeclClass() = default;

	virtual GEN_GETTER_BY_VAL(hdl_type)

};

// This class exists to provide temporary information about scope for
// "HdlType" instances that are enums.
class HdlDeclEnum : public HdlScope
{
private:		// variables
	HdlType* _hdl_type = nullptr;

public:		// functions
	HdlDeclEnum();

	HdlDeclEnum(HdlType&& s_hdl_type);

	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlDeclEnum, delete, default)

	virtual ~HdlDeclEnum() = default;


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

	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlDeclPackage, delete, default)

	virtual ~HdlDeclPackage() = default;

	inline HdlDeclPackage& operator = (const HdlDeclPackage& to_copy)
		= delete;
	inline HdlDeclPackage& operator = (HdlDeclPackage&& to_move) = default;

	virtual GEN_GETTER_AS_POINTER(symbol_table)
	virtual GEN_GETTER_AS_POINTER(hdl_type_table)
	virtual GEN_GETTER_AS_POINTER(hdl_function_table)
	virtual GEN_GETTER_AS_POINTER(parameter_vars)
};

// This class exists to provide temporary information about scope for
// "HdlFunction" instances.
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
