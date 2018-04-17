/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : uniform_tuple_accumulate
 * @created     : Saturday Mar 31, 2018 19:32:24 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_META_UNIFORM_TUPLE_ACCUMULATE_HPP
#define SDLPP_META_UNIFORM_TUPLE_ACCUMULATE_HPP

#include <tuple>
#include <type_traits>

// I know that it is overengineering, I just wanted to test.
namespace SDLpp
{
namespace meta
{

template <typename T, typename ...Ts>
struct uniform_type_pack
{
    static constexpr bool value = (std::is_same_v<T,Ts> && ...);
};

template <typename ...Ts>
constexpr inline bool uniform_type_pack_v = uniform_type_pack<Ts...>::value;

template <std::size_t i, typename ...Us, typename F, typename Res>
constexpr auto __uniform_tuple_accumulate_impl(std::tuple<Us...> const & t, Res && res, F && f)
{
    if constexpr ( i < sizeof...(Us) ) {
        auto result =
            __uniform_tuple_accumulate_impl<i+1>(
                    t,
                    std::move(f(std::forward<Res>(res), std::get<i>(t))),
                    std::forward<F>(f)
                );
        return result;
    }
    else {
        return res;
    }
}

template <
    typename ...Us,
    typename F = std::plus<Us...>,
    typename Res = std::invoke_result_t<decltype(F::operator())>
>
constexpr auto uniform_tuple_accumulate( std::tuple<Us...> const & t, Res && res, F && f = F{} )
{
    static_assert(uniform_type_pack_v<Us...>, "b");
    return __uniform_tuple_accumulate_impl<0>(t, std::forward<Res>(res), std::forward<F>(f));
}

} // namespace meta
} // namespace SDLpp

#endif /* SDLPP_META_UNIFORM_TUPLE_ACCUMULATE_HPP */

