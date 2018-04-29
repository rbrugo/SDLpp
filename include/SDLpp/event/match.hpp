/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : match
 * @created     : Sunday Apr 29, 2018 14:34:33 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_MATCH_HPP
#define SDLPP_MATCH_HPP

#include "event.hpp"
#include <functional>

namespace SDLpp
{

namespace detail
{

template <typename E, typename R, typename C, typename A>
bool is_invocable_by(E && e, R(C::*f)(A) const)
{
    return e.is_invocable_by(f);
}

template <typename E, typename R, typename A>
bool is_invocable_by(E && e, R(*f)(A))
{
    return e.is_invocable_by(f);
}

template <typename E, typename F>
bool is_invocable_by(E && e, F && f)
{
    //return e.is_invocable_by(f);
    return is_invocable_by(e, &std::add_const_t<std::decay_t<decltype(f)>>::operator());
}

template <typename E, typename C, typename A>
auto match_impl(E && event, void (C::*f)(A) const, C && callable)
{
    if ( detail::is_invocable_by(event, f) ) {
        event.call(std::forward<C>(callable), f);
    }
}

template < typename E, typename F >
auto match_impl(E && event, F && f)
{
    match_impl(
            std::forward<E>(event),
            &std::add_const_t<std::decay_t<decltype(f)>>::operator(),
            std::forward<F>(f)
        );
}


//Version for function objects - function object
template <typename E, typename C, typename A, typename ...Fs>//, typename = void>
auto match_impl(E && event, void (C::*f)(A) const, C && callable, Fs&&... fs)
{
    if ( ! detail::is_invocable_by(event, f) ) {
        if constexpr ( sizeof...(Fs) == 0 ) {
            return;
        }
        else {
            match_impl(std::forward<E>(event), std::forward<Fs>(fs)...);
        }
    }
    event.call(std::forward<C>(callable), f);
}

//Version for function objects - pointer-to-function-member
template < typename E, typename F, typename ...Fs >
auto match_impl(E && event, F && f, Fs&&... fs)
{
    match_impl(
            std::forward<E>(event),
            &std::add_const_t<std::decay_t<decltype(f)>>::operator(),
            std::forward<F>(f),
            std::forward<Fs>(fs)...
        );
}

} // namespace detail

template <typename E, typename... Fs>
auto match(E && e, Fs&&... fs)
{
    static_assert(
            std::is_same_v<std::decay_t<E>, event>,
            "`match's first argument must be an event"
        );
    detail::match_impl(std::forward<E>(e), std::forward<Fs>(fs)...);
}

} // namespace SDLpp

#endif /* SDLPP_MATCH_HPP */

