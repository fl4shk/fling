#ifndef src_frost_lhs_type_table_class_hpp
#define src_frost_lhs_type_table_class_hpp

// src/frost_lhs_type_table_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "src_code_pos_class.hpp"
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
	//typedef OrderedIdentToPointerTable<Symbol> ListVars;
	typedef OrderedIdentToPointerTable<Symbol> CompositeVars;
	typedef CompositeVars EnumVals;
	typedef OrderedIdentToPointerTable<FrostFunction> CompositeFuncs;

	enum class ComponentType
	{
		None,
		Enum,
		Packed,
		Unpacked,
		Splitvar,
	};

	enum class CompositeType
	{
		CompositePacked,
		CompositeUnpacked,
		CompositeSplitvar,
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
		ListVars _parameter_vars;

		// Both enum values and composite variables are stored here.
		CompositeVars _composite_vars;


		CompositeFuncs _funcs;

	public:		// functions
		ComponentData() = default;

		// Construct data for a composite "FrostLhsType"
		ComponentData(CompositeType s_composite_type,
			ListVars&& s_parameter_vars, CompositeVars&& s_composite_vars,
			CompositeFuncs&& s_funcs);


		// Construct data for an enum "FrostLhsType"
		ComponentData(EnumVals&& s_vals_of_enum);

		// We don't want copies of "FrostLhsType::ComponentData".
		GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(ComponentData);

		virtual ~ComponentData() = default;

		//bool operator == (const ComponentData& other) const;


		inline const EnumVals& vals_of_enum() const
		{
			return _composite_vars;
		}

		GEN_GETTER_BY_CON_REF(type)

		GEN_GETTER_BY_CON_REF(parameter_vars)


		GEN_GETTER_BY_CON_REF(composite_vars)
		GEN_GETTER_BY_CON_REF(funcs)
	};


private:		// variables
	SrcCodePos _src_code_pos;

	SavedString _ident = nullptr;

	bool _is_signed = false;


	ComponentData _component_data;

	// There is only one set of dimensions left of the symbol's identifer.
	DimensionExpr _left_dim_expr = nullptr;


public:		// functions
	FrostLhsType() = default;
	//FrostLhsType(SavedString s_ident, bool s_is_signed);
	FrostLhsType(const SrcCodePos& s_src_code_pos, SavedString s_ident,
		bool s_is_signed, DimensionExpr s_left_dim_expr);
	FrostLhsType(const SrcCodePos& s_src_code_pos, SavedString s_ident,
		ComponentData&& s_component_data);

	// We really don't want copies of "FrostLhsType"s.
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(FrostLhsType);
	virtual ~FrostLhsType() = default;

	//bool operator == (const FrostLhsType& other) const;

	bool is_same_builtin_strict_signedness(const FrostLhsType& other)
		const;
	bool is_same_builtin_ignore_signedness(const FrostLhsType& other)
		const;



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
	inline bool is_splitvar_composite() const
	{
		return (component_type() == ComponentType::Splitvar);
	}

	size_t left_dim() const;

	inline bool is_vector() const
	{
		return (_left_dim_expr != nullptr);
	}


	GEN_GETTER_BY_CON_REF(src_code_pos)

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
