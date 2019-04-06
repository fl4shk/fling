#ifndef src_frost_generate_class_hpp
#define src_frost_generate_class_hpp

// src/frost_generate_class.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
//#include "table_types.hpp"

#include "has_src_code_pos_base_classes.hpp"
#include "generate_header_classes.hpp"
#include "inside_mod_or_gen_class.hpp"


namespace frost_hdl
{

class FrostGenerate : public HasSrcCodePosBase
{
private:		// variables
	InsideModOrGen _inside_mod_or_gen;

	std::variant<GenerateHeaderFor*, GenerateHeaderIf*> _header;

public:		// functions
	FrostGenerate(const SrcCodePos& s_src_code_pos);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostGenerate);

	virtual ~FrostGenerate();
};

} // namespace frost_hdl


#endif		// src_frost_generate_class_hpp
