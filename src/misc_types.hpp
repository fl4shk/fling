#ifndef src_misc_types_hpp
#define src_misc_types_hpp

// src/misc_types.hpp

#include "misc_includes.hpp"
#include "ident_table_classes.hpp"
//#include "scoped_table_classes.hpp"

namespace frost_hdl
{
//typedef std::string string;

class AstNode;

template<typename Type>
inline string construct_str_from_pointer(Type* pointer)
{
	return sconcat(reinterpret_cast<uintptr_t>(pointer));
}

//// Used for temporary type identifiers before actual dimension expressions
//// are evaluated.
//template<typename Type>
//inline string construct_initial_type_ident_from_pointer
//	(const string& base_ident, Type* pointer)
//{
//	return sconcat(base_ident, "[", *construct_str_from_pointer
//		(pointer), "]");
//}
//
//template<typename FirstArgType, typename SecondArgType>
//inline string construct_initial_type_ident_from_two_ptrs
//	(const string& base_ident, FirstArgType* first_ptr,
//	SecondArgType* second_ptr)
//{
//	return sconcat(base_ident, "[", *construct_str_from_pointer(first_ptr),
//		" ", *construct_str_from_pointer(second_ptr), "]");
//}


//typedef std::vector<AstNode*> ParametersVec;
//
//
//template<typename Type>
//class PointerVector : public std::vector<Type*>
//{
//public:		// functions
//	inline PointerVector() = default;
//
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(PointerVector);
//	virtual ~PointerVector() = default;
//};

} // namespace frost_hdl


#endif		// src_misc_types_hpp
