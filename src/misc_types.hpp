#ifndef src_misc_types_hpp
#define src_misc_types_hpp

// src/misc_types.hpp

#include "misc_includes.hpp"
#include "ident_table_classes.hpp"
//#include "scoped_table_classes.hpp"

namespace frost_hdl
{
class Symbol;

// Used for temporary type identifiers before actual dimension expressions
// are evaluated.
template<typename Type>
SavedString construct_initial_type_ident_from_pointer
	(SavedString base_ident, Type* pointer)
{
	return dup_str(sconcat(*base_ident, "[",
		reinterpret_cast<uintptr_t>(pointer),
		"]"));
}



class ReplaceSymsMap
{
private:		// variables
	std::map<Symbol*, Symbol*> _inner_map;

public:		// functions
	ReplaceSymsMap();

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(ReplaceSymsMap);
	virtual ~ReplaceSymsMap();

	inline Symbol*& at(Symbol* some_orig_sym)
	{
		return _inner_map[some_orig_sym];
	}

	inline Symbol* at(Symbol* some_orig_sym) const
	{
		return _inner_map.at(some_orig_sym);
	}

	inline bool contains(Symbol* some_orig_sym) const
	{
		return (_inner_map.count(some_orig_sym) == 1);
	}

	inline void insert_or_assign(Symbol* some_orig_sym,
		Symbol* to_insert_or_assign)
	{
		at(some_orig_sym) = to_insert_or_assign;
	}

	GEN_GETTER_BY_CON_REF(inner_map);
};

template<typename Type>
class PointerVector : public std::vector<Type*>
{
public:		// functions
	inline PointerVector() = default;

	GEN_COPY_CONSTRUCTOR_AND_ASSIGN(PointerVector);
	virtual ~PointerVector() = default;
};




} // namespace frost_hdl


#endif		// src_misc_types_hpp
