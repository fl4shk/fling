class NodePackage : public NodeBase
{
public:  // functions
	inline NodePackage(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(ident),
			APPEND_CHILD(scope));
	}
	GEN_POST_CONSTRUCTOR(NodePackage);
};

class NodeScopePackage : public NodeList
{
public:  // functions
	inline NodeScopePackage(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopePackage);
};

class NodeModule : public NodeBase
{
public:  // functions
	inline NodeModule(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident,
		Child&& s_param_list,
		Child&& s_port_list,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(ident),
			APPEND_CHILD(param_list),
			APPEND_CHILD(port_list),
			APPEND_CHILD(scope));
	}
	GEN_POST_CONSTRUCTOR(NodeModule);
};

class NodeScopeModule : public NodeList
{
public:  // functions
	inline NodeScopeModule(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeModule);
};

class NodeInputSubPortList : public NodeList
{
public:  // functions
	inline NodeInputSubPortList(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_typename)
		: NodeList(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(typename));
	}
	GEN_POST_CONSTRUCTOR(NodeInputSubPortList);
};

class NodeOutputSubPortList : public NodeList
{
public:  // functions
	inline NodeOutputSubPortList(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_typename)
		: NodeList(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(typename));
	}
	GEN_POST_CONSTRUCTOR(NodeOutputSubPortList);
};

class NodeBidirSubPortList : public NodeList
{
public:  // functions
	inline NodeBidirSubPortList(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_typename)
		: NodeList(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(typename));
	}
	GEN_POST_CONSTRUCTOR(NodeBidirSubPortList);
};

class NodeSubParamList : public NodeList
{
public:  // functions
	inline NodeSubParamList(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_primary)
		: NodeList(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(primary));
	}
	GEN_POST_CONSTRUCTOR(NodeSubParamList);
};

class NodeIdentBracket : public NodeList
{
public:  // functions
	inline NodeIdentBracket(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_ident)
		: NodeList(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(ident));
	}
	GEN_POST_CONSTRUCTOR(NodeIdentBracket);
};

class NodeIdentScope : public NodeList
{
public:  // functions
	inline NodeIdentScope(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentScope);
};

class NodeIdentMemberAccess : public NodeList
{
public:  // functions
	inline NodeIdentMemberAccess(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentMemberAccess);
};

class NodeIdentExpr : public NodeList
{
public:  // functions
	inline NodeIdentExpr(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdentExpr);
};

class NodeNumExpr : public NodeBase
{
protected:  // variables
	BigNum _n;
public:  // functions
	inline NodeNumExpr(const SrcCodeChunk& s_src_code_chunk,
		const BigNum& s_n)
		: NodeBase(s_src_code_chunk), _n(s_n)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeNumExpr);
	GEN_GETTER_AND_SETTER_BY_CON_REF(n);
};

class NodeSizedNumExpr : public NodeBase
{
public:  // functions
	inline NodeSizedNumExpr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_size_expr,
		Child&& s_num_expr)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(size_expr),
			APPEND_CHILD(num_expr));
	}
	GEN_POST_CONSTRUCTOR(NodeSizedNumExpr);
};

class NodeBracketPair : public NodeBase
{
public:  // functions
	inline NodeBracketPair(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_expr)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(expr));
	}
	GEN_POST_CONSTRUCTOR(NodeBracketPair);
};

class NodeHasString : public NodeBase
{
protected:  // variables
	string _s;
public:  // functions
	inline NodeHasString(const SrcCodeChunk& s_src_code_chunk,
		const string& s_s)
		: NodeBase(s_src_code_chunk), _s(s_s)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeHasString);
	GEN_GETTER_AND_SETTER_BY_CON_REF(s);
};

class NodeIdent : public NodeHasString
{
public:  // functions
	inline NodeIdent(const SrcCodeChunk& s_src_code_chunk,
		const string& s_s)
		: NodeHasString(s_src_code_chunk,
			s_s)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeIdent);
};

class NodeConstString : public NodeHasString
{
public:  // functions
	inline NodeConstString(const SrcCodeChunk& s_src_code_chunk,
		const string& s_s)
		: NodeHasString(s_src_code_chunk,
			s_s)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeConstString);
};

class NodeEnum : public NodeBase
{
public:  // functions
	inline NodeEnum(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_typename,
		Child&& s_ident,
		Child&& s_scope)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(typename),
			APPEND_CHILD(ident),
			APPEND_CHILD(scope));
	}
	GEN_POST_CONSTRUCTOR(NodeEnum);
};

class NodeScopeEnum : public NodeList
{
public:  // functions
	inline NodeScopeEnum(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeEnum);
};

class NodeClass : public NodeBase
{
protected:  // variables
	bool _packed;
public:  // functions
	inline NodeClass(const SrcCodeChunk& s_src_code_chunk,
		const bool& s_packed,
		Child&& s_ident,
		Child&& s_param_list,
		Child&& s_extends,
		Child&& s_scope,
		Child&& s_var_list)
		: NodeBase(s_src_code_chunk), _packed(s_packed)
	{
		_add_indiv_children(APPEND_CHILD(ident),
			APPEND_CHILD(param_list),
			APPEND_CHILD(extends),
			APPEND_CHILD(scope),
			APPEND_CHILD(var_list));
	}
	GEN_POST_CONSTRUCTOR(NodeClass);
	GEN_GETTER_AND_SETTER_BY_CON_REF(packed);
};

class NodeScopeClass : public NodeList
{
public:  // functions
	inline NodeScopeClass(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeScopeClass);
};

class NodeTypename : public NodeBase
{
public:  // functions
	inline NodeTypename(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_bracket_pair,
		Child&& s_ident,
		Child&& s_param_inst_list)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(bracket_pair),
			APPEND_CHILD(ident),
			APPEND_CHILD(param_inst_list));
	}
	GEN_POST_CONSTRUCTOR(NodeTypename);
};

class NodePosParamArgInstList : public NodeList
{
public:  // functions
	inline NodePosParamArgInstList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodePosParamArgInstList);
};

class NodeNamedParamArgInstList : public NodeList
{
public:  // functions
	inline NodeNamedParamArgInstList(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeNamedParamArgInstList);
};

class NodeOneParamArgInst : public NodeBase
{
public:  // functions
	inline NodeOneParamArgInst(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(left),
			APPEND_CHILD(right));
	}
	GEN_POST_CONSTRUCTOR(NodeOneParamArgInst);
};

class NodeExprBase : public NodeBase
{
public:  // variables
	ExprValue value;
public:  // functions
	inline NodeExprBase(const SrcCodeChunk& s_src_code_chunk)
		: NodeBase(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBase);
};

class NodeExprBinopBase : public NodeExprBase
{
public:  // functions
	inline NodeExprBinopBase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(left),
			APPEND_CHILD(right));
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBase);
};

class NodeExprUnopBase : public NodeExprBase
{
public:  // functions
	inline NodeExprUnopBase(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(child));
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopBase);
};

class NodeExprBinopLogAnd : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopLogAnd(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopLogAnd);
};

class NodeExprBinopLogOr : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopLogOr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopLogOr);
};

class NodeExprBinopCmpEq : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopCmpEq(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpEq);
};

class NodeExprBinopCmpNe : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopCmpNe(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpNe);
};

class NodeExprBinopCmpLt : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopCmpLt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpLt);
};

class NodeExprBinopCmpGt : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopCmpGt(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpGt);
};

class NodeExprBinopCmpLe : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopCmpLe(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpLe);
};

class NodeExprBinopCmpGe : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopCmpGe(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopCmpGe);
};

class NodeExprBinopPlus : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopPlus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopPlus);
};

class NodeExprBinopMinus : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopMinus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopMinus);
};

class NodeExprBinopMul : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopMul(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopMul);
};

class NodeExprBinopDiv : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopDiv(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopDiv);
};

class NodeExprBinopMod : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopMod(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopMod);
};

class NodeExprBinopBitAnd : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopBitAnd(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitAnd);
};

class NodeExprBinopBitOr : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopBitOr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitOr);
};

class NodeExprBinopBitXor : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopBitXor(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitXor);
};

class NodeExprBinopBitLsl : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopBitLsl(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitLsl);
};

class NodeExprBinopBitLsr : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopBitLsr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitLsr);
};

class NodeExprBinopBitAsr : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopBitAsr(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopBitAsr);
};

class NodeExprUnopLogNot : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopLogNot(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopLogNot);
};

class NodeExprUnopBitNot : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopBitNot(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopBitNot);
};

class NodeExprUnopPlus : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopPlus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopPlus);
};

class NodeExprUnopMinus : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopMinus(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopMinus);
};

class NodeExprUnopDollarUnsgn : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarUnsgn(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarUnsgn);
};

class NodeExprUnopDollarSgn : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarSgn(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarSgn);
};

class NodeExprUnopDollarIsUnsgn : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarIsUnsgn(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarIsUnsgn);
};

class NodeExprUnopDollarIsSgn : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarIsSgn(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarIsSgn);
};

class NodeExprUnopDollarRange : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarRange(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarRange);
};

class NodeExprUnopDollarSize : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarSize(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarSize);
};

class NodeExprUnopDollarMsbpos : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarMsbpos(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarMsbpos);
};

class NodeExprUnopDollarFirst : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarFirst(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarFirst);
};

class NodeExprUnopDollarLast : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarLast(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarLast);
};

class NodeExprUnopDollarHigh : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarHigh(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarHigh);
};

class NodeExprUnopDollarLow : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarLow(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarLow);
};

class NodeExprUnopDollarClog2 : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopDollarClog2(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopDollarClog2);
};

class NodeExprBinopDollarPow : public NodeExprBinopBase
{
public:  // functions
	inline NodeExprBinopDollarPow(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_left,
		Child&& s_right)
		: NodeExprBinopBase(s_src_code_chunk,
			std::move(s_left),
			std::move(s_right))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprBinopDollarPow);
};

class NodeExprUnopTypeof : public NodeExprUnopBase
{
public:  // functions
	inline NodeExprUnopTypeof(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_child)
		: NodeExprUnopBase(s_src_code_chunk,
			std::move(s_child))
	{
	}
	GEN_POST_CONSTRUCTOR(NodeExprUnopTypeof);
};

class NodeExprCat : public NodeExprBase
{
public:  // functions
	inline NodeExprCat(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_list)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(list));
	}
	GEN_POST_CONSTRUCTOR(NodeExprCat);
};

class NodeListCat : public NodeList
{
public:  // functions
	inline NodeListCat(const SrcCodeChunk& s_src_code_chunk)
		: NodeList(s_src_code_chunk)
	{
	}
	GEN_POST_CONSTRUCTOR(NodeListCat);
};

class NodeExprFuncCall : public NodeExprBase
{
public:  // functions
	inline NodeExprFuncCall(const SrcCodeChunk& s_src_code_chunk,
		Child&& s_arg_list)
		: NodeExprBase(s_src_code_chunk)
	{
		_add_indiv_children(APPEND_CHILD(arg_list));
	}
	GEN_POST_CONSTRUCTOR(NodeExprFuncCall);
};

