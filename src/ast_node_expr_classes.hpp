class NodeExprBase : public NodeBase
{
public:		// variables
	ExprValue value;

public:		// functions
	inline NodeExprBase(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeExprBase);
	virtual ~NodeExprBase() = default;

	GEN_ACCEPT;
};

class NodeBinopBase : public NodeExprBase
{
public:		// functions
	NodeBinopBase(const SrcCodeChunk& s_src_code_chunk, Child&& s_left,
		Child&& s_right)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children("left", move(s_left),
			"right", move(s_right));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeBinopBase);
	virtual ~NodeBinopBase() = default;

	GEN_ACCEPT;
};

class NodeUnopBase : public NodeExprBase
{
public:		// functions
	inline NodeUnopBase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children("child", move(s_child));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeUnopBase);
	virtual ~NodeUnopBase() = default;

	GEN_ACCEPT;
};

//class Node
