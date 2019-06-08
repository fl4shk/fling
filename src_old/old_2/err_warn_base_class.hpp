#ifndef src_err_warn_base_class_hpp
#define src_err_warn_base_class_hpp

// src/err_warn_base_class.hpp

#include "misc_includes.hpp"
#include "src_code_chunk_class.hpp"
#include "parsed_src_code_class.hpp"

namespace frost_hdl
{

class ErrWarnBase
{
public:		// types
	typedef antlr4::ParserRuleContext ParserRuleContext;

protected:		// variables
	Ident _curr_filename;

public:		// functions
	inline ErrWarnBase() = default;

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ErrWarnBase);

	virtual ~ErrWarnBase() = default;

protected:		// functions
	inline void _err(ParserRuleContext* ctx, const Ident& msg)
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
			_err(_make_src_code_chunk(ctx), msg);
		}
		exit(1);
	}
	inline void _err(const SrcCodeChunk& src_code_chunk, const Ident& msg)
	{
		//_err(src_code_chunk.ctx(), msg);
		src_code_chunk.err(msg);
	}
	inline void _err(const Ident& msg)
	{
		//printerr("Error in file \"", *_filename, "\":  ", msg, "\n");
		printerr("Error:  ", msg, "\n");
		exit(1);
	}
	inline void _warn(ParserRuleContext* ctx, const Ident& msg)
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
			_warn(_make_src_code_chunk(ctx), msg);
		}
	}
	inline void _warn(const SrcCodeChunk& src_code_chunk, const Ident& msg)
	{
		//_warn(src_code_chunk.ctx(), msg);
		src_code_chunk.warn(msg);
	}
	inline void _warn(const Ident& msg)
	{
		printerr("Warning:  ", msg, "\n");
	}

	inline SrcCodeChunk _make_src_code_chunk(ParserRuleContext* ctx) const
	{
		return SrcCodeChunk(_curr_filename, ctx);
	}
};

} // namespace frost_hdl

#endif		// src_err_warn_base_class_hpp
