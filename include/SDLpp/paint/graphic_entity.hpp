/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : paint_test
 * @created     : Wednesday Oct 17, 2018 10:14:51 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_PAINT_GRAPHIC_ENTITY_HPP
#define SDLPP_PAINT_GRAPHIC_ENTITY_HPP

#include "../texture.hpp"
#include "../math/point_vector.hpp"

namespace SDLpp::paint
{

class graphic_entity //NOLINT
{
protected:
    using point = point2d;
    using vector = vector2d;

    renderer * _ren;
    point _origin;

public:
    constexpr graphic_entity(renderer & ren, point const & origin);
    virtual ~graphic_entity() noexcept = default;

    virtual inline auto move(vector const & dr)        noexcept -> void; //graphic_entity &;
    virtual inline auto set_position(point const & pt) noexcept -> graphic_entity &;
    virtual inline auto position()                     noexcept -> point          &;
    virtual inline auto position() const               noexcept -> point const    &;
    virtual        auto display()  const                        -> void = 0; //graphic_entity & = 0;
};

constexpr graphic_entity::graphic_entity(renderer & ren, point const & origin)
    : _ren{std::addressof(ren)}, _origin{origin}
{
    ;
}

inline void/*auto*/ graphic_entity::move(vector const & dr) noexcept// -> graphic_entity &
{
    _origin += dr;
    //return *this;
}

inline auto graphic_entity::set_position(point const & pt) noexcept -> graphic_entity &
{
    _origin = pt;
    return *this;
}

inline auto graphic_entity::position() noexcept -> point &
{
    return _origin;
}

inline auto graphic_entity::position() const noexcept -> point const &
{
    return _origin;
}

} // namespace SDLpp::paint

#endif /* SDLPP_PAINT_GRAPHIC_ENTITY_HPP */

