
#define ANY_JUST_ACCEPT_BASIC(arg) \
	arg->accept(this)

#define ANY_JUST_ACCEPT_LOOPED(iter, arg) \
	for (auto iter : arg) \
	{ \
		ANY_JUST_ACCEPT_BASIC(iter); \
	}

#define ANY_ACCEPT_IF_BASIC(arg) \
	if (arg) \
	{ \
		ANY_JUST_ACCEPT_BASIC(arg); \
	}


#define TOK_TO_DUPPED_STR(arg) \
	dup_str(arg->toString())

#define ANY_PUSH_TOK_IF(arg) \
	if (arg) \
	{ \
		_stacks.push_str(TOK_TO_DUPPED_STR(arg)); \
	}

#define DEBUG_EXPR(func, context) \
	printout("ParseTreeVisitor::", #func, "():  ", #context, ":  ", \
		!!ctx->context(), "\n")
