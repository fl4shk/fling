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
	typedef std::vector<ExprNum> NumVec;
	typedef std::vector<ExprValue> ValVec;

private:		// variables
	std::variant<ExprNum, NumVec, ValVec> _data;

public:		// functions
	//--------
	ExprValue();

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(ExprValue);

	~ExprValue();
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
};


} //namespace frost_hdl

#endif		// src_expr_value_class_hpp
