//--------
flingGlobalClass:
	KwClass (flingGlobalClassSpec ',')?
		flingClassInnards
	;
flingGlobalClassSpec

flingLocalClass:
	KwClass (flingLocalClassSpec ',')?
		flingClassInnards
	;

flingLocalClassSpec:
	KwSpec
	'{'
		flingLocalClassSpecItem
		(',' flingLocalClassSpecItem)*
		','?
	'}'
	;
//--------
