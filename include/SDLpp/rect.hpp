/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : rect
 * @created     : Wednesday Apr 18, 2018 12:49:02 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_RECT_HPP
#define SDLPP_RECT_HPP

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL.h>

namespace SDLpp
{
constexpr auto const windowpos_undefined = SDL_WINDOWPOS_UNDEFINED;

struct rect : public SDL_Rect
{
    constexpr rect() : rect{0, 0} {};
    constexpr rect(int x, int y, int w, int h) noexcept : SDL_Rect{x,y,w,h} {};
    constexpr rect(int w, int h) noexcept : rect{windowpos_undefined, windowpos_undefined, w, h} {};
    constexpr explicit rect(SDL_Rect origin) : SDL_Rect{origin} {};
};

} // namespace SDLpp

#endif /* SDLPP_RECT_HPP */

