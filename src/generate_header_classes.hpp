#ifndef src_generate_header_classes_hpp
#define src_generate_header_classes_hpp

// src/generate_header_classes.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
#include "pseudo_func_call_range_class.hpp"

namespace frost_hdl
{

class GenerateHeaderFor
{
protected:		// variables
	//SavedString iter_ident = nullptr;
	Symbol* _iter_sym = nullptr;
	PseudoFuncCallRange _pseudo_func_call_range;

public:		// functions
	GenerateHeaderFor() = default;

	inline GenerateHeaderFor(Symbol* s_iter_sym,
		const PseudoFuncCallRange& s_pseudo_func_call_range)
		: _iter_sym(s_iter_sym),
		_pseudo_func_call_range(s_pseudo_func_call_range)
	{
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(GenerateHeaderFor);

	virtual ~GenerateHeaderFor() = default;

	//inline bool is_valid() const
	//{
	//	return (_pseudo_func_call_range.is_valid()
	//		&& (!_pseudo_func_call_range.left()->references_symbol
	//		(_iter_sym))
	//		&& (!_pseudo_func_call_range.right()->references_symbol
	//		(_iter_sym)));
	//}

	GEN_GETTER_BY_VAL(iter_sym)
	GEN_GETTER_BY_CON_REF(pseudo_func_call_range)

};

class GenerateHeaderIf
{
protected:		// variables
	Expression* _condition = nullptr;

public:		// functions
	GenerateHeaderIf() = default;

	inline GenerateHeaderIf(Expression* s_condition)
		: _condition(s_condition)
	{
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(GenerateHeaderIf);

	virtual ~GenerateHeaderIf() = default;

	//inline bool is_valid() const
	//{
	//	return _condition->is_constant();
	//}

	GEN_GETTER_BY_VAL(condition)

};

} // namespace frost_hdl


#endif		// src_generate_header_classes_hpp
