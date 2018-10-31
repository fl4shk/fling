#ifndef src__slash__symbol_table_classes_hpp
#define src__slash__symbol_table_classes_hpp

// src/symbol_table_classes.hpp

#include "misc_includes.hpp"

#include "scoped_table_base_class.hpp"
#include "expr_num_class.hpp"


namespace frost_hdl
{

class Symbol
{
public:		// enums
	enum class CompiledType : bool
	{
		Reg,
		Wire,
	};

private:		// variables
	// The symbol's name
	Ident __name = nullptr;

	// The type name of this symbol.
	Ident __type = nullptr;

	// Used to allow forward referencing.
	bool __has_been_found = false;

	// Whether or not this Symbol will be compiled to a reg (vector)
	// or a wire (vector).  By default, it is assumed that this Symbol
	// will be compiled to a reg (vector), but that only applies to the
	// case when this Symbol is never assigned to.
	CompiledType __compiled_type = CompiledType::Reg;

	// This also contains the size of the Symbol, so even if a Symbol is
	// NOT constant, it still needs __expr_num to NOT be a nullptr.
	ExprNum* __expr_num = nullptr;

public:		// functions
	inline Symbol()
	{
	}


	inline Symbol(Ident s_name, Ident s_type)
		: __name(s_name), __type(s_type), __has_been_found(false),
		__compiled_type(CompiledType::Reg), __expr_num(nullptr)
	{
	}

	inline Symbol(const Symbol& to_copy) = default;
	inline Symbol(Symbol&& to_move) = default;

	inline Symbol& operator = (const Symbol& to_copy) = default;
	inline Symbol& operator = (Symbol&& to_move) = default;


	gen_getter_and_setter_by_con_ref(name);
	gen_setter_by_rval_ref(name);
	gen_getter_and_setter_by_con_ref(type);
	gen_setter_by_rval_ref(type);

	gen_getter_and_setter_by_val(has_been_found);
	gen_getter_and_setter_by_val(compiled_type);
	gen_getter_and_setter_by_val(expr_num);


};


class SymbolTable : public ScopedTableBase<Symbol>
{
public:		// functions
	SymbolTable();
	virtual ~SymbolTable();
};

} // namespace frost_hdl


#endif		// src__slash__symbol_table_classes_hpp
