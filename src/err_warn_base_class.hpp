#ifndef src_err_warn_base_class_hpp
#define src_err_warn_base_class_hpp

// src/err_warn_base_class.hpp

#include "misc_includes.hpp"
#include "src_code_chunk_class.hpp"

namespace frost_hdl
{

class ErrWarnBase
{
protected:		// variables
	string _curr_filename;

public:		// functions
	inline ErrWarnBase() = default;

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(ErrWarnBase);

	virtual ~ErrWarnBase() = default;

protected:		// functions
	inline void _err(const SrcCodeChunk& src_code_chunk, const string& msg)
	{
		//_err(src_code_chunk.ctx(), msg);
		src_code_chunk.err(msg);
	}
	inline void _err(const string& msg)
	{
		//printerr("Error in file \"", *_filename, "\":  ", msg, "\n");
		printerr("Error:  ", msg, "\n");
		exit(1);
	}
	inline void _warn(const SrcCodeChunk& src_code_chunk,
		const string& msg)
	{
		//_warn(src_code_chunk.ctx(), msg);
		src_code_chunk.warn(msg);
	}
	inline void _warn(const string& msg)
	{
		printerr("Warning:  ", msg, "\n");
	}
};

} // namespace frost_hdl

#endif		// src_err_warn_base_class_hpp
