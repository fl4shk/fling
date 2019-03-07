#ifndef src_general_allocator_class_hpp
#define src_general_allocator_class_hpp

// src/general_allocator_class.hpp

#include "misc_includes.hpp"


#include <map>

namespace frost_hdl
{
class Expression;
class Symbol;
class HdlLhsType;
class HdlFullType;
class HdlFunction;
//class HdlScope;

typedef std::string RawSavedString;
typedef const RawSavedString* SavedString;

typedef std::vector<bool> RawExprNumData;
typedef const RawExprNumData* ExprNumData;


class GeneralAllocator
{
private:		// static variables
	static std::map<RawSavedString, std::unique_ptr<const RawSavedString>>
		_str_pool;
	static std::map<RawExprNumData, std::unique_ptr<const RawExprNumData>>
		_expr_num_data_pool;
	static std::vector<std::unique_ptr<Expression>> _expr_pool;
	static std::vector<std::unique_ptr<Symbol>> _symbol_pool;
	static std::vector<std::unique_ptr<HdlLhsType>> _hdl_lhs_type_pool;
	static std::vector<std::unique_ptr<HdlFullType>> _hdl_full_type_pool;
	static std::vector<std::unique_ptr<HdlFunction>> _hdl_function_pool;

public:		// static functions
	static SavedString dup_str(const RawSavedString& to_dup);
	static SavedString dup_str(RawSavedString&& to_dup);
	static ExprNumData dup_expr_num_data(const RawExprNumData& to_dup); 
	static ExprNumData dup_expr_num_data(RawExprNumData&& to_dup); 

	template<typename ExprType>
	static inline Expression* save_expr(ExprType&& to_save)
	{
		return _inner_save_generic<Expression, ExprType>(_expr_pool,
			std::move(to_save));
	}
	template<typename ActualSymbol>
	static inline Symbol* save_symbol(ActualSymbol&& to_save)
	{
		return _inner_save_generic<Symbol, ActualSymbol>(_symbol_pool,
			std::move(to_save));
	}
	template<typename ActualHdlLhsType>
	static inline HdlLhsType* save_hdl_lhs_type(ActualHdlLhsType&& to_save)
	{
		return _inner_save_generic<HdlLhsType, ActualHdlLhsType>
			(_hdl_lhs_type_pool, std::move(to_save));
	}
	template<typename ActualHdlFullType>
	static inline HdlFullType* save_hdl_full_type
		(ActualHdlFullType&& to_save)
	{
		return _inner_save_generic<HdlFullType, ActualHdlFullType>
			(_hdl_full_type_pool, std::move(to_save));
	}
	template<typename ActualHdlFunction>
	static inline HdlFunction* save_hdl_function
		(ActualHdlFunction&& to_save)
	{
		return _inner_save_generic<HdlFunction, ActualHdlFunction>
			(_hdl_function_pool, std::move(to_save));
	}


private:		// static functions
	template<typename ToSaveBaseType, typename ToSaveType>
	static inline ToSaveBaseType* _inner_save_generic
		(std::vector<std::unique_ptr<ToSaveBaseType>>& pool,
		ToSaveType&& to_save)
	{
		std::unique_ptr<ToSaveBaseType> to_insert;
		to_insert.reset(new ToSaveType(std::move(to_save)));
		pool.push_back(std::move(to_insert));
		return pool.back().get();
	}

};


inline SavedString dup_str(const RawSavedString& to_dup)
{
	return GeneralAllocator::dup_str(to_dup);
}
inline SavedString dup_str(RawSavedString&& to_dup)
{
	return GeneralAllocator::dup_str(std::move(to_dup));
}
inline ExprNumData dup_expr_num_data(const RawExprNumData& to_dup)
{
	return GeneralAllocator::dup_expr_num_data(to_dup);
}
inline ExprNumData dup_expr_num_data(RawExprNumData&& to_dup)
{
	return GeneralAllocator::dup_expr_num_data(std::move(to_dup));
}

template<typename ExprType>
inline Expression* save_expr(ExprType&& to_save)
{
	return GeneralAllocator::save_expr(std::move(to_save));
}

template<typename ActualSymbol>
inline Symbol* save_symbol(ActualSymbol&& to_save)
{
	return GeneralAllocator::save_symbol(std::move(to_save));
}
template<typename ActualHdlLhsType>
inline HdlLhsType* save_hdl_lhs_type(ActualHdlLhsType&& to_save)
{
	return GeneralAllocator::save_hdl_lhs_type(std::move(to_save));
}
template<typename ActualHdlFullType>
inline HdlFullType* save_hdl_full_type(ActualHdlFullType&& to_save)
{
	return GeneralAllocator::save_hdl_full_type(std::move(to_save));
}
template<typename ActualHdlFunction>
inline HdlFunction* save_hdl_function(ActualHdlFunction&& to_save)
{
	return GeneralAllocator::save_hdl_function(std::move(to_save));
}

} // namespace frost_hdl

#endif		// src_general_allocator_class_hpp
