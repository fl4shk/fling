#ifndef src_symbol_table_class_hpp
#define src_symbol_table_class_hpp

// src/symbol_table_class.hpp

#include "misc_includes.hpp"
#include "general_allocator_class.hpp"
#include "scoped_table_base_class.hpp"
#include "expr_num_class.hpp"
#include "hdl_type_table_class.hpp"

namespace frost_hdl
{

class Symbol
{
protected:		// variables
	SavedString _ident = nullptr;
	HdlType* _hdl_type = nullptr;
	//Context* _context = nullptr;
	ExprNum* _value = nullptr;

public:		// functions
	inline Symbol() = default;
	Symbol(SavedString s_ident, HdlType* s_hdl_type);
	Symbol(SavedString s_ident, HdlType* s_hdl_type, ExprNum* s_value);


	// We really don't want copies of "Symbol"s.
	inline Symbol(const Symbol& to_copy) = delete;
	inline Symbol(Symbol&& to_move) = default;

	virtual ~Symbol() = default;


	// We really don't want copies of "Symbol"s.
	inline Symbol& operator = (const Symbol& to_copy) = delete;
	inline Symbol& operator = (Symbol&& to_move) = default;

	inline const HdlType& hdl_type() const
	{
		return (*_hdl_type);
	}

	inline const ExprNum& value() const
	{
		return (*_value);
	}

	inline bool is_constant() const
	{
		return (_value == nullptr);
	}
};

class SymbolTable : public ScopedTableBase<Symbol>
{
public:		// functions
	SymbolTable() = default;
	virtual ~SymbolTable() = default;
};

} // namespace frost_hdl

#endif		// src_symbol_table_class_hpp
