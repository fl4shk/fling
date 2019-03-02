#include "hdl_type_table_class.hpp"
#include "expression_classes.hpp"
#include "symbol_table_class.hpp"
#include "hdl_function_table_class.hpp"

namespace frost_hdl
{

HdlType::ComponentData::ComponentData(bool s_is_packed,
	ParameterVars&& s_parameter_vars, CompositeVars&& s_composite_vars,
	CompositeFuncs&& s_composite_funcs)
	: _is_packed(s_is_packed), _is_enum(false),
	_parameter_vars(std::move(s_parameter_vars)),
	_composite_vars(std::move(s_composite_vars)),
	_composite_funcs(std::move(s_composite_funcs))
{
}

void HdlType::ComponentData::init_as_enum(EnumVals&& s_vals_of_enum)
{
	_is_packed = false;
	_is_enum = true;
	_composite_vars = std::move(s_vals_of_enum);
}

HdlType::HdlType(SavedString s_ident, bool s_is_signed)
{
	_ident = s_ident;
	_is_signed = s_is_signed;
	_actually_exists = false;
	_left_dim_expr = nullptr;
}
HdlType::HdlType(SavedString s_ident, bool s_is_signed,
	Dimension s_left_dim_expr)
{
	_ident = s_ident;
	_is_signed = s_is_signed;
	_actually_exists = false;
	_left_dim_expr = s_left_dim_expr;
}
HdlType::HdlType(SavedString s_ident, ComponentData&& s_component_data)
{
	_ident = s_ident;
	_is_signed = false;
	_actually_exists = false;
	_component_data = std::move(s_component_data);
	_left_dim_expr = nullptr;
}

size_t HdlType::left_dim() const
{
	return (_left_dim_expr != nullptr)
		? BigNum(_left_dim_expr->value()).get_ui() : 1;
}

} // namespace frost_hdl