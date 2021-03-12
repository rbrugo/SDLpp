/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : entity
 * @created     : martedì feb 26, 2019 23:16:14 CET
 * @license     : MIT
 * */

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "collision.hpp"
#include "paint/graphic_entity.hpp"
#include "texture.hpp"
/* #include "paint/sprite.hpp" */


namespace SDLpp
{

template <typename Collision = collision::base, typename Graphic = paint::graphic_entity>
class entity : public Collision, public Graphic
{
    using cbox = Collision;
    using gbox = Graphic;

    vector2d    _speed;

public:
    entity(renderer & ren, point2d pos, collision::shape sh, vector2d const & speed = {0, 0}) :
        cbox{pos, std::move(sh)},
        gbox{ren, pos},
        _speed{speed}
    {
        ;
    }

    virtual inline void move() noexcept
    {
        this->move(_speed);
    }

    inline void move(vector2d const & dr) noexcept override
    {
        cbox::move(dr);
        gbox::move(dr);
    }
};

} // namespace SDLpp

#endif /* ENTITY_HPP */

