class NodeEnum : public NodeBase
{
	BLANK_TOK_PREFIX_SET(Tok::KwEnum);

public:		// functions
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
		bool s_packed, Child&& s_ident, Child&& s_param_list,
		Child&& s_extends, Child&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_packed = s_packed;
		_add_indiv_children("ident", move(s_ident),
			"param_list", move(s_param_list),
			"extends", move(s_extends),
			"scope", move(s_scope));
	}

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeClass);
	virtual ~NodeClass() = default;

	GEN_ACCEPT;
};

class NodePostTypenameIdent : public NodeList
{
public:		// functions
	inline NodePostTypenameIdent(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident)
		: NodeList(s_src_code_chunk)
	{
		_add_indiv_children("ident", move(s_ident));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodePostTypenameIdent);
	virtual ~NodePostTypenameIdent() = default;

	GEN_ACCEPT;
};
