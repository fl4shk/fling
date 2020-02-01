//--------
flingDeclVarPostSpecInnards:
	flingDeclVarPostSpecInnards0
	| flingDeclVarPostSpecInnards1
	| flingDeclVarPostSpecInnards2
	| flingDeclVarPostSpecInnards3
	;
flingDeclVarPostSpecInnards0:
	flingIdentList (',')?
	;
flingDeclVarPostSpecInnards1:
	flingDeclVarPostSpecInnards0 ':' flingTypename
	;
flingDeclVarPostSpecInnards2:
	flingDeclVarPostSpecInnards0 '=' flingExpr
	;
flingDeclVarPostSpecInnards3:
	flingDeclVarPostSpecInnards1 '=' flingExpr
	;
//--------
