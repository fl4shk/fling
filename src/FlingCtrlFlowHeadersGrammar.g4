flingIfHeader:
	'if' flingExpr
	;
flingElseIfHeader:
	'else' flingIfHeader
	;
flingElseHeader:
	'else'
	;

flingGenIfHeader:
	'gen' flingIfHeader
	;
flingElseGenIfHeader:
	'else' 'gen' flingIfHeader
	;
flingElseGenHeader:
	'else' 'gen'
	;

flingMatchHeader:
	'match' flingExpr
	;
flingGenMatchHeader:
	'gen' flingMatchHeader
	;

flingForHeader:
	'for' flingBasicIdent 'in' flingExpr
	;
flingGenForHeader:
	'gen' flingForHeader
	;

flingWhileHeader:
	'while' flingExpr
	;
flingGenWhileHeader:
	'gen' flingWhileHeader
	;

flingDoHeader:
	'do'
	;
flingGenDoHeader:
	'gen' flingDoHeader
	;

