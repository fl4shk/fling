class NodeExprBase : public NodeBase
{
public:		// variables
	ExprValue value;

public:		// functions
	inline NodeExprBase(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBase);
};

class NodeExprBinopBase : public NodeExprBase
{
public:		// functions
	NodeExprBinopBase(const SrcCodeChunk& s_src_code_chunk, Child&& s_left,
		Child&& s_right)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(left)
			APPEND_CHILD(right));
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBase);
};

class NodeExprUnopBase : public NodeExprBase
{
public:		// functions
	inline NodeExprUnopBase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(child));
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopBase);
};

