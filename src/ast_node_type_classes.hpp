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

GEN_LIST_BASIC(NodeScopeEnum)

class NodeClass : public NodeBase
{
	TOK_PREFIX_SET({Tok::KwPacked}, Tok::KwClass);

protected:		// variables
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
	GEN_GETTER_BY_VAL(packed)
};

GEN_LIST_BASIC(NodeScopeClass)
GEN_LIST_W_ONE_C(NodeTypename, param_inst_list)
