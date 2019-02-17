#include "general_allocator_class.hpp"
#include "expr_num_class.hpp"
#include "expression_classes.hpp"

namespace frost_hdl
{

std::map<RawSavedString, std::unique_ptr<const RawSavedString>>
	GeneralAllocator::_str_pool;
std::map<RawExprNumData, std::unique_ptr<const RawExprNumData>>
	GeneralAllocator::_expr_num_data_pool;
std::vector<std::unique_ptr<Expression>> GeneralAllocator::_expr_pool;


SavedString GeneralAllocator::dup_str(const RawSavedString& to_dup)
{
	auto& pool = _str_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<const RawSavedString> to_insert;
		to_insert.reset(new RawSavedString(to_dup));
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}
SavedString GeneralAllocator::dup_str(RawSavedString&& to_dup)
{
	auto& pool = _str_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<const RawSavedString> to_insert;
		to_insert.reset(new RawSavedString(std::move(to_dup)));
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
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

Expression* GeneralAllocator::save_expr(Expression&& to_save)
{
	auto& pool = _expr_pool;

	std::unique_ptr<Expression> to_insert;
	to_insert.reset(new Expression(std::move(to_save)));
	pool.push_back(std::move(to_insert));
	return pool.back().get();
}

} // namespace frost_hdl
