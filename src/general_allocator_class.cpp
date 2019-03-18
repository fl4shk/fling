#include "general_allocator_class.hpp"
#include "expr_num_class.hpp"
#include "expression_classes.hpp"
#include "symbol_table_class.hpp"
#include "frost_lhs_type_table_class.hpp"
#include "frost_full_type_table_class.hpp"
#include "frost_function_table_class.hpp"
#include "frost_module_table_class.hpp"
#include "frost_package_table_class.hpp"
#include "list_for_gen_save_define.hpp"

namespace frost_hdl
{

std::map<RawSavedString, std::unique_ptr<const RawSavedString>>
	GeneralAllocator::_str_pool;
std::map<RawExprNumData, std::unique_ptr<const RawExprNumData>>
	GeneralAllocator::_expr_num_data_pool;

#define GEN_SAVE_POOLS(pool_prefix, contained_type, dummy) \
	MoveOnlyPrevCurrPair<std::vector<std::unique_ptr<contained_type>>> \
		GeneralAllocator::_##pool_prefix##_pool;

LIST_FOR_GEN_SAVE(GEN_SAVE_POOLS)

#undef GEN_SAVE_POOLS


SavedString GeneralAllocator::dup_str(const RawSavedString& to_dup)
{
	auto& pool = _str_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<RawSavedString> to_insert;
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
		auto ret = pool.insert_or_assign(*to_insert, std::move(to_insert));
		return ret.first->second.get();
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
ExprNumData GeneralAllocator::dup_expr_num_data(RawExprNumData&& to_dup)
{
	auto& pool = _expr_num_data_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<const RawExprNumData> to_insert;
		to_insert.reset(new RawExprNumData(std::move(to_dup)));
		auto ret = pool.insert_or_assign(*to_insert, std::move(to_insert));
		return ret.first->second.get();
	}

	return pool.at(to_dup).get();
}


} // namespace frost_hdl
