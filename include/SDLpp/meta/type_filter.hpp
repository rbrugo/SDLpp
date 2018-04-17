/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : type_filter
 * @created     : Saturday Mar 31, 2018 18:47:17 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_META_TYPE_FILTER_HPP
#define SDLPP_META_TYPE_FILTER_HPP

#include <tuple>

namespace SDLpp
{
namespace meta
{
    template <typename T, typename U>
    constexpr auto filter_element(U elem)
    {
        if constexpr ( std::is_same_v<T, std::decay_t<U>> ) {
            return std::tuple{elem};
        }
        else {
            return std::tuple<>{};
        }
    }

    //Old
    //template <typename T, typename ...Us>
    //constexpr auto tuple_filter(Us ...args)
    //{
        //return std::tuple_cat( (filter_element<T,Us>(args))... );
    //}

    template <typename T, typename ...Us>
    constexpr auto type_filter(Us ...args)
    {
        return std::tuple_cat( (filter_element<T,Us>(args))... );
    }

} // namespace meta
} // namespace SDLpp

#endif /* SDLPP_META_TYPE_FILTER_HPP */

