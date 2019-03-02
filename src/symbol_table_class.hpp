#ifndef src_symbol_table_class_hpp
#define src_symbol_table_class_hpp

// src/symbol_table_class.hpp

#include "misc_includes.hpp"
#include "general_allocator_class.hpp"
#include "scoped_table_base_class.hpp"
#include "ident_table_classes.hpp"
//#include "expression_classes.hpp"
//#include "hdl_type_table_class.hpp"

namespace frost_hdl
{

class HdlType;
class Expression;

// This class represents variables and named constants.
class Symbol
{
protected:		// variables
	SavedString _ident = nullptr;

	// Whether or not this symbol is a named constant.
	bool _is_constant = false;

	HdlType* _hdl_type = nullptr;
	Expression* _starting_value = nullptr;

public:		// functions
	Symbol() = default;
	inline Symbol(SavedString s_ident, bool s_is_constant,
		HdlType* s_hdl_type)
		: Symbol(s_ident, s_is_constant, s_hdl_type, nullptr)
	{
	}
	Symbol(SavedString s_ident, bool s_is_constant, HdlType* s_hdl_type,
		Expression* s_starting_value);


	// We really don't want copies of "Symbol"s.
	inline Symbol(const Symbol& to_copy) = delete;
	inline Symbol(Symbol&& to_move) = default;

	virtual ~Symbol() = default;


	// We really don't want copies of "Symbol"s.
	inline Symbol& operator = (const Symbol& to_copy) = delete;
	inline Symbol& operator = (Symbol&& to_move) = default;



	GEN_GETTER_BY_VAL(ident)
	GEN_GETTER_BY_VAL(is_constant)
	GEN_GETTER_BY_VAL(hdl_type)

	GEN_GETTER_AND_SETTER_BY_VAL(starting_value)
};

// "SymbolTable" isn't scoped because scoping information is stored in the
// "StatementTable" class.
class SymbolTable : public IdentToPointerTable<Symbol>
{
public:		// functions
	SymbolTable() = default;
	virtual ~SymbolTable() = default;
};

} // namespace frost_hdl

#endif		// src_symbol_table_class_hpp
