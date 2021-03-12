/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : rect
 * @created     : Sunday Nov 04, 2018 19:10:10 CET
 * @license     : MIT
 * */

#ifndef SDLPP_RECT_HPP
#define SDLPP_RECT_HPP

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL.h>
#include "math/point_vector.hpp"

namespace SDLpp
{

constexpr auto const windowpos_undefined = SDL_WINDOWPOS_UNDEFINED;//NOLINT

namespace math
{
template <typename Numeric = int16_t> struct basic_rect;

template <>
struct basic_rect<int16_t> : public SDL_Rect
{
    constexpr basic_rect() : basic_rect{0, 0} {};
    constexpr basic_rect(int x, int y, int w, int h) noexcept : SDL_Rect{x,y,w,h} {};
    constexpr basic_rect(int w, int h) noexcept : basic_rect{windowpos_undefined, windowpos_undefined, w, h} {};
    constexpr explicit basic_rect(SDL_Rect origin) : SDL_Rect{origin} {};
};

template <typename T>
struct basic_rect
{
    static_assert(std::is_arithmetic_v<T>, "In SDLpp::basic_rect<T>, T must be a numeric type");
    T x{}, y{};
    T w{}, h{};
    constexpr basic_rect(T x, T y, T w, T h) noexcept : x{x}, y{y}, w{w}, h{h} { }
    constexpr basic_rect(T w, T h) noexcept : basic_rect{{}, {}, w, h} { }
    constexpr auto origin() const { return math::basic_point2d{x, y}; }
};
} // namespace math

using rect = math::basic_rect<int16_t>;

} // namespace SDLpp

#endif /* SDLPP_RECT_HPP */

