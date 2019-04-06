#include "frost_lhs_type_class.hpp"
#include "expression_classes.hpp"
#include "symbol_class.hpp"
#include "frost_function_class.hpp"

namespace frost_hdl
{

// Construct data for a composite "FrostLhsType"
FrostLhsType::ComponentData::ComponentData(bool s_is_packed,
	SymbolTable&& s_parameter_symbol_table,
	CompositeVars&& s_composite_vars, CompositeFuncs&& s_funcs)
{
	_type = s_is_packed ? ComponentType::Packed : ComponentType::Unpacked;

	_parameter_symbol_table = std::move(s_parameter_symbol_table);
	_can_be_parameterized = true;
	_composite_vars = std::move(s_composite_vars);
	_funcs = std::move(s_funcs);

}


// Construct data for an enum "FrostLhsType"
FrostLhsType::ComponentData::ComponentData(EnumVals&& s_vals_of_enum)
{
	_type = ComponentType::Enum;
	_composite_vars = std::move(s_vals_of_enum);
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
FrostLhsType::FrostLhsType(const SrcCodePos& s_src_code_pos,
	SavedString s_ident, bool s_is_signed, DimensionExpr s_left_dim_expr)
	: HasSrcCodePosAndIdentBase(s_src_code_pos, s_ident)
{
	_is_signed = s_is_signed;
	_left_dim_expr = s_left_dim_expr;
}
FrostLhsType::FrostLhsType(const SrcCodePos& s_src_code_pos,
	SavedString s_ident, ComponentData&& s_component_data)
	: HasSrcCodePosAndIdentBase(s_src_code_pos, s_ident)
{
	_is_signed = false;
	_component_data = std::move(s_component_data);
	_left_dim_expr = nullptr;
}
SavedString FrostLhsType::construct_initial_builtin_type_ident
	(bool s_is_signed, Expression* s_left_dim_expr)
{
	std::string s_ident = "logic ";

	if (s_is_signed)
	{
		s_ident += "signed ";
	}

	if (s_left_dim_expr != nullptr)
	{
		// Need some way to make the name unique!  Also, how do I handle
		// cases where I don't know the values of named constants yet?
		s_ident += *construct_initial_type_ident_from_expr
			(dup_str(s_ident), s_left_dim_expr);
	}

	return dup_str(s_ident);
}

bool FrostLhsType::is_same_builtin_strict_signedness
	(const FrostLhsType& other) const
{
	return (is_same_builtin_ignore_signedness(other)
		&& (is_signed() == other.is_signed()));
}
bool FrostLhsType::is_same_builtin_ignore_signedness
	(const FrostLhsType& other) const
{
	return (is_builtin() && other.is_builtin()
		&& (left_dim() == other.left_dim()));
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
