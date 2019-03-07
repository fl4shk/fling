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

	GEN_CM_CONSTRUCTORS_AND_ASSIGN(PointerVector, default, default);
	virtual ~PointerVector() = default;

};

// Used for error reporting during semantic analysis.
// Many, many things derive from this.
class HasSourceCodePosBase
{
protected:		// variables
	size_t _line = 0, _pos_in_line = 0;

public:		// functions
	inline HasSourceCodePosBase() = default;

	inline HasSourceCodePosBase(size_t s_line, size_t s_pos_in_line)
		: _line(s_line), _pos_in_line(s_pos_in_line)
	{
	}


	virtual ~HasSourceCodePosBase() = default;


	GEN_GETTER_AND_SETTER_BY_VAL(line)
	GEN_GETTER_AND_SETTER_BY_VAL(pos_in_line)
};

} // namespace frost_hdl


#endif		// src_misc_types_hpp
