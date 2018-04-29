/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : poll_event
 * @created     : Sunday Apr 29, 2018 16:25:21 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_EVENT_POLL_EVENT_HPP
#define SDLPP_EVENT_POLL_EVENT_HPP

#include "event.hpp"
#include <tl/optional.hpp>

namespace SDLpp
{

inline bool poll_event(event & e) noexcept
{
    //return SDL_PollEvent(&e);
    return e.poll();
}

inline bool poll_event(tl::optional<event> & e)
{
    if ( ! e ) {
        e = event{};
    }
    //return SDL_PollEvent( std::addressof( e.value()  )) != 0;
    return e->poll();
}

inline tl::optional<event> poll_event() noexcept(std::is_nothrow_constructible_v<tl::optional<event>>)
{
    event e{};
    return poll_event(e) ? tl::optional{e} : tl::nullopt;
}


} // namespace SDLpp

#endif /* SDLPP_EVENT_POLL_EVENT_HPP */

