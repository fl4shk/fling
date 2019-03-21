#ifndef src_symbol_table_class_hpp
#define src_symbol_table_class_hpp

// src/symbol_table_class.hpp

#include "misc_includes.hpp"
#include "general_allocator_class.hpp"
#include "ident_table_classes.hpp"
//#include "expression_classes.hpp"
//#include "frost_full_type_table_class.hpp"
//#include "misc_types.hpp"
#include "src_code_pos_class.hpp"
#include "frost_statement_table_class.hpp"


namespace frost_hdl
{

class FrostFullType;
class Expression;

// This class represents variables and named constants, including named
// constants used as parameters to a parameterized... thing (such as an
// "FrostDeclModule" or a composite type).
//
// An instantiation of a "parameter"ized construct will have a different
// set of "Symbol"s for its "parameter"s than the set of "Symbol"s used for
// the construct's definition.
class Symbol
{
public:		// types
	typedef std::vector<Expression*> ValueExprs;

	//typedef std::vector<Symbol*> OrderedIdentToPointerTable<Symbol>;

	enum class PortType
	{
		// "parameter"s, Local vars
		NonPort,

		// Ports
		Input,
		Output,
		Inout,
		//Splitvar,
	};

private:		// variables
	SrcCodePos _src_code_pos;

	SavedString _ident = nullptr;

	PortType _port_type = PortType::NonPort;

	// Whether or not this symbol is a named constant.
	bool _is_constant = false;

	FrostFullType* _frost_full_type = nullptr;


	// Compile-time values are stored here for both scalars and arrays.
	// For parameters, store a "nullptr" in *any* of the elements of this
	// "ValueExprs" to indicate that this parameter *does not* have a
	// default value.
	ValueExprs _value_exprs;

	// Actual parameter values for this "Symbol"'s "FrostFullType"
	ListVars _parameter_vars;


	// "_init_block_context" is part of what determines whether or not this
	// "Symbol" becomes a wire in the generated HDL.
	FrostStatementTable::Node* _init_block_context = nullptr;

	// Where is this symbol driven?  The allowed options are
	// "FrostStmtContAssign", "FrostStmtBehavBlockAlwaysComb", and
	// "FrostStmtBehavBlockAlwaysSeq".
	FrostStatementTable::Node* _driver_block_context = nullptr;


public:		// functions
	Symbol() = default;

	// Non-constant scalar or array constructor
	Symbol(const SrcCodePos& s_src_code_pos, SavedString s_ident,
		PortType s_port_type, FrostFullType* s_frost_full_type);

	// Constant scalar or array constructor
	Symbol(const SrcCodePos& s_src_code_pos, SavedString s_ident,
		PortType s_port_type, FrostFullType* s_frost_full_type,
		ValueExprs&& s_value_exprs);


	// We really don't want copies of "Symbol"s.
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(Symbol);
	virtual ~Symbol() = default;

	// Used to determine if a "parameter" has a default value.
	bool has_default_value() const;


	//// Defined symbols *always* have a type, so we don't need to store
	//// anything extra to figure out the type of a symbol.
	//inline bool actually_exists() const
	//{
	//	return (_frost_full_type != nullptr);
	//}

	bool becomes_wire() const;
	inline bool becomes_reg() const
	{
		return (!becomes_wire());
	}


	GEN_GETTER_BY_CON_REF(src_code_pos)
	GEN_GETTER_BY_VAL(ident)
	GEN_GETTER_BY_VAL(port_type)
	GEN_GETTER_BY_VAL(is_constant)
	GEN_GETTER_BY_VAL(frost_full_type)

	GEN_GETTER_BY_CON_REF(value_exprs)

	GEN_GETTER_BY_CON_REF(parameter_vars)
	GEN_SETTER_BY_RVAL_REF(parameter_vars)

	GEN_GETTER_AND_SETTER_BY_VAL(init_block_context)
	GEN_GETTER_AND_SETTER_BY_VAL(driver_block_context)

};

// "SymbolTable" isn't scoped because scoping information is stored in the
// "FrostScopeTable" class.
class SymbolTable : public IdentToPointerTable<Symbol>
{
public:		// functions
	SymbolTable() = default;
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(SymbolTable);
	virtual ~SymbolTable() = default;
};

} // namespace frost_hdl

#endif		// src_symbol_table_class_hpp
