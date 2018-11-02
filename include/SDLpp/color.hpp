/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : color
 * @created     : Monday Jul 16, 2018 23:08:31 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_COLOR_HPP
#define SDLPP_COLOR_HPP

#include <SDL2/SDL_pixels.h>

namespace SDLpp
{

struct color : public SDL_Color
{
    constexpr color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF) : SDL_Color{r, g, b, a} { }
    constexpr color() : color{ 0x00, 0x00, 0x00, 0x00 } { }
    constexpr explicit color(SDL_Color c) : SDL_Color{c} { }
    constexpr explicit operator uint32_t() const noexcept
    {
        return SDL_FOURCC(r, g, b, a);
    }
};

namespace colors
{
    constexpr inline const color red     {255,   0,      0,      255};
    constexpr inline const color lime    {0,     255,    0,      255};
    constexpr inline const color blue    {0,     0,      255,    255};
    constexpr inline const color white   {255,   255,    255,    255};
    constexpr inline const color black   {0,     0,      0,      255};
    constexpr inline const color cyan    {0,     255,    255,    255};
    constexpr inline const color magenta {255,   0,      255,    255};
    constexpr inline const color yellow  {255,   255,    0,      255};
    constexpr inline const color green   {0,     128,    0,      255};
    constexpr inline const color gray    {128,   128,    128,    255};
    constexpr inline const color nothing {0,     0,      0,      0};
} // namespace colors

} // namespace SDLpp

#endif /* SDLPP_COLOR_HPP */

