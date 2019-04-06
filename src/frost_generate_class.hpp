#ifndef src_frost_generate_class_hpp
#define src_frost_generate_class_hpp

// src/frost_generate_class.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
//#include "table_types.hpp"


namespace frost_hdl
{

class FrostGenerate
{
private:		// variables
	SrcCodePos _src_code_pos;
	SavedString _ident = nullptr;

	SymbolTable _local_symbol_table;

public:		// functions
	FrostGenerate(const SrcCodePos& s_src_code_pos,
		SavedString s_ident);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostGenerate);

	virtual ~FrostGenerate();

	GEN_GETTER_BY_CON_REF(src_code_pos)
	GEN_GETTER_BY_VAL(ident)

	GEN_GETTERS_BY_CON_REF_AND_REF(local_symbol_table)
};

} // namespace frost_hdl


#endif		// src_frost_generate_class_hpp
