/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : init_flags
 * @created     : Monday Mar 12, 2018 00:19:48 CET
 * @license     : MIT
 * */

#ifndef SDLPP_INIT_FLAGS_HPP
#define SDLPP_INIT_FLAGS_HPP

#include <SDL2/SDL.h>

namespace SDLpp
{
namespace flag
{

enum class init : decltype(SDL_INIT_VIDEO) //window init
{
    none        = 0,
    timer       = SDL_INIT_TIMER,
    audio       = SDL_INIT_AUDIO,
    video       = SDL_INIT_VIDEO,
    joystick    = SDL_INIT_JOYSTICK,
    haptic      = SDL_INIT_HAPTIC,
    gamecontroller = SDL_INIT_GAMECONTROLLER,
    events      = SDL_INIT_EVENTS,
    everything  = SDL_INIT_EVERYTHING,
    noparachute = SDL_INIT_NOPARACHUTE
};
constexpr init operator &(init a, init b) noexcept
{
    return static_cast<init>( static_cast<uint32_t>(a) & static_cast<uint32_t>(b) );
}
constexpr init & operator &=(init & a, init b) noexcept
{
    a = a & b;
    return a;
}
constexpr init operator |(init a, init b) noexcept
{
    return static_cast<init>( static_cast<uint32_t>(a) | static_cast<uint32_t>(b) );
}
constexpr init & operator |=(init & a, init b) noexcept
{
    a = a | b;
    return a;
}

} // namespace flag
} // namespace SDLpp

#endif /* SDLPP_INIT_FLAGS_HPP */

