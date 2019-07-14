class NodeProgram : public NodeList
{
public:		// functions
	inline NodeProgram(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeProgram);
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

class NodeScopeModule : public NodeList
{
public:		// functions
	inline NodeScopeModule(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeModule);
	virtual Type type() const
	{
		return Type::ScopeModule;
	}
	virtual string name() const
	{
		return "ScopeModule";
	}
};

class NodeInputPortArgSublist : public NodeList
{
protected:		// children
	Child _the_typename;
public:		// functions
	inline NodeInputPortArgSublist(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_the_typename)
		: NodeList(s_src_code_chunk),
		_the_typename(std::move(s_the_typename))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeInputPortArgSublist);
	virtual Type type() const
	{
		return Type::InputPortArgSublist;
	}
	virtual string name() const
	{
		return "InputPortArgSublist";
	}
	GEN_GETTER_BY_CON_REF(the_typename)
	GEN_SETTER_BY_RVAL_REF(the_typename)
};

class NodeOutputPortArgSublist : public NodeList
{
protected:		// children
	Child _the_typename;
public:		// functions
	inline NodeOutputPortArgSublist(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_the_typename)
		: NodeList(s_src_code_chunk),
		_the_typename(std::move(s_the_typename))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeOutputPortArgSublist);
	virtual Type type() const
	{
		return Type::OutputPortArgSublist;
	}
	virtual string name() const
	{
		return "OutputPortArgSublist";
	}
	GEN_GETTER_BY_CON_REF(the_typename)
	GEN_SETTER_BY_RVAL_REF(the_typename)
};

class NodeBidirPortArgSublist : public NodeList
{
protected:		// children
	Child _the_typename;
public:		// functions
	inline NodeBidirPortArgSublist(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_the_typename)
		: NodeList(s_src_code_chunk),
		_the_typename(std::move(s_the_typename))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBidirPortArgSublist);
	virtual Type type() const
	{
		return Type::BidirPortArgSublist;
	}
	virtual string name() const
	{
		return "BidirPortArgSublist";
	}
	GEN_GETTER_BY_CON_REF(the_typename)
	GEN_SETTER_BY_RVAL_REF(the_typename)
};

class NodeParamArgSublist : public NodeList
{
protected:		// children
	Child _primary;
public:		// functions
	inline NodeParamArgSublist(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_primary)
		: NodeList(s_src_code_chunk),
		_primary(std::move(s_primary))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeParamArgSublist);
	virtual Type type() const
	{
		return Type::ParamArgSublist;
	}
	virtual string name() const
	{
		return "ParamArgSublist";
	}
	GEN_GETTER_BY_CON_REF(primary)
	GEN_SETTER_BY_RVAL_REF(primary)
};

class NodeOneParamModule : public NodeBase
{
protected:		// children
	Child _ident_etc;
public:		// functions
	inline NodeOneParamModule(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident_etc)
		: NodeBase(s_src_code_chunk),
		_ident_etc(std::move(s_ident_etc))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeOneParamModule);
	virtual Type type() const
	{
		return Type::OneParamModule;
	}
	virtual string name() const
	{
		return "OneParamModule";
	}
	GEN_GETTER_BY_CON_REF(ident_etc)
	GEN_SETTER_BY_RVAL_REF(ident_etc)
};

class NodeParamModuleSublist : public NodeList
{
public:		// functions
	inline NodeParamModuleSublist(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeParamModuleSublist);
	virtual Type type() const
	{
		return Type::ParamModuleSublist;
	}
	virtual string name() const
	{
		return "ParamModuleSublist";
	}
};

class NodeParamArgList : public NodeList
{
public:		// functions
	inline NodeParamArgList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeParamArgList);
	virtual Type type() const
	{
		return Type::ParamArgList;
	}
	virtual string name() const
	{
		return "ParamArgList";
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

class NodeIdentBracket : public NodeList
{
protected:		// children
	Child _ident;
public:		// functions
	inline NodeIdentBracket(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident)
		: NodeList(s_src_code_chunk),
		_ident(std::move(s_ident))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentBracket);
	virtual Type type() const
	{
		return Type::IdentBracket;
	}
	virtual string name() const
	{
		return "IdentBracket";
	}
	GEN_GETTER_BY_CON_REF(ident)
	GEN_SETTER_BY_RVAL_REF(ident)
};

class NodeIdentScope : public NodeBase
{
public:		// functions
	inline NodeIdentScope(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentScope);
	virtual Type type() const
	{
		return Type::IdentScope;
	}
	virtual string name() const
	{
		return "IdentScope";
	}
};

class NodeCall : public NodeBase
{
protected:		// children
	Child _ident,
		_param_inst_list,
		_arg_inst_list;
public:		// functions
	inline NodeCall(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident,
		Child&& s_param_inst_list,
		Child&& s_arg_inst_list)
		: NodeBase(s_src_code_chunk),
		_ident(std::move(s_ident)),
		_param_inst_list(std::move(s_param_inst_list)),
		_arg_inst_list(std::move(s_arg_inst_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeCall);
	virtual Type type() const
	{
		return Type::Call;
	}
	virtual string name() const
	{
		return "Call";
	}
	GEN_GETTER_BY_CON_REF(ident)
	GEN_SETTER_BY_RVAL_REF(ident)
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
	Child _expr;
public:		// functions
	inline NodeBracketPair(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBracketPair);
	virtual Type type() const
	{
		return Type::BracketPair;
	}
	virtual string name() const
	{
		return "BracketPair";
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
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
	virtual Type type() const
	{
		return Type::ConstString;
	}
	virtual string name() const
	{
		return "ConstString";
	}
};

class NodeScopeUnnamed : public NodeList
{
public:		// functions
	inline NodeScopeUnnamed(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeUnnamed);
	virtual Type type() const
	{
		return Type::ScopeUnnamed;
	}
	virtual string name() const
	{
		return "ScopeUnnamed";
	}
};

class NodeEnum : public NodeBase
{
protected:		// children
	Child _the_typename,
		_ident,
		_scope;
public:		// functions
	inline NodeEnum(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_the_typename,
		Child&& s_ident,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_the_typename(std::move(s_the_typename)),
		_ident(std::move(s_ident)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeEnum);
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
};

class NodeScopeEnum : public NodeList
{
public:		// functions
	inline NodeScopeEnum(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeEnum);
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
	bool _virtual_extends;
protected:		// children
	Child _ident,
		_param_list,
		_extends,
		_scope,
		_var_list;
public:		// functions
	inline NodeClass(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_packed, const bool& s_virtual_extends,
		Child&& s_ident,
		Child&& s_param_list,
		Child&& s_extends,
		Child&& s_scope,
		Child&& s_var_list)
		: NodeBase(s_src_code_chunk), _packed(s_packed),
		_virtual_extends(s_virtual_extends),
		_ident(std::move(s_ident)),
		_param_list(std::move(s_param_list)),
		_extends(std::move(s_extends)),
		_scope(std::move(s_scope)),
		_var_list(std::move(s_var_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeClass);
	virtual Type type() const
	{
		return Type::Class;
	}
	virtual string name() const
	{
		return "Class";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(packed)
	GEN_GETTER_AND_SETTER_BY_CON_REF(virtual_extends)
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
protected:		// children
	Child _the_typename;
public:		// functions
	inline NodeExtends(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_the_typename)
		: NodeBase(s_src_code_chunk),
		_the_typename(std::move(s_the_typename))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExtends);
	virtual Type type() const
	{
		return Type::Extends;
	}
	virtual string name() const
	{
		return "Extends";
	}
	GEN_GETTER_BY_CON_REF(the_typename)
	GEN_SETTER_BY_RVAL_REF(the_typename)
};

class NodeUnion : public NodeBase
{
protected:		// children
	Child _ident,
		_scope;
public:		// functions
	inline NodeUnion(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_ident(std::move(s_ident)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeUnion);
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
};

class NodeScopeUnion : public NodeList
{
public:		// functions
	inline NodeScopeUnion(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeUnion);
	virtual Type type() const
	{
		return Type::ScopeUnion;
	}
	virtual string name() const
	{
		return "ScopeUnion";
	}
};

class NodeTypename : public NodeBase
{
protected:		// children
	Child _ident_etc,
		_param_inst_list;
public:		// functions
	inline NodeTypename(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident_etc,
		Child&& s_param_inst_list)
		: NodeBase(s_src_code_chunk),
		_ident_etc(std::move(s_ident_etc)),
		_param_inst_list(std::move(s_param_inst_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeTypename);
	virtual Type type() const
	{
		return Type::Typename;
	}
	virtual string name() const
	{
		return "Typename";
	}
	GEN_GETTER_BY_CON_REF(ident_etc)
	GEN_SETTER_BY_RVAL_REF(ident_etc)
	GEN_GETTER_BY_CON_REF(param_inst_list)
	GEN_SETTER_BY_RVAL_REF(param_inst_list)
};

class NodeType : public NodeBase
{
public:		// functions
	inline NodeType(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeType);
	virtual Type type() const
	{
		return Type::Type;
	}
	virtual string name() const
	{
		return "Type";
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
public:		// variables
	ExprValue value;
public:		// functions
	inline NodeExprBase(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBase);
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
	virtual Type type() const
	{
		return Type::ExprUnopMinus;
	}
	virtual string name() const
	{
		return "ExprUnopMinus";
	}
};

class NodeExprUnopDollarUnsgn : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarUnsgn(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarUnsgn);
	virtual Type type() const
	{
		return Type::ExprUnopDollarUnsgn;
	}
	virtual string name() const
	{
		return "ExprUnopDollarUnsgn";
	}
};

class NodeExprUnopDollarSgn : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarSgn(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarSgn);
	virtual Type type() const
	{
		return Type::ExprUnopDollarSgn;
	}
	virtual string name() const
	{
		return "ExprUnopDollarSgn";
	}
};

class NodeExprUnopDollarIsUnsgn : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarIsUnsgn(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarIsUnsgn);
	virtual Type type() const
	{
		return Type::ExprUnopDollarIsUnsgn;
	}
	virtual string name() const
	{
		return "ExprUnopDollarIsUnsgn";
	}
};

class NodeExprUnopDollarIsSgn : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarIsSgn(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarIsSgn);
	virtual Type type() const
	{
		return Type::ExprUnopDollarIsSgn;
	}
	virtual string name() const
	{
		return "ExprUnopDollarIsSgn";
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
	virtual Type type() const
	{
		return Type::ExprUnopDollarRange;
	}
	virtual string name() const
	{
		return "ExprUnopDollarRange";
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
	virtual Type type() const
	{
		return Type::ExprUnopDollarSize;
	}
	virtual string name() const
	{
		return "ExprUnopDollarSize";
	}
};

class NodeExprUnopDollarMsbpos : public NodeExprUnopBase
{
public:		// functions
	inline NodeExprUnopDollarMsbpos(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
		std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarMsbpos);
	virtual Type type() const
	{
		return Type::ExprUnopDollarMsbpos;
	}
	virtual string name() const
	{
		return "ExprUnopDollarMsbpos";
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
		_stmt_list;
public:		// functions
	inline NodeStmtAnyFor(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_var,
		Child&& s_items,
		Child&& s_stmt_list)
		: NodeBase(s_src_code_chunk),
		_var(std::move(s_var)),
		_items(std::move(s_items)),
		_stmt_list(std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAnyFor);
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
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
};

class NodeStmtFor : public NodeStmtAnyFor
{
public:		// functions
	inline NodeStmtFor(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_var,
		Child&& s_items,
		Child&& s_stmt_list)
		: NodeStmtAnyFor(s_src_code_chunk,
		std::move(s_var),
		std::move(s_items),
		std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtFor);
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
		Child&& s_stmt_list)
		: NodeStmtAnyFor(s_src_code_chunk,
		std::move(s_var),
		std::move(s_items),
		std::move(s_stmt_list)),
		_label(std::move(s_label))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtGenerateFor);
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

class NodeStmtAnyIf : public NodeBase
{
protected:		// children
	Child _cond_expr,
		_stmt_list,
		_stmt_else;
public:		// functions
	inline NodeStmtAnyIf(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_stmt_list,
		Child&& s_stmt_else)
		: NodeBase(s_src_code_chunk),
		_cond_expr(std::move(s_cond_expr)),
		_stmt_list(std::move(s_stmt_list)),
		_stmt_else(std::move(s_stmt_else))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAnyIf);
	virtual Type type() const
	{
		return Type::StmtAnyIf;
	}
	virtual string name() const
	{
		return "StmtAnyIf";
	}
	GEN_GETTER_BY_CON_REF(cond_expr)
	GEN_SETTER_BY_RVAL_REF(cond_expr)
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
	GEN_GETTER_BY_CON_REF(stmt_else)
	GEN_SETTER_BY_RVAL_REF(stmt_else)
};

class NodeStmtAnyElse : public NodeBase
{
protected:		// children
	Child _stmt_list;
public:		// functions
	inline NodeStmtAnyElse(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_stmt_list)
		: NodeBase(s_src_code_chunk),
		_stmt_list(std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAnyElse);
	virtual Type type() const
	{
		return Type::StmtAnyElse;
	}
	virtual string name() const
	{
		return "StmtAnyElse";
	}
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
};

class NodeStmtIf : public NodeStmtAnyIf
{
public:		// functions
	inline NodeStmtIf(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_stmt_list,
		Child&& s_stmt_else)
		: NodeStmtAnyIf(s_src_code_chunk,
		std::move(s_cond_expr),
		std::move(s_stmt_list),
		std::move(s_stmt_else))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtIf);
	virtual Type type() const
	{
		return Type::StmtIf;
	}
	virtual string name() const
	{
		return "StmtIf";
	}
};

class NodeStmtElse : public NodeStmtAnyElse
{
public:		// functions
	inline NodeStmtElse(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_stmt_list)
		: NodeStmtAnyElse(s_src_code_chunk,
		std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtElse);
	virtual Type type() const
	{
		return Type::StmtElse;
	}
	virtual string name() const
	{
		return "StmtElse";
	}
};

class NodeStmtGenerateIf : public NodeStmtAnyIf
{
public:		// functions
	inline NodeStmtGenerateIf(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_stmt_list,
		Child&& s_stmt_else)
		: NodeStmtAnyIf(s_src_code_chunk,
		std::move(s_cond_expr),
		std::move(s_stmt_list),
		std::move(s_stmt_else))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtGenerateIf);
	virtual Type type() const
	{
		return Type::StmtGenerateIf;
	}
	virtual string name() const
	{
		return "StmtGenerateIf";
	}
};

class NodeStmtGenerateElse : public NodeStmtAnyElse
{
public:		// functions
	inline NodeStmtGenerateElse(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_stmt_list)
		: NodeStmtAnyElse(s_src_code_chunk,
		std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtGenerateElse);
	virtual Type type() const
	{
		return Type::StmtGenerateElse;
	}
	virtual string name() const
	{
		return "StmtGenerateElse";
	}
};

class NodeStmtWhile : public NodeBase
{
protected:		// children
	Child _cond_expr,
		_stmt_list;
public:		// functions
	inline NodeStmtWhile(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_stmt_list)
		: NodeBase(s_src_code_chunk),
		_cond_expr(std::move(s_cond_expr)),
		_stmt_list(std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtWhile);
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
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
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
	virtual Type type() const
	{
		return Type::StmtContAssign;
	}
	virtual string name() const
	{
		return "StmtContAssign";
	}
};

class NodeStmtLabMemberAccessPublic : public NodeBase
{
public:		// functions
	inline NodeStmtLabMemberAccessPublic(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtLabMemberAccessPublic);
	virtual Type type() const
	{
		return Type::StmtLabMemberAccessPublic;
	}
	virtual string name() const
	{
		return "StmtLabMemberAccessPublic";
	}
};

class NodeStmtLabMemberAccessProtected : public NodeBase
{
public:		// functions
	inline NodeStmtLabMemberAccessProtected(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtLabMemberAccessProtected);
	virtual Type type() const
	{
		return Type::StmtLabMemberAccessProtected;
	}
	virtual string name() const
	{
		return "StmtLabMemberAccessProtected";
	}
};

class NodeStmtLabMemberAccessPrivate : public NodeBase
{
public:		// functions
	inline NodeStmtLabMemberAccessPrivate(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtLabMemberAccessPrivate);
	virtual Type type() const
	{
		return Type::StmtLabMemberAccessPrivate;
	}
	virtual string name() const
	{
		return "StmtLabMemberAccessPrivate";
	}
};

class NodeStmtSwitch : public NodeBase
{
protected:		// children
	Child _ident_etc,
		_stmt_list;
public:		// functions
	inline NodeStmtSwitch(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident_etc,
		Child&& s_stmt_list)
		: NodeBase(s_src_code_chunk),
		_ident_etc(std::move(s_ident_etc)),
		_stmt_list(std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtSwitch);
	virtual Type type() const
	{
		return Type::StmtSwitch;
	}
	virtual string name() const
	{
		return "StmtSwitch";
	}
	GEN_GETTER_BY_CON_REF(ident_etc)
	GEN_SETTER_BY_RVAL_REF(ident_etc)
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
};

class NodeStmtSwitchz : public NodeStmtSwitch
{
public:		// functions
	inline NodeStmtSwitchz(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident_etc,
		Child&& s_stmt_list)
		: NodeStmtSwitch(s_src_code_chunk,
		std::move(s_ident_etc),
		std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtSwitchz);
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
	Child _expr;
public:		// functions
	inline NodeStmtCase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtCase);
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
};

class NodeStmtDefault : public NodeBase
{
public:		// functions
	inline NodeStmtDefault(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtDefault);
	virtual Type type() const
	{
		return Type::StmtDefault;
	}
	virtual string name() const
	{
		return "StmtDefault";
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
		_inst_ident_etc,
		_arg_inst_list;
public:		// functions
	inline NodeStmtInstModule(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_module_ident,
		Child&& s_param_inst_list,
		Child&& s_inst_ident_etc,
		Child&& s_arg_inst_list)
		: NodeBase(s_src_code_chunk),
		_module_ident(std::move(s_module_ident)),
		_param_inst_list(std::move(s_param_inst_list)),
		_inst_ident_etc(std::move(s_inst_ident_etc)),
		_arg_inst_list(std::move(s_arg_inst_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtInstModule);
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
	GEN_GETTER_BY_CON_REF(inst_ident_etc)
	GEN_SETTER_BY_RVAL_REF(inst_ident_etc)
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
	Child _stmt_list;
public:		// functions
	inline NodeStmtInitial(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_stmt_list)
		: NodeBase(s_src_code_chunk),
		_stmt_list(std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtInitial);
	virtual Type type() const
	{
		return Type::StmtInitial;
	}
	virtual string name() const
	{
		return "StmtInitial";
	}
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
};

class NodeStmtAlwaysComb : public NodeBase
{
protected:		// children
	Child _stmt_list;
public:		// functions
	inline NodeStmtAlwaysComb(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_stmt_list)
		: NodeBase(s_src_code_chunk),
		_stmt_list(std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAlwaysComb);
	virtual Type type() const
	{
		return Type::StmtAlwaysComb;
	}
	virtual string name() const
	{
		return "StmtAlwaysComb";
	}
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
};

class NodeStmtAlwaysBlk : public NodeBase
{
protected:		// children
	Child _edge_list,
		_stmt_list;
public:		// functions
	inline NodeStmtAlwaysBlk(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_edge_list,
		Child&& s_stmt_list)
		: NodeBase(s_src_code_chunk),
		_edge_list(std::move(s_edge_list)),
		_stmt_list(std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAlwaysBlk);
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
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
};

class NodeStmtAlwaysFf : public NodeBase
{
protected:		// children
	Child _edge_list,
		_stmt_list;
public:		// functions
	inline NodeStmtAlwaysFf(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_edge_list,
		Child&& s_stmt_list)
		: NodeBase(s_src_code_chunk),
		_edge_list(std::move(s_edge_list)),
		_stmt_list(std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAlwaysFf);
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
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
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
	Child _ident_etc;
public:		// functions
	inline NodePosedgeInst(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident_etc)
		: NodeBase(s_src_code_chunk),
		_ident_etc(std::move(s_ident_etc))
	{
	}
	GEN_POST_CONSTRUCTOR(NodePosedgeInst);
	virtual Type type() const
	{
		return Type::PosedgeInst;
	}
	virtual string name() const
	{
		return "PosedgeInst";
	}
	GEN_GETTER_BY_CON_REF(ident_etc)
	GEN_SETTER_BY_RVAL_REF(ident_etc)
};

class NodeNegedgeInst : public NodeBase
{
protected:		// children
	Child _ident_etc;
public:		// functions
	inline NodeNegedgeInst(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident_etc)
		: NodeBase(s_src_code_chunk),
		_ident_etc(std::move(s_ident_etc))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeNegedgeInst);
	virtual Type type() const
	{
		return Type::NegedgeInst;
	}
	virtual string name() const
	{
		return "NegedgeInst";
	}
	GEN_GETTER_BY_CON_REF(ident_etc)
	GEN_SETTER_BY_RVAL_REF(ident_etc)
};

class NodeEdgeList : public NodeList
{
public:		// functions
	inline NodeEdgeList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeEdgeList);
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
protected:		// variables
	bool _is_static;
	bool _is_virtual;
protected:		// children
	Child _param_list,
		_arg_list,
		_ident_or_op,
		_stmt_list;
public:		// functions
	inline NodeDeclCallable(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_is_static, const bool& s_is_virtual,
		Child&& s_param_list,
		Child&& s_arg_list,
		Child&& s_ident_or_op,
		Child&& s_stmt_list)
		: NodeBase(s_src_code_chunk), _is_static(s_is_static),
		_is_virtual(s_is_virtual),
		_param_list(std::move(s_param_list)),
		_arg_list(std::move(s_arg_list)),
		_ident_or_op(std::move(s_ident_or_op)),
		_stmt_list(std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclCallable);
	virtual Type type() const
	{
		return Type::DeclCallable;
	}
	virtual string name() const
	{
		return "DeclCallable";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(is_static)
	GEN_GETTER_AND_SETTER_BY_CON_REF(is_virtual)
	GEN_GETTER_BY_CON_REF(param_list)
	GEN_SETTER_BY_RVAL_REF(param_list)
	GEN_GETTER_BY_CON_REF(arg_list)
	GEN_SETTER_BY_RVAL_REF(arg_list)
	GEN_GETTER_BY_CON_REF(ident_or_op)
	GEN_SETTER_BY_RVAL_REF(ident_or_op)
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
};

class NodeDeclFunc : public NodeDeclCallable
{
protected:		// variables
	bool _is_const;
protected:		// children
	Child _the_typename;
public:		// functions
	inline NodeDeclFunc(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_is_const, const bool& s_is_static, const bool& s_is_virtual,
		Child&& s_the_typename,
		Child&& s_param_list,
		Child&& s_arg_list,
		Child&& s_ident_or_op,
		Child&& s_stmt_list)
		: NodeDeclCallable(s_src_code_chunk,
		s_is_static,
		s_is_virtual,
		std::move(s_param_list),
		std::move(s_arg_list),
		std::move(s_ident_or_op),
		std::move(s_stmt_list)), _is_const(s_is_const),
		_the_typename(std::move(s_the_typename))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclFunc);
	virtual Type type() const
	{
		return Type::DeclFunc;
	}
	virtual string name() const
	{
		return "DeclFunc";
	}
	GEN_GETTER_AND_SETTER_BY_CON_REF(is_const)
	GEN_GETTER_BY_CON_REF(the_typename)
	GEN_SETTER_BY_RVAL_REF(the_typename)
};

class NodeDeclProc : public NodeDeclCallable
{
protected:		// variables
	bool _is_port;
public:		// functions
	inline NodeDeclProc(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_is_port, const bool& s_is_static, const bool& s_is_virtual,
		Child&& s_param_list,
		Child&& s_arg_list,
		Child&& s_ident_or_op,
		Child&& s_stmt_list)
		: NodeDeclCallable(s_src_code_chunk,
		s_is_static,
		s_is_virtual,
		std::move(s_param_list),
		std::move(s_arg_list),
		std::move(s_ident_or_op),
		std::move(s_stmt_list)), _is_port(s_is_port)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclProc);
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
		const bool& s_is_static, const bool& s_is_virtual,
		Child&& s_param_list,
		Child&& s_arg_list,
		Child&& s_ident_or_op,
		Child&& s_stmt_list)
		: NodeDeclCallable(s_src_code_chunk,
		s_is_static,
		s_is_virtual,
		std::move(s_param_list),
		std::move(s_arg_list),
		std::move(s_ident_or_op),
		std::move(s_stmt_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclTask);
	virtual Type type() const
	{
		return Type::DeclTask;
	}
	virtual string name() const
	{
		return "DeclTask";
	}
};

class NodeDeclVar : public NodeBase
{
protected:		// children
	Child _the_typename,
		_ident_bracket,
		_port_inst_list,
		_expr;
public:		// functions
	inline NodeDeclVar(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_the_typename,
		Child&& s_ident_bracket,
		Child&& s_port_inst_list,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk),
		_the_typename(std::move(s_the_typename)),
		_ident_bracket(std::move(s_ident_bracket)),
		_port_inst_list(std::move(s_port_inst_list)),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclVar);
	virtual Type type() const
	{
		return Type::DeclVar;
	}
	virtual string name() const
	{
		return "DeclVar";
	}
	GEN_GETTER_BY_CON_REF(the_typename)
	GEN_SETTER_BY_RVAL_REF(the_typename)
	GEN_GETTER_BY_CON_REF(ident_bracket)
	GEN_SETTER_BY_RVAL_REF(ident_bracket)
	GEN_GETTER_BY_CON_REF(port_inst_list)
	GEN_SETTER_BY_RVAL_REF(port_inst_list)
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
};

class NodeDeclConst : public NodeDeclVar
{
public:		// functions
	inline NodeDeclConst(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_the_typename,
		Child&& s_ident_bracket,
		Child&& s_port_inst_list,
		Child&& s_expr)
		: NodeDeclVar(s_src_code_chunk,
		std::move(s_the_typename),
		std::move(s_ident_bracket),
		std::move(s_port_inst_list),
		std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclConst);
	virtual Type type() const
	{
		return Type::DeclConst;
	}
	virtual string name() const
	{
		return "DeclConst";
	}
};

class NodeDeclVarList : public NodeList
{
public:		// functions
	inline NodeDeclVarList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeDeclVarList);
	virtual Type type() const
	{
		return Type::DeclVarList;
	}
	virtual string name() const
	{
		return "DeclVarList";
	}
};

