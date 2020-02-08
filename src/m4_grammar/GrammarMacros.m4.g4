changequote(<:,:>)dnl
define(<:_type_etc_list:>,
<:
	fling$1Class
	| fling$1Mixin
	| fling$1Variant
	| fling$1Enum
	| fling$1Union
	| fling$1Trait
:>)dnl
define(<:_list:>,
	<:PunctLBrace <:$1:> (PunctComma <:$1:>)* PunctComma? PunctRBrace:>)dnl
define(<:_spec:>,
	<:KwSpec _list(<:$1:>):>)dnl
define(<:_gen:>,
<:
fling<:$1:>Gen:
	flingSharedGenItem

	| fling<:$1:>GenCond
	| fling<:$1:>GenMux
	| fling<:$1:>GenMatch

	| fling<:$1:>GenFor
	| fling<:$1:>GenWhile

	| fling<:$1:>GenScope
	| fling<:$1:>GenTry
	;

fling<:$1:>GenCond:
	flingGenCondHeader
	PunctLBrace
		fling<:$1:>GenIf
		(PunctComma fling<:$1:>GenIf)*
		(PunctComma fling<:$1:>GenElse)?
		PunctComma?
	PunctRBrace
	;
fling<:$1:>GenIf:
	flingIfHeader fling<:$1:>ScopeInnards
	;
fling<:$1:>GenElse:
	flingElseHeader fling<:$1:>ScopeInnards
	;


fling<:$1:>GenMux:
	flingGenMuxHeader
	PunctRBrace
		// if
		fling<:$1:>ScopeInnards

		// else
		PunctComma fling<:$1:>ScopeInnards
	PunctRBrace
	;


fling<:$1:>GenMatch:
	flingGenMatchHeader
	PunctRBrace
		(
			fling<:$1:>GenCase
			(PunctComma fling<:$1:>GenCase)*
			(PunctComma fling<:$1:>GenDefault)?
			PunctComma?
		)?
	PunctRBrace
	;

fling<:$1:>GenMatchOptions:
	fling<:$1:>GenCase
	| fling<:$1:>GenDefault
	;
fling<:$1:>GenCase:
	flingCaseHeader fling<:$1:>ScopeInnards
	;
fling<:$1:>GenDefault:
	flingDefaultHeader fling<:$1:>ScopeInnards
	;


fling<:$1:>GenFor:
	flingGenForHeader fling<:$1:>ScopeInnards
	;
fling<:$1:>GenWhile:
	flingGenWhileHeader fling<:$1:>ScopeInnards
	;

fling<:$1:>GenScope:
	flingGenScopeHeader fling<:$1:>ScopeInnards
	;

fling<:$1:>GenTry:
	flingGenTryHeader
	PunctRBrace
		fling<:$1:>Gen
		PunctComma fling<:$1:>GenCatch
		PunctComma?
	PunctRBrace
	;
fling<:$1:>GenCatch:
	flingCaseHeader fling<:$1:>Gen
	;
:>)dnl
