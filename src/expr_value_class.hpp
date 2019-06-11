#ifndef src_expr_value_class_hpp
#define src_expr_value_class_hpp

// src/expr_value_class.hpp

#include "misc_includes.hpp"
#include "expr_num_class.hpp"

namespace frost_hdl
{

// Class for the value of an expression (or the value of a symbol)
class ExprValue final
{
public:		// types
	using NumVec = std::vector<ExprNum>;
	using ValVec = std::vector<ExprValue>;

private:		// variables
	string _ident;
	std::variant<ExprNum, NumVec, ValVec> _data;

public:		// functions
	//--------
	ExprValue();
	ExprValue(const string& s_ident);
	ExprValue(string&& s_ident);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ExprValue);
	~ExprValue();
	//--------

	//--------
	inline bool has_ident() const
	{
		return (_ident.size() > 0);
	}
	//--------

	//--------
	inline bool holds_expr_num() const
	{
		return std::holds_alternative<ExprNum>(_data);
	}
	inline bool holds_num_vec() const
	{
		return std::holds_alternative<NumVec>(_data);
	}
	inline bool holds_val_vec() const
	{
		return std::holds_alternative<ValVec>(_data);
	}
	//--------

	//--------
	inline void make_hold_expr_num()
	{
		_data = ExprNum();
	}
	inline void make_hold_num_vec()
	{
		_data = NumVec();
	}
	inline void make_hold_val_vec()
	{
		_data = ValVec();
	}
	//--------

	//--------
	inline ExprNum& expr_num()
	{
		return std::get<ExprNum>(_data);
	}
	inline const ExprNum& expr_num() const
	{
		return std::get<ExprNum>(_data);
	}
	//--------

	//--------
	inline NumVec& num_vec()
	{
		return std::get<NumVec>(_data);
	}
	inline const NumVec& num_vec() const
	{
		return std::get<NumVec>(_data);
	}
	//--------

	//--------
	inline ValVec& val_vec()
	{
		return std::get<ValVec>(_data);
	}
	inline const ValVec& val_vec() const
	{
		return std::get<ValVec>(_data);
	}
	//--------

	//--------
	GEN_GETTER_BY_CON_REF(ident)
	//--------
};


} //namespace frost_hdl

#endif		// src_expr_value_class_hpp
