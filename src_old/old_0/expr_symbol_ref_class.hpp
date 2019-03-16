#ifndef src_expr_symbol_ref_class_hpp
#define src_expr_symbol_ref_class_hpp

// src/expr_symbol_ref_class.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
#include "expr_chunk_class.hpp"

namespace frost_hdl
{

class ExprSymbolRef
{
private:		// variables
	Symbol* __symbol = nullptr;
	std::vector<ExprChunk> __indexing;

public:		// functions
	inline ExprSymbolRef()
	{
	}

	inline ExprSymbolRef(const ExprSymbolRef& to_copy) = default;

	inline ExprSymbolRef& operator = (const ExprSymbolRef& to_copy)
		= default;

	inline bool has_valid_indexing() const
	{
		return (indexing().size() == symbol()->arr_dim().size());
	}

	inline bool operator < (const ExprSymbolRef& to_cmp) const
	{
		if (symbol() < to_cmp.symbol())
		{
			return true;
		}
		else if (symbol() == to_cmp.symbol())
		{
			return (indexing() < to_cmp.indexing());
		}
		else
		{
			return false;
		}
	}

	gen_getter_and_setter_by_val(symbol);
	gen_getter_by_ref(indexing);
	gen_getter_by_con_ref(indexing);

};

} // namespace frost_hdl

#endif		// src_expr_symbol_ref_class_hpp
