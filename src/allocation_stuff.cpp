#include "allocation_stuff.hpp"

namespace frost_hdl
{

class DupStuff
{
	friend BigNum* cstm_numdup(const BigNum& to_dup);
	friend std::string* cstm_strdup(const std::string& to_dup);
	friend ExprNum* alloc_expr_num(size_t s_size, BigNum* s_val);

private:			// static variables
	static std::map<BigNum, BigNum*> __num_pool;
	static std::map<std::string, std::unique_ptr<std::string>> __str_pool;
	static std::vector<std::unique_ptr<ExprNum>> __expr_num_pool;

};


std::map<BigNum, BigNum*> DupStuff::__num_pool;
std::map<std::string, std::unique_ptr<std::string>> DupStuff::__str_pool;
std::vector<std::unique_ptr<ExprNum>> DupStuff::__expr_num_pool;


BigNum* cstm_numdup(const BigNum& to_dup)
{
	auto& pool = DupStuff::__num_pool;

	if (pool.count(to_dup) == 0)
	{
		//std::unique_ptr<BigNum> to_insert;
		//to_insert.reset(new BigNum());
		BigNum* to_insert = new BigNum();
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup);
}

std::string* cstm_strdup(const std::string& to_dup)
{
	auto& pool = DupStuff::__str_pool;

	if (pool.count(to_dup) == 0)
	{
		std::unique_ptr<std::string> to_insert;
		to_insert.reset(new std::string());
		*to_insert = to_dup;
		pool[to_dup] = std::move(to_insert);
	}

	return pool.at(to_dup).get();
}

ExprNum* alloc_expr_num(size_t s_size, BigNum* s_val)
{
	std::unique_ptr<ExprNum> to_push(new ExprNum(s_size, s_val));
	DupStuff::__expr_num_pool.push_back(std::move(to_push));
	return DupStuff::__expr_num_pool.back().get();
}

} // namespace frost_hdl
