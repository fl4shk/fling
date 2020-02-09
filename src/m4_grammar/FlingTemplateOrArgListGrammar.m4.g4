//--------
flingTemplateDeclList:
	PunctCmpLt
		(flingTemplateDeclListInnards0 | flingTemplateDeclListInnards1)
		PunctComma?
	PunctCmpGt
	;

flingTemplateDeclListInnards0:
	flingTemplateDeclListItem0 (PunctComma flingTemplateDeclListItem0)*
	;
flingTemplateDeclListInnards1:
	flingTemplateDeclListItem1 (PunctComma flingTemplateDeclListItem1)*
	;

flingTemplateDeclListItem0:
	flingIdentList PunctColon KwType (PunctLParen flingExpr PunctRParen)?
	| flingIdentList PunctColon flingExpr
	;
flingTemplateDeclListItem1:
	flingTemplateDeclListItem0 PunctAssign flingExpr
	;


flingArgDeclList:
	PunctLParen
		(flingArgDeclListInnards0 | flingArgDeclListInnards1)
		PunctComma?
	PunctRParen
	;
flingArgDeclListInnards0:
	flingArgDeclListItem0 (PunctComma flingArgDeclListItem0)*
	;
flingArgDeclListInnards1:
	(flingArgDeclListInnards0 PunctComma)?
	flingArgDeclListItem1 (PunctComma flingArgDeclListItem1)*
	;

flingArgDeclListItem0:
	flingIdentList PunctColon flingExpr
	;
flingArgDeclListItem1:
	flingArgDeclListItem0 PunctAssign flingExpr
	;
//--------

//--------
flingTemplateInstList:
	PunctCmpLt
		(
			flingInstPosListInnards
			| flingInstNamedListInnards
		)
	PunctCmpGt
	;

flingArgInstList:
	PunctLParen
		(
			flingInstPosListInnards
			| flingInstNamedListInnards
		)
	PunctRParen
	;
flingInstPosListInnards:
	_list(flingInstPosListInnardsItem)
	;
flingInstPosListInnardsItem:
	flingExpr
	;
flingInstNamedListInnards:
	_list(flingInstNamedListInnardsItem)
	;
flingInstNamedListInnardsItem:
	flingIdent PunctMapsTo flingExpr
	;
//--------
