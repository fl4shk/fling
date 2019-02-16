#include "allocation_stuff.hpp"
#include "expr_num_class.hpp"
#include "expression_classes.hpp"

namespace frost_hdl
{

class DupStuff
{
	friend std::string* cstm_str_dup(const std::string& to_dup);
	friend Expression* save_expr(Expression&& to_save);

private:			// static variables
	static std::map<std::string, std::unique_ptr<std::string>> _str_pool;
	static std::vector<std::unique_ptr<Expression>> _expr_pool;

};


std::map<std::string, std::unique_ptr<std::string>> DupStuff::_str_pool;
std::vector<std::unique_ptr<Expression>> DupStuff::_expr_pool;

//ExprNum* cstm_num_dup(const ExprNum& to_dup)
//{
//	auto& pool = DupStuff::_num_pool;
//
//	if (pool.count(to_dup) == 0)
//	{
//		std::unique_ptr<ExprNum> to_insert;
//		to_insert.reset(new ExprNum());
//		//ExprNum* to_insert = new ExprNum();
//		*to_insert = to_dup;
//		pool[to_dup] = std::move(to_insert);
//	}
//
//	return pool.at(to_dup).get();
//}

std::string* cstm_str_dup(const std::string& to_dup)
{
	auto& pool = DupStuff::_str_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<std::string> to_insert;
		to_insert.reset(new std::string());
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}

Expression* save_expr(Expression&& to_save)
{
	auto& pool = DupStuff::_expr_pool;

	std::unique_ptr<Expression> to_insert;
	to_insert.reset(new Expression(std::move(to_save)));
	pool.push_back(std::move(to_insert));
	return pool.back().get();
}


} // namespace frost_hdl
