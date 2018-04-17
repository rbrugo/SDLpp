/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : img_flags
 * @created     : Sunday Mar 25, 2018 23:52:02 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_IMG_FLAGS_HPP
#define SDLPP_IMG_FLAGS_HPP

#include <SDL2/SDL_image.h>

namespace SDLpp
{
namespace flag
{
using _sdl_img_flag_t = decltype(IMG_INIT_JPG);

enum class img
{
    none    = 0,
    jpg     = IMG_INIT_JPG,
    png     = IMG_INIT_PNG,
    tif     = IMG_INIT_TIF
};
constexpr img operator &(img a, img b) noexcept
{
    return static_cast<img>( static_cast<_sdl_img_flag_t>(a) & static_cast<_sdl_img_flag_t>(b) );
}
constexpr img & operator &=(img & a, img b) noexcept
{
    a = a & b;
    return a;
}
constexpr img operator |(img a, img b) noexcept
{
    return static_cast<img>( static_cast<_sdl_img_flag_t>(a) | static_cast<_sdl_img_flag_t>(b) );
}
constexpr img & operator |=(img & a, img b) noexcept
{
    a = a | b;
    return a;
}

} // namespace flag
} // namespace SDLpp

#endif /* SDLPP_IMG_FLAGS_HPP */

