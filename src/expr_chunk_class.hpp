#ifndef src__slash__expr_chunk_class_hpp
#define src__slash__expr_chunk_class_hpp

// src/expr_chunk_class.hpp

#include "misc_includes.hpp"
#include "symbol_table_classes.hpp"
#include "expr_num_class.hpp"

namespace frost_hdl
{

// A chunk of an expression.
class ExprChunk
{
public:		// enums
	enum class Type : bool
	{
		Symbol,
		ExprNum,
	};

private:		// variables
	Type __type = Type::Symbol;

	std::variant<Symbol*, ExprNum*> __val;

public:		// functions
	inline ExprChunk()
	{
		__type = Type::Symbol;
		__val = static_cast<Symbol*>(nullptr);
	}

	// Eh, these can just be used for 
	inline ExprChunk(const ExprChunk& to_copy) = default;

	inline ExprChunk& operator = (const ExprChunk& to_copy) = default;


	inline void set_symbol(Symbol* n_val)
	{
		__type = Type::Symbol;
		__val = n_val;
	}
	inline Symbol* symbol() const
	{
		return std::get<Symbol*>(__val);
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

	inline bool is_constant() const
	{
		switch (type())
		{
			case Type::Symbol:
				return symbol()->is_constant();
				break;
			case Type::ExprNum:
				return expr_num()->is_constant();
				break;
		}

		// Eek!
		return false;
	}

	gen_getter_by_val(type);
};

} // namespace frost_hdl


#endif		// src__slash__expr_chunk_class_hpp
