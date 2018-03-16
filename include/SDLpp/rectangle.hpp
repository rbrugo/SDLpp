/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : rectangle
 * @created     : Monday Feb 26, 2018 22:56:39 CET
 * @license     : MIT
 * */

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

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

    rectangle(int _x, int _y, int _w, int _h) : x{_x}, y{_y}, width{_w}, height{_h} { ; }
    rectangle(int _w, int _h) : rectangle{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _w, _h} { ; }
    rectangle(SDL_Rect const & r) : x{r.x}, y{r.y}, width{r.w}, height{r.h} { ; }
    operator SDL_Rect() const { return SDL_Rect{x, y, width, height}; }
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

#endif /* RECTANGLE_HPP */

