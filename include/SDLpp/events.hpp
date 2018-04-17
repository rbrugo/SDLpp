/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : events
 * @created     : Sunday Mar 18, 2018 18:49:05 CET
 * @license     : MIT
 * */

#ifndef SDLPP_EVENTS_HPP
#define SDLPP_EVENTS_HPP

#include <SDL2/SDL.h>
#include <optional>

namespace SDLpp
{

using event = SDL_Event;
using opt_event = std::optional<event>;

inline bool poll_event(event & e) noexcept
{
    //return SDL_PollEvent( std::addressof(e) ) != 0;
    return SDL_PollEvent(&e);
}

inline bool poll_event(std::optional<event> & e)
{
    if ( ! e ) {
        e = event{};
    }
    return SDL_PollEvent( std::addressof( e.value()  )) != 0;
}

inline std::optional<event> poll_event() noexcept(std::is_nothrow_constructible_v<std::optional<event>>)
{
    event e{};
    return poll_event(e) ? std::optional{e} : std::nullopt;
}

} // namespace SDLpp

#endif /* SDLPP_EVENTS_HPP */

