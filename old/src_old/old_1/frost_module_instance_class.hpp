#ifndef src_frost_module_instance_class_hpp
#define src_frost_module_instance_class_hpp

// src/frost_module_instance_class.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
#include "table_types.hpp"

namespace frost_hdl
{

class ModuleInstConnection : public HasSrcCodePosBase
{
private:		// variables
	// The symbol that we're connecting to  
	Symbol* _symbol = nullptr;

	// The IdentExpr that we are connecting to the symbol
	Expression* _ident_expr = nullptr;

public:		// variables
	ModuleInstConnection(const SrcCodePos& s_src_code_pos,
		Symbol* s_symbol, Expression* s_ident_expr);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(ModuleInstConnection);
	virtual ~ModuleInstConnection();

	// This is for use with an IdentTable<ModuleInstConnection>.
	inline SavedString ident() const
	{
		return _symbol->ident();
	}

	GEN_GETTER_BY_VAL(symbol)
	GEN_GETTER_BY_VAL(ident_expr)
};

// The identifier here is optional and perhaps only useful for debugging,
// but if it exists, it must be unique within the scope that this module
// instance lives in, but it only has to be unique among module instance
// identifiers (i.e. you can have a variable with the same name).
// 
// An identifier will be generated if there isn't one passed
class FrostModuleInstance : public HasSrcCodePosBase
{
private:		// variables
	SavedString _ident = nullptr;

	// The place *where* the module was instantiated
	ModuleScope* _where = nullptr;

	// The type of module that was instantiated.
	FrostModule* _what = nullptr;

	// *Something* has to verify that these are valid.  At the time of
	// writing this comment, I don't know what that something is.  Once
	// support for interfaces is added into the compiler, the verification
	// of these will be done *after* converting interfaces into real ports.
	//
	// This is just another place in the IR where I have to duplicate
	// or otherwise create new symbols, and create new expressions
	// referencing those symbols. 
	ModuleInstConnectionTable _parameter_connection_table,
		_port_connection_table;

public:		// functions
	FrostModuleInstance(const SrcCodePos& s_src_code_pos,
		SavedString s_ident, ModuleScope* s_where,
		FrostModule* s_what);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostModuleInstance);

	virtual ~FrostModuleInstance();

	//inline bool has_generated_ident() const
	//{
	//	return ((*ident())[0] == '\\');
	//}

	SavedString ident() const;

	GEN_GETTER_BY_VAL(where)
	GEN_GETTER_BY_VAL(what)
	GEN_GETTERS_BY_CON_REF_AND_REF(parameter_connection_table)
	GEN_GETTERS_BY_CON_REF_AND_REF(port_connection_table)

};

} // namespace frost_hdl


#endif		// src_frost_module_instance_class_hpp
