//#ifndef src_ptvisitor_list_for_gen_stack_defines_hpp
//#define src_ptvisitor_list_for_gen_stack_defines_hpp

// src/ptvisitor/list_for_gen_stack_defines.hpp

//X(stack_type, ret_type, whateverfix)
#define LIST_FOR_GEN_STACK(X) \
	X(BigNum, const BigNum&, big_num) \
	X(SmallNum, SmallNum, small_num) \
	X(Ident, const Ident&, str) \
	X(SrcCodeChunk, const SrcCodeChunk&, src_code_chunk) \
	X(AstNode*, AstNode*, ast_node) \


//#endif		// src_ptvisitor_list_for_gen_stack_defines_hpp
