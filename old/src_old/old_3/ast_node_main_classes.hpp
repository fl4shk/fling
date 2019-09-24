class NodeProgram : public NodeList
{
public:		// functions
	inline NodeProgram(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeProgram);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Program;
	}
	virtual string name() const
	{
		return "Program";
	}
};

class NodePackage : public NodeBase
{
protected:		// children
	Child _ident,
		_scope;
public:		// functions
	inline NodePackage(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_ident(std::move(s_ident)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodePackage);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:ident\n(", ident()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Package;
	}
	virtual string name() const
	{
		return "Package";
	}
	GEN_GETTER_BY_CON_REF(ident)
	GEN_SETTER_BY_RVAL_REF(ident)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeScopePackage : public NodeList
{
public:		// functions
	inline NodeScopePackage(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopePackage);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ScopePackage;
	}
	virtual string name() const
	{
		return "ScopePackage";
	}
};

class NodeModule : public NodeBase
{
protected:		// children
	Child _ident,
		_param_list,
		_port_list,
		_scope;
public:		// functions
	inline NodeModule(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident,
		Child&& s_param_list,
		Child&& s_port_list,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_ident(std::move(s_ident)),
		_param_list(std::move(s_param_list)),
		_port_list(std::move(s_port_list)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeModule);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:ident\n(", ident()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:param_list\n(", param_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:port_list\n(", port_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Module;
	}
	virtual string name() const
	{
		return "Module";
	}
	GEN_GETTER_BY_CON_REF(ident)
	GEN_SETTER_BY_RVAL_REF(ident)
	GEN_GETTER_BY_CON_REF(param_list)
	GEN_SETTER_BY_RVAL_REF(param_list)
	GEN_GETTER_BY_CON_REF(port_list)
	GEN_SETTER_BY_RVAL_REF(port_list)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeScopeModproc : public NodeList
{
public:		// functions
	inline NodeScopeModproc(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeModproc);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ScopeModproc;
	}
	virtual string name() const
	{
		return "ScopeModproc";
	}
};

class NodeParamArgTypeSublist : public NodeBase
{
protected:		// variables
	bool _param_pack;
protected:		// children
	Child _ident_term_equals_extra_list;
public:		// functions
	inline NodeParamArgTypeSublist(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_param_pack,
		Child&& s_ident_term_equals_extra_list)
		: NodeBase(s_src_code_chunk), _param_pack(s_param_pack),
		_ident_term_equals_extra_list(std::move(s_ident_term_equals_extra_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeParamArgTypeSublist);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _param_pack(", _param_pack, ")\n");
		ret += sconcat("  child:ident_term_equals_extra_list\n(", ident_term_equals_extra_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ParamArgTypeSublist;
	}
	virtual string name() const
	{
		return "ParamArgTypeSublist";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(param_pack)
	GEN_GETTER_BY_CON_REF(ident_term_equals_extra_list)
	GEN_SETTER_BY_RVAL_REF(ident_term_equals_extra_list)
};

class NodeArgPortSublist : public NodeBase
{
protected:		// variables
	string _port_dir;
protected:		// children
	Child _param_arg_var_sublist;
public:		// functions
	inline NodeArgPortSublist(const SrcCodeChunk& s_src_code_chunk,
		const string& s_port_dir,
		Child&& s_param_arg_var_sublist)
		: NodeBase(s_src_code_chunk), _port_dir(s_port_dir),
		_param_arg_var_sublist(std::move(s_param_arg_var_sublist))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeArgPortSublist);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _port_dir(", _port_dir, ")\n");
		ret += sconcat("  child:param_arg_var_sublist\n(", param_arg_var_sublist()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ArgPortSublist;
	}
	virtual string name() const
	{
		return "ArgPortSublist";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(port_dir)
	GEN_GETTER_BY_CON_REF(param_arg_var_sublist)
	GEN_SETTER_BY_RVAL_REF(param_arg_var_sublist)
};

class NodeParamArgVarSublist : public NodeBase
{
protected:		// variables
	bool _param_pack;
protected:		// children
	Child _the_typename,
		_ident_term_equals_extra_list;
public:		// functions
	inline NodeParamArgVarSublist(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_param_pack,
		Child&& s_the_typename,
		Child&& s_ident_term_equals_extra_list)
		: NodeBase(s_src_code_chunk), _param_pack(s_param_pack),
		_the_typename(std::move(s_the_typename)),
		_ident_term_equals_extra_list(std::move(s_ident_term_equals_extra_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeParamArgVarSublist);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _param_pack(", _param_pack, ")\n");
		ret += sconcat("  child:the_typename\n(", the_typename()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:ident_term_equals_extra_list\n(", ident_term_equals_extra_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ParamArgVarSublist;
	}
	virtual string name() const
	{
		return "ParamArgVarSublist";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(param_pack)
	GEN_GETTER_BY_CON_REF(the_typename)
	GEN_SETTER_BY_RVAL_REF(the_typename)
	GEN_GETTER_BY_CON_REF(ident_term_equals_extra_list)
	GEN_SETTER_BY_RVAL_REF(ident_term_equals_extra_list)
};

class NodeParamModuleSublist : public NodeBase
{
protected:		// children
	Child _ident_term_equals_extra_list;
public:		// functions
	inline NodeParamModuleSublist(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident_term_equals_extra_list)
		: NodeBase(s_src_code_chunk),
		_ident_term_equals_extra_list(std::move(s_ident_term_equals_extra_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeParamModuleSublist);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:ident_term_equals_extra_list\n(", ident_term_equals_extra_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ParamModuleSublist;
	}
	virtual string name() const
	{
		return "ParamModuleSublist";
	}
	GEN_GETTER_BY_CON_REF(ident_term_equals_extra_list)
	GEN_SETTER_BY_RVAL_REF(ident_term_equals_extra_list)
};

class NodeParamList : public NodeList
{
public:		// functions
	inline NodeParamList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeParamList);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ParamList;
	}
	virtual string name() const
	{
		return "ParamList";
	}
};

class NodeArgList : public NodeList
{
public:		// functions
	inline NodeArgList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeArgList);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ArgList;
	}
	virtual string name() const
	{
		return "ArgList";
	}
};

class NodeLeftRightBase : public NodeBase
{
protected:		// children
	Child _left,
		_right;
public:		// functions
	inline NodeLeftRightBase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBase(s_src_code_chunk),
		_left(std::move(s_left)),
		_right(std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeLeftRightBase);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::LeftRightBase;
	}
	virtual string name() const
	{
		return "LeftRightBase";
	}
	GEN_GETTER_BY_CON_REF(left)
	GEN_SETTER_BY_RVAL_REF(left)
	GEN_GETTER_BY_CON_REF(right)
	GEN_SETTER_BY_RVAL_REF(right)
};

class NodeIdentTerminal : public NodeList
{
protected:		// children
	Child _ident;
public:		// functions
	inline NodeIdentTerminal(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident)
		: NodeList(s_src_code_chunk),
		_ident(std::move(s_ident))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentTerminal);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:ident\n(", ident()->dbg_to_string(), "\n)\n");
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::IdentTerminal;
	}
	virtual string name() const
	{
		return "IdentTerminal";
	}
	GEN_GETTER_BY_CON_REF(ident)
	GEN_SETTER_BY_RVAL_REF(ident)
};

class NodeIdentMemberAccess : public NodeBase
{
public:		// functions
	inline NodeIdentMemberAccess(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentMemberAccess);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::IdentMemberAccess;
	}
	virtual string name() const
	{
		return "IdentMemberAccess";
	}
};

class NodeIdentScopeAccess : public NodeBase
{
public:		// functions
	inline NodeIdentScopeAccess(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentScopeAccess);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::IdentScopeAccess;
	}
	virtual string name() const
	{
		return "IdentScopeAccess";
	}
};

class NodeCall : public NodeBase
{
protected:		// children
	Child _ident_or_ident_terminal,
		_param_inst_list,
		_arg_inst_list;
public:		// functions
	inline NodeCall(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident_or_ident_terminal,
		Child&& s_param_inst_list,
		Child&& s_arg_inst_list)
		: NodeBase(s_src_code_chunk),
		_ident_or_ident_terminal(std::move(s_ident_or_ident_terminal)),
		_param_inst_list(std::move(s_param_inst_list)),
		_arg_inst_list(std::move(s_arg_inst_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeCall);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:ident_or_ident_terminal\n(", ident_or_ident_terminal()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:param_inst_list\n(", param_inst_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:arg_inst_list\n(", arg_inst_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Call;
	}
	virtual string name() const
	{
		return "Call";
	}
	GEN_GETTER_BY_CON_REF(ident_or_ident_terminal)
	GEN_SETTER_BY_RVAL_REF(ident_or_ident_terminal)
	GEN_GETTER_BY_CON_REF(param_inst_list)
	GEN_SETTER_BY_RVAL_REF(param_inst_list)
	GEN_GETTER_BY_CON_REF(arg_inst_list)
	GEN_SETTER_BY_RVAL_REF(arg_inst_list)
};

class NodeIdentEtc : public NodeList
{
public:		// functions
	inline NodeIdentEtc(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentEtc);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::IdentEtc;
	}
	virtual string name() const
	{
		return "IdentEtc";
	}
};

class NodeNumExpr : public NodeBase
{
protected:		// variables
	BigNum _n;
public:		// functions
	inline NodeNumExpr(const SrcCodeChunk& s_src_code_chunk,
		const BigNum& s_n)
		: NodeBase(s_src_code_chunk), _n(s_n)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeNumExpr);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _n(", _n, ")\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::NumExpr;
	}
	virtual string name() const
	{
		return "NumExpr";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(n)
};

class NodeSizedNumExpr : public NodeNumExpr
{
protected:		// children
	Child _size;
public:		// functions
	inline NodeSizedNumExpr(const SrcCodeChunk& s_src_code_chunk,
		const BigNum& s_n,
		Child&& s_size)
		: NodeNumExpr(s_src_code_chunk,
		s_n),
		_size(std::move(s_size))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSizedNumExpr);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _n(", _n, ")\n");
		ret += sconcat("  child:size\n(", size()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::SizedNumExpr;
	}
	virtual string name() const
	{
		return "SizedNumExpr";
	}
	GEN_GETTER_BY_CON_REF(size)
	GEN_SETTER_BY_RVAL_REF(size)
};

class NodeBracketPair : public NodeBase
{
protected:		// children
	Child _left,
		_right;
public:		// functions
	inline NodeBracketPair(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBase(s_src_code_chunk),
		_left(std::move(s_left)),
		_right(std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBracketPair);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BracketPair;
	}
	virtual string name() const
	{
		return "BracketPair";
	}
	GEN_GETTER_BY_CON_REF(left)
	GEN_SETTER_BY_RVAL_REF(left)
	GEN_GETTER_BY_CON_REF(right)
	GEN_SETTER_BY_RVAL_REF(right)
};

class NodeParenPair : public NodeBase
{
public:		// functions
	inline NodeParenPair(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeParenPair);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ParenPair;
	}
	virtual string name() const
	{
		return "ParenPair";
	}
};

class NodeHasString : public NodeBase
{
protected:		// variables
	string _s;
public:		// functions
	inline NodeHasString(const SrcCodeChunk& s_src_code_chunk,
		const string& s_s)
		: NodeBase(s_src_code_chunk), _s(s_s)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeHasString);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _s(", _s, ")\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::HasString;
	}
	virtual string name() const
	{
		return "HasString";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(s)
};

class NodeIdent : public NodeHasString
{
public:		// functions
	inline NodeIdent(const SrcCodeChunk& s_src_code_chunk,
		const string& s_s)
		: NodeHasString(s_src_code_chunk,
		s_s)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdent);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _s(", _s, ")\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Ident;
	}
	virtual string name() const
	{
		return "Ident";
	}
};

class NodeConstString : public NodeHasString
{
public:		// functions
	inline NodeConstString(const SrcCodeChunk& s_src_code_chunk,
		const string& s_s)
		: NodeHasString(s_src_code_chunk,
		s_s)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeConstString);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _s(", _s, ")\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ConstString;
	}
	virtual string name() const
	{
		return "ConstString";
	}
};

class NodeScopeBehav : public NodeList
{
public:		// functions
	inline NodeScopeBehav(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeBehav);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ScopeBehav;
	}
	virtual string name() const
	{
		return "ScopeBehav";
	}
};

class NodeEnum : public NodeBase
{
protected:		// children
	Child _the_typename,
		_ident,
		_scope,
		_var_list;
public:		// functions
	inline NodeEnum(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_the_typename,
		Child&& s_ident,
		Child&& s_scope,
		Child&& s_var_list)
		: NodeBase(s_src_code_chunk),
		_the_typename(std::move(s_the_typename)),
		_ident(std::move(s_ident)),
		_scope(std::move(s_scope)),
		_var_list(std::move(s_var_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeEnum);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:the_typename\n(", the_typename()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:ident\n(", ident()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:var_list\n(", var_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Enum;
	}
	virtual string name() const
	{
		return "Enum";
	}
	GEN_GETTER_BY_CON_REF(the_typename)
	GEN_SETTER_BY_RVAL_REF(the_typename)
	GEN_GETTER_BY_CON_REF(ident)
	GEN_SETTER_BY_RVAL_REF(ident)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
	GEN_GETTER_BY_CON_REF(var_list)
	GEN_SETTER_BY_RVAL_REF(var_list)
};

class NodeScopeEnum : public NodeList
{
public:		// functions
	inline NodeScopeEnum(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeEnum);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ScopeEnum;
	}
	virtual string name() const
	{
		return "ScopeEnum";
	}
};

class NodeClass : public NodeBase
{
protected:		// variables
	bool _packed;
protected:		// children
	Child _ident,
		_param_list,
		_extends,
		_scope,
		_var_list;
public:		// functions
	inline NodeClass(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_packed,
		Child&& s_ident,
		Child&& s_param_list,
		Child&& s_extends,
		Child&& s_scope,
		Child&& s_var_list)
		: NodeBase(s_src_code_chunk), _packed(s_packed),
		_ident(std::move(s_ident)),
		_param_list(std::move(s_param_list)),
		_extends(std::move(s_extends)),
		_scope(std::move(s_scope)),
		_var_list(std::move(s_var_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeClass);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _packed(", _packed, ")\n");
		ret += sconcat("  child:ident\n(", ident()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:param_list\n(", param_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:extends\n(", extends()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:var_list\n(", var_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Class;
	}
	virtual string name() const
	{
		return "Class";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(packed)
	GEN_GETTER_BY_CON_REF(ident)
	GEN_SETTER_BY_RVAL_REF(ident)
	GEN_GETTER_BY_CON_REF(param_list)
	GEN_SETTER_BY_RVAL_REF(param_list)
	GEN_GETTER_BY_CON_REF(extends)
	GEN_SETTER_BY_RVAL_REF(extends)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
	GEN_GETTER_BY_CON_REF(var_list)
	GEN_SETTER_BY_RVAL_REF(var_list)
};

class NodeScopeClass : public NodeList
{
public:		// functions
	inline NodeScopeClass(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeClass);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ScopeClass;
	}
	virtual string name() const
	{
		return "ScopeClass";
	}
};

class NodeExtends : public NodeBase
{
protected:		// variables
	bool _is_virtual;
protected:		// children
	Child _the_typename;
public:		// functions
	inline NodeExtends(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_is_virtual,
		Child&& s_the_typename)
		: NodeBase(s_src_code_chunk), _is_virtual(s_is_virtual),
		_the_typename(std::move(s_the_typename))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExtends);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _is_virtual(", _is_virtual, ")\n");
		ret += sconcat("  child:the_typename\n(", the_typename()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Extends;
	}
	virtual string name() const
	{
		return "Extends";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(is_virtual)
	GEN_GETTER_BY_CON_REF(the_typename)
	GEN_SETTER_BY_RVAL_REF(the_typename)
};

class NodeMemberCallable : public NodeBase
{
protected:		// variables
	bool _is_const;
	bool _is_virtual;
	bool _is_static;
	bool _is_ref;
protected:		// children
	Child _callable;
public:		// functions
	inline NodeMemberCallable(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_is_const,
		const bool& s_is_virtual,
		const bool& s_is_static,
		const bool& s_is_ref,
		Child&& s_callable)
		: NodeBase(s_src_code_chunk), _is_const(s_is_const),
		_is_virtual(s_is_virtual),
		_is_static(s_is_static),
		_is_ref(s_is_ref),
		_callable(std::move(s_callable))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeMemberCallable);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _is_const(", _is_const, ")\n");
		ret += sconcat("  _is_virtual(", _is_virtual, ")\n");
		ret += sconcat("  _is_static(", _is_static, ")\n");
		ret += sconcat("  _is_ref(", _is_ref, ")\n");
		ret += sconcat("  child:callable\n(", callable()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::MemberCallable;
	}
	virtual string name() const
	{
		return "MemberCallable";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(is_const)
	GEN_GETTER_AND_SETTER_BY_CON_REF(is_virtual)
	GEN_GETTER_AND_SETTER_BY_CON_REF(is_static)
	GEN_GETTER_AND_SETTER_BY_CON_REF(is_ref)
	GEN_GETTER_BY_CON_REF(callable)
	GEN_SETTER_BY_RVAL_REF(callable)
};

class NodeUnion : public NodeBase
{
protected:		// children
	Child _ident,
		_scope,
		_var_list;
public:		// functions
	inline NodeUnion(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident,
		Child&& s_scope,
		Child&& s_var_list)
		: NodeBase(s_src_code_chunk),
		_ident(std::move(s_ident)),
		_scope(std::move(s_scope)),
		_var_list(std::move(s_var_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnion);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:ident\n(", ident()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:var_list\n(", var_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Union;
	}
	virtual string name() const
	{
		return "Union";
	}
	GEN_GETTER_BY_CON_REF(ident)
	GEN_SETTER_BY_RVAL_REF(ident)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
	GEN_GETTER_BY_CON_REF(var_list)
	GEN_SETTER_BY_RVAL_REF(var_list)
};

class NodeScopeUnion : public NodeList
{
public:		// functions
	inline NodeScopeUnion(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeUnion);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ScopeUnion;
	}
	virtual string name() const
	{
		return "ScopeUnion";
	}
};

class NodeParamPossibleTypename : public NodeBase
{
protected:		// children
	Child _primary,
		_param_inst_list;
public:		// functions
	inline NodeParamPossibleTypename(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_primary,
		Child&& s_param_inst_list)
		: NodeBase(s_src_code_chunk),
		_primary(std::move(s_primary)),
		_param_inst_list(std::move(s_param_inst_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeParamPossibleTypename);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:primary\n(", primary()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:param_inst_list\n(", param_inst_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ParamPossibleTypename;
	}
	virtual string name() const
	{
		return "ParamPossibleTypename";
	}
	GEN_GETTER_BY_CON_REF(primary)
	GEN_SETTER_BY_RVAL_REF(primary)
	GEN_GETTER_BY_CON_REF(param_inst_list)
	GEN_SETTER_BY_RVAL_REF(param_inst_list)
};

class NodeNoParamPossibleTypename : public NodeBase
{
protected:		// children
	Child _primary;
public:		// functions
	inline NodeNoParamPossibleTypename(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_primary)
		: NodeBase(s_src_code_chunk),
		_primary(std::move(s_primary))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeNoParamPossibleTypename);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:primary\n(", primary()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::NoParamPossibleTypename;
	}
	virtual string name() const
	{
		return "NoParamPossibleTypename";
	}
	GEN_GETTER_BY_CON_REF(primary)
	GEN_SETTER_BY_RVAL_REF(primary)
};

class NodeTypeof : public NodeBase
{
protected:		// children
	Child _expr_or_typename;
public:		// functions
	inline NodeTypeof(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr_or_typename)
		: NodeBase(s_src_code_chunk),
		_expr_or_typename(std::move(s_expr_or_typename))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeTypeof);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr_or_typename\n(", expr_or_typename()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Typeof;
	}
	virtual string name() const
	{
		return "Typeof";
	}
	GEN_GETTER_BY_CON_REF(expr_or_typename)
	GEN_SETTER_BY_RVAL_REF(expr_or_typename)
};

class NodeTypeRange : public NodeBase
{
protected:		// children
	Child _range_suffix;
public:		// functions
	inline NodeTypeRange(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_range_suffix)
		: NodeBase(s_src_code_chunk),
		_range_suffix(std::move(s_range_suffix))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeTypeRange);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:range_suffix\n(", range_suffix()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::TypeRange;
	}
	virtual string name() const
	{
		return "TypeRange";
	}
	GEN_GETTER_BY_CON_REF(range_suffix)
	GEN_SETTER_BY_RVAL_REF(range_suffix)
};

class NodeRangeSuffix : public NodeBase
{
public:		// functions
	inline NodeRangeSuffix(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeRangeSuffix);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::RangeSuffix;
	}
	virtual string name() const
	{
		return "RangeSuffix";
	}
};

class NodeAuto : public NodeBase
{
public:		// functions
	inline NodeAuto(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeAuto);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Auto;
	}
	virtual string name() const
	{
		return "Auto";
	}
};

class NodeVoid : public NodeBase
{
public:		// functions
	inline NodeVoid(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeVoid);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Void;
	}
	virtual string name() const
	{
		return "Void";
	}
};

class NodeUwire : public NodeBase
{
public:		// functions
	inline NodeUwire(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUwire);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Uwire;
	}
	virtual string name() const
	{
		return "Uwire";
	}
};

class NodeSwire : public NodeBase
{
public:		// functions
	inline NodeSwire(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSwire);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Swire;
	}
	virtual string name() const
	{
		return "Swire";
	}
};

class NodeUbit : public NodeBase
{
public:		// functions
	inline NodeUbit(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUbit);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Ubit;
	}
	virtual string name() const
	{
		return "Ubit";
	}
};

class NodeSbit : public NodeBase
{
public:		// functions
	inline NodeSbit(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSbit);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Sbit;
	}
	virtual string name() const
	{
		return "Sbit";
	}
};

class NodeUbyte : public NodeBase
{
public:		// functions
	inline NodeUbyte(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUbyte);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Ubyte;
	}
	virtual string name() const
	{
		return "Ubyte";
	}
};

class NodeSbyte : public NodeBase
{
public:		// functions
	inline NodeSbyte(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSbyte);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Sbyte;
	}
	virtual string name() const
	{
		return "Sbyte";
	}
};

class NodeUshortint : public NodeBase
{
public:		// functions
	inline NodeUshortint(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUshortint);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Ushortint;
	}
	virtual string name() const
	{
		return "Ushortint";
	}
};

class NodeSshortint : public NodeBase
{
public:		// functions
	inline NodeSshortint(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSshortint);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Sshortint;
	}
	virtual string name() const
	{
		return "Sshortint";
	}
};

class NodeUint : public NodeBase
{
public:		// functions
	inline NodeUint(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUint);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Uint;
	}
	virtual string name() const
	{
		return "Uint";
	}
};

class NodeSint : public NodeBase
{
public:		// functions
	inline NodeSint(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSint);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Sint;
	}
	virtual string name() const
	{
		return "Sint";
	}
};

class NodeUlongint : public NodeBase
{
public:		// functions
	inline NodeUlongint(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUlongint);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Ulongint;
	}
	virtual string name() const
	{
		return "Ulongint";
	}
};

class NodeSlongint : public NodeBase
{
public:		// functions
	inline NodeSlongint(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSlongint);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Slongint;
	}
	virtual string name() const
	{
		return "Slongint";
	}
};

class NodeSelf : public NodeBase
{
public:		// functions
	inline NodeSelf(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSelf);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Self;
	}
	virtual string name() const
	{
		return "Self";
	}
};

class NodePosParamArgInstList : public NodeList
{
public:		// functions
	inline NodePosParamArgInstList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodePosParamArgInstList);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::PosParamArgInstList;
	}
	virtual string name() const
	{
		return "PosParamArgInstList";
	}
};

class NodeNamedParamArgInstList : public NodeList
{
public:		// functions
	inline NodeNamedParamArgInstList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeNamedParamArgInstList);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::NamedParamArgInstList;
	}
	virtual string name() const
	{
		return "NamedParamArgInstList";
	}
};

class NodeOneParamArgInst : public NodeLeftRightBase
{
public:		// functions
	inline NodeOneParamArgInst(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeLeftRightBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeOneParamArgInst);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::OneParamArgInst;
	}
	virtual string name() const
	{
		return "OneParamArgInst";
	}
};

class NodeExprBase : public NodeBase
{
public:		// functions
	inline NodeExprBase(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBase);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ExprBase;
	}
	virtual string name() const
	{
		return "ExprBase";
	}
};

class NodeBinopExprBase : public NodeExprBase
{
protected:		// children
	Child _left,
		_right;
public:		// functions
	inline NodeBinopExprBase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBase(s_src_code_chunk),
		_left(std::move(s_left)),
		_right(std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprBase);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprBase;
	}
	virtual string name() const
	{
		return "BinopExprBase";
	}
	GEN_GETTER_BY_CON_REF(left)
	GEN_SETTER_BY_RVAL_REF(left)
	GEN_GETTER_BY_CON_REF(right)
	GEN_SETTER_BY_RVAL_REF(right)
};

class NodeUnopExprBase : public NodeExprBase
{
protected:		// children
	Child _child;
public:		// functions
	inline NodeUnopExprBase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprBase(s_src_code_chunk),
		_child(std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprBase);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprBase;
	}
	virtual string name() const
	{
		return "UnopExprBase";
	}
	GEN_GETTER_BY_CON_REF(child)
	GEN_SETTER_BY_RVAL_REF(child)
};

class NodeBinopExprLogAnd : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprLogAnd(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprLogAnd);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprLogAnd;
	}
	virtual string name() const
	{
		return "BinopExprLogAnd";
	}
};

class NodeBinopExprLogOr : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprLogOr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprLogOr);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprLogOr;
	}
	virtual string name() const
	{
		return "BinopExprLogOr";
	}
};

class NodeBinopExprCmpEq : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprCmpEq(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprCmpEq);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprCmpEq;
	}
	virtual string name() const
	{
		return "BinopExprCmpEq";
	}
};

class NodeBinopExprCmpNe : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprCmpNe(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprCmpNe);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprCmpNe;
	}
	virtual string name() const
	{
		return "BinopExprCmpNe";
	}
};

class NodeBinopExprCmpLt : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprCmpLt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprCmpLt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprCmpLt;
	}
	virtual string name() const
	{
		return "BinopExprCmpLt";
	}
};

class NodeBinopExprCmpGt : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprCmpGt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprCmpGt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprCmpGt;
	}
	virtual string name() const
	{
		return "BinopExprCmpGt";
	}
};

class NodeBinopExprCmpLe : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprCmpLe(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprCmpLe);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprCmpLe;
	}
	virtual string name() const
	{
		return "BinopExprCmpLe";
	}
};

class NodeBinopExprCmpGe : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprCmpGe(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprCmpGe);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprCmpGe;
	}
	virtual string name() const
	{
		return "BinopExprCmpGe";
	}
};

class NodeBinopExprPlus : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprPlus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprPlus);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprPlus;
	}
	virtual string name() const
	{
		return "BinopExprPlus";
	}
};

class NodeBinopExprMinus : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprMinus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprMinus);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprMinus;
	}
	virtual string name() const
	{
		return "BinopExprMinus";
	}
};

class NodeBinopExprMul : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprMul(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprMul);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprMul;
	}
	virtual string name() const
	{
		return "BinopExprMul";
	}
};

class NodeBinopExprDiv : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprDiv(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprDiv);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprDiv;
	}
	virtual string name() const
	{
		return "BinopExprDiv";
	}
};

class NodeBinopExprMod : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprMod(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprMod);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprMod;
	}
	virtual string name() const
	{
		return "BinopExprMod";
	}
};

class NodeBinopExprBitAnd : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprBitAnd(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprBitAnd);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprBitAnd;
	}
	virtual string name() const
	{
		return "BinopExprBitAnd";
	}
};

class NodeBinopExprBitOr : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprBitOr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprBitOr);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprBitOr;
	}
	virtual string name() const
	{
		return "BinopExprBitOr";
	}
};

class NodeBinopExprBitXor : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprBitXor(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprBitXor);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprBitXor;
	}
	virtual string name() const
	{
		return "BinopExprBitXor";
	}
};

class NodeBinopExprBitLsl : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprBitLsl(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprBitLsl);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprBitLsl;
	}
	virtual string name() const
	{
		return "BinopExprBitLsl";
	}
};

class NodeBinopExprBitLsr : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprBitLsr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprBitLsr);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprBitLsr;
	}
	virtual string name() const
	{
		return "BinopExprBitLsr";
	}
};

class NodeBinopExprBitAsr : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprBitAsr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprBitAsr);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprBitAsr;
	}
	virtual string name() const
	{
		return "BinopExprBitAsr";
	}
};

class NodeUnopExprLogNot : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprLogNot(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprLogNot);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprLogNot;
	}
	virtual string name() const
	{
		return "UnopExprLogNot";
	}
};

class NodeUnopExprBitNot : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprBitNot(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprBitNot);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprBitNot;
	}
	virtual string name() const
	{
		return "UnopExprBitNot";
	}
};

class NodeUnopExprPlus : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprPlus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprPlus);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprPlus;
	}
	virtual string name() const
	{
		return "UnopExprPlus";
	}
};

class NodeUnopExprMinus : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprMinus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprMinus);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprMinus;
	}
	virtual string name() const
	{
		return "UnopExprMinus";
	}
};

class NodeUnopExprDollarUnsigned : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarUnsigned(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarUnsigned);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarUnsigned;
	}
	virtual string name() const
	{
		return "UnopExprDollarUnsigned";
	}
};

class NodeUnopExprDollarSigned : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarSigned(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarSigned);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarSigned;
	}
	virtual string name() const
	{
		return "UnopExprDollarSigned";
	}
};

class NodeUnopExprDollarIsUnsigned : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarIsUnsigned(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarIsUnsigned);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarIsUnsigned;
	}
	virtual string name() const
	{
		return "UnopExprDollarIsUnsigned";
	}
};

class NodeUnopExprDollarIsSigned : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarIsSigned(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarIsSigned);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarIsSigned;
	}
	virtual string name() const
	{
		return "UnopExprDollarIsSigned";
	}
};

class NodeUnopExprDollarRange : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarRange(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarRange);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarRange;
	}
	virtual string name() const
	{
		return "UnopExprDollarRange";
	}
};

class NodeUnopExprDollarRevrange : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarRevrange(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarRevrange);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarRevrange;
	}
	virtual string name() const
	{
		return "UnopExprDollarRevrange";
	}
};

class NodeUnopExprDollarSize : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarSize(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarSize);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarSize;
	}
	virtual string name() const
	{
		return "UnopExprDollarSize";
	}
};

class NodeUnopExprDollarFirst : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarFirst(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarFirst);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarFirst;
	}
	virtual string name() const
	{
		return "UnopExprDollarFirst";
	}
};

class NodeUnopExprDollarLast : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarLast(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarLast);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarLast;
	}
	virtual string name() const
	{
		return "UnopExprDollarLast";
	}
};

class NodeUnopExprDollarHigh : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarHigh(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarHigh);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarHigh;
	}
	virtual string name() const
	{
		return "UnopExprDollarHigh";
	}
};

class NodeUnopExprDollarLow : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarLow(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarLow);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarLow;
	}
	virtual string name() const
	{
		return "UnopExprDollarLow";
	}
};

class NodeUnopExprDollarClog2 : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprDollarClog2(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprDollarClog2);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprDollarClog2;
	}
	virtual string name() const
	{
		return "UnopExprDollarClog2";
	}
};

class NodeBinopExprDollarPow : public NodeBinopExprBase
{
public:		// functions
	inline NodeBinopExprDollarPow(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBinopExprBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBinopExprDollarPow);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BinopExprDollarPow;
	}
	virtual string name() const
	{
		return "BinopExprDollarPow";
	}
};

class NodePseudoExprDollarBase : public NodeBase
{
protected:		// children
	Child _child;
public:		// functions
	inline NodePseudoExprDollarBase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeBase(s_src_code_chunk),
		_child(std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodePseudoExprDollarBase);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::PseudoExprDollarBase;
	}
	virtual string name() const
	{
		return "PseudoExprDollarBase";
	}
	GEN_GETTER_BY_CON_REF(child)
	GEN_SETTER_BY_RVAL_REF(child)
};

class NodePseudoExprDollarPast : public NodePseudoExprDollarBase
{
public:		// functions
	inline NodePseudoExprDollarPast(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodePseudoExprDollarBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodePseudoExprDollarPast);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::PseudoExprDollarPast;
	}
	virtual string name() const
	{
		return "PseudoExprDollarPast";
	}
};

class NodePseudoExprDollarStable : public NodePseudoExprDollarBase
{
public:		// functions
	inline NodePseudoExprDollarStable(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodePseudoExprDollarBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodePseudoExprDollarStable);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::PseudoExprDollarStable;
	}
	virtual string name() const
	{
		return "PseudoExprDollarStable";
	}
};

class NodePseudoExprDollarRose : public NodePseudoExprDollarBase
{
public:		// functions
	inline NodePseudoExprDollarRose(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodePseudoExprDollarBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodePseudoExprDollarRose);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::PseudoExprDollarRose;
	}
	virtual string name() const
	{
		return "PseudoExprDollarRose";
	}
};

class NodePseudoExprDollarFell : public NodePseudoExprDollarBase
{
public:		// functions
	inline NodePseudoExprDollarFell(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodePseudoExprDollarBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodePseudoExprDollarFell);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::PseudoExprDollarFell;
	}
	virtual string name() const
	{
		return "PseudoExprDollarFell";
	}
};

class NodePseudoExprDollarGlobalClock : public NodeBase
{
public:		// functions
	inline NodePseudoExprDollarGlobalClock(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodePseudoExprDollarGlobalClock);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::PseudoExprDollarGlobalClock;
	}
	virtual string name() const
	{
		return "PseudoExprDollarGlobalClock";
	}
};

class NodeUnopExprTypeof : public NodeUnopExprBase
{
public:		// functions
	inline NodeUnopExprTypeof(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeUnopExprBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnopExprTypeof);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UnopExprTypeof;
	}
	virtual string name() const
	{
		return "UnopExprTypeof";
	}
};

class NodeCatExpr : public NodeExprBase
{
protected:		// children
	Child _list;
public:		// functions
	inline NodeCatExpr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_list)
		: NodeExprBase(s_src_code_chunk),
		_list(std::move(s_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeCatExpr);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:list\n(", list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::CatExpr;
	}
	virtual string name() const
	{
		return "CatExpr";
	}
	GEN_GETTER_BY_CON_REF(list)
	GEN_SETTER_BY_RVAL_REF(list)
};

class NodeListCat : public NodeList
{
public:		// functions
	inline NodeListCat(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeListCat);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ListCat;
	}
	virtual string name() const
	{
		return "ListCat";
	}
};

class NodeReplExpr : public NodeExprBase
{
protected:		// children
	Child _how_much_expr,
		_to_repl_expr;
public:		// functions
	inline NodeReplExpr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_how_much_expr,
		Child&& s_to_repl_expr)
		: NodeExprBase(s_src_code_chunk),
		_how_much_expr(std::move(s_how_much_expr)),
		_to_repl_expr(std::move(s_to_repl_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeReplExpr);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:how_much_expr\n(", how_much_expr()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:to_repl_expr\n(", to_repl_expr()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ReplExpr;
	}
	virtual string name() const
	{
		return "ReplExpr";
	}
	GEN_GETTER_BY_CON_REF(how_much_expr)
	GEN_SETTER_BY_RVAL_REF(how_much_expr)
	GEN_GETTER_BY_CON_REF(to_repl_expr)
	GEN_SETTER_BY_RVAL_REF(to_repl_expr)
};

class NodeRangeExprAny : public NodeExprBase
{
protected:		// children
	Child _which_range;
public:		// functions
	inline NodeRangeExprAny(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_which_range)
		: NodeExprBase(s_src_code_chunk),
		_which_range(std::move(s_which_range))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeRangeExprAny);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:which_range\n(", which_range()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::RangeExprAny;
	}
	virtual string name() const
	{
		return "RangeExprAny";
	}
	GEN_GETTER_BY_CON_REF(which_range)
	GEN_SETTER_BY_RVAL_REF(which_range)
};

class NodeRangeOne : public NodeBase
{
protected:		// children
	Child _child;
public:		// functions
	inline NodeRangeOne(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeBase(s_src_code_chunk),
		_child(std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeRangeOne);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:child\n(", child()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::RangeOne;
	}
	virtual string name() const
	{
		return "RangeOne";
	}
	GEN_GETTER_BY_CON_REF(child)
	GEN_SETTER_BY_RVAL_REF(child)
};

class NodeRangeTwo : public NodeLeftRightBase
{
public:		// functions
	inline NodeRangeTwo(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeLeftRightBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeRangeTwo);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::RangeTwo;
	}
	virtual string name() const
	{
		return "RangeTwo";
	}
};

class NodeStmtList : public NodeList
{
public:		// functions
	inline NodeStmtList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtList);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::StmtList;
	}
	virtual string name() const
	{
		return "StmtList";
	}
};

class NodeAnyForStmt : public NodeBase
{
protected:		// children
	Child _var,
		_items,
		_scope;
public:		// functions
	inline NodeAnyForStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_var,
		Child&& s_items,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_var(std::move(s_var)),
		_items(std::move(s_items)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeAnyForStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:var\n(", var()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:items\n(", items()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::AnyForStmt;
	}
	virtual string name() const
	{
		return "AnyForStmt";
	}
	GEN_GETTER_BY_CON_REF(var)
	GEN_SETTER_BY_RVAL_REF(var)
	GEN_GETTER_BY_CON_REF(items)
	GEN_SETTER_BY_RVAL_REF(items)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeForStmt : public NodeAnyForStmt
{
public:		// functions
	inline NodeForStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_var,
		Child&& s_items,
		Child&& s_scope)
		: NodeAnyForStmt(s_src_code_chunk,
		std::move(s_var),
		std::move(s_items),
		std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeForStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:var\n(", var()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:items\n(", items()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ForStmt;
	}
	virtual string name() const
	{
		return "ForStmt";
	}
};

class NodeGenerateForStmt : public NodeAnyForStmt
{
protected:		// children
	Child _label;
public:		// functions
	inline NodeGenerateForStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_label,
		Child&& s_var,
		Child&& s_items,
		Child&& s_scope)
		: NodeAnyForStmt(s_src_code_chunk,
		std::move(s_var),
		std::move(s_items),
		std::move(s_scope)),
		_label(std::move(s_label))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeGenerateForStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:label\n(", label()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:var\n(", var()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:items\n(", items()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::GenerateForStmt;
	}
	virtual string name() const
	{
		return "GenerateForStmt";
	}
	GEN_GETTER_BY_CON_REF(label)
	GEN_SETTER_BY_RVAL_REF(label)
};

class NodeIfStmt : public NodeBase
{
protected:		// children
	Child _cond_expr,
		_scope,
		_else_stmt;
public:		// functions
	inline NodeIfStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_scope,
		Child&& s_else_stmt)
		: NodeBase(s_src_code_chunk),
		_cond_expr(std::move(s_cond_expr)),
		_scope(std::move(s_scope)),
		_else_stmt(std::move(s_else_stmt))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIfStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:cond_expr\n(", cond_expr()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:else_stmt\n(", else_stmt()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::IfStmt;
	}
	virtual string name() const
	{
		return "IfStmt";
	}
	GEN_GETTER_BY_CON_REF(cond_expr)
	GEN_SETTER_BY_RVAL_REF(cond_expr)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
	GEN_GETTER_BY_CON_REF(else_stmt)
	GEN_SETTER_BY_RVAL_REF(else_stmt)
};

class NodeGenerateIfStmt : public NodeIfStmt
{
public:		// functions
	inline NodeGenerateIfStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_scope,
		Child&& s_else_stmt)
		: NodeIfStmt(s_src_code_chunk,
		std::move(s_cond_expr),
		std::move(s_scope),
		std::move(s_else_stmt))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeGenerateIfStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:cond_expr\n(", cond_expr()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:else_stmt\n(", else_stmt()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::GenerateIfStmt;
	}
	virtual string name() const
	{
		return "GenerateIfStmt";
	}
};

class NodeWhileStmt : public NodeBase
{
protected:		// children
	Child _cond_expr,
		_scope;
public:		// functions
	inline NodeWhileStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_cond_expr(std::move(s_cond_expr)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeWhileStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:cond_expr\n(", cond_expr()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::WhileStmt;
	}
	virtual string name() const
	{
		return "WhileStmt";
	}
	GEN_GETTER_BY_CON_REF(cond_expr)
	GEN_SETTER_BY_RVAL_REF(cond_expr)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeBehavAssignStmt : public NodeLeftRightBase
{
public:		// functions
	inline NodeBehavAssignStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeLeftRightBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBehavAssignStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::BehavAssignStmt;
	}
	virtual string name() const
	{
		return "BehavAssignStmt";
	}
};

class NodeContAssignStmt : public NodeLeftRightBase
{
public:		// functions
	inline NodeContAssignStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeLeftRightBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeContAssignStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ContAssignStmt;
	}
	virtual string name() const
	{
		return "ContAssignStmt";
	}
};

class NodeMemberAccessPublicStmt : public NodeBase
{
public:		// functions
	inline NodeMemberAccessPublicStmt(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeMemberAccessPublicStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::MemberAccessPublicStmt;
	}
	virtual string name() const
	{
		return "MemberAccessPublicStmt";
	}
};

class NodeMemberAccessProtectedStmt : public NodeBase
{
public:		// functions
	inline NodeMemberAccessProtectedStmt(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeMemberAccessProtectedStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::MemberAccessProtectedStmt;
	}
	virtual string name() const
	{
		return "MemberAccessProtectedStmt";
	}
};

class NodeMemberAccessPrivateStmt : public NodeBase
{
public:		// functions
	inline NodeMemberAccessPrivateStmt(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeMemberAccessPrivateStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::MemberAccessPrivateStmt;
	}
	virtual string name() const
	{
		return "MemberAccessPrivateStmt";
	}
};

class NodeSwitchStmt : public NodeBase
{
protected:		// children
	Child _expr,
		_scope;
public:		// functions
	inline NodeSwitchStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSwitchStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::SwitchStmt;
	}
	virtual string name() const
	{
		return "SwitchStmt";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeSwitchzStmt : public NodeSwitchStmt
{
public:		// functions
	inline NodeSwitchzStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr,
		Child&& s_scope)
		: NodeSwitchStmt(s_src_code_chunk,
		std::move(s_expr),
		std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSwitchzStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::SwitchzStmt;
	}
	virtual string name() const
	{
		return "SwitchzStmt";
	}
};

class NodeExprCaseItem : public NodeBase
{
protected:		// children
	Child _expr,
		_scope;
public:		// functions
	inline NodeExprCaseItem(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprCaseItem);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ExprCaseItem;
	}
	virtual string name() const
	{
		return "ExprCaseItem";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeDefaultCaseItem : public NodeBase
{
protected:		// children
	Child _scope;
public:		// functions
	inline NodeDefaultCaseItem(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDefaultCaseItem);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::DefaultCaseItem;
	}
	virtual string name() const
	{
		return "DefaultCaseItem";
	}
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeScopeSwitch : public NodeList
{
public:		// functions
	inline NodeScopeSwitch(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeSwitch);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ScopeSwitch;
	}
	virtual string name() const
	{
		return "ScopeSwitch";
	}
};

class NodeUsingStmt : public NodeLeftRightBase
{
public:		// functions
	inline NodeUsingStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeLeftRightBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUsingStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:left\n(", left()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:right\n(", right()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::UsingStmt;
	}
	virtual string name() const
	{
		return "UsingStmt";
	}
};

class NodeInstModuleStmt : public NodeBase
{
protected:		// children
	Child _module_ident,
		_param_inst_list,
		_inst_ident,
		_arg_inst_list;
public:		// functions
	inline NodeInstModuleStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_module_ident,
		Child&& s_param_inst_list,
		Child&& s_inst_ident,
		Child&& s_arg_inst_list)
		: NodeBase(s_src_code_chunk),
		_module_ident(std::move(s_module_ident)),
		_param_inst_list(std::move(s_param_inst_list)),
		_inst_ident(std::move(s_inst_ident)),
		_arg_inst_list(std::move(s_arg_inst_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeInstModuleStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:module_ident\n(", module_ident()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:param_inst_list\n(", param_inst_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:inst_ident\n(", inst_ident()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:arg_inst_list\n(", arg_inst_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::InstModuleStmt;
	}
	virtual string name() const
	{
		return "InstModuleStmt";
	}
	GEN_GETTER_BY_CON_REF(module_ident)
	GEN_SETTER_BY_RVAL_REF(module_ident)
	GEN_GETTER_BY_CON_REF(param_inst_list)
	GEN_SETTER_BY_RVAL_REF(param_inst_list)
	GEN_GETTER_BY_CON_REF(inst_ident)
	GEN_SETTER_BY_RVAL_REF(inst_ident)
	GEN_GETTER_BY_CON_REF(arg_inst_list)
	GEN_SETTER_BY_RVAL_REF(arg_inst_list)
};

class NodeReturnStmt : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeReturnStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeReturnStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ReturnStmt;
	}
	virtual string name() const
	{
		return "ReturnStmt";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeDollarResizeStmt : public NodeBase
{
protected:		// children
	Child _ident_etc,
		_expr;
public:		// functions
	inline NodeDollarResizeStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident_etc,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_ident_etc(std::move(s_ident_etc)),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDollarResizeStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:ident_etc\n(", ident_etc()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::DollarResizeStmt;
	}
	virtual string name() const
	{
		return "DollarResizeStmt";
	}
	GEN_GETTER_BY_CON_REF(ident_etc)
	GEN_SETTER_BY_RVAL_REF(ident_etc)
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeInitialBlock : public NodeBase
{
protected:		// children
	Child _scope;
public:		// functions
	inline NodeInitialBlock(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeInitialBlock);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::InitialBlock;
	}
	virtual string name() const
	{
		return "InitialBlock";
	}
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeAlwaysCombBlock : public NodeBase
{
protected:		// children
	Child _scope;
public:		// functions
	inline NodeAlwaysCombBlock(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeAlwaysCombBlock);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::AlwaysCombBlock;
	}
	virtual string name() const
	{
		return "AlwaysCombBlock";
	}
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeAlwaysBlkBlock : public NodeBase
{
protected:		// children
	Child _edge_list,
		_scope;
public:		// functions
	inline NodeAlwaysBlkBlock(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_edge_list,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_edge_list(std::move(s_edge_list)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeAlwaysBlkBlock);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:edge_list\n(", edge_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::AlwaysBlkBlock;
	}
	virtual string name() const
	{
		return "AlwaysBlkBlock";
	}
	GEN_GETTER_BY_CON_REF(edge_list)
	GEN_SETTER_BY_RVAL_REF(edge_list)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeAlwaysFfBlock : public NodeBase
{
protected:		// children
	Child _edge_list,
		_scope;
public:		// functions
	inline NodeAlwaysFfBlock(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_edge_list,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_edge_list(std::move(s_edge_list)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeAlwaysFfBlock);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:edge_list\n(", edge_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::AlwaysFfBlock;
	}
	virtual string name() const
	{
		return "AlwaysFfBlock";
	}
	GEN_GETTER_BY_CON_REF(edge_list)
	GEN_SETTER_BY_RVAL_REF(edge_list)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeAssertStmt : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeAssertStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeAssertStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::AssertStmt;
	}
	virtual string name() const
	{
		return "AssertStmt";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeAssumeStmt : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeAssumeStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeAssumeStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::AssumeStmt;
	}
	virtual string name() const
	{
		return "AssumeStmt";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeCoverStmt : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeCoverStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeCoverStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::CoverStmt;
	}
	virtual string name() const
	{
		return "CoverStmt";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeRestrictStmt : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeRestrictStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeRestrictStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::RestrictStmt;
	}
	virtual string name() const
	{
		return "RestrictStmt";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeStaticAssertStmt : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeStaticAssertStmt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStaticAssertStmt);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::StaticAssertStmt;
	}
	virtual string name() const
	{
		return "StaticAssertStmt";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodePosedgeInst : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodePosedgeInst(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodePosedgeInst);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::PosedgeInst;
	}
	virtual string name() const
	{
		return "PosedgeInst";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeNegedgeInst : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeNegedgeInst(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeNegedgeInst);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:expr\n(", expr()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::NegedgeInst;
	}
	virtual string name() const
	{
		return "NegedgeInst";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeEdgeList : public NodeList
{
public:		// functions
	inline NodeEdgeList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeEdgeList);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::EdgeList;
	}
	virtual string name() const
	{
		return "EdgeList";
	}
};

class NodeDeclCallable : public NodeBase
{
protected:		// children
	Child _param_list,
		_arg_list,
		_ident_or_op,
		_scope;
public:		// functions
	inline NodeDeclCallable(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_param_list,
		Child&& s_arg_list,
		Child&& s_ident_or_op,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_param_list(std::move(s_param_list)),
		_arg_list(std::move(s_arg_list)),
		_ident_or_op(std::move(s_ident_or_op)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclCallable);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:param_list\n(", param_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:arg_list\n(", arg_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:ident_or_op\n(", ident_or_op()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::DeclCallable;
	}
	virtual string name() const
	{
		return "DeclCallable";
	}
	GEN_GETTER_BY_CON_REF(param_list)
	GEN_SETTER_BY_RVAL_REF(param_list)
	GEN_GETTER_BY_CON_REF(arg_list)
	GEN_SETTER_BY_RVAL_REF(arg_list)
	GEN_GETTER_BY_CON_REF(ident_or_op)
	GEN_SETTER_BY_RVAL_REF(ident_or_op)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeDeclFunc : public NodeDeclCallable
{
protected:		// children
	Child _the_typename;
public:		// functions
	inline NodeDeclFunc(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_the_typename,
		Child&& s_param_list,
		Child&& s_arg_list,
		Child&& s_ident_or_op,
		Child&& s_scope)
		: NodeDeclCallable(s_src_code_chunk,
		std::move(s_param_list),
		std::move(s_arg_list),
		std::move(s_ident_or_op),
		std::move(s_scope)),
		_the_typename(std::move(s_the_typename))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclFunc);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:the_typename\n(", the_typename()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:param_list\n(", param_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:arg_list\n(", arg_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:ident_or_op\n(", ident_or_op()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::DeclFunc;
	}
	virtual string name() const
	{
		return "DeclFunc";
	}
	GEN_GETTER_BY_CON_REF(the_typename)
	GEN_SETTER_BY_RVAL_REF(the_typename)
};

class NodeDeclProc : public NodeDeclCallable
{
protected:		// variables
	bool _is_port;
public:		// functions
	inline NodeDeclProc(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_is_port,
		Child&& s_param_list,
		Child&& s_arg_list,
		Child&& s_ident_or_op,
		Child&& s_scope)
		: NodeDeclCallable(s_src_code_chunk,
		std::move(s_param_list),
		std::move(s_arg_list),
		std::move(s_ident_or_op),
		std::move(s_scope)), _is_port(s_is_port)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclProc);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _is_port(", _is_port, ")\n");
		ret += sconcat("  child:param_list\n(", param_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:arg_list\n(", arg_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:ident_or_op\n(", ident_or_op()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::DeclProc;
	}
	virtual string name() const
	{
		return "DeclProc";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(is_port)
};

class NodeDeclTask : public NodeDeclCallable
{
public:		// functions
	inline NodeDeclTask(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_param_list,
		Child&& s_arg_list,
		Child&& s_ident_or_op,
		Child&& s_scope)
		: NodeDeclCallable(s_src_code_chunk,
		std::move(s_param_list),
		std::move(s_arg_list),
		std::move(s_ident_or_op),
		std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclTask);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:param_list\n(", param_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:arg_list\n(", arg_list()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:ident_or_op\n(", ident_or_op()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::DeclTask;
	}
	virtual string name() const
	{
		return "DeclTask";
	}
};

class NodeIdentTermEqualsExtra : public NodeBase
{
protected:		// children
	Child _ident_terminal,
		_extra;
public:		// functions
	inline NodeIdentTermEqualsExtra(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident_terminal,
		Child&& s_extra)
		: NodeBase(s_src_code_chunk),
		_ident_terminal(std::move(s_ident_terminal)),
		_extra(std::move(s_extra))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentTermEqualsExtra);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:ident_terminal\n(", ident_terminal()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:extra\n(", extra()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::IdentTermEqualsExtra;
	}
	virtual string name() const
	{
		return "IdentTermEqualsExtra";
	}
	GEN_GETTER_BY_CON_REF(ident_terminal)
	GEN_SETTER_BY_RVAL_REF(ident_terminal)
	GEN_GETTER_BY_CON_REF(extra)
	GEN_SETTER_BY_RVAL_REF(extra)
};

class NodeIdentTermEqualsExtraList : public NodeList
{
public:		// functions
	inline NodeIdentTermEqualsExtraList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentTermEqualsExtraList);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::IdentTermEqualsExtraList;
	}
	virtual string name() const
	{
		return "IdentTermEqualsExtraList";
	}
};

class NodeDeclConstList : public NodeBase
{
protected:		// children
	Child _the_typename,
		_ident_term_equals_extra_list;
public:		// functions
	inline NodeDeclConstList(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_the_typename,
		Child&& s_ident_term_equals_extra_list)
		: NodeBase(s_src_code_chunk),
		_the_typename(std::move(s_the_typename)),
		_ident_term_equals_extra_list(std::move(s_ident_term_equals_extra_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclConstList);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:the_typename\n(", the_typename()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:ident_term_equals_extra_list\n(", ident_term_equals_extra_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::DeclConstList;
	}
	virtual string name() const
	{
		return "DeclConstList";
	}
	GEN_GETTER_BY_CON_REF(the_typename)
	GEN_SETTER_BY_RVAL_REF(the_typename)
	GEN_GETTER_BY_CON_REF(ident_term_equals_extra_list)
	GEN_SETTER_BY_RVAL_REF(ident_term_equals_extra_list)
};

class NodeDeclVarList : public NodeDeclConstList
{
public:		// functions
	inline NodeDeclVarList(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_the_typename,
		Child&& s_ident_term_equals_extra_list)
		: NodeDeclConstList(s_src_code_chunk,
		std::move(s_the_typename),
		std::move(s_ident_term_equals_extra_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclVarList);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:the_typename\n(", the_typename()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:ident_term_equals_extra_list\n(", ident_term_equals_extra_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::DeclVarList;
	}
	virtual string name() const
	{
		return "DeclVarList";
	}
};

class NodeModport : public NodeList
{
protected:		// children
	Child _ident;
public:		// functions
	inline NodeModport(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident)
		: NodeList(s_src_code_chunk),
		_ident(std::move(s_ident))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeModport);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:ident\n(", ident()->dbg_to_string(), "\n)\n");
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::Modport;
	}
	virtual string name() const
	{
		return "Modport";
	}
	GEN_GETTER_BY_CON_REF(ident)
	GEN_SETTER_BY_RVAL_REF(ident)
};

class NodeModportSubList : public NodeBase
{
protected:		// variables
	string _port_dir;
protected:		// children
	Child _ident_list;
public:		// functions
	inline NodeModportSubList(const SrcCodeChunk& s_src_code_chunk,
		const string& s_port_dir,
		Child&& s_ident_list)
		: NodeBase(s_src_code_chunk), _port_dir(s_port_dir),
		_ident_list(std::move(s_ident_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeModportSubList);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  _port_dir(", _port_dir, ")\n");
		ret += sconcat("  child:ident_list\n(", ident_list()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::ModportSubList;
	}
	virtual string name() const
	{
		return "ModportSubList";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(port_dir)
	GEN_GETTER_BY_CON_REF(ident_list)
	GEN_SETTER_BY_RVAL_REF(ident_list)
};

class NodeIdentList : public NodeList
{
public:		// functions
	inline NodeIdentList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentList);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += "  list\n  (";
		for (size_t i=0; i<list.size(); ++i)
		{
			ret += "    ";
			ret += list.at(i)->dbg_to_string();
			if ((i + 1) < list.size())
			{
				ret += ", ";
			}
			ret += "  )\n";
		}
		ret += "  )\n";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::IdentList;
	}
	virtual string name() const
	{
		return "IdentList";
	}
};

