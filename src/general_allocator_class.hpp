#ifndef src_general_allocator_class_hpp
#define src_general_allocator_class_hpp

// src/general_allocator_class.hpp

#include "misc_includes.hpp"


#include <map>

namespace frost_hdl
{
class Expression;

typedef std::string RawSavedString;
typedef const RawSavedString* SavedString;

typedef std::vector<bool> RawExprNumData;
typedef const RawExprNumData* ExprNumData;

class GeneralAllocator
{
private:		// static variables
	static std::map<RawSavedString, std::unique_ptr<const RawSavedString>>
		_str_pool;
	static std::map<RawExprNumData,
		std::unique_ptr<const RawExprNumData>> _expr_num_data_pool;
	static std::vector<std::unique_ptr<Expression>> _expr_pool;

public:		// static functions
	static SavedString dup_str(const RawSavedString& to_dup);
	static ExprNumData dup_expr_num_data(const RawExprNumData& to_dup); 

	template<typename ExprType>
	static inline Expression* save_expr(ExprType&& to_save)
	{
		auto& pool = _expr_pool;

		std::unique_ptr<Expression> to_insert;
		to_insert.reset(new ExprType(std::move(to_save)));
		pool.push_back(std::move(to_insert));
		return pool.back().get();
	}
};

inline SavedString dup_str(const RawSavedString& to_dup)
{
	return GeneralAllocator::dup_str(to_dup);
}
inline ExprNumData dup_expr_num_data(const RawExprNumData& to_dup)
{
	return GeneralAllocator::dup_expr_num_data(to_dup);
}

template<typename ExprType>
inline Expression* save_expr(ExprType&& to_save)
{
	return GeneralAllocator::save_expr(std::move(to_save));
}

} // namespace frost_hdl

#endif		// src_general_allocator_class_hpp
