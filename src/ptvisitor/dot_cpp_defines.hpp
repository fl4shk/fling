#define ANY_JUST_ACCEPT_BASIC(arg) \
	arg->accept(this)


// This takes the iterator variable name as an argument to help prevent
// name collisions
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


#define ANY_PUSH_TOK_IF(arg) \
	if (arg) \
	{ \
		_stacks.push_str(arg->toString()); \
	}

#define DEBUG_EXPR(func, context) \
	printout("PTVisitor::", #func, "():  ", #context, ":  ", \
		!!ctx->context(), "\n")
