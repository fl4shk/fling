#ifndef src_frost_full_type_class_hpp
#define src_frost_full_type_class_hpp

// src/frost_full_type_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "ast_node_class.hpp"

namespace frost_hdl
{

class FrostFullType final
{
private:		// variables
	ParametersFpnVec _parameters_fpn_vec;

public:		// functions
	FrostFullType();

	GEN_GENERIC_CM_CONSTRUCTORS_AND_ASSIGN(FrostFullType, delete, delete);

	~FrostFullType();
};

} // namespace frost_hdl


#endif		// src_frost_full_type_class_hpp
