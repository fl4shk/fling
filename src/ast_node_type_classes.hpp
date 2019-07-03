class NodeEnum : public NodeBase
{
public:		// functions
	inline NodeEnum(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_typename, Child&& s_ident, Child&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(typename),
			APPEND_CHILD(ident),
			APPEND_CHILD(scope));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeEnum);
	virtual ~NodeEnum() = default;

	GEN_ACCEPT;
};

GEN_LIST_BASIC(NodeScopeEnum)

class NodeClass : public NodeBase
{
protected:		// variables
	bool _packed = false;

public:		// functions
	inline NodeClass(const SrcCodeChunk& s_src_code_chunk,
		bool s_packed, Child&& s_ident, Child&& s_param_list,
		Child&& s_extends, Child&& s_scope, Child&& s_var_list)
		: NodeBase(s_src_code_chunk)
	{
		_packed = s_packed;
		_add_indiv_children(APPEND_CHILD(ident),
			APPEND_CHILD(param_list),
			APPEND_CHILD(extends),
			APPEND_CHILD(scope),
			APPEND_CHILD(var_list));
	}

	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeClass);
	virtual ~NodeClass() = default;

	GEN_ACCEPT;
	GEN_GETTER_BY_VAL(packed)
};

GEN_LIST_BASIC(NodeScopeClass)
class NodeTypename : public NodeBase
{
public:		// functions
	inline NodeTypename(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_bracket_pair, Child&& s_ident, Child&& s_param_inst_list)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(bracket_pair),
			APPEND_CHILD(ident),
			APPEND_CHILD(param_inst_list));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeTypename);
	virtual ~NodeTypename() = default;

	GEN_ACCEPT;
};
GEN_LIST_BASIC(NodePosParamArgInstList)
GEN_LIST_BASIC(NodeNamedParamArgInstList)

class NodeOneParamArgInst : public NodeBase
{
public:		// functions
	inline NodeOneParamArgInst(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left, Child&& s_right)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(left),
			APPEND_CHILD(right));
	}
	GEN_MOVE_ONLY_CONSTRUCTORS_AND_ASSIGN(NodeOneParamArgInst);
	virtual ~NodeOneParamArgInst() = default;

	GEN_ACCEPT;
};
