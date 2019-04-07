#ifndef src_module_scope_class_hpp
#define src_module_scope_class_hpp

// src/module_scope_class.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
#include "frost_function_class.hpp"
#include "frost_full_type_class.hpp"
#include "generate_parent_class.hpp"

namespace frost_hdl
{

// Here we have a rare instance of a class used in the IR not being derived
// from "HasSrcCodePosBase"
// This class is used to represent the insides of of a "FrostModule" or the
// insides of a "FrostGenerate".
class ModuleScope
{
protected:		// variables
	// This is intended to be used for searching for symbols in the
	// "ParseTreeVisitor"
	GenerateParent _parent;

public:		// variables
	// These are public because "ModuleScope" is intended to be used, as
	// you may have guessed from this class's name, only inside
	// "FrostModule" or "FrostGenerate".
	SymbolTable local_symbol_table;
	FrostLhsTypeTable frost_lhs_type_table;
	FrostFullTypeTable frost_full_type_table;
	FrostFunctionTable frost_function_table;
	FrostStatementTable frost_statement_table;
	FrostGenerateTable frost_generate_table;

public:		// functions
	ModuleScope();

	// We don't want the tables to be initialized inline, so we call
	// the constructor.  That is the purpose of having the constructor be
	// in the ".cpp" file.  Link time optimization might mess with me here
	// in some cases, though, heh.
	template<typename ParentType>
	inline ModuleScope(ParentType* s_parent)
		: ModuleScope()
	{
		_parent = s_parent;
	}

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(ModuleScope);

	virtual ~ModuleScope();

	Symbol* find_symbol(SavedString some_name) const;
	inline bool contains_symbol(SavedString some_name) const
	{
		return (find_symbol(some_name) != nullptr);
	}

	GEN_GETTER_BY_CON_REF(parent)
};

} // namespace frost_hdl

#endif		// src_module_scope_class_hpp
