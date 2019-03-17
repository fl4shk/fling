#ifndef src_misc_types_hpp
#define src_misc_types_hpp

// src/misc_types.hpp

#include "misc_includes.hpp"
#include "ident_table_classes.hpp"
#include <ANTLRErrorListener.h>

namespace frost_hdl
{

class Symbol;

typedef OrderedIdentToPointerTable<Symbol> ListVars;

template<typename Type>
class PointerVector : public std::vector<Type*>
{
public:		// functions
	inline PointerVector() = default;

	GEN_COPY_CONSTRUCTOR_AND_ASSIGN(PointerVector);
	virtual ~PointerVector() = default;

};


template<typename Type>
class MoveOnlyPrevCurrPair
{
protected:		// variables
	Type _prev;
	
public:		// variables
	Type curr;

public:		// functions
	inline MoveOnlyPrevCurrPair() = default;
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(MoveOnlyPrevCurrPair);
	virtual ~MoveOnlyPrevCurrPair() = default;

	inline void back_up()
	{
		_prev = std::move(curr);
		curr = Type();
	}

	GEN_GETTER_BY_CON_REF(prev)
};

// Used for error reporting during semantic analysis.
// Many, many things use this.
class SrcCodePos
{
private:		// variables
	antlr4::ParserRuleContext* _ctx = nullptr;
	size_t _src_line = 0, _src_pos_in_line = 0;

public:		// functions
	SrcCodePos();
	SrcCodePos(antlr4::ParserRuleContext* s_ctx);

	//GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(SrcCodePos);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(SrcCodePos);

	virtual ~SrcCodePos();

	inline void err(const std::string& msg) const
	{
		printerr("Error on line ", _src_line, ", position ",
			_src_pos_in_line, ":  ", msg, "\n");
		exit(1);
	}
	inline void warn(const std::string& msg) const
	{
		printerr("Warning on line ", _src_line, ", position ",
			_src_pos_in_line, ":  ", msg, "\n");
	}


	GEN_GETTER_BY_VAL(src_line)
	GEN_GETTER_BY_VAL(src_pos_in_line)
};

} // namespace frost_hdl


#endif		// src_misc_types_hpp
