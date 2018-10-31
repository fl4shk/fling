#ifndef src__slash__expression_class_hpp
#define src__slash__expression_class_hpp

// src/expression_class.hpp

#include "misc_includes.hpp"
#include "symbol_table_classes.hpp"

namespace frost_hdl
{

class Expression
{
public:		// enums
	enum class Type : bool
	{
		Symbol,
		BigNum,
	};

private:		// variables
	Type __type = Type::Symbol;

	std::variant<Symbol*, BigNum*> __val;

public:		// functions
	inline Expression()
	{
		__type = Type::Symbol;
		__val = static_cast<Symbol*>(nullptr);
	}


	inline void set_sym_val(Symbol* n_val)
	{
		__type = Type::Symbol;
		__val = n_val;
	}
	inline Symbol* sym_val() const
	{
		return std::get<Symbol*>(__val);
	}

	inline void set_big_num_val(BigNum* n_val)
	{
		__type = Type::BigNum;
		__val = n_val;
	}
	inline BigNum* big_num_val() const
	{
		return std::get<BigNum*>(__val);
	}

	gen_getter_by_val(type);
};

} // namespace frost_hdl


#endif		// src__slash__expression_class_hpp
