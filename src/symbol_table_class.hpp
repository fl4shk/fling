#ifndef src_symbol_table_class_hpp
#define src_symbol_table_class_hpp

// src/symbol_table_class.hpp

#include "misc_includes.hpp"
#include "general_allocator_class.hpp"
#include "ident_table_classes.hpp"
//#include "expression_classes.hpp"
//#include "hdl_type_table_class.hpp"


namespace frost_hdl
{

class HdlType;
class Expression;

// This class represents variables and named constants, including named
// constants used as parameters to a parameterized... thing (such as an
// "HdlModule" or a composite type).
//
// An instantiation of a "parameter"ized construct will have a different
// set of "Symbol"s for its "parameter"s than the set of "Symbol"s used for
// the construct's definition.
class Symbol
{
public:		// types
	typedef std::vector<Expression*> ValueExprs;

	//typedef std::vector<Symbol*> OrderedIdentToPointerTable<Symbol>;

private:		// variables
	SavedString _ident = nullptr;

	// Whether or not this symbol is a named constant.
	bool _is_constant = false;

	// If this "Symbol"'s declaration has not yet been seen, then
	// "_hdl_type" will be set to "nullptr".  Use "actually_exists()" to
	// get this information.
	HdlType* _hdl_type = nullptr;

	// For arrays, this *must* be set an Expression that evaluates to the
	// size of the array.  If "_right_dim_expr" is set to "nullptr", then
	// this "Symbol" is not an array.,
	Expression* _right_dim_expr = nullptr;

	// Compile-time values are stored here for both scalars and arrays.
	// For parameters, store a "nullptr" in *any* of the elements of this
	// "ValueExprs" to indicate that this parameter *does not* have a
	// default value.
	ValueExprs _value_exprs;

	// Actual parameter values for this "Symbol"'s "HdlType"
	OrderedIdentToPointerTable<Symbol> _parameter_vars;

public:		// functions
	Symbol() = default;

	// Unknown type symbol where all we have is its name, due to it being
	// used earlier than it was defined (needs stuff filled in later!)
	Symbol(SavedString s_ident);

	// Non-constant scalar constructors
	inline Symbol(HdlType* s_hdl_type)
		: Symbol(_ident, s_hdl_type)
	{
	}
	Symbol(SavedString s_ident, HdlType* s_hdl_type);

	// Constant scalar constructors, or non-constant array constructors
	inline Symbol(HdlType* s_hdl_type, bool s_is_array,
		Expression* scalar_val_or_arr_size)
		: Symbol(_ident, s_hdl_type, s_is_array, scalar_val_or_arr_size)
	{
	}
	Symbol(SavedString s_ident, HdlType* s_hdl_type,
		bool s_is_array, Expression* scalar_val_or_arr_size);

	// Constant array constructors
	Symbol(SavedString s_ident, HdlType* s_hdl_type,
		ValueExprs&& s_value_exprs);


	// We really don't want copies of "Symbol"s.
	inline Symbol(const Symbol& to_copy) = delete;
	inline Symbol(Symbol&& to_move) = default;

	//virtual ~Symbol() = default;


	// We really don't want copies of "Symbol"s.
	inline Symbol& operator = (const Symbol& to_copy) = delete;
	inline Symbol& operator = (Symbol&& to_move) = default;

	// Used to determine if a "parameter" has a default value.
	bool has_default_value() const;

	inline bool is_array() const
	{
		return (_right_dim_expr != nullptr);
	}

	// Defined symbols *always* have a type.
	inline bool actually_exists() const
	{
		return (_hdl_type != nullptr);
	}


	GEN_GETTER_BY_VAL(ident)
	GEN_GETTER_BY_VAL(is_constant)
	GEN_GETTER_BY_VAL(hdl_type)

	GEN_GETTER_BY_VAL(right_dim_expr)
	GEN_GETTER_BY_CON_REF(value_exprs)

	GEN_GETTER_BY_CON_REF(parameter_vars)
	GEN_SETTER_BY_RVAL_REF(parameter_vars)


};

// "SymbolTable" isn't scoped because scoping information is stored in the
// "HdlScopeTable" class.
class SymbolTable : public IdentToPointerTable<Symbol>
{
public:		// functions
	SymbolTable() = default;
	virtual ~SymbolTable() = default;
};

} // namespace frost_hdl

#endif		// src_symbol_table_class_hpp
