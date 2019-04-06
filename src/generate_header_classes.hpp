#ifndef src_generate_header_classes_hpp
#define src_generate_header_classes_hpp

// src/generate_header_classes.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
#include "pseudo_func_call_range_class.hpp"

namespace frost_hdl
{

class GenerateHeaderFor
{
public:		// variables
	//SavedString iter_ident = nullptr;
	Symbol* iter_sym = nullptr;
	PseudoFuncCallRange pseudo_func_call_range;

public:		// functions
	inline bool is_valid() const
	{
		return (pseudo_func_call_range.is_constant()
			&& (!pseudo_func_call_range.left()->references_symbol
			(iter_sym))
			&& (!pseudo_func_call_range.right()->references_symbol
			(iter_sym)));
	}

};

class GenerateHeaderIf
{
public:		// variables
	Expression* condition = nullptr;

public:		// functions
	inline bool is_valid() const
	{
		return condition->is_constant();
	}

};

} // namespace frost_hdl


#endif		// src_generate_header_classes_hpp
