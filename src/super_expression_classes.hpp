#ifndef src_super_expression_classes_hpp
#define src_super_expression_classes_hpp

// src/super_expression_classes.hpp

#include "misc_includes.hpp"
#include "expression_class.hpp"
#include "has_src_code_pos_base_classes.hpp"

namespace frost_hdl
{


// Class for a superset of the "Expression" class that can be of *any*
// type (not just built-in types).
// "function"s and "task"s should take these as inputs, outputs, etc.
// Also, "function"s return these.
class SuperExpression : public HasSrcCodePosBase
{
public:		// types

protected:		// variables
	Symbol _value;

public:		// functions
	SuperExpression(const SrcCodePos& s_src_code_pos);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(SuperExpression);

	virtual ~SuperExpression();
};

} // namespace frost_hdl

#endif		// src_super_expression_classes_hpp
