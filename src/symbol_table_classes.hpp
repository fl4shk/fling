#ifndef src__slash__symbol_table_classes_hpp
#define src__slash__symbol_table_classes_hpp

// src/symbol_table_classes.hpp

#include "misc_includes.hpp"

#include "scoped_table_base_class.hpp"


class Symbol
{
private:		// variables
	// The symbol's name
	Ident __name;

	// The type name of this symbol.
	Ident __type;

	// Used to allow forward referencing.
	bool __has_been_found = false;

	size_t __size = 0;


public:		// functions
	inline Symbol()
	{
	}
	//inline Symbol(Ident s_name, u64 s_addr)
	//	: __name(s_name), __addr(s_addr), __found_as_label(false)
	//{
	//}

	//inline Symbol(Ident s_name, Ident s_type)
	//	: __name(s_name), __type(s_type), __has_been_found(false)
	//{
	//}
	inline Symbol(const Symbol& to_copy) = default;
	inline Symbol(Symbol&& to_move) = default;

	inline Symbol& operator = (const Symbol& to_copy) = default;
	inline Symbol& operator = (Symbol&& to_move) = default;

	gen_getter_and_setter_by_con_ref(name);
	gen_setter_by_rval_ref(name);
	gen_getter_and_setter_by_con_ref(type);
	gen_setter_by_rval_ref(type);

	//gen_getter_and_setter_by_val(addr);
	gen_getter_and_setter_by_val(has_been_found);

	//gen_getter_and_setter_by_val(is_constant);
};


class SymbolTable : public ScopedTableBase<Symbol>
{
public:		// functions
	SymbolTable();
	virtual ~SymbolTable();
};




#endif		// src__slash__symbol_table_classes_hpp
