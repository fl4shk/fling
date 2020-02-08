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
	flingIdent (PunctColon flingExpr)? PunctComma flingExpr
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
	KwCatch PunctLParen flingIdent (PunctColon flingExpr)? PunctRParen
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
	KwGen PunctLBracket KwVar PunctRBracket flingVarPostSpecInnards
	;
flingGeneval:
	KwGeneval flingExpr
	;
flingGenBreak:
	KwGen PunctLBracket KwBreak PunctRBracket flingBreakHeaderSuffix
	;
flingGenContinue:
	KwGen PunctLBracket KwContinue PunctRBracket flingContinueHeaderSuffix
	;
flingGenLabel:
	KwGen PunctLBracket KwLabel PunctRBracket flingLabelHeaderSuffix
	;
//--------

//--------
flingGenCondHeader:
	KwGen PunctLBracket KwCond PunctRBracket
	;
flingGenMuxHeader:
	KwGen PunctLBracket KwMux PunctRBracket flingMuxHeaderSuffix
	;

flingGenMatchHeader:
	KwGen PunctLBracket KwMatch PunctRBracket flingMatchHeaderSuffix
	;
//--------

//--------
flingGenForHeader:
	KwGen PunctLBracket KwFor PunctRBracket flingForHeaderSuffix
	;
flingGenWhileHeader:
	KwGen PunctLBracket KwWhile PunctRBracket flingWhileHeaderSuffix
	;
//--------

//--------
flingGenScopeHeader:
	KwGen PunctLBracket KwScope PunctRBracket flingScopeHeaderSuffix
	;
//--------

//--------
flingGenTryHeader:
	KwGen PunctLBracket KwTry PunctRBracket
	;
//--------
