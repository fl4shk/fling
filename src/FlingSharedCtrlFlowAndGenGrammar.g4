//--------
flingMuxHeaderSuffix:
	'(' flingExpr ')'
	;

flingIfHeader:
	KwIf '(' flingExpr ')'
	;
flingElifHeader:
	KwElif '(' flingExpr ')'
	;
flingElseHeader:
	KwElse
	;
//--------

//--------
flingMatchHeaderSuffix:
	'(' flingExpr ')'
	;

flingCaseHeader:
	KwCase
	'('
		// This is temporary.  It needs an update for later versions of the
		// language.
		flingExprList
	')'
	;
flingDefaultHeader:
	KwDefault
	;
//--------

//--------
flingForHeaderSuffix:
	'(' flingIdent (':' flingExpr)? ',' flingExpr ')'
	;
flingWhileHeaderSuffix:
	'(' flingExpr ')'
	;

flingBreakHeaderSuffix:
	('(' flingIdent ')')?
	;
flingContinueHeaderSuffix:
	('(' flingIdent ')')?
	;

flingLabelHeaderSuffix:
	'(' flingIdent ')'
	;
flingScopeHeader:
	KwScope ('(' flingIdent ')')?
	;
//--------

//--------
flingCatchHeaderSuffix:
	'(' flingIdent (':' flingExpr)? ')'
	;
//--------

//--------
flingSharedGenItem:
	flingGenVar
	| flingGenBreak
	| flingGenContinue
	| flingGenLabel
	;
flingGenVar:
	KwGen '{' KwVar '}' '(' flingDeclVarPostSpecInnards ')'
	;
flingGenBreak:
	KwGen '{' KwBreak '}' flingBreakHeaderSuffix
	;
flingGenContinue:
	KwGen '{' KwContinue '}' flingContinueHeaderSuffix
	;
flingGenLabel:
	KwGen '{' KwLabel '}' flingLabelHeaderSuffix
	;
//--------

//--------
flingGenCondHeader:
	KwGen '{' KwCond '}'
	;
flingGenMuxHeader:
	KwGen '{' KwMux '}' flingMuxHeaderSuffix
	;

flingGenMatchHeader:
	KwGen '{' KwMatch '}' flingMatchHeaderSuffix
	;
//--------

//--------
flingGenForHeader:
	KwGen '{' KwFor '}' flingForHeaderSuffix
	;
flingGenWhileHeader:
	KwGen '{' KwWhile '}' flingWhileHeaderSuffix
	;
//--------

//--------
flingGenExceptHeader:
	KwGen '{' KwExcept '}'
	;
flingGenTryHeader:
	KwGen '{' KwTry '}'
	;
flingGenCatchHeader:
	KwGen '{' KwCatch '}' flingCatchHeaderSuffix
	;
//--------
