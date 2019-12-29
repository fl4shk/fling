flingBasicIdent:
	flingHighIdent ('cat' flingHighIdent)*
	;
flingGenIdent:
	'gen' '<' flingBasicIdent '>'
	;

flingHighIdent:
	TokIdent
	| '#' '(' flingExpr ')'
	;

flingIdent:
	flingBasicIdent
	| flingGenIdent
	;

flingRawString:
	TokStringLiteral
	| TokKwFromident '(' flingIdent ')'
	;
