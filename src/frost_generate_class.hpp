#ifndef src_frost_generate_class_hpp
#define src_frost_generate_class_hpp

// src/frost_generate_class.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
//#include "table_types.hpp"

#include "has_src_code_pos_base_classes.hpp"
#include "generate_header_classes.hpp"
#include "module_scope_class.hpp"


namespace frost_hdl
{

class FrostGenerate : public HasSrcCodePosBase
{
private:		// variables
	ModuleScope _module_scope;

	GenerateParent _parent;

	std::variant<GenerateHeaderFor, GenerateHeaderIf> _header;

public:		// functions
	FrostGenerate(const SrcCodePos& s_src_code_pos);

	template<typename ParentType, typename HeaderType>
	inline FrostGenerate(const SrcCodePos& s_src_code_pos,
		ParentType* s_parent, const HeaderType& s_header)
		: FrostGenerate(s_src_code_pos)
	{
		_parent = s_parent;
		_header = s_header;
	}

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostGenerate);

	virtual ~FrostGenerate();

	GEN_GETTERS_BY_CON_REF_AND_REF(module_scope)
	GEN_GETTER_BY_CON_REF(parent)
	GEN_GETTER_BY_CON_REF(header)
};

} // namespace frost_hdl


#endif		// src_frost_generate_class_hpp
