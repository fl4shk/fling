flingIdent:
	flingHighIdent ('cat' flingHighIdent)*
	;

flingHighIdent:
	TokIdent
	| '#' '(' flingExpr ')'
	;

flingRawString:
	TokStringLiteral
	| TokKwFromident '(' flingIdent ')'
	;
