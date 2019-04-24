#ifndef src_generate_block_header_classes_hpp
#define src_generate_block_header_classes_hpp

// src/generate_block_header_classes.hpp

#include "misc_includes.hpp"
#include "symbol_class.hpp"
#include "pseudo_func_call_range_class.hpp"

namespace frost_hdl
{

class GenerateBlockHeaderFor
{
protected:		// variables
	//SavedString iter_ident = nullptr;
	Symbol* _iter_sym = nullptr;
	PseudoFuncCallRange _pseudo_func_call_range;

public:		// functions
	GenerateBlockHeaderFor() = default;

	inline GenerateBlockHeaderFor(Symbol* s_iter_sym,
		const PseudoFuncCallRange& s_pseudo_func_call_range)
		: _iter_sym(s_iter_sym),
		_pseudo_func_call_range(s_pseudo_func_call_range)
	{
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(GenerateBlockHeaderFor);

	virtual ~GenerateBlockHeaderFor() = default;

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

class GenerateBlockHeaderIf
{
protected:		// variables
	Expression* _condition = nullptr;

public:		// functions
	GenerateBlockHeaderIf() = default;

	inline GenerateBlockHeaderIf(Expression* s_condition)
		: _condition(s_condition)
	{
	}

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(GenerateBlockHeaderIf);

	virtual ~GenerateBlockHeaderIf() = default;

	//inline bool is_valid() const
	//{
	//	return _condition->is_constant();
	//}

	GEN_GETTER_BY_VAL(condition)

};

typedef std::variant<GenerateBlockHeaderFor, GenerateBlockHeaderIf>
	AnyGenerateBlockHeader;

} // namespace frost_hdl


#endif		// src_generate_block_header_classes_hpp
