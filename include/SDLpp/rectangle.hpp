/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : rectangle
 * @created     : Monday Feb 26, 2018 22:56:39 CET
 * @license     : MIT
 * */

#ifndef SDLPP_RECTANGLE_HPP
#define SDLPP_RECTANGLE_HPP

#include <SDL2/SDL.h>

namespace SDLpp
{

/// Similar to SDL_Rect
struct rectangle
{
    int x;
    int y;
    int width;
    int height;

    rectangle(int _x, int _y, int _w, int _h) noexcept : x{_x}, y{_y}, width{_w}, height{_h} { ; }
    rectangle(int _w, int _h) noexcept : rectangle{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _w, _h} { ; }
    explicit rectangle(SDL_Rect const & r) noexcept : rectangle{ r.x, r.y, r.w, r.h } { ; }
    //rectangle(SDL_Rect const & r) : x{r.x}, y{r.y}, width{r.w}, height{r.h} { ; }
    //rectangle(rectangle const &) = default;
    //rectangle(rectangle &&) = default;

    explicit operator SDL_Rect() const noexcept { return SDL_Rect{x, y, width, height}; }
};
/*struct rectangle : SDL_Rect
{
    SDL_Rect rect;

    rectangle(int _x, int _y, int _w, int _h) : rect{ _x, _y, _w, _h } { ; }
    rectangle(int _w, int _h) : rectangle{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _w, _h} { ; }
    rectangle(SDL_Rect const & r) : rect{r} { ; }
    operator SDL_Rect() const { return rect; }
};*/



} // namespace SDLpp

#endif /* SDLPP_RECTANGLE_HPP */

