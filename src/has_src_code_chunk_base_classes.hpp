#ifndef src_has_src_code_chunk_base_classes_hpp
#define src_has_src_code_chunk_base_classes_hpp

// src/has_src_code_chunk_base_classes.hpp

#include "misc_includes.hpp"
#include "src_code_chunk_class.hpp"
//#include "general_allocator_class.hpp"

namespace frost_hdl
{

class HasSrcCodeChunkBase
{
protected:		// variables
	SrcCodeChunk _src_code_chunk;

public:		// functions
	HasSrcCodeChunkBase();
	HasSrcCodeChunkBase(const SrcCodeChunk& s_src_code_chunk);

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(HasSrcCodeChunkBase);

	virtual ~HasSrcCodeChunkBase();

	GEN_GETTER_BY_CON_REF(src_code_chunk);
};

class HasSrcCodeChunkAndIdentBase : public HasSrcCodeChunkBase
{
protected:		// variables
	std::string _ident;

public:		// functions
	HasSrcCodeChunkAndIdentBase();
	HasSrcCodeChunkAndIdentBase(const SrcCodeChunk& s_src_code_chunk,
		const std::string& s_ident);

	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(HasSrcCodeChunkAndIdentBase);

	virtual ~HasSrcCodeChunkAndIdentBase();

	GEN_GETTER_BY_CON_REF(ident);
};

} // namespace frost_hdl

#endif		// src_has_src_code_chunk_base_classes_hpp
