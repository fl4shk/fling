#ifndef src_frost_lhs_type_class_hpp
#define src_frost_lhs_type_class_hpp

// src/frost_lhs_type_class.hpp

#include "misc_includes.hpp"
#include "symbol_value_class.hpp"

namespace frost_hdl
{

class FrostLhsType final : public HasSrcCodePosAndIdentBase
{
private:		//  variables
	
public:		// functions
	FrostLhsType();

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostLhsType);

	~FrostLhsType();
};

} // namespace frost_hdl

#endif		// src_frost_lhs_type_class_hpp
