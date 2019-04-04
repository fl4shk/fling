#ifndef src_in_scope_errwarn_base_class_hpp
#define src_in_scope_errwarn_base_class_hpp

// src/in_scope_errwarn_base_class.hpp

#include "misc_includes.hpp"

#include "general_allocator_class.hpp"

namespace frost_hdl
{

//// Used for more consistent error/warning reporting
//template<typename ActualSrcCodePos>
//class InScopeErrWarnBase
//{
//public:		// functions
//	inline InScopeErrWarnBase() = default;
//
//	GEN_CM_BOTH_CONSTRUCTORS_AND_ASSIGN(InScopeErrWarnBase);
//	virtual ~InScopeErrWarnBase() = default; 
//
//	inline void in_scope_err(const ActualSrcCodePos& some_src_code_pos,
//		const std::string& msg) const
//	{
//		some_src_code_pos.err(sconcat("In ", scope_type_str(), " \"",
//			*ident(), "\":  ", msg));
//	}
//	inline void in_scope_warn(const ActualSrcCodePos& some_src_code_pos,
//		const std::string& msg) const
//	{
//		some_src_code_pos.warn(sconcat("In ", scope_type_str(), " \"",
//			*ident(), "\":  ", msg));
//	}
//
//	virtual std::string scope_type_str() const = 0;
//	//virtual const ActualSrcCodePos& src_code_pos() const = 0;
//	virtual SavedString ident() const = 0;
//
//};

} // namespace frost_hdl

#endif		// src_in_scope_errwarn_base_class_hpp
