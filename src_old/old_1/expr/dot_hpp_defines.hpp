// src/expr/dot_hpp_defines.hpp

#define REMOVE_CONST_REF(to_remove_from) \
	std::remove_const<std::remove_reference<to_remove_from>::type>::type

// Used to prevent accidentally doing a "save_expr" of the wrong type.
#define SAFE_SAVE_EXPR save_expr<REMOVE_CONST_REF(decltype(*this))>
#define DUP_CHILD(child) child->dup_with_changed_symbols(replace_syms_map)

#define TO_HDL_SOURCE(child) (*child()->to_hdl_source())
