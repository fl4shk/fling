#ifndef src_misc_utility_funcs_hpp
#define src_misc_utility_funcs_hpp

// src/misc_utility_funcs.hpp

#include "misc_includes.hpp"

namespace frost_hdl
{

//inline Ident pretabbed(const Ident& to_pre_tab)
//{
//	return sconcat("\t", to_pre_tab);
//}
//inline Ident dblpretabbed(const Ident& to_pre_tab)
//{
//	return pretabbed(pretabbed(to_pre_tab));
//}

template<typename FirstArgType, typename... RemArgTypes>
inline Ident pretabbed(const FirstArgType& first_arg,
	RemArgTypes&&... rem_args)
{
	return sconcat("\t", first_arg, rem_args...);
}
template<typename FirstArgType, typename... RemArgTypes>
inline Ident dblpretabbed(const FirstArgType& first_arg,
	RemArgTypes&&... rem_args)
{
	return pretabbed(pretabbed("\t", first_arg, rem_args...));
}

} // namespace frost_hdl

#endif		// src_misc_utility_funcs_hpp
