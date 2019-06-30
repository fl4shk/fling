class NodeEnum : public NodeBase
{
	BLANK_TOK_PREFIX_SET(Tok::KwEnum);

public:		// functions
	inline NodeEnum(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident, Child&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children("ident", move(s_ident),
			"scope", move(s_scope));
	}
	inline NodeEnum(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_typename, Child&& s_ident, Child&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children("typename", move(s_typename),
			"ident", move(s_ident),
			"scope", move(s_scope));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeEnum);
	virtual ~NodeEnum() = default;

	GEN_ACCEPT;
};

class NodeClass : public NodeBase
{
	TOK_PREFIX_SET({Tok::KwPacked}, Tok::KwClass);

private:		// variables
	bool _packed = false;

public:		// functions
	inline NodeClass(const SrcCodeChunk& s_src_code_chunk,
		bool s_packed, Child&& s_ident, Child&& s_class_extras,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_packed = s_packed;
		_add_indiv_children("ident", move(s_ident),
			"class_extras", move(s_class_extras),
			"scope", move(s_scope));
	}

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeClass);
	virtual ~NodeClass() = default;

	GEN_ACCEPT;
};

class NodeClassExtras : public NodeBase
{
public:		// functions
	inline NodeClassExtras(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	inline NodeClassExtras(const SrcCodeChunk& s_src_code_chunk,
		const string& which, Child&& s_child)
		: NodeBase(s_src_code_chunk)
	{
		//if (!which)
		//{
		//	_add_indiv_children("param_list", move(s_child));
		//}
		//else // if (which)
		//{
		//	_add_indiv_children("extends", move(s_child));
		//}
		_add_indiv_children(which, move(s_child));
	}
	inline NodeClassExtras(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_param_list, Child&& s_extends)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children("param_list", move(s_param_list),
			"extends", move(s_extends));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeClassExtras);
	virtual ~NodeClassExtras() = default;

	GEN_ACCEPT;
};
