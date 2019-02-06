#include "allocation_stuff.hpp"

namespace frost_hdl
{

class DupStuff
{
	friend BigNum* cstm_numdup(const BigNum& to_dup);
	friend std::string* cstm_strdup(const std::string& to_dup);
	//friend ExprNum* cstm_expr_numdup(const ExprNum& to_dup);
	//friend ExprSymbolRef* cstm_expr_symbol_refdup
	//	(const ExprSymbolRef& to_dup);

private:			// static variables
	static std::map<BigNum, std::unique_ptr<BigNum>> __num_pool;
	static std::map<std::string, std::unique_ptr<std::string>> __str_pool;
	//static std::map<ExprNum, std::unique_ptr<ExprNum>> __expr_num_pool;
	//static std::map<ExprSymbolRef, std::unique_ptr<ExprSymbolRef>>
	//	__expr_symbol_ref_pool;

};


std::map<BigNum, std::unique_ptr<BigNum>> DupStuff::__num_pool;
std::map<std::string, std::unique_ptr<std::string>> DupStuff::__str_pool;
//std::map<ExprNum, std::unique_ptr<ExprNum>> DupStuff::__expr_num_pool;
//std::map<ExprSymbolRef, std::unique_ptr<ExprSymbolRef>>
//	DupStuff::__expr_symbol_ref_pool;

BigNum* cstm_numdup(const BigNum& to_dup)
{
	auto& pool = DupStuff::__num_pool;

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


//ExprNum* cstm_expr_numdup(const ExprNum& to_dup)
//{
//	auto& pool = DupStuff::__expr_num_pool;
//
//	if (pool.count(to_dup) == 0)
//	{
//		std::unique_ptr<ExprNum> to_insert;
//		to_insert.reset(new ExprNum());
//		*to_insert = to_dup;
//		pool[to_dup] = std::move(to_insert);
//	}
//
//	return pool.at(to_dup).get();
//}
//
//ExprSymbolRef* cstm_expr_symbol_refdup(const ExprSymbolRef& to_dup)
//{
//	auto& pool = DupStuff::__expr_symbol_ref_pool;
//
//	if (pool.count(to_dup) == 0)
//	{
//		std::unique_ptr<ExprSymbolRef> to_insert;
//		to_insert.reset(new ExprSymbolRef());
//		*to_insert = to_dup;
//		pool[to_dup] = std::move(to_insert);
//	}
//
//	return pool.at(to_dup).get();
//}

} // namespace frost_hdl
