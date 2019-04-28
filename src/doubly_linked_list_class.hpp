#ifndef src_doubly_linked_list_class_hpp
#define src_doubly_linked_list_class_hpp

// src/doubly_linked_list_class.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

template<typename Type>
class DoublyLinkedList
{
public:		// types
	class Node final
	{
	private:		// variables
		Node * _next = nullptr, * _prev = nullptr;

	public:		// variables
		Type data;

	public:		// functions
		inline Node() = default;
		inline ~Node() = default;

		GEN_GETTER_BY_VAL(next)
		GEN_GETTER_BY_VAL(prev)
	};

private:		// variables

public:		// functions
};

} // namespace frost_hdl


#endif		// src_doubly_linked_list_class_hpp
