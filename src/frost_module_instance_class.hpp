#ifndef src_frost_module_instance_class_hpp
#define src_frost_module_instance_class_hpp

// src/frost_module_instance_class.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
#include "table_types.hpp"

namespace frost_hdl
{


// The identifier here is optional and perhaps only useful for debugging.
class FrostModuleInstance : public HasSrcCodePosAndIdentBase
{
private:		// variables
	ModuleScope* _where = nullptr;
	FrostModule* _what = nullptr;

	IdentExprToSymbolConnectionMap _parameter_connection_map,
		_input_connection_map, _output_connection_map;

public:		// functions
	FrostModuleInstance(const SrcCodePos& s_src_code_pos,
		SavedString s_ident);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostModuleInstance);

	virtual ~FrostModuleInstance();

	GEN_GETTER_AND_SETTER_BY_VAL(where)
	GEN_GETTER_AND_SETTER_BY_VAL(what)
	GEN_GETTERS_BY_CON_REF_AND_REF(parameter_connection_map)
	GEN_GETTERS_BY_CON_REF_AND_REF(input_connection_map)
	GEN_GETTERS_BY_CON_REF_AND_REF(output_connection_map)
};

} // namespace frost_hdl


#endif		// src_frost_module_instance_class_hpp
