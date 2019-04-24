#ifndef src_err_warn_base_class_hpp
#define src_err_warn_base_class_hpp

// src/err_warn_base_class.hpp

#include "misc_includes.hpp"
#include "src_code_pos_class.hpp"
#include "parsed_src_code_class.hpp"

namespace frost_hdl
{

class ErrWarnBase
{
public:		// types
	typedef antlr4::ParserRuleContext ParserRuleContext;

protected:		// variables
	SavedString _curr_filename = nullptr;

public:		// functions
	inline ErrWarnBase() = default;

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ErrWarnBase);

	virtual ~ErrWarnBase() = default;

protected:		// functions
	inline void _err(antlr4::ParserRuleContext* ctx,
		const std::string& msg)
	{
		if (ctx == nullptr)
		{
			printerr("Error:  ", msg, "\n");
		}
		else
		{
			//auto tok = ctx->getStart();
			//const size_t line = tok->getLine();
			//const size_t pos_in_line = tok->getCharPositionInLine();
			////printerr("Error in file \"", *_filename, "\", on line ",
			////	line, ", position ", pos_in_line, ":  ", msg, "\n");
			//printerr("Error on line ", line, ", position ", pos_in_line, 
			//	":  ", msg, "\n");
			_err(_make_src_code_pos(ctx), msg);
		}
		exit(1);
	}
	inline void _err(const SrcCodePos& src_code_pos,
		const std::string& msg)
	{
		//_err(src_code_pos.ctx(), msg);
		src_code_pos.err(msg);
	}
	inline void _err(const std::string& msg)
	{
		//printerr("Error in file \"", *_filename, "\":  ", msg, "\n");
		printerr("Error:  ", msg, "\n");
		exit(1);
	}
	inline void _warn(ParserRuleContext* ctx, const std::string& msg)
	{
		if (ctx == nullptr)
		{
			printerr("Warning:  ", msg, "\n");
		}
		else
		{
			//auto tok = ctx->getStart();
			//const size_t line = tok->getLine();
			//const size_t pos_in_line = tok->getCharPositionInLine();
			////printerr("Error in file \"", *_filename, "\", on line ",
			////	line, ", position ", pos_in_line, ":  ", msg, "\n");
			//printerr("Warning on line ", line, ", position ", pos_in_line, 
			//	":  ", msg, "\n");
			_warn(_make_src_code_pos(ctx), msg);
		}
	}
	inline void _warn(const SrcCodePos& src_code_pos,
		const std::string& msg)
	{
		//_warn(src_code_pos.ctx(), msg);
		src_code_pos.warn(msg);
	}
	inline void _warn(const std::string& msg)
	{
		printerr("Warning:  ", msg, "\n");
	}

	inline SrcCodePos _make_src_code_pos(ParserRuleContext* ctx) const
	{
		return SrcCodePos(_curr_filename, ctx);
	}
};

} // namespace frost_hdl

#endif		// src_err_warn_base_class_hpp
