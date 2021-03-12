/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : generic_shape
 * @created     : Saturday Nov 03, 2018 21:28:00 CET
 * @license     : MIT
 * */

#ifndef SDLPP_PAINT_GENERIC_SHAPE_HPP
#define SDLPP_PAINT_GENERIC_SHAPE_HPP

#include "../color.hpp"
#include "graphic_entity.hpp"

namespace SDLpp
{
namespace paint
{

struct generic_shape : public graphic_entity//NOLINT
{
protected:
    using point = point2d;
public:
    SDLpp::color color;
    constexpr generic_shape(SDLpp::renderer & ren, point const & origin, SDLpp::color c = colors::black) noexcept;
    void display() const override = 0;
    ~generic_shape() noexcept override = default;
};

constexpr generic_shape::generic_shape(SDLpp::renderer & ren, point const & origin, SDLpp::color c) noexcept :
    graphic_entity{ren, origin}, color{c}
{
    ;
}

} // namespace paint
} // namespace SDLpp

#endif /* SDLPP_PAINT_GENERIC_SHAPE_HPP */

