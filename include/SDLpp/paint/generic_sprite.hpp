/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : generic_sprite
 * @created     : Wednesday Oct 17, 2018 10:39:28 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_PAINT_GENERIC_SPRITE_HPP
#define SDLPP_PAINT_GENERIC_SPRITE_HPP

/* #include <SDLpp/texture.hpp> */
#include "../texture.hpp"
#include "../math/point_vector.hpp"
#include "graphic_entity.hpp"

namespace SDLpp::paint
{

class generic_sprite : public graphic_entity //NOLINT
{
protected:
    /* int32_t _n_cols; */
    int32_t _cycles_per_sprite;
    mutable int32_t _frame_counter = 0;
    mutable int32_t _frame_index = 0;
    texture _texture;
    /* rect _size; */

public:
    inline generic_sprite(
        renderer & ren, point const & origin, std::string const & filename, int32_t cycles_per_sprite
    );
    inline ~generic_sprite() noexcept override = default;

    //move
    //set_position
    //position
    inline void display() const override = 0;
    inline texture const & get_texture() const;

    struct file_load_error : std::runtime_error
    {
        file_load_error(std::string const & err) : std::runtime_error{err} { }; //NOLINT
    };
};

inline generic_sprite::generic_sprite(
    renderer & ren, point const & origin, std::string const & filename, int32_t cycles_per_sprite
) :
    graphic_entity{ren, origin},
    _cycles_per_sprite{cycles_per_sprite},
    _texture{ren, filename}
{
    if (!_texture) {
        auto error_text = std::string{"Cannot load the file "}
                        .append(filename)
                        .append(": maybe the file does not exists");
        throw file_load_error(error_text);
    }
}

inline texture const & generic_sprite::get_texture() const
{
    return _texture;
}

} // namespace SDLpp::paint

#endif /* SDLPP_PAINT_GENERIC_SPRITE_HPP */

