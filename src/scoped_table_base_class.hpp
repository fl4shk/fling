#ifndef src_scoped_table_base_class_hpp
#define src_scoped_table_base_class_hpp

// src/scoped_table_base_class.hpp

#include "misc_includes.hpp"
#include "ident_table_classes.hpp"

namespace frost_hdl
{

template<typename Type, template<class> typename ContainerType=std::vector>
class ScopedTableNode
{
public:		// typedefs
	typedef SavedString Ident;

public:		// variables
	IdentToPointerTable<Type> table;

	ScopedTableNode* parent;
	ContainerType<ScopedTableNode*> children;


public:		// functions
	inline ScopedTableNode(ScopedTableNode* s_parent=nullptr)
		: parent(s_parent)
	{
	}

	virtual ~ScopedTableNode()
	{
	}


	inline void append_child(ScopedTableNode* to_append)
	{
		children.push_back(to_append);
	}

	//[[gnu::noinline]]
	ContainerType<std::map<Ident, Type*>*>
		get_all_children_tables() const
	{
		ContainerType<std::map<Ident, Type*>*> ret;

		_inner_get_all_children_tables(ret);

		return ret;
	}

protected:		// functions
	//[[gnu::noinline]]
	void _inner_get_all_children_tables
		(ContainerType<std::map<Ident, Type*>*>& ret) const
	{
		// Find all the tables
		for (auto iter : children)
		{
			ret.push_back(&(iter->table.table()));
			iter->_inner_get_all_children_tables(ret);
		}
	}
};

// This is kind of like a stack
// 
// Symbols need to be kept around even after they go out of scope.
// This is useful for both optimization purposes (re-use old local variable
// space, for example) and also... to guarantee correct code generation,
// lol.
template<typename Type, template<class> typename ContainerType=std::vector>
class ScopedTableBase
{
public:		// typedefs and constants
	// We want the largest signed integer type here (new change to old
	// code for this, as before it was simply using the "int64_t" type.)
	typedef intmax_t ScopeLevel;

	//static constexpr ScopeLevel builtin_scope_level = 0;
	//static constexpr ScopeLevel not_found_level = builtin_scope_level - 1;

	typedef ScopedTableNode<Type, ContainerType> Node;

	typedef SavedString Ident;

public:		// classes


protected:		// variables
	Node _tree;


	// The number of scopes that have been made - 1
	// This is the part that's kind of like a stack.
	ScopeLevel _scope_num = -1;

	// I can't remember why exactly this wasn't
	// ContainerType<std::unique_ptr<WhateverT>>, but I'll leave it be
	// since I believe the destructor here *does* work properly.
	// Note to self:  NEVER delete the contained pointers outside of the
	// destructor.
	ContainerType<Node*> _node_pool;
	ContainerType<Type*> _data_pool;


public:		// functions
	inline ScopedTableBase()
	{
		//_curr_node = &_tree;
		auto some_curr_node = &_tree;
		mkscope(some_curr_node);
	}

	// This destructor may never be called before the compiler stops
	// running.
	virtual ~ScopedTableBase()
	{
		for (size_t i=0; i<_node_pool.size(); ++i)
		{
			delete _node_pool.at(i);
		}

		for (size_t i=0; i<_data_pool.size(); ++i)
		{
			delete _data_pool.at(i);
		}
	}

	//[[gnu::noinline]]
	void mkscope(Node*& some_curr_node)
	{
		++_scope_num;

		if (scope_num() < static_cast<ScopeLevel>(0))
		{
			printerr("ScopedTableBase::mkscope():  ",
				"Far, FAR too many scopes!\n");
			exit(1);
		}

		_node_pool.push_back(new Node(some_curr_node));

		some_curr_node->append_child(_node_pool.back());
		auto old_curr_node = some_curr_node;
		some_curr_node = some_curr_node->children.back();
		some_curr_node->parent = old_curr_node;
	}
	//[[gnu::noinline]]
	void rmscope(Node*& some_curr_node)
	{
		if (some_curr_node != &_tree)
		{
			some_curr_node = some_curr_node->parent;
		}
		else
		{
			printerr("ScopedTableBase::rmscope():  Eek!\n");
			exit(1);
		}
	}

	inline void insert_or_assign(Node* some_curr_node,
		const Type& to_insert_or_assign)
	{
		_data_pool.push_back(new Type(to_insert_or_assign));
		some_curr_node->table.insert_or_assign(_data_pool.back());
	}
	inline void insert_or_assign(Node* some_curr_node,
		Type&& to_insert_or_assign)
	{
		_data_pool.push_back(new Type(std::move(to_insert_or_assign)));
		some_curr_node->table.insert_or_assign(_data_pool.back());
	}


	//[[gnu::noinline]]
	Type* find(Node* some_curr_node, Ident some_name)
	{
		//for (s64 i=scope_lev(); i>=builtin_scope_level; --i)
		for (auto p=some_curr_node; p!=&_tree; p=p->parent)
		{
			//if (table().at(i).contains(some_name))
			//{
			//	return &table().at(i).at(some_name);
			//}
			if (p->table.contains(some_name))
			{
				return p->table.at(some_name);
			}
		}

		return nullptr;
	}


	//inline Type* find_func_arg(Node* some_func_node, Ident some_name)
	//{
	//	//auto func_node = _ident_to_func_node_map.at(some_func_name);

	//	if (some_func_node->children.front()->table.contains(some_name))
	//	{
	//		return some_func_node->children.front()->table.at(some_name);
	//	}

	//	return nullptr;
	//}

	inline Type* find_in_this_blklev(Node* some_curr_node, Ident some_name)
	{
		//if (table.at(scope_lev()).back().contains(some_name))
		//{
		//	return &table.at(scope_lev()).back().at(some_name);
		//}

		if (some_curr_node->table.contains(some_name))
		{
			return some_curr_node->table.at(some_name);
		}

		return nullptr;
	}

	inline Type* find_or_insert(Node* some_curr_node, Ident some_name)
	{
		{
			auto search = find(some_curr_node, some_name);

			if (search != nullptr)
			{
				return search;
			}
		}

		Type to_insert;
		to_insert.set_name(some_name);
		insert_or_assign(some_curr_node, std::move(to_insert));

		return find(some_curr_node, some_name);
	}

	GEN_GETTER_BY_CON_REF(tree)
	GEN_GETTER_BY_REF(tree)

	GEN_GETTER_BY_VAL(scope_num)
	//GEN_GETTER_BY_VAL(scope_lev)
};

} // namespace frost_hdl

#endif		// src_scoped_table_base_class_hpp
