#include "pseudo_func_call_range_class.hpp"

namespace frost_hdl
{

size_t PseudoFuncCallRange::size() const
{
	if (is_ascending())
	{
		return (BigNum(static_cast<BigNum>(right()->value())
			- static_cast<BigNum>(left()->value()) + BigNum(1))).get_ui();
	}
	else // if (is_descending())
	{
		return (BigNum(static_cast<BigNum>(left()->value())
			- static_cast<BigNum>(right()->value()) + BigNum(1))).get_ui();
	}
}

} // namespace frost_hdl
