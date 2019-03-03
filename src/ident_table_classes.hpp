#ifndef src_ident_table_classes_hpp
#define src_ident_table_classes_hpp

// src/ident_table_classes.hpp

#include "misc_includes.hpp"
#include "general_allocator_class.hpp"

namespace frost_hdl
{

//typedef std::string* Ident;

template<typename Type>
class IdentTable
{
public:		// typedefs
	typedef SavedString Ident;

private:		// variables
	std::map<Ident, Type> _table;

public:		// functions
	IdentTable() = default;
	virtual ~IdentTable() = default;

	// Type accessors
	inline Type& at(Ident some_name)
	{
		return _table[some_name];
	}

	inline const Type& at(Ident some_name) const
	{
		return _table.at(some_name);
	}

	inline bool contains(Ident some_name) const
	{
		return (_table.count(some_name) == 1);
	}

	inline void insert_or_assign(const Type& to_insert_or_assign)
	{
		at(to_insert_or_assign.ident()) = to_insert_or_assign;
	}
	inline void insert_or_assign(Type&& to_insert_or_assign)
	{
		at(to_insert_or_assign.ident()) = std::move(to_insert_or_assign);
	}

	GEN_GETTER_BY_CON_REF(table);
};

template<typename Type>
class IdentToPointerTable
{
public:		// typedefs
	typedef SavedString Ident;

private:		// variables
	std::map<Ident, Type*> _table;

public:		// functions
	IdentToPointerTable() = default;
	virtual ~IdentToPointerTable() = default;

	// Type accessors
	inline auto& at(Ident some_name)
	{
		return _table[some_name];
	}

	inline const auto& at(Ident some_name) const
	{
		return _table.at(some_name);
	}

	inline bool contains(Ident some_name) const
	{
		return (_table.count(some_name) == 1);
	}

	inline void insert_or_assign(Type* to_insert_or_assign)
	{
		at(to_insert_or_assign->ident()) = to_insert_or_assign;
	}

	GEN_GETTER_BY_CON_REF(table);
	GEN_GETTER_BY_REF(table);
};

template<typename Type>
class OrderedIdentToPointerTable : public std::vector<Type*>
{
public:		// types
	typedef std::vector<Type*> Base;

public:		// functions
	OrderedIdentToPointerTable() = default;

	inline OrderedIdentToPointerTable
		(const OrderedIdentToPointerTable& to_copy) = delete;
	inline OrderedIdentToPointerTable
		(OrderedIdentToPointerTable&& to_move) = default;

	virtual ~OrderedIdentToPointerTable() = default;

	inline OrderedIdentToPointerTable& operator =
		(const OrderedIdentToPointerTable& to_copy) = delete;
	inline OrderedIdentToPointerTable& operator =
		(OrderedIdentToPointerTable&& to_move) = default;

	Type* find(SavedString some_name) const
	{
		for (size_t i=0; i<Base::size(); ++i)
		{
			if (Base::at(i).ident() == some_name)
			{
				return Base::at(i);
			}
		}

		return nullptr;
	}

	inline bool contains(SavedString some_name) const
	{
		return (find(some_name) != nullptr);
	}

	bool attempt_push_back(Type* to_push)
	{
		if (!contains(to_push->ident()))
		{
			push_back(to_push);
			return true;
		}

		return false;
	}
};

} // namespace frost_hdl

#endif		// src_ident_table_classes_hpp
