/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : shapes
 * @created     : Sunday Nov 04, 2018 02:02:45 CET
 * @license     : MIT
 * */

#ifndef SDLPP_PAINT_SHAPES_HPP
#define SDLPP_PAINT_SHAPES_HPP

#include "generic_shape.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>

namespace SDLpp
{
namespace paint
{

struct line : public generic_shape//NOLINT
{
    point _end;
    /* uint16_t _thickness; */
public:
    auto & from() noexcept { return _origin; }
    auto & to()   noexcept { return _end; }
    /* auto & thickness() noexcept { return _thickness; } */
    auto   from() const noexcept { return _origin; }
    auto   to()   const noexcept { return _end; }
    /* auto   thickness() const noexcept { return _thickness; } */

    constexpr line(renderer & ren, point const & origin, point const & end, /*uint16_t thickness = 1,*/ SDLpp::color c = colors::black) noexcept;
    constexpr line(renderer & len, point const & origin, double theta, double length, /*uint16_t thickness = 1,*/ SDLpp::color c = colors::black) noexcept;

    void display() const noexcept override;
    ~line() noexcept override = default;
};

template <typename Allocator = std::allocator<point2d>>
struct multiline : public generic_shape//NOLINT
{
protected:
    std::vector<point, Allocator> _points;
    uint8_t _thickness;

public:
    template <typename ...Pts, typename = std::enable_if_t<std::is_same_v<Pts..., point>, void>>
    constexpr multiline(renderer &, uint8_t thickness, SDLpp::color, Pts &&... pts);
    constexpr multiline(renderer &, uint8_t thickness, SDLpp::color, std::initializer_list<point> pts);

    void display() const noexcept override;
    ~multiline() noexcept override = default;
};

struct circle : public generic_shape//NOLINT
{
protected:
    double _radius;
    bool _filled = true;

public:
    constexpr circle(renderer & ren, point const & origin, double radius, SDLpp::color c = colors::red, bool fill = true) noexcept;
    constexpr circle(renderer & ren, double radius) noexcept;

    void display() const noexcept override;
    ~circle() noexcept override = default;

};

struct rectangle : public generic_shape//NOLINT
{
protected:
    double _w, _h;
    bool _filled = true;

public:
    constexpr rectangle(renderer & ren, point const & origin, double w, double h, SDLpp::color c = colors::red, bool fill = true) noexcept;
    constexpr rectangle(renderer & ren, rect const & xywh, SDLpp::color c = colors::red, bool fill = true) noexcept;

    void display() const noexcept override;
    ~rectangle() noexcept override = default;
};

/// LINE
constexpr line::line(
    renderer & ren, point const & origin, point const & end, /*uint16_t thickness,*/ SDLpp::color c
) noexcept
: generic_shape{ren, origin, c}, _end{end}//, _thickness{thickness}
{
    ;
}

constexpr line::line(
    renderer & ren, point const & origin, double theta, double length, /*uint16_t thickness,*/ SDLpp::color c
) noexcept :
    generic_shape{ren, origin, c},
    _end{origin.x() + length * std::cos(theta), origin.y() + length * std::sin(theta)}//,
    /* _thickness{thickness} */
{
    ;
}

inline void line::display() const noexcept
{
    auto const [x1, y1] = _origin;
    auto const [x2, y2] = _end;
    /* ren.set_draw_\\color(c); */
    /* thickLineColor(_ren->handler(), x1, y1, x2, y2, _thickness, static_cast<uint32_t>(color)); */
    aalineColor(_ren->handler(), x1, y1, x2, y2, static_cast<uint32_t>(color));
}

/// MULTILINE
template <typename Allocator>
template <typename ...Pts, typename>
constexpr multiline<Allocator>::multiline(renderer & ren, uint8_t thickness, SDLpp::color c, Pts &&... pts) :
    multiline{ren, thickness, c, std::initializer_list<point>(pts...)}
{
    ;
}

template <typename Allocator>
constexpr multiline<Allocator>::multiline(
    renderer & ren, uint8_t thickness, SDLpp::color c, std::initializer_list<point> pts
) : generic_shape{ren, point{0, 0}, c}, _points{pts}
{
    ;
}

template <typename Allocator>
void multiline<Allocator>::display() const noexcept
{
    auto const size = _points.size();
    for (auto i = 0ul; i < size - 1; ++i) {
        auto const [x1, y1] = _points[i];
        auto const [x2, y2] = _points[i+1];

        thickLinesColor(_ren->handler(), x1, y1, x2, y2, _thickness, static_cast<uint32_t>(color));
    }
}

/// CIRCLE
constexpr circle::circle(renderer & ren, point const & origin, double radius, SDLpp::color c, bool fill) noexcept
:   generic_shape{ren, origin, c}, _radius{radius}, _filled{fill}
{
    ;
}

constexpr circle::circle(renderer & ren, double radius) noexcept :
    circle{ren, {0, 0}, radius}
{
    ;
}

inline void circle::display() const noexcept
{
    auto [x, y] = _origin;
    if (_filled) {
        filledCircleColor(_ren->handler(), x, y, _radius, static_cast<uint32_t>(color));
    } else {
        circleColor(_ren->handler(), x, y, _radius, static_cast<uint32_t>(color));
    }
}

/// RECTANGLE
constexpr rectangle::rectangle(renderer & ren, point const & origin, double w, double h, SDLpp::color c, bool fill) noexcept :
    generic_shape{ren, origin, c}, _w{w}, _h{h}, _filled{fill}
{
    ;
}

constexpr rectangle::rectangle(renderer & ren, rect const & xywh, SDLpp::color c, bool fill) noexcept :
    rectangle{ren, point(xywh.x, xywh.y), static_cast<double>(xywh.w), static_cast<double>(xywh.h), c, fill}
{
    ;
}

inline void rectangle::display() const noexcept
{
    auto [_x, _y] = _origin;
    if (_filled) {
        boxColor(_ren->handler(), _x, _y, _x + _w, _y + _h, static_cast<uint32_t>(color));
    } else {
        rectangleColor(_ren->handler(), _x, _y, _x + _w, _y + _h, static_cast<uint32_t>(color));
    }
}


} // namespace paint
} // namespace SDLpp

#endif /* SDLPP_PAINT_SHAPES_HPP */

