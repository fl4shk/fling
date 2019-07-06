//#ifndef src_list_of_ast_node_classes_define_hpp
//#define src_list_of_ast_node_classes_define_hpp

// src/list_of_ast_node_classes_define.hpp

#define LIST_OF_AST_NODE_CLASSES(X) \
	X(NodeBase) \
	X(NodeList) \
	X(NodePackage) \
	X(NodeScopePackage) \
	X(NodeModule) \
	X(NodeScopeModule) \
	X(NodeInputSubPortList) \
	X(NodeOutputSubPortList) \
	X(NodeBidirSubPortList) \
	X(NodeSubParamList) \
	X(NodePostTypenameIdent) \
	X(NodeBracketPair) \
	X(NodeHasString) \
	X(NodeIdent) \
	X(NodeConstString) \
	X(NodeEnum) \
	X(NodeScopeEnum) \
	X(NodeClass) \
	X(NodeScopeClass) \
	X(NodeTypename) \
	X(NodePosParamArgInstList) \
	X(NodeNamedParamArgInstList) \
	X(NodeOneParamArgInst) \
	X(NodeExprBase) \
	X(NodeExprBinopBase) \
	X(NodeExprUnopBase) \

//#endif		// src_list_of_ast_node_classes_define_hpp
