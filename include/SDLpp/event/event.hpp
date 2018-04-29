/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : event
 * @created     : Sunday Apr 29, 2018 14:27:47 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_EVENT_EVENT_HPP
#define SDLPP_EVENT_EVENT_HPP

#include <SDL2/SDL_events.h>
#include "event_category.hpp"

#include <typeinfo>

namespace SDLpp
{

class event
{
private:
    SDL_Event _event;

public:
    SDL_Event & handler() { return _event; }
    SDL_Event const & handler() const { return _event; }
    inline auto poll() { return SDL_PollEvent(&_event) != 0; }

    template <typename R, typename A, typename = std::enable_if_t<meta::is_event_category_v<A>, void>>
    inline bool is_invocable_by(R(*f)(A));
    template <
        typename R,
        typename C,
        typename A,
        typename = std::enable_if_t<meta::is_event_category_v<std::decay_t<A>>, void>
    >
    inline bool is_invocable_by(R(C::*f)(A) const);

    template <typename R, typename A, typename = std::enable_if_t<meta::is_event_category_v<A>, void>>
    inline auto call(R(*f)(A)) const -> R;

    template < typename R, typename C, typename A, typename = void >
    inline auto call(C && c, R(C::*f)(A) const) const -> R;
};

template < typename R, typename A, typename >
inline bool event::is_invocable_by([[maybe_unused]] R(*f)(A))
{
    return (_event.type == std::decay_t<A>::value);
}

template <typename R, typename C, typename A, typename >
inline bool event::is_invocable_by([[maybe_unused]] R(C::*f)(A) const)
{
    return (_event.type == std::decay_t<A>::value);
}

template <typename R, typename A, typename >
inline auto event::call(R(*f)(A)) const -> R
{
    if constexpr ( std::is_same_v<R, void> ) {
        f(_event.*(std::decay_t<A>::member));
    }
    else {
        return f(_event.*(std::decay<A>::member));
    }
}

template < typename R, typename C, typename A, typename >
inline auto event::call(C && c, R(C::*f)(A) const) const -> R
{
    if constexpr ( std::is_same_v<R, void> ) {
        A ret{_event.*(std::decay_t<A>::member)};
        (c.*f)(ret);
    }
    else {
        return (c.*f)(_event.*(std::decay_t<A>::member));
    }
}

} // namespace SDLpp

#endif /* SDLPP_EVENT_EVENT_HPP */

