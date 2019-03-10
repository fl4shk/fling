#include "frost_lhs_type_table_class.hpp"
#include "expression_classes.hpp"
#include "symbol_table_class.hpp"
#include "frost_function_table_class.hpp"

namespace frost_hdl
{

// Construct data for a non-portsplit composite "FrostLhsType"
FrostLhsType::ComponentData::ComponentData(bool s_is_packed,
	ParameterVars&& s_parameter_vars, CompositeVars&& s_non_portsplit_vars,
	CompositeFuncs&& s_funcs)
{
	_type = s_is_packed ? ComponentType::Packed : ComponentType::Unpacked;

	_parameter_vars = std::move(s_parameter_vars);
	_non_portsplit_vars = std::move(s_non_portsplit_vars);
	_funcs = std::move(s_funcs);

}

// Construct data for a portsplit composite "FrostLhsType"
FrostLhsType::ComponentData::ComponentData
	(ParameterVars&& s_parameter_vars,
	CompositeVars&& s_portsplit_input_vars,
	CompositeVars&& s_portsplit_output_vars,
	CompositeVars&& s_portsplit_inout_vars, CompositeFuncs&& s_funcs)
{
	_type = ComponentType::Portsplit;

	_parameter_vars = std::move(s_parameter_vars);
	_portsplit_input_vars = std::move(s_portsplit_input_vars);
	_portsplit_output_vars = std::move(s_portsplit_output_vars);
	_portsplit_inout_vars = std::move(s_portsplit_inout_vars);
	_funcs = std::move(s_funcs);
}

// Construct data for an enum "FrostLhsType"
FrostLhsType::ComponentData::ComponentData(EnumVals&& s_vals_of_enum)
{
	_type = ComponentType::Enum;
	_non_portsplit_vars = std::move(s_vals_of_enum);
}

//bool FrostLhsType::ComponentData::operator ==
//	(const ComponentData& other) const
//{
//	if (type() != other.type())
//	{
//		return false;
//	}
//
//
//	return true;
//}


//FrostLhsType::FrostLhsType(SavedString s_ident, bool s_is_signed)
//{
//	_ident = s_ident;
//	_is_signed = s_is_signed;
//	_left_dim_expr = nullptr;
//}
FrostLhsType::FrostLhsType(SavedString s_ident, bool s_is_signed,
	DimensionExpr s_left_dim_expr)
{
	_ident = s_ident;
	_is_signed = s_is_signed;
	_left_dim_expr = s_left_dim_expr;
}
FrostLhsType::FrostLhsType(SavedString s_ident,
	ComponentData&& s_component_data)
{
	_ident = s_ident;
	_is_signed = false;
	_component_data = std::move(s_component_data);
	_left_dim_expr = nullptr;
}

//bool FrostLhsType::operator == (const FrostLhsType& other) const
//{
//	switch (component_type())
//	{
//	case ComponentType::None:
//		return ((is_signed() == other.is_signed())
//			&& (left_dim() == other.left_dim()));
//		break;
//
//	case ComponentType::Enum:
//		return ((is_signed() == other.is_signed())
//			&& (left_dim() == other.left_dim())
//			&& (component_data() == other.component_data()));
//		break;
//
//	default:
//		return (component_data() == other.component_data());
//		break;
//	}
//}

size_t FrostLhsType::left_dim() const
{
	return (_left_dim_expr != nullptr)
		? static_cast<BigNum>(_left_dim_expr->value()).get_ui() : 1;
	//return (_left_dim_expr != nullptr)
	//	? _left_dim_expr->value().convert_to_unsigned_bignum() : 1;
}

} // namespace frost_hdl
