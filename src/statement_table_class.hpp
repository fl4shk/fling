#ifndef src_statement_table_class_hpp
#define src_statement_table_class_hpp

// src/statement_table_class.hpp

#include "misc_includes.hpp"
#include "scoped_table_classes.hpp"
#include "symbol_table_class.hpp"
#include "hdl_type_table_class.hpp"

namespace frost_hdl
{

// Base class for a statement (primarily for the insides of an "HdlModule",
// but also includes the insides of an "HdlFunction")
class Statement
{
protected:		// variables

public:		// functions
	Statement() = default;

	inline Statement(const Statement& to_copy) = delete;
	inline Statement(Statement&& to_move) = default;


	virtual ~Statement() = default;

	inline Statement& operator = (const Statement& to_copy) = delete;
	inline Statement& operator = (Statement&& to_move) = default;


};

class StatementTable : public ScopedUnnamedTable<Statement>
{
public:		// functions
	StatementTable() = default;
	virtual ~StatementTable() = default;
};


} // namespace frost_hdl


#endif		// src_statement_table_class_hpp
