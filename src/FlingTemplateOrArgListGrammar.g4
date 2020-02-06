//--------
flingTemplateDeclList:
	'<'
		flingTemplateDeclListItem
		(',' flingTemplateDeclListItem)*
		','?
	'>'
	;

flingArgDeclList:
	'('
		flingArgDeclListItem
		(',' flingArgDeclListItem)*
		','?
	')'
	;

flingArgDeclListItem:
	flingIdentList ':' flingTypename
	;
//--------

//--------
flingTemplateInstList:
	'<' (flingInstPosListInnards | flingInstNamedListInnards) '>'
	;

flingArgInstList:
	'(' (flingInstPosListInnards | flingInstNamedListInnards) ')'
	;
flingInstPosListInnards:
	flingInstPosListInnardsItem
	(',' flingInstPosListInnardsItem)*
	','?
	;
flingInstPosListInnardsItem:
	flingExpr
	;
flingInstNamedListInnards:
	flingInstNamedListInnardsItem
	(',' flingInstNamedListInnardsItem)*
	','?
	;
flingInstNamedListInnardsItem:
	flingIdent PunctNamedMap flingExpr
	;
//--------
