#include "expr_chunk_class.hpp"

namespace frost_hdl
{

inline bool ExprChunk::operator < (const ExprChunk& to_cmp) const
{
	const u32 temp = ((static_cast<u32>(type()) << 1)
		| (static_cast<u32>(to_cmp.type())));

	switch (temp)
	{
		case 0b00:
			return (expr_symbol_ref() < to_cmp.expr_symbol_ref());
			break;

		case 0b01:
			return true;

		case 0b10:
			return false;

		case 0b11:
			return (expr_num() < to_cmp.expr_num());
			break;
	}

	// Eek!
	return false;
}

} // namespace frost_hdl
