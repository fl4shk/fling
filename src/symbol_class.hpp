#ifndef src_symbol_class_hpp
#define src_symbol_class_hpp

// src/symbol_class.hpp

#include "misc_includes.hpp"
#include "general_allocator_class.hpp"

#include "has_src_code_chunk_base_classes.hpp"

//#include "symbol_value_class.hpp"

namespace frost_hdl
{

class FrostProgramNode;
class FrostFullType;

class Symbol final
{
public:		// types
	typedef std::vector<FrostProgramNode*> ParametersFpnVec;

private:		// variables
	FrostProgramNode * _lhs_type_name_fpn = nullptr,
		* _ident_fpn = nullptr, * _arr_size_fpn = nullptr;
	ParametersFpnVec _parameters_fpn_vec;

public:		// functions
	Symbol();

	Symbol(FrostProgramNode* s_lhs_type_name_fpn,
		FrostProgramNode* s_ident_fpn, FrostProgramNode* s_arr_size_fpn,
		ParametersFpnVec&& s_parameters_fpn_vec);


	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Symbol);

	~Symbol();

	SavedString ident() const;
	FrostFullType frost_full_type() const;

	GEN_GETTER_BY_VAL(lhs_type_name_fpn)
	GEN_GETTER_BY_VAL(ident_fpn)
	GEN_GETTER_BY_VAL(arr_size_fpn)
	GEN_GETTER_BY_CON_REF(parameters_fpn_vec)
};

} // namespace frost_hdl

#endif		// src_symbol_class_hpp
