//--------
flingGlobalClass:
	KwClass (flingGlobalClassSpec PunctComma)?
		flingClassInnards
	;
flingGlobalClassSpec
	_spec(flingGlobalClassSpecItem)
	;

flingLocalClass:
	KwClass (flingLocalClassSpec PunctComma)?
		flingClassInnards
	;

flingLocalClassSpec:
	_spec(flingLocalClassSpecItem)
	;
//--------
