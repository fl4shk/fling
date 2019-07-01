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

class NodeExprBinopBase : public NodeExprBase
{
public:		// functions
	NodeExprBinopBase(const SrcCodeChunk& s_src_code_chunk, Child&& s_left,
		Child&& s_right)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children("left", move(s_left),
			"right", move(s_right));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeExprBinopBase);
	virtual ~NodeExprBinopBase() = default;

	GEN_ACCEPT;
};

class NodeExprUnopBase : public NodeExprBase
{
public:		// functions
	inline NodeExprUnopBase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children("child", move(s_child));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeExprUnopBase);
	virtual ~NodeExprUnopBase() = default;

	GEN_ACCEPT;
};

