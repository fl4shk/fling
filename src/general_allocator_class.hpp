#ifndef src_general_allocator_class_hpp
#define src_general_allocator_class_hpp

// src/general_allocator_class.hpp

#include "misc_includes.hpp"
#include "misc_types.hpp"
#include "list_for_gen_save_define.hpp"


#include <map>

namespace frost_hdl
{

#define GEN_SAVE(dummy_0, needed, dummy_1) \
	class needed;

LIST_FOR_GEN_SAVE(GEN_SAVE)

#undef GEN_SAVE

typedef std::string RawSavedString;
typedef const RawSavedString* SavedString;

typedef std::vector<bool> RawExprNumData;
typedef const RawExprNumData* ExprNumData;


class GeneralAllocator
{
private:		// static variables
	static std::map<RawSavedString, std::unique_ptr<const RawSavedString>>
		_str_pool;
	static std::map<RawExprNumData, std::unique_ptr<const RawExprNumData>>
		_expr_num_data_pool;

	#define GEN_SAVE_POOLS(pool_prefix, contained_type, dummy) \
		static MoveOnlyPrevCurrPair<std::vector<std::unique_ptr \
			<contained_type>> _##pool_prefix##_pool;

	LIST_FOR_GEN_SAVE(GEN_SAVE_POOLS)

	#undef GEN_SAVE_POOLS

public:		// static functions
	static SavedString dup_str(const RawSavedString& to_dup);
	static SavedString dup_str(RawSavedString&& to_dup);
	static ExprNumData dup_expr_num_data(const RawExprNumData& to_dup); 
	static ExprNumData dup_expr_num_data(RawExprNumData&& to_dup); 


	#define GEN_SAVE(reuse, ret_type, template_type) \
		template<typename template_type> \
		static inline ret_type* save_##reuse(template_type&& to_save) \
		{ \
			return _inner_save_generic<ret_type, template_type> \
				(_##reuse##_pool, std::move(to_save)); \
		}

	LIST_FOR_GEN_SAVE(GEN_SAVE)

	#undef GEN_SAVE



private:		// static functions
	template<typename ToSaveBaseType, typename ToSaveType>
	static inline ToSaveBaseType* _inner_save_generic(MoveOnlyPrevCurrPair
		<std::vector<std::unique_ptr<ToSaveBaseType>>>& pool,
		ToSaveType&& to_save)
	{
		std::unique_ptr<ToSaveBaseType> to_insert;
		to_insert.reset(new ToSaveType(std::move(to_save)));
		pool().push_back(std::move(to_insert));
		return pool().back().get();
	}

};


inline SavedString dup_str(const RawSavedString& to_dup)
{
	return GeneralAllocator::dup_str(to_dup);
}
inline SavedString dup_str(RawSavedString&& to_dup)
{
	return GeneralAllocator::dup_str(std::move(to_dup));
}

template<typename FirstArgType, typename SecondArgType,
	typename... RemArgTypes>
inline SavedString dup_str(FirstArgType&& first_arg,
	SecondArgType&& second_arg, RemArgTypes&&... rem_args)
{
	return dup_str(sconcat(first_arg, second_arg, rem_args...));
}

inline ExprNumData dup_expr_num_data(const RawExprNumData& to_dup)
{
	return GeneralAllocator::dup_expr_num_data(to_dup);
}
inline ExprNumData dup_expr_num_data(RawExprNumData&& to_dup)
{
	return GeneralAllocator::dup_expr_num_data(std::move(to_dup));
}

#define GEN_SAVE(suffix, ret_type, template_type) \
	template<typename template_type> \
	inline ret_type* save_##suffix(template_type&& to_save) \
	{ \
		return GeneralAllocator::save_##suffix(std::move(to_save)); \
	}

LIST_FOR_GEN_SAVE(GEN_SAVE)

#undef GEN_SAVE
#undef LIST_FOR_GEN_SAVE

} // namespace frost_hdl

#endif		// src_general_allocator_class_hpp
