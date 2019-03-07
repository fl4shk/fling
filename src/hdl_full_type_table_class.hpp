#ifndef src_hdl_full_type_table_class_hpp
#define src_hdl_full_type_table_class_hpp

// src/hdl_full_type_table_class.hpp

#include "misc_includes.hpp"
#include "hdl_lhs_type_table_class.hpp"


namespace frost_hdl
{

// The full-fledged type of a "Symbol".  A "typedef" feaure will be
// facilitated with this as well.
class HdlFullType : public HasSourceCodePosBase
{
private:		// variables
	// for typedefs
	SavedString _ident = nullptr;

	HdlLhsType* _hdl_lhs_type = nullptr;
	Expression* _right_dim_expr = nullptr;

public:		// functions
	inline HdlFullType() = default;

	HdlFullType(SavedString s_ident, HdlLhsType* s_hdl_lhs_type,
		Expression* s_right_dim_expr);

	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlFullType, delete, default);
	virtual ~HdlFullType() = default;

	bool operator == (const HdlFullType& other) const;

	inline bool is_array() const
	{
		return (_right_dim_expr != nullptr);
	}

	inline size_t left_dim() const
	{
		return _hdl_lhs_type->left_dim();
	}
	size_t right_dim() const;

	GEN_GETTER_BY_VAL(ident)
	GEN_GETTER_BY_VAL(hdl_lhs_type)
	GEN_GETTER_BY_VAL(right_dim_expr)
};

class HdlFullTypeTable : public IdentToPointerTable<HdlFullType>
{
public:		// functions
	HdlFullTypeTable() = default;
	virtual ~HdlFullTypeTable() = default;
};

} // namespace frost_hdl


#endif		// src_hdl_full_type_table_class_hpp
