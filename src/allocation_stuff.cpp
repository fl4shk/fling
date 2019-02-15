#include "allocation_stuff.hpp"
#include "expression_classes.hpp"

namespace frost_hdl
{

class DupStuff
{
	friend BigNum* cstm_num_dup(const BigNum& to_dup);
	friend std::string* cstm_str_dup(const std::string& to_dup);
	friend Expression* save_expr(Expression&& to_move);

private:			// static variables
	static std::map<BigNum, std::unique_ptr<BigNum>> _num_pool;
	static std::map<std::string, std::unique_ptr<std::string>> _str_pool;
	static std::vector<std::unique_ptr<Expression>> _expr_pool;

};


std::map<BigNum, std::unique_ptr<BigNum>> DupStuff::_num_pool;
std::map<std::string, std::unique_ptr<std::string>> DupStuff::_str_pool;
std::vector<std::unique_ptr<Expression>> DupStuff::_expr_pool;

BigNum* cstm_num_dup(const BigNum& to_dup)
{
	auto& pool = DupStuff::_num_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<BigNum> to_insert;
		to_insert.reset(new BigNum());
		//BigNum* to_insert = new BigNum();
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}

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


} // namespace frost_hdl
