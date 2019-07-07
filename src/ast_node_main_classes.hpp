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
};

class NodeInputSubPortArgList : public NodeList
{
protected:		// children
	Child _typename;
public:		// functions
	inline NodeInputSubPortArgList(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_typename)
		: NodeList(s_src_code_chunk),
		_typename(std::move(s_typename))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeInputSubPortArgList);
	virtual Type type() const
	{
		return Type::InputSubPortArgList;
	}
	GEN_GETTER_BY_CON_REF(typename)
	GEN_SETTER_BY_RVAL_REF(typename)
};

class NodeOutputSubPortArgList : public NodeList
{
protected:		// children
	Child _typename;
public:		// functions
	inline NodeOutputSubPortArgList(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_typename)
		: NodeList(s_src_code_chunk),
		_typename(std::move(s_typename))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeOutputSubPortArgList);
	virtual Type type() const
	{
		return Type::OutputSubPortArgList;
	}
	GEN_GETTER_BY_CON_REF(typename)
	GEN_SETTER_BY_RVAL_REF(typename)
};

class NodeBidirSubPortArgList : public NodeList
{
protected:		// children
	Child _typename;
public:		// functions
	inline NodeBidirSubPortArgList(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_typename)
		: NodeList(s_src_code_chunk),
		_typename(std::move(s_typename))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeBidirSubPortArgList);
	virtual Type type() const
	{
		return Type::BidirSubPortArgList;
	}
	GEN_GETTER_BY_CON_REF(typename)
	GEN_SETTER_BY_RVAL_REF(typename)
};

class NodeSubParamArgList : public NodeList
{
protected:		// children
	Child _primary;
public:		// functions
	inline NodeSubParamArgList(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_primary)
		: NodeList(s_src_code_chunk),
		_primary(std::move(s_primary))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSubParamArgList);
	virtual Type type() const
	{
		return Type::SubParamArgList;
	}
	GEN_GETTER_BY_CON_REF(primary)
	GEN_SETTER_BY_RVAL_REF(primary)
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
	GEN_GETTER_BY_CON_REF(left)
	GEN_SETTER_BY_RVAL_REF(left)
	GEN_GETTER_BY_CON_REF(right)
	GEN_SETTER_BY_RVAL_REF(right)
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
};

class NodeCall : public NodeBase
{
protected:		// children
	Child _ident_etc,
		_param_inst_list;
public:		// functions
	inline NodeCall(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident_etc,
		Child&& s_param_inst_list)
		: NodeBase(s_src_code_chunk),
		_ident_etc(std::move(s_ident_etc)),
		_param_inst_list(std::move(s_param_inst_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeCall);
	virtual Type type() const
	{
		return Type::Call;
	}
	GEN_GETTER_BY_CON_REF(ident_etc)
	GEN_SETTER_BY_RVAL_REF(ident_etc)
	GEN_GETTER_BY_CON_REF(param_inst_list)
	GEN_SETTER_BY_RVAL_REF(param_inst_list)
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
};

class NodeEnum : public NodeBase
{
protected:		// children
	Child _typename,
		_ident,
		_scope;
public:		// functions
	inline NodeEnum(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_typename,
		Child&& s_ident,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk),
		_typename(std::move(s_typename)),
		_ident(std::move(s_ident)),
		_scope(std::move(s_scope))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeEnum);
	virtual Type type() const
	{
		return Type::Enum;
	}
	GEN_GETTER_BY_CON_REF(typename)
	GEN_SETTER_BY_RVAL_REF(typename)
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
	virtual Type type() const
	{
		return Type::Class;
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
	virtual Type type() const
	{
		return Type::ScopeClass;
	}
};

class NodeTypename : public NodeBase
{
protected:		// children
	Child _ident,
		_param_inst_list;
public:		// functions
	inline NodeTypename(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident,
		Child&& s_param_inst_list)
		: NodeBase(s_src_code_chunk),
		_ident(std::move(s_ident)),
		_param_inst_list(std::move(s_param_inst_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeTypename);
	virtual Type type() const
	{
		return Type::Typename;
	}
	GEN_GETTER_BY_CON_REF(ident)
	GEN_SETTER_BY_RVAL_REF(ident)
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
};

class NodePort : public NodeBase
{
public:		// functions
	inline NodePort(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodePort);
	virtual Type type() const
	{
		return Type::Port;
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
};

class NodeSliceRange : public NodeLeftRightBase
{
public:		// functions
	inline NodeSliceRange(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeLeftRightBase(s_src_code_chunk,
		std::move(s_left),
		std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeSliceRange);
	virtual Type type() const
	{
		return Type::SliceRange;
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
};

class NodeExprRangeAny : public NodeExprBase
{
protected:		// children
	Child _expr;
public:		// functions
	inline NodeExprRangeAny(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeExprBase(s_src_code_chunk),
		_expr(std::move(s_expr))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprRangeAny);
	virtual Type type() const
	{
		return Type::ExprRangeAny;
	}
	GEN_GETTER_BY_CON_REF(expr)
	GEN_SETTER_BY_RVAL_REF(expr)
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
};

class NodeStmtAnyFor : public NodeBase
{
protected:		// children
	Child _var,
		_items;
public:		// functions
	inline NodeStmtAnyFor(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_var,
		Child&& s_items)
		: NodeBase(s_src_code_chunk),
		_var(std::move(s_var)),
		_items(std::move(s_items))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAnyFor);
	virtual Type type() const
	{
		return Type::StmtAnyFor;
	}
	GEN_GETTER_BY_CON_REF(var)
	GEN_SETTER_BY_RVAL_REF(var)
	GEN_GETTER_BY_CON_REF(items)
	GEN_SETTER_BY_RVAL_REF(items)
};

class NodeStmtFor : public NodeStmtAnyFor
{
public:		// functions
	inline NodeStmtFor(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_var,
		Child&& s_items)
		: NodeStmtAnyFor(s_src_code_chunk,
		std::move(s_var),
		std::move(s_items))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtFor);
	virtual Type type() const
	{
		return Type::StmtFor;
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
		Child&& s_items)
		: NodeStmtAnyFor(s_src_code_chunk,
		std::move(s_var),
		std::move(s_items)),
		_label(std::move(s_label))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtGenerateFor);
	virtual Type type() const
	{
		return Type::StmtGenerateFor;
	}
	GEN_GETTER_BY_CON_REF(label)
	GEN_SETTER_BY_RVAL_REF(label)
};

class NodeStmtAnyIf : public NodeBase
{
protected:		// children
	Child _cond_expr,
		_stmt_list,
		_else;
public:		// functions
	inline NodeStmtAnyIf(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_stmt_list,
		Child&& s_else)
		: NodeBase(s_src_code_chunk),
		_cond_expr(std::move(s_cond_expr)),
		_stmt_list(std::move(s_stmt_list)),
		_else(std::move(s_else))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtAnyIf);
	virtual Type type() const
	{
		return Type::StmtAnyIf;
	}
	GEN_GETTER_BY_CON_REF(cond_expr)
	GEN_SETTER_BY_RVAL_REF(cond_expr)
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
	GEN_GETTER_BY_CON_REF(else)
	GEN_SETTER_BY_RVAL_REF(else)
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
	GEN_GETTER_BY_CON_REF(stmt_list)
	GEN_SETTER_BY_RVAL_REF(stmt_list)
};

class NodeStmtGenerateIf : public NodeStmtAnyIf
{
public:		// functions
	inline NodeStmtGenerateIf(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_stmt_list,
		Child&& s_else)
		: NodeStmtAnyIf(s_src_code_chunk,
		std::move(s_cond_expr),
		std::move(s_stmt_list),
		std::move(s_else))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtGenerateIf);
	virtual Type type() const
	{
		return Type::StmtGenerateIf;
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
};

class NodeStmtIf : public NodeStmtAnyIf
{
public:		// functions
	inline NodeStmtIf(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_cond_expr,
		Child&& s_stmt_list,
		Child&& s_else)
		: NodeStmtAnyIf(s_src_code_chunk,
		std::move(s_cond_expr),
		std::move(s_stmt_list),
		std::move(s_else))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtIf);
	virtual Type type() const
	{
		return Type::StmtIf;
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
};

class NodeStmtInstModule : public NodeBase
{
protected:		// children
	Child _module_ident,
		_inst_ident,
		_arg_inst_list;
public:		// functions
	inline NodeStmtInstModule(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_module_ident,
		Child&& s_inst_ident,
		Child&& s_arg_inst_list)
		: NodeBase(s_src_code_chunk),
		_module_ident(std::move(s_module_ident)),
		_inst_ident(std::move(s_inst_ident)),
		_arg_inst_list(std::move(s_arg_inst_list))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeStmtInstModule);
	virtual Type type() const
	{
		return Type::StmtInstModule;
	}
	GEN_GETTER_BY_CON_REF(module_ident)
	GEN_SETTER_BY_RVAL_REF(module_ident)
	GEN_GETTER_BY_CON_REF(inst_ident)
	GEN_SETTER_BY_RVAL_REF(inst_ident)
	GEN_GETTER_BY_CON_REF(arg_inst_list)
	GEN_SETTER_BY_RVAL_REF(arg_inst_list)
};

