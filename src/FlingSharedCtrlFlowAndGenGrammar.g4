//--------
flingCommonCtrlFlowArgList:
	'(' flingExpr ')'
	;
//--------

//--------
flingIfHeaderSuffix:
	flingCommonCtrlFlowArgList
	;
flingElifHeaderSuffix:
	flingCommonCtrlFlowArgList
	;
//--------

//--------
flingSwitchHeaderSuffix:
	flingCommonCtrlFlowArgList
	;
flingTagswitchHeaderSuffix:
	flingCommonCtrlFlowArgList
	;
flingCaseHeaderSuffix:
	flingCommonCtrlFlowArgList
	;
//--------

//--------
flingForHeaderSuffix:
	'(' flingIdent ',' flingExpr ')'
	;
flingWhileHeaderSuffix:
	flingCommonCtrlFlowArgList
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
flingScopeHeaderSuffix:
	'(' flingIdent ')'
	;
//--------

//--------
flingSharedGenItem:
	flingGenCall
	| flingGenSet
	| flingGenVar
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
flingGenSwitchHeader:
	KwGen '<' KwSwitch '>' flingSwitchHeaderSuffix
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

flingGenBreak:
	KwGen '<' KwBreak '>' flingBreakHeaderSuffix
	;
flingGenContinue:
	KwGen '<' KwContinue '>' flingContinueHeaderSuffix
	;

flingGenLabelHeader:
	KwGen '<' KwLabel '>' flingLabelHeaderSuffix
	;

flingGenScopeHeader:
	KwGen '<' KwScope '>' flingScopeHeaderSuffix
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
