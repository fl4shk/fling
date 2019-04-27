#ifndef src_symbol_class_hpp
#define src_symbol_class_hpp

// src/symbol_class.hpp

#include "misc_includes.hpp"
#include "general_allocator_class.hpp"

#include "has_src_code_pos_base_classes.hpp"

//#include "symbol_value_class.hpp"

namespace frost_hdl
{

class FrostProgramNode;
class FrostLhsType;

class Symbol final
{
private:		// variables
	FrostProgramNode * _lhs_type_name_fpn = nullptr,
		* _ident_fpn = nullptr, * _arr_size_fpn = nullptr;
	FrostLhsType* _frost_lhs_type = nullptr;

public:		// functions
	Symbol();

	Symbol(FrostProgramNode* s_lhs_type_name_fpn,
		FrostProgramNode* s_ident_fpn, FrostProgramNode* s_arr_size_fpn);

	Symbol(FrostProgramNode* s_lhs_type_name_fpn,
		FrostProgramNode* s_ident_fpn, FrostProgramNode* s_arr_size_fpn,
		FrostLhsType* s_frost_lhs_type);

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(Symbol);

	~Symbol();

	GEN_GETTER_BY_VAL(lhs_type_name_fpn)
	GEN_GETTER_BY_VAL(ident_fpn)
	GEN_GETTER_BY_VAL(arr_size_fpn)
	GEN_GETTER_AND_SETTER_BY_VAL(frost_lhs_type)
};

} // namespace frost_hdl

#endif		// src_symbol_class_hpp
