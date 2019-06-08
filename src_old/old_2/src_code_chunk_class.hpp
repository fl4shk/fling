#ifndef src_src_code_chunk_class_hpp
#define src_src_code_chunk_class_hpp

// src/src_code_chunk_class.hpp

#include "misc_includes.hpp"
#include <ANTLRErrorListener.h>
#include "misc_types.hpp"
//#include "general_allocator_class.hpp"

namespace frost_hdl
{

// Used for error reporting during semantic analysis.
// Many, many things use this, usually in the form of deriving from
// `HasSrcCodeChunkBase`
class SrcCodeChunk
{
private:		// variables
	Ident _filename;
	antlr4::ParserRuleContext* _ctx = nullptr;
	Ident _text;
	size_t _src_line = 0, _src_pos_in_line = 0;

public:		// functions
	SrcCodeChunk();
	explicit SrcCodeChunk(const Ident& s_filename,
		antlr4::ParserRuleContext* s_ctx);
	explicit SrcCodeChunk(const Ident& s_filename,
		const Ident& s_text, size_t s_src_line,
		size_t s_src_pos_in_line);

	//GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(SrcCodeChunk);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(SrcCodeChunk);

	virtual ~SrcCodeChunk();

	Ident convert_to_pos_string() const;
	Ident convert_to_errwarn_string() const;

	inline void syntax_error(const Ident& msg, int status=1) const
	{
		printerr("Syntax error at ", convert_to_errwarn_string(), ":  ",
			msg, "\n");
		exit(status);
	}
	inline void err(const Ident& msg, int status=1) const
	{
		printerr("Error at ", convert_to_errwarn_string(), ":  ", msg,
			"\n");
		exit(status);
	}
	inline void warn(const Ident& msg) const
	{
		printerr("Warning at ", convert_to_errwarn_string(), ":  ", msg,
			"\n");
	}



	GEN_GETTER_BY_CON_REF(filename)
	GEN_GETTER_BY_VAL(ctx)
	GEN_GETTER_BY_CON_REF(text)
	GEN_GETTER_BY_VAL(src_line)
	GEN_GETTER_BY_VAL(src_pos_in_line)
};

} // namespace frost_hdl


#endif		// src_src_code_chunk_class_hpp
