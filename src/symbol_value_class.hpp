#ifndef src_symbol_value_class_hpp
#define src_symbol_value_class_hpp

// src/symbol_value_class.hpp

#include "misc_includes.hpp"
#include "has_src_code_pos_base_classes.hpp"
//#include "frost_program_node_class.hpp"

namespace frost_hdl
{

class FrostLhsType;
class FrostProgramNode;

class SymbolValue final : public HasSrcCodePosAndIdentBase
{
private:		// variables
	FrostLhsType* _frost_lhs_type = nullptr;

	FrostProgramNode* _data_size_fpn = nullptr;

	std::variant<std::vector<SymbolValue>, std::vector<FrostProgramNode*>,
		FrostProgramNode*>
		_data;

public:		// functions
	SymbolValue();

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(SymbolValue);

	~SymbolValue();
};

} // namespace frost_hdl


#endif		// src_symbol_value_class_hpp
