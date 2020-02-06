//--------
flingMuxHeaderSuffix:
	flingExpr
	;

flingIfHeader:
	flingExpr
	;
flingElseHeader:
	KwElse
	;
//--------

//--------
flingMatchHeaderSuffix:
	flingExpr
	;

flingCaseHeader:
	// This is temporary.  It needs an update for later versions of the
	// language.
	flingExprList
	;
flingDefaultHeader:
	KwDefault
	;
//--------

//--------
flingForHeaderSuffix:
	flingIdent (':' flingExpr)? ',' flingExpr
	;
flingWhileHeaderSuffix:
	flingExpr
	;

flingBreakHeaderSuffix:
	flingIdent?
	;
flingContinueHeaderSuffix:
	flingIdent?
	;

flingLabelHeaderSuffix:
	flingIdent
	;
flingScopeHeaderSuffix:
	flingAttr?
	;
//--------

//--------
flingCatchHeader:
	KwCatch '(' flingIdent (':' flingExpr)? ')'
	;
//--------

//--------
flingSharedGenItem:
	flingGenVar
	| flingGeneval
	| flingGenBreak
	| flingGenContinue
	| flingGenLabel
	;
flingGenVar:
	KwGen '[' KwVar ']' '{' flingDeclVarPostSpecInnards '}'
	;
flingGeneval:
	KwGeneval flingExpr
	;
flingGenBreak:
	KwGen '[' KwBreak ']' flingBreakHeaderSuffix
	;
flingGenContinue:
	KwGen '[' KwContinue ']' flingContinueHeaderSuffix
	;
flingGenLabel:
	KwGen '[' KwLabel ']' flingLabelHeaderSuffix
	;
//--------

//--------
flingGenCondHeader:
	KwGen '[' KwCond ']'
	;
flingGenMuxHeader:
	KwGen '[' KwMux ']' flingMuxHeaderSuffix
	;

flingGenMatchHeader:
	KwGen '[' KwMatch ']' flingMatchHeaderSuffix
	;
//--------

//--------
flingGenForHeader:
	KwGen '[' KwFor ']' flingForHeaderSuffix
	;
flingGenWhileHeader:
	KwGen '[' KwWhile ']' flingWhileHeaderSuffix
	;
//--------

//--------
flingGenScopeHeader:
	KwGen '[' KwScope ']' flingScopeHeaderSuffix
	;
//--------

//--------
flingGenTryHeader:
	KwGen '[' KwTry ']'
	;
//--------
