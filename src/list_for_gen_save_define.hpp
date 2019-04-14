//#ifndef src_list_for_gen_save_define_hpp
//#define src_list_for_gen_save_define_hpp

// src/list_for_gen_save_define.hpp

#define LIST_FOR_GEN_SAVE(X) \
	X(expr, Expression, ExprType) \
	X(symbol, Symbol, ActualSymbol) \
	X(frost_lhs_type, FrostLhsType, ActualFrostLhsType) \
	X(frost_full_type, FrostFullType, ActualFrostFullType) \
	X(frost_function, FrostFunction, ActualFrostFunction) \
	X(frost_module, FrostModule, ActualFrostModule) \
	X(frost_package, FrostPackage, ActualFrostPackage) \
	X(frost_generate_block_in_module, FrostGenerateBlockInModule, \
		ActualFrostGenerateBlockInModule) \

//#endif		// src_list_for_gen_save_define_hpp
