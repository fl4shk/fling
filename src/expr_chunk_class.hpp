#ifndef src_expr_chunk_class_hpp
#define src_expr_chunk_class_hpp

// src/expr_chunk_class.hpp

#include "misc_includes.hpp"
#include "symbol_table_class.hpp"
//#include "expr_symbol_ref_class.hpp"
#include "expr_num_class.hpp"

namespace frost_hdl
{

class ExprSymbolRef;

// A chunk of an expression.
class ExprChunk
{
public:		// enums
	enum class Type : bool
	{
		ExprSymbolRef,
		ExprNum,
	};

private:		// variables
	Type __type = Type::ExprSymbolRef;

	std::variant<ExprSymbolRef*, ExprNum*> __val;

public:		// functions
	inline ExprChunk()
	{
		__type = Type::ExprSymbolRef;
		__val = static_cast<ExprSymbolRef*>(nullptr);
	}

	inline ExprChunk(const ExprChunk& to_copy) = default;

	inline ExprChunk& operator = (const ExprChunk& to_copy) = default;


	inline void set_expr_symbol_ref(ExprSymbolRef* n_val)
	{
		__type = Type::ExprSymbolRef;
		__val = n_val;
	}
	inline ExprSymbolRef* expr_symbol_ref() const
	{
		return std::get<ExprSymbolRef*>(__val);
	}

	inline void set_expr_num(ExprNum* n_val)
	{
		__type = Type::ExprNum;
		__val = n_val;
	}
	inline ExprNum* expr_num() const
	{
		return std::get<ExprNum*>(__val);
	}

	inline ExprNum* any_expr_num() const;

	inline bool operator < (const ExprChunk& to_cmp) const
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

	inline bool is_constant() const
	{
		return any_expr_num()->is_constant();
	}

	gen_getter_by_val(type);

private:		// functions
	//inline void* any_contained_pointer() const
	//{
	//	switch (type())
	//	{
	//	case Type::ExprSymbolRef:
	//		return expr_symbol_ref();
	//		break;

	//	case Type::ExprNum:
	//		return expr_num();
	//		break;
	//	}
	//}
};

} // namespace frost_hdl


#include "expr_symbol_ref_class.hpp"

namespace frost_hdl
{

inline ExprNum* ExprChunk::any_expr_num() const
{
	switch (type())
	{
	case Type::ExprSymbolRef:
		return expr_symbol_ref()->symbol()->expr_num();
		break;
	case Type::ExprNum:
		return expr_num();
		break;
	}

	// Eek!
	return nullptr;
}

} // namespace frost_hdl

#endif		// src_expr_chunk_class_hpp
