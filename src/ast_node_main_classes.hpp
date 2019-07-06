class NodePackage : public NodeBase
{
public:  // functions
	inline NodePackage(const SrcCodeChunk& s_src_code_chunk, Child&& s_ident,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(ident),
			APPEND_CHILD(scope));
	}
	GEN_POST_CONSTRUCTOR(NodePackage)
};

class NodeScopePackage : public NodeList
{
public:  // functions
	inline NodeScopePackage(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopePackage)
};

class NodeModule : public NodeBase
{
public:  // functions
	inline NodeModule(const SrcCodeChunk& s_src_code_chunk, Child&& s_ident,
		Child&& s_param_list,
		Child&& s_port_list,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(ident),
			APPEND_CHILD(param_list),
			APPEND_CHILD(port_list),
			APPEND_CHILD(scope));
	}
	GEN_POST_CONSTRUCTOR(NodeModule)
};

class NodeScopeModule : public NodeList
{
public:  // functions
	inline NodeScopeModule(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeModule)
};

class NodeInputSubPortList : public NodeList
{
public:  // functions
	inline NodeInputSubPortList(const SrcCodeChunk& s_src_code_chunk, Child&& s_typename)
		: NodeList(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(typename));
	}
	GEN_POST_CONSTRUCTOR(NodeInputSubPortList)
};

class NodeOutputSubPortList : public NodeList
{
public:  // functions
	inline NodeOutputSubPortList(const SrcCodeChunk& s_src_code_chunk, Child&& s_typename)
		: NodeList(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(typename));
	}
	GEN_POST_CONSTRUCTOR(NodeOutputSubPortList)
};

class NodeBidirSubPortList : public NodeList
{
public:  // functions
	inline NodeBidirSubPortList(const SrcCodeChunk& s_src_code_chunk, Child&& s_typename)
		: NodeList(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(typename));
	}
	GEN_POST_CONSTRUCTOR(NodeBidirSubPortList)
};

class NodeSubParamList : public NodeList
{
public:  // functions
	inline NodeSubParamList(const SrcCodeChunk& s_src_code_chunk, Child&& s_primary)
		: NodeList(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(primary));
	}
	GEN_POST_CONSTRUCTOR(NodeSubParamList)
};

class NodePostTypenameIdent : public NodeList
{
public:  // functions
	inline NodePostTypenameIdent(const SrcCodeChunk& s_src_code_chunk, Child&& s_ident)
		: NodeList(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(ident));
	}
	GEN_POST_CONSTRUCTOR(NodePostTypenameIdent)
};

class NodeBracketPair : public NodeBase
{
public:  // functions
	inline NodeBracketPair(const SrcCodeChunk& s_src_code_chunk, Child&& s_expr)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(expr));
	}
	GEN_POST_CONSTRUCTOR(NodeBracketPair)
};

class NodeHasString : public NodeBase
{
protected:  // variables
	string _s;
public:  // functions
	inline NodeHasString(const SrcCodeChunk& s_src_code_chunk, const string& s_s)
		: NodeBase(s_src_code_chunk), _s(s_s)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeHasString)
};

class NodeIdent : public NodeHasString
{
public:  // functions
	inline NodeIdent(const SrcCodeChunk& s_src_code_chunk, const string& s_s)
		: NodeHasString(s_src_code_chunk, s_s)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdent)
};

class NodeConstString : public NodeHasString
{
public:  // functions
	inline NodeConstString(const SrcCodeChunk& s_src_code_chunk, const string& s_s)
		: NodeHasString(s_src_code_chunk, s_s)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeConstString)
};

class NodeEnum : public NodeBase
{
public:  // functions
	inline NodeEnum(const SrcCodeChunk& s_src_code_chunk, Child&& s_typename,
		Child&& s_ident,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(typename),
			APPEND_CHILD(ident),
			APPEND_CHILD(scope));
	}
	GEN_POST_CONSTRUCTOR(NodeEnum)
};

class NodeScopeEnum : public NodeList
{
public:  // functions
	inline NodeScopeEnum(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeEnum)
};

class NodeClass : public NodeBase
{
protected:  // variables
	bool _packed;
public:  // functions
	inline NodeClass(const SrcCodeChunk& s_src_code_chunk, const bool& s_packed, Child&& s_ident,
		Child&& s_param_list,
		Child&& s_extends,
		Child&& s_scope,
		Child&& s_var_list)
		: NodeBase(s_src_code_chunk), _packed(s_packed)
	{
		_add_indiv_children(APPEND_CHILD(ident),
			APPEND_CHILD(param_list),
			APPEND_CHILD(extends),
			APPEND_CHILD(scope),
			APPEND_CHILD(var_list));
	}
	GEN_POST_CONSTRUCTOR(NodeClass)
};

class NodeScopeClass : public NodeList
{
public:  // functions
	inline NodeScopeClass(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeClass)
};

class NodeTypename : public NodeBase
{
public:  // functions
	inline NodeTypename(const SrcCodeChunk& s_src_code_chunk, Child&& s_bracket_pair,
		Child&& s_ident,
		Child&& s_param_inst_list)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(bracket_pair),
			APPEND_CHILD(ident),
			APPEND_CHILD(param_inst_list));
	}
	GEN_POST_CONSTRUCTOR(NodeTypename)
};

class NodePosParamArgInstList : public NodeList
{
public:  // functions
	inline NodePosParamArgInstList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodePosParamArgInstList)
};

class NodeNamedParamArgInstList : public NodeList
{
public:  // functions
	inline NodeNamedParamArgInstList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeNamedParamArgInstList)
};

class NodeOneParamArgInst : public NodeBase
{
public:  // functions
	inline NodeOneParamArgInst(const SrcCodeChunk& s_src_code_chunk, Child&& s_left,
		Child&& s_right)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(left),
			APPEND_CHILD(right));
	}
	GEN_POST_CONSTRUCTOR(NodeOneParamArgInst)
};

class NodeExprBase : public NodeBase
{
public:  // variables
	ExprValue value;
public:  // functions
	inline NodeExprBase(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBase)
};

class NodeExprBinopBase : public NodeExprBase
{
public:  // functions
	inline NodeExprBinopBase(const SrcCodeChunk& s_src_code_chunk, Child&& s_left,
		Child&& s_right)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(left),
			APPEND_CHILD(right));
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBase)
};

class NodeExprUnopBase : public NodeExprBase
{
public:  // functions
	inline NodeExprUnopBase(const SrcCodeChunk& s_src_code_chunk, Child&& s_child)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(child));
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopBase)
};

