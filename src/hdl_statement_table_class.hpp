#ifndef src_hdl_statement_table_class_hpp
#define src_hdl_statement_table_class_hpp

// src/hdl_statement_table_class.hpp

#include "misc_includes.hpp"
#include "scoped_table_classes.hpp"
#include "symbol_table_class.hpp"
#include "hdl_type_table_class.hpp"

namespace frost_hdl
{

// Base class for a statement (primarily for the insides of an "HdlModule",
// but also intended for use inside of an "HdlFunction")
class HdlStatement
{
protected:		// variables
	// Component "Expression"s.
	std::vector<Expression*> _expressions;

public:		// functions
	HdlStatement() = default;

	inline HdlStatement(const HdlStatement& to_copy) = delete;
	inline HdlStatement(HdlStatement&& to_move) = default;


	virtual ~HdlStatement() = default;

	inline HdlStatement& operator = (const HdlStatement& to_copy) = delete;
	inline HdlStatement& operator = (HdlStatement&& to_move) = default;
};

class HdlStatementTable : public ScopedUnnamedTable<HdlStatement>
{
public:		// functions
	HdlStatementTable() = default;
	virtual ~HdlStatementTable() = default;
};


} // namespace frost_hdl


#endif		// src_hdl_statement_table_class_hpp
