#ifndef src_src_code_chunk_class_hpp
#define src_src_code_chunk_class_hpp

// src/src_code_chunk_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
//#include "general_allocator_class.hpp"

namespace frost_hdl
{

// Used for error reporting during semantic analysis.
class SrcCodeChunk
{
private:		// variables
	string _filename;
	string _text;
	size_t _src_line = 0, _src_pos_in_line = 0;

public:		// functions
	SrcCodeChunk();
	explicit SrcCodeChunk(const string& s_filename,
		const string& s_text, size_t s_src_line,
		size_t s_src_pos_in_line);

	//GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(SrcCodeChunk);
	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(SrcCodeChunk);

	virtual ~SrcCodeChunk();

	string convert_to_pos_string() const;
	string convert_to_errwarn_string() const;

	inline void syntax_error(const string& msg, int status=1) const
	{
		printerr("Syntax error at ", convert_to_errwarn_string(), ":  ",
			msg, "\n");
		exit(status);
	}
	inline void err(const string& msg, int status=1) const
	{
		printerr("Error at ", convert_to_errwarn_string(), ":  ", msg,
			"\n");
		exit(status);
	}
	inline void warn(const string& msg) const
	{
		printerr("Warning at ", convert_to_errwarn_string(), ":  ", msg,
			"\n");
	}



	GEN_GETTER_BY_CON_REF(filename)
	GEN_GETTER_BY_CON_REF(text)
	GEN_GETTER_BY_VAL(src_line)
	GEN_GETTER_BY_VAL(src_pos_in_line)
};

} // namespace frost_hdl


#endif		// src_src_code_chunk_class_hpp
