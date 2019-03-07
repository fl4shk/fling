#ifndef src_hdl_statement_table_class_hpp
#define src_hdl_statement_table_class_hpp

// src/hdl_statement_table_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "scoped_table_classes.hpp"
#include "symbol_table_class.hpp"
#include "hdl_lhs_type_table_class.hpp"

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

	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlStatement, delete, default);


	virtual ~HdlStatement() = default;


	// Only some classes derived from "HdlStatement" need for this to
	// sometimes return a message other than "nullptr".
	// The returned message will be used as (part of?) an error message if
	// it is not a "nullptr".
	virtual SavedString is_valid() const;
};

class HdlStatementTable : public ScopedUnnamedTable<HdlStatement>
{
public:		// functions
	HdlStatementTable() = default;
	virtual ~HdlStatementTable() = default;
};


} // namespace frost_hdl


#endif		// src_hdl_statement_table_class_hpp
