//#ifndef src_gen_stacks_stuff_hpp
//#define src_gen_stacks_stuff_hpp

// src/gen_stacks_stuff.hpp

class Stacks
{
private:		// variables
	#define GEN_STACK(stack_type, dummy, whateverfix) \
		std::stack<stack_type> _##whateverfix##_inner_stack; 

	LIST_FOR_GEN_STACK(GEN_STACK)
	#undef GEN_STACK

public:		// functions
	#define GEN_STACK_FUNCS(dummy, ret_type, whateverfix) \
		inline void push_##whateverfix(ret_type to_push) \
		{ \
			_##whateverfix##_inner_stack.push(to_push); \
		} \
		inline auto get_top_##whateverfix() \
		{ \
			return _##whateverfix##_inner_stack.top(); \
		} \
		inline auto pop_##whateverfix() \
		{ \
			auto ret = _##whateverfix##_inner_stack.top(); \
			_##whateverfix##_inner_stack.pop(); \
			return ret; \
		} \
		inline const auto& whateverfix##_inner_stack() const \
		{ \
			return _##whateverfix##_inner_stack; \
		}

	LIST_FOR_GEN_STACK(GEN_STACK_FUNCS)
	#undef GEN_STACK_FUNCS

} _stacks;

#define GEN_WITH_STACKS(stack_type, var_type, whateverfix) \
friend class with_stacks_##whateverfix; \
class with_stacks_##whateverfix \
{ \
private:		/* variables */ \
	/* I considered making this a static variable, but.... */ \
	PtVisitor* _pt_visitor = nullptr; \
\
public:		/* functions */ \
	inline with_stacks_##whateverfix(PtVisitor* s_pt_visitor, \
		var_type to_push) \
	{ \
		_pt_visitor = s_pt_visitor; \
		_pt_visitor->_stacks.push_##whateverfix(to_push); \
	} \
	\
	inline with_stacks_##whateverfix \
		(const with_stacks_##whateverfix& to_copy) = default; \
	\
	inline ~with_stacks_##whateverfix() \
	{ \
		_pt_visitor->_stacks.pop_##whateverfix(); \
	} \
	\
	inline with_stacks_##whateverfix& operator = \
		(const with_stacks_##whateverfix& to_copy) = default; \
};

LIST_FOR_GEN_STACK(GEN_WITH_STACKS)
#undef GEN_WITH_STACKS

//#endif		// src_gen_stacks_stuff_hpp
