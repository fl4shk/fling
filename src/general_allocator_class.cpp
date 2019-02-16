#include "general_allocator_class.hpp"
#include "expr_num_class.hpp"
#include "expression_classes.hpp"

namespace frost_hdl
{

std::map<std::string, std::unique_ptr<std::string>>
	GeneralAllocator::_str_pool;
std::vector<std::unique_ptr<Expression>> GeneralAllocator::_expr_pool;

std::map<std::vector<bool>, std::unique_ptr<const RawExprNumData>>
	GeneralAllocator::_expr_num_data_pool;

std::string* GeneralAllocator::dup_str(const std::string& to_dup)
{
	auto& pool = _str_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<std::string> to_insert;
		to_insert.reset(new std::string());
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}

Expression* GeneralAllocator::save_expr(Expression&& to_save)
{
	auto& pool = _expr_pool;

	std::unique_ptr<Expression> to_insert;
	to_insert.reset(new Expression(std::move(to_save)));
	pool.push_back(std::move(to_insert));
	return pool.back().get();
}
ExprNumData GeneralAllocator::dup_expr_num_data
	(const RawExprNumData& to_dup)
{
	auto& pool = _expr_num_data_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<const RawExprNumData> to_insert;
		to_insert.reset(new RawExprNumData(to_dup));
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}
ExprNumData GeneralAllocator::dup_expr_num_data
	(RawExprNumData&& to_dup)
{
	auto& pool = _expr_num_data_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<const RawExprNumData> to_insert;
		to_insert.reset(new RawExprNumData(std::move(to_dup)));
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}


} // namespace frost_hdl
