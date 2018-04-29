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

namespace SDLpp
{

class event
{
private:
    SDL_Event _event;

public:
    SDL_Event & handler() { return _event; }
    SDL_Event const & handler() const { return _event; }
    auto poll() { return SDL_PollEvent(&_event); }

    template <typename R, typename A, typename = std::enable_if_t<meta::is_event_category_v<A>, void>>
    bool is_invocable_by(R(*f)(A));
    template <
        typename R,
        typename C,
        typename A,
        typename = std::enable_if_t<meta::is_event_category_v<A>, void>
    >
    bool is_invocable_by(R(C::*f)(A) const);

    template <typename R, typename A, typename = std::enable_if_t<meta::is_event_category_v<A>, void>>
    auto call(R(*&&f)(A)) const -> R;

    template <
        typename R,
        typename C,
        typename A,
        typename = void
    >
    auto call(C && c, R(C::*f)(A) const) const -> R;
};

template < typename R, typename A, typename >
bool event::is_invocable_by([[maybe_unused]] R(*f)(A))
{
    return _event.type == A::value;
}

template <typename R, typename C, typename A, typename >
bool event::is_invocable_by([[maybe_unused]] R(C::*f)(A) const)
{
    return _event.type == A::value;
}

template <typename R, typename A, typename >
auto event::call(R(*&&f)(A)) const -> R
{
    if constexpr ( std::is_same_v<R, void> ) {
        f(_event.*(A::member));
    }
    else {
        return f(_event.*(A::member));
    }
}

template < typename R, typename C, typename A, typename >
auto event::call(C && c, R(C::*f)(A) const) const -> R
{
    if constexpr ( std::is_same_v<R, void> ) {
        A ret{_event.*(A::member)};
        (c.*f)(std::move(ret));
    }
    else {
        return (c.*f)(_event.*(A::member));
    }
}

} // namespace SDLpp

#endif /* SDLPP_EVENT_EVENT_HPP */

