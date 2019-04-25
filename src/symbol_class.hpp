#ifndef src_symbol_class_hpp
#define src_symbol_class_hpp

// src/symbol_class.hpp

#include "misc_includes.hpp"
#include "general_allocator_class.hpp"

#include "has_src_code_pos_base_classes.hpp"

#include "symbol_value_class.hpp"

namespace frost_hdl
{

class Symbol final : public HasSrcCodePosBase
{
private:		// variables
	SymbolValue _value;

public:		// functions
	Symbol();


	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Symbol);

	~Symbol();

};

} // namespace frost_hdl

#endif		// src_symbol_class_hpp
