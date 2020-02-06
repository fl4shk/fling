//--------
flingTemplateDeclList:
	;

flingArgDeclList:
	;
//--------

//--------
flingTemplateInstList:
	'<'
		(
			flingTemplateInstPosListInnards
			| flingTemplateInstNamedListInnards
		)
	'>'
	;

flingArgInstList:
	'(' 
		(
			flingArgInstPosListInnards | flingArgInstNamedListInnards
		)
	')'
	;
//--------
