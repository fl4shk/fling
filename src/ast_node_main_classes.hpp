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
protected:		// children
	Child _callable;
public:		// functions
	inline NodeMemberCallable(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_is_const,
		const bool& s_is_virtual,
		const bool& s_is_static,
		Child&& s_callable)
		: NodeBase(s_src_code_chunk), _is_const(s_is_const),
		_is_virtual(s_is_virtual),
		_is_static(s_is_static),
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

class NodeExprBinopBase : public NodeExprBase
{
protected:		// children
	Child _left,
		_right;
public:		// functions
	inline NodeExprBinopBase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBase(s_src_code_chunk),
		_left(std::move(s_left)),
		_right(std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBase);
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
		return Type::ExprBinopBase;
	}
	virtual string name() const
	{
		return "ExprBinopBase";
	}
	GEN_GETTER_BY_CON_REF(left)
	GEN_SETTER_BY_RVAL_REF(left)
	GEN_GETTER_BY_CON_REF(right)
	GEN_SETTER_BY_RVAL_REF(right)
};

class NodeExprUnopBase : public NodeExprBase
{
protected:		// children
	Child _child;
public:		// functions
	inline NodeExprUnopBase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprBase(s_src_code_chunk),
		_child(std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopBase);
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
		return Type::ExprUnopBase;
	}
	virtual string name() const
	{
		return "ExprUnopBase";
	}
	GEN_GETTER_BY_CON_REF(child)
	GEN_SETTER_BY_RVAL_REF(child)
};

class NodeExprBinopLogAnd : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopLogAnd(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopLogAnd);
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
		return Type::ExprBinopLogAnd;
	}
	virtual string name() const
	{
		return "ExprBinopLogAnd";
	}
};

class NodeExprBinopLogOr : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopLogOr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopLogOr);
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
		return Type::ExprBinopLogOr;
	}
	virtual string name() const
	{
		return "ExprBinopLogOr";
	}
};

class NodeExprBinopCmpEq : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopCmpEq(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpEq);
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
		return Type::ExprBinopCmpEq;
	}
	virtual string name() const
	{
		return "ExprBinopCmpEq";
	}
};

class NodeExprBinopCmpNe : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopCmpNe(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpNe);
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
		return Type::ExprBinopCmpNe;
	}
	virtual string name() const
	{
		return "ExprBinopCmpNe";
	}
};

class NodeExprBinopCmpLt : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopCmpLt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpLt);
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
		return Type::ExprBinopCmpLt;
	}
	virtual string name() const
	{
		return "ExprBinopCmpLt";
	}
};

class NodeExprBinopCmpGt : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopCmpGt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpGt);
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
		return Type::ExprBinopCmpGt;
	}
	virtual string name() const
	{
		return "ExprBinopCmpGt";
	}
};

class NodeExprBinopCmpLe : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopCmpLe(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpLe);
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
		return Type::ExprBinopCmpLe;
	}
	virtual string name() const
	{
		return "ExprBinopCmpLe";
	}
};

class NodeExprBinopCmpGe : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopCmpGe(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpGe);
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
		return Type::ExprBinopCmpGe;
	}
	virtual string name() const
	{
		return "ExprBinopCmpGe";
	}
};

class NodeExprBinopPlus : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopPlus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopPlus);
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
		return Type::ExprBinopPlus;
	}
	virtual string name() const
	{
		return "ExprBinopPlus";
	}
};

class NodeExprBinopMinus : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopMinus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopMinus);
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
		return Type::ExprBinopMinus;
	}
	virtual string name() const
	{
		return "ExprBinopMinus";
	}
};

class NodeExprBinopMul : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopMul(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopMul);
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
		return Type::ExprBinopMul;
	}
	virtual string name() const
	{
		return "ExprBinopMul";
	}
};

class NodeExprBinopDiv : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopDiv(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopDiv);
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
		return Type::ExprBinopDiv;
	}
	virtual string name() const
	{
		return "ExprBinopDiv";
	}
};

class NodeExprBinopMod : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopMod(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopMod);
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
		return Type::ExprBinopMod;
	}
	virtual string name() const
	{
		return "ExprBinopMod";
	}
};

class NodeExprBinopBitAnd : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopBitAnd(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitAnd);
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
		return Type::ExprBinopBitAnd;
	}
	virtual string name() const
	{
		return "ExprBinopBitAnd";
	}
};

class NodeExprBinopBitOr : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopBitOr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitOr);
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
		return Type::ExprBinopBitOr;
	}
	virtual string name() const
	{
		return "ExprBinopBitOr";
	}
};

class NodeExprBinopBitXor : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopBitXor(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitXor);
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
		return Type::ExprBinopBitXor;
	}
	virtual string name() const
	{
		return "ExprBinopBitXor";
	}
};

class NodeExprBinopBitLsl : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopBitLsl(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitLsl);
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
		return Type::ExprBinopBitLsl;
	}
	virtual string name() const
	{
		return "ExprBinopBitLsl";
	}
};

class NodeExprBinopBitLsr : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopBitLsr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitLsr);
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
		return Type::ExprBinopBitLsr;
	}
	virtual string name() const
	{
		return "ExprBinopBitLsr";
	}
};

class NodeExprBinopBitAsr : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopBitAsr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitAsr);
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
		return Type::ExprBinopBitAsr;
	}
	virtual string name() const
	{
		return "ExprBinopBitAsr";
	}
};

class NodeExprUnopLogNot : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopLogNot(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopLogNot);
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
		return Type::ExprUnopLogNot;
	}
	virtual string name() const
	{
		return "ExprUnopLogNot";
	}
};

class NodeExprUnopBitNot : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopBitNot(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopBitNot);
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
		return Type::ExprUnopBitNot;
	}
	virtual string name() const
	{
		return "ExprUnopBitNot";
	}
};

class NodeExprUnopPlus : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopPlus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopPlus);
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
		return Type::ExprUnopPlus;
	}
	virtual string name() const
	{
		return "ExprUnopPlus";
	}
};

class NodeExprUnopMinus : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopMinus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopMinus);
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
		return Type::ExprUnopMinus;
	}
	virtual string name() const
	{
		return "ExprUnopMinus";
	}
};

class NodeExprUnopDollarUnsigned : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarUnsigned(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarUnsigned);
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
		return Type::ExprUnopDollarUnsigned;
	}
	virtual string name() const
	{
		return "ExprUnopDollarUnsigned";
	}
};

class NodeExprUnopDollarSigned : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarSigned(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarSigned);
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
		return Type::ExprUnopDollarSigned;
	}
	virtual string name() const
	{
		return "ExprUnopDollarSigned";
	}
};

class NodeExprUnopDollarIsUnsigned : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarIsUnsigned(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarIsUnsigned);
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
		return Type::ExprUnopDollarIsUnsigned;
	}
	virtual string name() const
	{
		return "ExprUnopDollarIsUnsigned";
	}
};

class NodeExprUnopDollarIsSigned : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarIsSigned(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarIsSigned);
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
		return Type::ExprUnopDollarIsSigned;
	}
	virtual string name() const
	{
		return "ExprUnopDollarIsSigned";
	}
};

class NodeExprUnopDollarRange : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarRange(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarRange);
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
		return Type::ExprUnopDollarRange;
	}
	virtual string name() const
	{
		return "ExprUnopDollarRange";
	}
};

class NodeExprUnopDollarRevrange : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarRevrange(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarRevrange);
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
		return Type::ExprUnopDollarRevrange;
	}
	virtual string name() const
	{
		return "ExprUnopDollarRevrange";
	}
};

class NodeExprUnopDollarSize : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarSize(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarSize);
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
		return Type::ExprUnopDollarSize;
	}
	virtual string name() const
	{
		return "ExprUnopDollarSize";
	}
};

class NodeExprUnopDollarFirst : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarFirst(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarFirst);
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
		return Type::ExprUnopDollarFirst;
	}
	virtual string name() const
	{
		return "ExprUnopDollarFirst";
	}
};

class NodeExprUnopDollarLast : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarLast(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarLast);
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
		return Type::ExprUnopDollarLast;
	}
	virtual string name() const
	{
		return "ExprUnopDollarLast";
	}
};

class NodeExprUnopDollarHigh : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarHigh(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarHigh);
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
		return Type::ExprUnopDollarHigh;
	}
	virtual string name() const
	{
		return "ExprUnopDollarHigh";
	}
};

class NodeExprUnopDollarLow : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarLow(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarLow);
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
		return Type::ExprUnopDollarLow;
	}
	virtual string name() const
	{
		return "ExprUnopDollarLow";
	}
};

class NodeExprUnopDollarClog2 : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarClog2(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarClog2);
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
		return Type::ExprUnopDollarClog2;
	}
	virtual string name() const
	{
		return "ExprUnopDollarClog2";
	}
};

class NodeExprBinopDollarPow : public NodeExprBinopBase
{
public:		// functions
	inline NodeExprBinopDollarPow(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopDollarPow);
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
		return Type::ExprBinopDollarPow;
	}
	virtual string name() const
	{
		return "ExprBinopDollarPow";
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

class NodeExprUnopTypeof : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopTypeof(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopTypeof);
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
		return Type::ExprUnopTypeof;
	}
	virtual string name() const
	{
		return "ExprUnopTypeof";
	}
};

class NodeExprCat : public NodeExprBase
{
protected:		// children
	Child _list;
public:		// functions
	inline NodeExprCat(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_list)
		: NodeExprBase(s_src_code_chunk),
		_list(std::move(s_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprCat);
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
		return Type::ExprCat;
	}
	virtual string name() const
	{
		return "ExprCat";
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

class NodeExprRepl : public NodeExprBase
{
protected:		// children
	Child _how_much_expr,
		_to_repl_expr;
public:		// functions
	inline NodeExprRepl(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_how_much_expr,
		Child&& s_to_repl_expr)
		: NodeExprBase(s_src_code_chunk),
		_how_much_expr(std::move(s_how_much_expr)),
		_to_repl_expr(std::move(s_to_repl_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprRepl);
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
		return Type::ExprRepl;
	}
	virtual string name() const
	{
		return "ExprRepl";
	}
	GEN_GETTER_BY_CON_REF(how_much_expr)
	GEN_SETTER_BY_RVAL_REF(how_much_expr)
	GEN_GETTER_BY_CON_REF(to_repl_expr)
	GEN_SETTER_BY_RVAL_REF(to_repl_expr)
};

class NodeExprRangeAny : public NodeExprBase
{
protected:		// children
	Child _which_range;
public:		// functions
	inline NodeExprRangeAny(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_which_range)
		: NodeExprBase(s_src_code_chunk),
		_which_range(std::move(s_which_range))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprRangeAny);
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
		return Type::ExprRangeAny;
	}
	virtual string name() const
	{
		return "ExprRangeAny";
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

class NodeStmtAnyFor : public NodeBase
{
protected:		// children
	Child _var,
		_items,
		_scope;
public:		// functions
	inline NodeStmtAnyFor(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_var,
		Child&& s_items,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_var(std::move(s_var)),
		_items(std::move(s_items)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAnyFor);
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
		return Type::StmtAnyFor;
	}
	virtual string name() const
	{
		return "StmtAnyFor";
	}
	GEN_GETTER_BY_CON_REF(var)
	GEN_SETTER_BY_RVAL_REF(var)
	GEN_GETTER_BY_CON_REF(items)
	GEN_SETTER_BY_RVAL_REF(items)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeStmtFor : public NodeStmtAnyFor
{
public:		// functions
	inline NodeStmtFor(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_var,
		Child&& s_items,
		Child&& s_scope)
		: NodeStmtAnyFor(s_src_code_chunk,
		std::move(s_var),
		std::move(s_items),
		std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtFor);
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
		return Type::StmtFor;
	}
	virtual string name() const
	{
		return "StmtFor";
	}
};

class NodeStmtGenerateFor : public NodeStmtAnyFor
{
protected:		// children
	Child _label;
public:		// functions
	inline NodeStmtGenerateFor(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_label,
		Child&& s_var,
		Child&& s_items,
		Child&& s_scope)
		: NodeStmtAnyFor(s_src_code_chunk,
		std::move(s_var),
		std::move(s_items),
		std::move(s_scope)),
		_label(std::move(s_label))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtGenerateFor);
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
		return Type::StmtGenerateFor;
	}
	virtual string name() const
	{
		return "StmtGenerateFor";
	}
	GEN_GETTER_BY_CON_REF(label)
	GEN_SETTER_BY_RVAL_REF(label)
};

class NodeStmtIf : public NodeBase
{
protected:		// children
	Child _cond_expr,
		_scope,
		_stmt_else;
public:		// functions
	inline NodeStmtIf(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_scope,
		Child&& s_stmt_else)
		: NodeBase(s_src_code_chunk),
		_cond_expr(std::move(s_cond_expr)),
		_scope(std::move(s_scope)),
		_stmt_else(std::move(s_stmt_else))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtIf);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:cond_expr\n(", cond_expr()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:stmt_else\n(", stmt_else()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::StmtIf;
	}
	virtual string name() const
	{
		return "StmtIf";
	}
	GEN_GETTER_BY_CON_REF(cond_expr)
	GEN_SETTER_BY_RVAL_REF(cond_expr)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
	GEN_GETTER_BY_CON_REF(stmt_else)
	GEN_SETTER_BY_RVAL_REF(stmt_else)
};

class NodeStmtGenerateIf : public NodeStmtIf
{
public:		// functions
	inline NodeStmtGenerateIf(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_scope,
		Child&& s_stmt_else)
		: NodeStmtIf(s_src_code_chunk,
		std::move(s_cond_expr),
		std::move(s_scope),
		std::move(s_stmt_else))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtGenerateIf);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += sconcat("  child:cond_expr\n(", cond_expr()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:scope\n(", scope()->dbg_to_string(), "\n)\n");
		ret += sconcat("  child:stmt_else\n(", stmt_else()->dbg_to_string(), "\n)\n");
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::StmtGenerateIf;
	}
	virtual string name() const
	{
		return "StmtGenerateIf";
	}
};

class NodeStmtWhile : public NodeBase
{
protected:		// children
	Child _cond_expr,
		_scope;
public:		// functions
	inline NodeStmtWhile(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_cond_expr(std::move(s_cond_expr)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtWhile);
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
		return Type::StmtWhile;
	}
	virtual string name() const
	{
		return "StmtWhile";
	}
	GEN_GETTER_BY_CON_REF(cond_expr)
	GEN_SETTER_BY_RVAL_REF(cond_expr)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeStmtBehavAssign : public NodeLeftRightBase
{
public:		// functions
	inline NodeStmtBehavAssign(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeLeftRightBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtBehavAssign);
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
		return Type::StmtBehavAssign;
	}
	virtual string name() const
	{
		return "StmtBehavAssign";
	}
};

class NodeStmtContAssign : public NodeLeftRightBase
{
public:		// functions
	inline NodeStmtContAssign(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeLeftRightBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtContAssign);
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
		return Type::StmtContAssign;
	}
	virtual string name() const
	{
		return "StmtContAssign";
	}
};

class NodeStmtMemberAccessPublic : public NodeBase
{
public:		// functions
	inline NodeStmtMemberAccessPublic(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtMemberAccessPublic);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::StmtMemberAccessPublic;
	}
	virtual string name() const
	{
		return "StmtMemberAccessPublic";
	}
};

class NodeStmtMemberAccessProtected : public NodeBase
{
public:		// functions
	inline NodeStmtMemberAccessProtected(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtMemberAccessProtected);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::StmtMemberAccessProtected;
	}
	virtual string name() const
	{
		return "StmtMemberAccessProtected";
	}
};

class NodeStmtMemberAccessPrivate : public NodeBase
{
public:		// functions
	inline NodeStmtMemberAccessPrivate(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtMemberAccessPrivate);
	virtual string dbg_to_string() const
	{
		string ret;
		ret += name() + "\n(";
		ret += ")";
		return ret;
	}
	virtual Type type() const
	{
		return Type::StmtMemberAccessPrivate;
	}
	virtual string name() const
	{
		return "StmtMemberAccessPrivate";
	}
};

class NodeStmtSwitch : public NodeBase
{
protected:		// children
	Child _expr,
		_scope;
public:		// functions
	inline NodeStmtSwitch(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtSwitch);
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
		return Type::StmtSwitch;
	}
	virtual string name() const
	{
		return "StmtSwitch";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeStmtSwitchz : public NodeStmtSwitch
{
public:		// functions
	inline NodeStmtSwitchz(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr,
		Child&& s_scope)
		: NodeStmtSwitch(s_src_code_chunk,
		std::move(s_expr),
		std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtSwitchz);
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
		return Type::StmtSwitchz;
	}
	virtual string name() const
	{
		return "StmtSwitchz";
	}
};

class NodeStmtCase : public NodeBase
{
protected:		// children
	Child _expr,
		_scope;
public:		// functions
	inline NodeStmtCase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtCase);
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
		return Type::StmtCase;
	}
	virtual string name() const
	{
		return "StmtCase";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeStmtDefault : public NodeBase
{
protected:		// children
	Child _scope;
public:		// functions
	inline NodeStmtDefault(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtDefault);
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
		return Type::StmtDefault;
	}
	virtual string name() const
	{
		return "StmtDefault";
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

class NodeStmtUsing : public NodeLeftRightBase
{
public:		// functions
	inline NodeStmtUsing(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeLeftRightBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtUsing);
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
		return Type::StmtUsing;
	}
	virtual string name() const
	{
		return "StmtUsing";
	}
};

class NodeStmtInstModule : public NodeBase
{
protected:		// children
	Child _module_ident,
		_param_inst_list,
		_inst_ident,
		_arg_inst_list;
public:		// functions
	inline NodeStmtInstModule(const SrcCodeChunk& s_src_code_chunk,
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
	GEN_POST_CONSTRUCTOR(NodeStmtInstModule);
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
		return Type::StmtInstModule;
	}
	virtual string name() const
	{
		return "StmtInstModule";
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

class NodeStmtReturn : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeStmtReturn(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtReturn);
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
		return Type::StmtReturn;
	}
	virtual string name() const
	{
		return "StmtReturn";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeStmtInitial : public NodeBase
{
protected:		// children
	Child _scope;
public:		// functions
	inline NodeStmtInitial(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtInitial);
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
		return Type::StmtInitial;
	}
	virtual string name() const
	{
		return "StmtInitial";
	}
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeStmtAlwaysComb : public NodeBase
{
protected:		// children
	Child _scope;
public:		// functions
	inline NodeStmtAlwaysComb(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAlwaysComb);
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
		return Type::StmtAlwaysComb;
	}
	virtual string name() const
	{
		return "StmtAlwaysComb";
	}
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeStmtAlwaysBlk : public NodeBase
{
protected:		// children
	Child _edge_list,
		_scope;
public:		// functions
	inline NodeStmtAlwaysBlk(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_edge_list,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_edge_list(std::move(s_edge_list)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAlwaysBlk);
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
		return Type::StmtAlwaysBlk;
	}
	virtual string name() const
	{
		return "StmtAlwaysBlk";
	}
	GEN_GETTER_BY_CON_REF(edge_list)
	GEN_SETTER_BY_RVAL_REF(edge_list)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeStmtAlwaysFf : public NodeBase
{
protected:		// children
	Child _edge_list,
		_scope;
public:		// functions
	inline NodeStmtAlwaysFf(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_edge_list,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_edge_list(std::move(s_edge_list)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAlwaysFf);
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
		return Type::StmtAlwaysFf;
	}
	virtual string name() const
	{
		return "StmtAlwaysFf";
	}
	GEN_GETTER_BY_CON_REF(edge_list)
	GEN_SETTER_BY_RVAL_REF(edge_list)
	GEN_GETTER_BY_CON_REF(scope)
	GEN_SETTER_BY_RVAL_REF(scope)
};

class NodeStmtAssert : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeStmtAssert(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAssert);
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
		return Type::StmtAssert;
	}
	virtual string name() const
	{
		return "StmtAssert";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeStmtAssume : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeStmtAssume(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAssume);
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
		return Type::StmtAssume;
	}
	virtual string name() const
	{
		return "StmtAssume";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeStmtCover : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeStmtCover(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtCover);
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
		return Type::StmtCover;
	}
	virtual string name() const
	{
		return "StmtCover";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeStmtRestrict : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeStmtRestrict(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtRestrict);
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
		return Type::StmtRestrict;
	}
	virtual string name() const
	{
		return "StmtRestrict";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeStmtStaticAssert : public NodeBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeStmtStaticAssert(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtStaticAssert);
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
		return Type::StmtStaticAssert;
	}
	virtual string name() const
	{
		return "StmtStaticAssert";
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

