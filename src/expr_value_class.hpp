#ifndef src_expr_value_class_hpp
#define src_expr_value_class_hpp

// src/expr_value_class.hpp

#include "misc_includes.hpp"
#include "expr_num_class.hpp"
#include "has_src_code_chunk_base_classes.hpp"

namespace frost_hdl
{

// Class for values
class ExprValue final : HasSrcCodeChunkAndIdentBase
{
public:		// types
	typedef std::vector<ExprNum> NumVec;

	// Use a linked list here to make removal faster
	typedef CircLinkedList<ExprValue> ValList;

private:		// variables
	std::variant<ExprNum, NumVec, ValList> _data;

public:		// functions
	ExprValue();

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(ExprValue);

	~ExprValue();

	inline bool holds_expr_num() const
	{
		return std::holds_alternative<ExprNum>(_data);
	}
	inline bool holds_num_vec() const
	{
		return std::holds_alternative<NumVec>(_data);
	}
	inline bool holds_val_list() const
	{
		return std::holds_alternative<ValList>(_data);
	}

	inline void make_hold_expr_num()
	{
		_data = ExprNum();
	}
	inline void make_hold_num_vec()
	{
		_data = NumVec();
	}
	inline void make_hold_val_list()
	{
		_data = ValList();
	}

	inline ExprNum& expr_num()
	{
		return std::get<ExprNum>(_data);
	}
	inline const ExprNum& expr_num() const
	{
		return std::get<ExprNum>(_data);
	}

	inline NumVec& num_vec()
	{
		return std::get<NumVec>(_data);
	}
	inline const NumVec& num_vec() const
	{
		return std::get<NumVec>(_data);
	}

	inline ValList& val_list()
	{
		return std::get<ValList>(_data);
	}
	inline const ValList& val_list() const
	{
		return std::get<ValList>(_data);
	}
};


} //namespace frost_hdl

#endif		// src_expr_value_class_hpp
