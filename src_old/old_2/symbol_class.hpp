#ifndef src_symbol_class_hpp
#define src_symbol_class_hpp

// src/symbol_class.hpp

#include "misc_includes.hpp"
#include "has_src_code_chunk_base_classes.hpp"

namespace frost_hdl
{

class AstNode;

class Symbol final
{
public:		// types
	enum class ScopeType
	{
		None,
		Package,
		Interface,
		Module,
		Function,
		Task,
	};

	enum class SymbolType
	{
		None,
		Var,
		Function,
		LhsType,
		//TypedefOfLhsType,
	};

	enum class PortType
	{
		None,
		Interface,
		InterfaceVar,
		Input,
		Output,

		// This might only ever be used for `task` arguments.
		// I am unsure about permitting it for `module` ports.
		Inout,
	};

protected:		// variables
	Ident _ident;
	AstNode* _decl_ast_node = nullptr;

public:		// functions
	Symbol();
	Symbol(const Ident& s_ident, AstNode* s_decl_ast_node);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Symbol);

	~Symbol(); 

	GEN_GETTER_BY_CON_REF(ident)
	GEN_GETTER_BY_VAL(decl_ast_node)
};


} // namespace frost_hdl


#endif		// src_symbol_class_hpp
