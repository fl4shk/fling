#ifndef src_general_allocator_class_hpp
#define src_general_allocator_class_hpp

// src/general_allocator_class.hpp

#include "misc_includes.hpp"


#include <map>

namespace frost_hdl
{
class Expression;
class Symbol;
class FrostLhsType;
class FrostFullType;
class FrostFunction;
class FrostModule;
//class FrostScope;

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
	static std::vector<std::unique_ptr<FrostLhsType>> _frost_lhs_type_pool;
	static std::vector<std::unique_ptr<FrostFullType>>
		_frost_full_type_pool;
	static std::vector<std::unique_ptr<FrostFunction>>
		_frost_function_pool;
	static std::vector<std::unique_ptr<FrostModule>> _frost_module_pool;

public:		// static functions
	static SavedString dup_str(const RawSavedString& to_dup);
	static SavedString dup_str(RawSavedString&& to_dup);
	static ExprNumData dup_expr_num_data(const RawExprNumData& to_dup); 
	static ExprNumData dup_expr_num_data(RawExprNumData&& to_dup); 


	#define GEN_SAVE(reuse, ret_type, template_type) \
		template<typename template_type> \
		static inline ret_type* save_##reuse(template_type&& to_save) \
		{ \
			return _inner_save_generic<ret_type, template_type> \
				(_##reuse##_pool, std::move(to_save)); \
		}

	GEN_SAVE(expr, Expression, ExprType)
	GEN_SAVE(symbol, Symbol, ActualSymbol)
	GEN_SAVE(frost_lhs_type, FrostLhsType, ActualFrostLhsType)
	GEN_SAVE(frost_full_type, FrostFullType, ActualFrostFullType)
	GEN_SAVE(frost_function, FrostFunction, ActualFrostFunction)
	GEN_SAVE(frost_module, FrostModule, ActualFrostModule)

	#undef GEN_SAVE


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

template<typename FirstArgType, typename SecondArgType,
	typename... RemArgTypes>
inline SavedString dup_str(FirstArgType&& first_arg,
	SecondArgType&& second_arg, RemArgTypes&&... rem_args)
{
	return dup_str(sconcat(first_arg, second_arg, rem_args...));
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
template<typename ActualFrostLhsType>
inline FrostLhsType* save_frost_lhs_type
	(ActualFrostLhsType&& to_save)
{
	return GeneralAllocator::save_frost_lhs_type(std::move(to_save));
}
template<typename ActualFrostFullType>
inline FrostFullType* save_frost_full_type
	(ActualFrostFullType&& to_save)
{
	return GeneralAllocator::save_frost_full_type(std::move(to_save));
}
template<typename ActualFrostFunction>
inline FrostFunction* save_frost_function
	(ActualFrostFunction&& to_save)
{
	return GeneralAllocator::save_frost_function(std::move(to_save));
}
template<typename ActualFrostModule>
inline FrostModule* save_frost_module
	(ActualFrostModule&& to_save)
{
	return GeneralAllocator::save_frost_module(std::move(to_save));
}

} // namespace frost_hdl

#endif		// src_general_allocator_class_hpp
