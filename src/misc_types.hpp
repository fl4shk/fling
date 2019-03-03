#ifndef src_misc_types_hpp
#define src_misc_types_hpp

// src/misc_types.hpp

#include "misc_includes.hpp"
#include "ident_table_classes.hpp"

namespace frost_hdl
{

class Symbol;

typedef OrderedIdentToPointerTable<Symbol> ParameterVars;

template<typename Type>
class PointerVector : public std::vector<Type*>
{
public:		// functions
	inline PointerVector() = default;

	inline PointerVector(const PointerVector& to_copy) = default;
	inline PointerVector(PointerVector&& to_move) = default;

	virtual ~PointerVector() = default;

	inline PointerVector& operator = (const PointerVector& to_copy)
		= default;
	inline PointerVector& operator = (PointerVector&& to_move)
		= default;
};

} // namespace frost_hdl


#endif		// src_misc_types_hpp
