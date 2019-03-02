#ifndef src_hdl_type_table_class_hpp
#define src_hdl_type_table_class_hpp

// src/hdl_type_table_class.hpp

#include "misc_includes.hpp"
#include "general_allocator_class.hpp"
#include "ident_table_classes.hpp"

namespace frost_hdl
{

// The type of a "Symbol".  Used for 
class HdlType
{
public:		// typedefs
	typedef std::vector<Expression*> Dimensions;

protected:		// variables
	// "_actually_exists" needs to be set to true before this "HdlType" is
	// permitted to be used.
	bool _actually_exists = false;

	//// "struct" or "class"
	//bool _is_composite = false;
	bool _is_signed = false;

	// "_right_dim" affects whether or not this "HdlType" is an array.
	Dimensions _left_dim, _right_dim;

public:		// functions
	HdlType() = default;
	HdlType(bool s_is_signed);

	// We really don't want copies of "HdlType"s.
	inline HdlType(const HdlType& to_copy) = delete;
	inline HdlType(HdlType&& to_move) = default;

	virtual ~HdlType() = default;

	// We really don't want copies of "HdlType"s.
	inline HdlType& operator = (const HdlType& to_copy) = delete;
	inline HdlType& operator = (HdlType&& to_move) = default;

	GEN_GETTER_AND_SETTER_BY_VAL(actually_exists)
	GEN_GETTER_AND_SETTER_BY_VAL(is_signed)

	GEN_GETTER_BY_CON_REF(left_dim)
	GEN_SETTER_BY_RVAL_REF(left_dim)
	GEN_GETTER_BY_CON_REF(right_dim)
	GEN_SETTER_BY_RVAL_REF(right_dim)
};


// "HdlTypeTable" isn't scoped because scoping information is stored in the
// "StatementTable" class.
class HdlTypeTable
{
public:		/// typedefs
	typedef std::map<HdlType::Dimensions, HdlType*> InnerTable;

protected:		// variables
	//IdentTable<HdlType>
public:		// functions
	HdlTypeTable() = default;
	virtual ~HdlTypeTable() = default;
};

} // namespace frost_hdl

#endif		// src_hdl_type_table_class_hpp
