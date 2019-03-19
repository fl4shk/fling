#ifndef src_frost_full_type_table_class_hpp
#define src_frost_full_type_table_class_hpp

// src/frost_full_type_table_class.hpp

#include "misc_includes.hpp"
#include "frost_lhs_type_table_class.hpp"


namespace frost_hdl
{

// The full-fledged type of a "Symbol".  A "typedef" feaure will be
// facilitated with this as well.
class FrostFullType
{
private:		// variables
	// for typedefs
	SavedString _ident = nullptr;

	FrostLhsType* _frost_lhs_type = nullptr;
	Expression* _right_dim_expr = nullptr;

public:		// functions
	inline FrostFullType() = default;

	FrostFullType(FrostLhsType* s_frost_lhs_type);
	FrostFullType(FrostLhsType* s_frost_lhs_type,
		Expression* s_right_dim_expr);
	FrostFullType(SavedString s_ident,
		FrostLhsType* s_frost_lhs_type,
		Expression* s_right_dim_expr);

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostFullType);
	virtual ~FrostFullType() = default;

	bool operator == (const FrostFullType& other) const;

	inline bool is_array() const
	{
		return (_right_dim_expr != nullptr);
	}

	inline size_t left_dim() const
	{
		return _frost_lhs_type->left_dim();
	}
	size_t right_dim() const;

	GEN_GETTER_BY_VAL(ident)
	GEN_GETTER_BY_VAL(frost_lhs_type)
	GEN_GETTER_BY_VAL(right_dim_expr)
};

class FrostFullTypeTable : public IdentToPointerTable<FrostFullType>
{
public:		// functions
	FrostFullTypeTable() = default;
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostFullTypeTable);
	virtual ~FrostFullTypeTable() = default;
};

} // namespace frost_hdl


#endif		// src_frost_full_type_table_class_hpp
