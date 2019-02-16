#ifndef src_general_allocator_class_hpp
#define src_general_allocator_class_hpp

// src/general_allocator_class.hpp

#include "misc_includes.hpp"


#include <map>

namespace frost_hdl
{
class Expression;
typedef std::vector<bool> RawExprNumData;
typedef const RawExprNumData * ExprNumData;

class GeneralAllocator
{
private:		// static variables
	static std::map<std::string, std::unique_ptr<std::string>> _str_pool;
	static std::vector<std::unique_ptr<Expression>> _expr_pool;
	static std::map<std::vector<bool>,
		std::unique_ptr<const RawExprNumData>> _expr_num_data_pool;

public:		// static functions
	static std::string* dup_str(const std::string& to_dup);
	static Expression* save_expr(Expression&& to_save);
	static ExprNumData dup_expr_num_data(const RawExprNumData& to_dup); 
	static ExprNumData dup_expr_num_data(RawExprNumData&& to_dup); 
};

inline std::string* dup_str(const std::string& to_dup)
{
	return GeneralAllocator::dup_str(to_dup);
}
inline Expression* save_expr(Expression&& to_save)
{
	return GeneralAllocator::save_expr(std::move(to_save));
}
inline ExprNumData dup_expr_num_data(const RawExprNumData& to_dup)
{
	return GeneralAllocator::dup_expr_num_data(to_dup);
}
inline ExprNumData dup_expr_num_data(RawExprNumData&& to_dup)
{
	return GeneralAllocator::dup_expr_num_data(std::move(to_dup));
}

} // namespace frost_hdl

#endif		// src_general_allocator_class_hpp
