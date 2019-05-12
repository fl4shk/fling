#ifndef src_ast_builder_class_hpp
#define src_ast_builder_class_hpp

// src/ast_builder_class.hpp

#include "ast_node_class.hpp"

namespace frost_hdl
{

class AstBuilder final
{
public:		// types
	typedef AstNode::Type Type;

private:		// static functions
	static inline auto _build(const SrcCodeChunk& s_src_code_chunk,
		Type s_type)
	{
		return AstNode::make_child(s_src_code_chunk, s_type);
	}

public:		// static functions
	//static inline auto mk_bad(const SrcCodeChunk& s_src_code_chunk)
	//{
	//	return _build(s_src_code_chunk, Type::Bad);
	//}

	static inline auto mk_program(const SrcCodeChunk& s_src_code_chunk)
	{
		return _build(s_src_code_chunk, Type::Program);
	}
};

} // namespace frost_hdl

#endif		// src_ast_builder_class_hpp
