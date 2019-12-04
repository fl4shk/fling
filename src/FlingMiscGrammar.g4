flingIdent:
	TokScopeAccess? flingLowIdent
	;

flingLowIdent:
	flingMidIdent ('::' flingMidIdent)*
	;

flingMidIdent:
	flingHighIdent ('cat' flingHighIdent)*
	;

flingHighIdent:
	TokIdent
	| '#' flingExpr
	;

flingString:
	TokStringLiteral
	| TokKwFromident '(' flingIdent ')'
	;
