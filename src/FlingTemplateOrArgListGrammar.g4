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
		(
			flingArgDecListInnards0
			| flingArgDecListInnards1
		)
		','?
	')'
	;
flingArgDeclListInnards0:
	flingArgDeclListItem0 (',' flingArgDeclListItem0)*
	;
flingArgDeclListInnards1:
	(flingArgDecListInnards0 ',')?
	flingArgDeclListItem1 (',' flingArgDeclListItem1)*
	;

flingArgDeclListItem0:
	flingIdentList ':' flingExpr
	;
flingArgDeclListItem1:
	flingArgDeclListItem0 '=' flingExpr
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
