//#ifndef src_ptvisitor_list_for_gen_stack_defines_hpp
//#define src_ptvisitor_list_for_gen_stack_defines_hpp

// src/ptvisitor/list_for_gen_stack_defines.hpp

//X(stack_type, ret_type, whateverfix)
#define LIST_FOR_GEN_STACK(X) \
	X(BigNum, const BigNum&, big_num) \
	X(SmallNum, SmallNum, small_num) \
	X(SavedString, SavedString, str) \
	X(SrcCodeChunk, SrcCodeChunk, src_code_chunk) \
	X(Expression*, Expression*, expr) \
	X(Symbol*, Symbol*, sym) \
	X(FrostLhsType*, FrostLhsType*, lhs_type) \
	X(FrostFullType*, FrostFullType*, full_type) \
	X(FrostStatementTable::Node*, FrostStatementTable::Node*, \
		statement_table_node) \
	X(ModuleScope*, ModuleScope*, module_scope) \
	/* X(InterfaceScope*, InterfaceScope*, interface_scope) */ \
	X(PseudoFuncCallRange, PseudoFuncCallRange, \
		pseudo_func_call_range) \
	X(AnyGenerateBlockHeader, AnyGenerateBlockHeader, \
		any_generate_block_header) \


//#endif		// src_ptvisitor_list_for_gen_stack_defines_hpp
