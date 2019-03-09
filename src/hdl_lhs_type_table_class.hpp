#ifndef src_hdl_lhs_type_table_class_hpp
#define src_hdl_lhs_type_table_class_hpp

// src/hdl_lhs_type_table_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "general_allocator_class.hpp"
#include "ident_table_classes.hpp"

namespace frost_hdl
{

class Expression;
class Symbol;
class HdlFunction;

// The left-hand side of a type, i.e. everything about a type except for
// array dimensions.  
class HdlLhsType : public HasSourceCodePosBase
{
public:		// types
	typedef Expression* DimensionExpr;


	//typedef std::vector<Symbol*> OrderedPointerList<Symbol>;
	//typedef std::vector<Symbol*> CompositeVars;
	//typedef OrderedIdentToPointerTable<Symbol> ParameterVars;
	typedef OrderedIdentToPointerTable<Symbol> CompositeVars;
	typedef CompositeVars EnumVals;
	typedef OrderedIdentToPointerTable<HdlFunction> CompositeFuncs;

	// Stuff for custom types, not counting those that are arrays.
	// If custom types that are arrays are supported (most likely via some
	// "HdlLhsTypedef" functionality), another data structure will be
	// necessary within the compiler, and it will be outside the realm of
	// "HdlLhsType".
	class ComponentData
	{
	private:		// variables
		bool _is_packed = false;
		bool _is_enum = false;
		ParameterVars _parameter_vars;

		// Both enum values and composite variables are stored here.
		CompositeVars _composite_vars;

		CompositeFuncs _composite_funcs;

	public:		// functions
		ComponentData() = default;

		// Construct data for a composite "HdlLhsType"
		ComponentData(bool s_is_packed,
			ParameterVars&& s_parameter_vars,
			CompositeVars&& s_composite_vars,
			CompositeFuncs&& s_composite_funcs);

		// Construct data for an enum "HdlLhsType"
		ComponentData(EnumVals&& s_vals_of_enum);

		// We don't want copies of "HdlLhsType::ComponentData".
		GEN_CM_CONSTRUCTORS_AND_ASSIGN(ComponentData, delete, default);

		virtual ~ComponentData() = default;


		inline const EnumVals& vals_of_enum() const
		{
			return _composite_vars;
		}

		GEN_GETTER_BY_VAL(is_packed)
		GEN_GETTER_BY_VAL(is_enum)
		GEN_GETTER_BY_CON_REF(parameter_vars)
		GEN_GETTER_BY_CON_REF(composite_vars)
		GEN_GETTER_BY_CON_REF(composite_funcs)
	};


private:		// variables
	SavedString _ident = nullptr;

	bool _is_signed = false;


	ComponentData _component_data;

	// There is only one set of dimensions left of the symbol's identifer.
	DimensionExpr _left_dim_expr = nullptr;


public:		// functions
	HdlLhsType() = default;
	//HdlLhsType(SavedString s_ident, bool s_is_signed);
	HdlLhsType(SavedString s_ident, bool s_is_signed,
		DimensionExpr s_left_dim_expr);
	HdlLhsType(SavedString s_ident, ComponentData&& s_component_data);

	// We really don't want copies of "HdlLhsType"s.
	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlLhsType, delete, default);
	virtual ~HdlLhsType() = default;

	//bool operator == (const HdlLhsType& other) const;


	inline bool can_be_parameterized() const
	{
		return (component_data().parameter_vars().size() > 0);
	}

	inline bool is_enum() const
	{
		return component_data().is_enum();
	}

	// Whether or not this "HdlLhsType" represents "struct" or "class".
	// If "is_composite()" is true, then "_left_dim_expr" and "_is_signed"
	// are not used.
	inline bool is_composite() const
	{
		//return ((component_data().composite_vars().size() > 0)
		//	|| (component_data().composite_funcs().size() > 0));
		return ((component_data().parameter_vars().size() > 0)
			|| (component_data().composite_vars().size() > 0)
			|| (component_data().composite_funcs().size() > 0));
	}

	inline bool is_packed_composite() const
	{
		return (is_composite() && component_data().is_packed());
	}
	inline bool is_unpacked_composite() const
	{
		return (is_composite() && (!component_data().is_packed()));
	}

	inline bool is_builtin() const
	{
		return ((!is_composite()) && (!is_enum()));
	}

	size_t left_dim() const;

	//// We don't need an "is_vector()" member function.
	//inline bool is_vector() const
	//{
	//	//return (_left_dim_expr != nullptr)
	//	//	&& static_cast<BigNum>(_left_dim_expr->values()).get_ui();
	//}


	GEN_GETTER_BY_VAL(ident)
	GEN_GETTER_BY_VAL(is_signed)



	GEN_GETTER_BY_CON_REF(component_data)

	//GEN_GETTER_AND_SETTER_BY_VAL(left_dim_expr)
	GEN_GETTER_BY_VAL(left_dim_expr)
};


// "HdlLhsTypeTable" isn't scoped because scoping information is stored
// in the "HdlScopeTable" class.
class HdlLhsTypeTable : public IdentToPointerTable<HdlLhsType>
{
public:		// functions
	HdlLhsTypeTable() = default;
	GEN_CM_CONSTRUCTORS_AND_ASSIGN(HdlLhsTypeTable, delete, default);
	virtual ~HdlLhsTypeTable() = default;
};


} // namespace frost_hdl

#endif		// src_hdl_lhs_type_table_class_hpp
