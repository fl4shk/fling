#ifndef src_symbol_class_hpp
#define src_symbol_class_hpp

// src/symbol_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "general_allocator_class.hpp"

#include "has_src_code_chunk_base_classes.hpp"

//#include "symbol_value_class.hpp"

namespace frost_hdl
{

class FrostProgramNode;
class FrostFullType;

class Symbol final
{
private:		// variables
	SavedString _ident = nullptr;
	FrostProgramNode* _var_decl_fpn = nullptr;

public:		// functions
	Symbol();

	Symbol(SavedString s_ident, FrostProgramNode* s_var_decl_fpn);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Symbol);

	~Symbol();

	//FrostFullType frost_full_type() const;

	GEN_GETTER_BY_VAL(var_decl_fpn)
	GEN_GETTER_BY_VAL(ident)
};

} // namespace frost_hdl

#endif		// src_symbol_class_hpp
