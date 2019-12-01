grammar FlingGrammar;

import FlingSwGrammar;
import FlingHdlGrammar;
import FlingBuildScriptGrammar;

flingProgram:
	(
		flingSwProgram
		| flingHdlProgram
		| flingBuildScript
	)
	EOF
	;
