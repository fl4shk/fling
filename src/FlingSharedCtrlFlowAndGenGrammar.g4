//--------
flingIfHeaderSuffix:
	'(' flingExpr ')'
	;
flingElifHeaderSuffix:
	'(' flingExpr ')'
	;
//--------

//--------
flingMatchHeaderSuffix:
	'(' flingExpr ')'
	;
flingCaseHeaderSuffix:
	'(' flingExprList ')'
	;
//--------

//--------
flingForHeaderSuffix:
	'(' flingIdent ',' flingExpr ')'
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
flingSharedGenItem:
	flingGenCall
	| flingGenSet
	| flingGenVar
	| flingGenBreak
	| flingGenContinue
	| flingGenLabel
	;
flingGenCall:
	KwGen '<' KwCall '>' flingCommonCtrlFlowArgList
	;
flingGenSet:
	KwGen '<' KwSet '>' '(' flingExpr ',' flingExpr ')'
	;
flingGenVar:
	KwGen '<' KwVar '>' '(' flingDeclVarPostSpecInnards ')'
	;
flingGenBreak:
	KwGen '<' KwBreak '>' flingBreakHeaderSuffix
	;
flingGenContinue:
	KwGen '<' KwContinue '>' flingContinueHeaderSuffix
	;
flingGenLabel:
	KwGen '<' KwLabel '>' flingLabelHeaderSuffix
	;
//--------

//--------
flingGenIfHeader:
	KwGen '<' KwIf '>' flingIfHeaderSuffix
	;
flingGenElifHeader:
	KwGen '<' KwElif '>' flingElifHeaderSuffix
	;
flingGenElseHeader:
	KwGen '<' KwElse '>'
	;
//--------

//--------
flingGenMatchHeader:
	KwGen '<' KwMatch '>' flingMatchHeaderSuffix
	;
flingGenTagswitchHeader:
	KwGen '<' KwTagswitch '>' flingTagswitchHeaderSuffix
	;
flingGenCaseHeader:
	KwGen '<' KwCase '>' flingCaseHeaderSuffix
	;
flingGenDefaultHeader:
	KwGen '<' KwDefault '>'
	;
//--------

//--------
flingGenForHeader:
	KwGen '<' KwFor '>' flingForHeaderSuffix
	;
flingGenWhileHeader:
	KwGen '<' KwWhile '>' flingWhileHeaderSuffix
	;
//--------

//--------
flingGenTryHeader:
	KwGen '<' KwTry '>'
	;
flingGenCatchHeader:
	KwGen '<' KwCatch '>' '(' flingIdent (':' flingTypename)? ')'
	;
//--------
