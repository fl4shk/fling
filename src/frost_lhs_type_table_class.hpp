#ifndef src_frost_lhs_type_table_class_hpp
#define src_frost_lhs_type_table_class_hpp

// src/frost_lhs_type_table_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "general_allocator_class.hpp"
#include "ident_table_classes.hpp"

namespace frost_hdl
{

class Expression;
class Symbol;
class FrostFunction;

// The left-hand side of a type, i.e. everything about a type except for
// array dimensions.  
class FrostLhsType
{
public:		// types
	typedef Expression* DimensionExpr;


	//typedef std::vector<Symbol*> OrderedPointerList<Symbol>;
	//typedef std::vector<Symbol*> CompositeVars;
	//typedef OrderedIdentToPointerTable<Symbol> ParameterVars;
	typedef OrderedIdentToPointerTable<Symbol> CompositeVars;
	typedef CompositeVars EnumVals;
	typedef OrderedIdentToPointerTable<FrostFunction> CompositeFuncs;

	enum class ComponentType
	{
		None,
		Enum,
		Packed,
		Unpacked,
		Portsplit,
	};

	// Stuff for custom types, not counting those that are arrays.
	// If custom types that are arrays are supported (most likely via some
	// "FrostLhsTypedef" functionality), another data structure will be
	// necessary within the compiler, and it will be outside the realm of
	// "FrostLhsType".
	class ComponentData
	{
	private:		// variables
		ComponentType _type = ComponentType::None;
		ParameterVars _parameter_vars;

		CompositeVars _portsplit_input_vars, _portsplit_output_vars,
			_portsplit_inout_vars;

		// Both enum values and non-portsplit composite variables are
		// stored here.
		CompositeVars _non_portsplit_vars;


		CompositeFuncs _funcs;

	public:		// functions
		ComponentData() = default;

		// Construct data for a non-portsplit composite "FrostLhsType"
		ComponentData(bool s_is_packed,
			ParameterVars&& s_parameter_vars,
			CompositeVars&& s_non_portsplit_vars,
			CompositeFuncs&& s_funcs);

		// Construct data for a portsplit composite "FrostLhsType"
		ComponentData(ParameterVars&& s_parameter_vars,
			CompositeVars&& s_portsplit_input_vars,
			CompositeVars&& s_portsplit_output_vars,
			CompositeVars&& s_portsplit_inout_vars,
			CompositeFuncs&& s_funcs);

		// Construct data for an enum "FrostLhsType"
		ComponentData(EnumVals&& s_vals_of_enum);

		// We don't want copies of "FrostLhsType::ComponentData".
		GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(ComponentData);

		virtual ~ComponentData() = default;

		//bool operator == (const ComponentData& other) const;


		inline const EnumVals& vals_of_enum() const
		{
			return _non_portsplit_vars;
		}

		GEN_GETTER_BY_CON_REF(type)

		GEN_GETTER_BY_CON_REF(parameter_vars)

		GEN_GETTER_BY_CON_REF(portsplit_input_vars)
		GEN_GETTER_BY_CON_REF(portsplit_output_vars)
		GEN_GETTER_BY_CON_REF(portsplit_inout_vars)

		GEN_GETTER_BY_CON_REF(non_portsplit_vars)
		GEN_GETTER_BY_CON_REF(funcs)
	};


private:		// variables
	SavedString _ident = nullptr;

	bool _is_signed = false;


	ComponentData _component_data;

	// There is only one set of dimensions left of the symbol's identifer.
	DimensionExpr _left_dim_expr = nullptr;


public:		// functions
	FrostLhsType() = default;
	//FrostLhsType(SavedString s_ident, bool s_is_signed);
	FrostLhsType(SavedString s_ident, bool s_is_signed,
		DimensionExpr s_left_dim_expr);
	FrostLhsType(SavedString s_ident, ComponentData&& s_component_data);

	// We really don't want copies of "FrostLhsType"s.
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostLhsType);
	virtual ~FrostLhsType() = default;

	//bool operator == (const FrostLhsType& other) const;


	inline bool can_be_parameterized() const
	{
		return (component_data().parameter_vars().size() > 0);
	}

	inline ComponentType component_type() const
	{
		return _component_data.type();
	}

	inline bool is_builtin() const
	{
		return (component_type() == ComponentType::None);
	}
	inline bool is_enum() const
	{
		return (component_type() == ComponentType::Enum);
	}
	inline bool is_packed_composite() const
	{
		return (component_type() == ComponentType::Packed);
	}
	inline bool is_unpacked_composite() const
	{
		return (component_type() == ComponentType::Unpacked);
	}
	inline bool is_portsplit_composite() const
	{
		return (component_type() == ComponentType::Portsplit);
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


// "FrostLhsTypeTable" isn't scoped scoped types are part of other
// "...Table" classes, and also part of "Compiler" for global scope.
class FrostLhsTypeTable : public IdentToPointerTable<FrostLhsType>
{
public:		// functions
	FrostLhsTypeTable() = default;
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostLhsTypeTable);
	virtual ~FrostLhsTypeTable() = default;
};


} // namespace frost_hdl

#endif		// src_frost_lhs_type_table_class_hpp
