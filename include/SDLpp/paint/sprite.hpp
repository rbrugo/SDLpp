/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : sprite
 * @created     : Wednesday Oct 17, 2018 11:32:21 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_PAINT_SPRITE_HPP
#define SDLPP_PAINT_SPRITE_HPP

#include "generic_sprite.hpp"

namespace SDLpp::paint
{

class sprite : public generic_sprite //NOLINT
{
protected:
    int32_t _n_cols;
    rect _size;
public:
    inline sprite(
        renderer & ren, point const & origin, std::string const & filename,
        int32_t n_cols = 1, int32_t cycles_per_sprite = 1
    );
    inline sprite(
        renderer & ren, point const & origin, std::string const & filename,
        rect const & origin_size, int32_t n_cols = 1, int32_t cycles_per_sprite = 1
    );
    ~sprite() noexcept override = default;

    constexpr rect const & geometry() const noexcept;

    inline void display() const override;
};


inline sprite::sprite(
    renderer & ren, point const & origin, std::string const & filename,
    rect const & origin_size, int32_t n_cols, int32_t cycles_per_sprite
) : generic_sprite{ren, origin, filename, cycles_per_sprite}, _n_cols{n_cols}
{
    _size = origin_size;
}

inline sprite::sprite(
    renderer & ren, point const & origin, std::string const & filename,
    int32_t n_cols, int32_t cycles_per_sprite
) :
    generic_sprite{ren, origin, filename, cycles_per_sprite}, _n_cols{n_cols}
{
    auto [x, y, w, h] = *_texture.geometry();
    _size = rect{x, y, w / n_cols, h};
}

constexpr rect const & sprite::geometry() const noexcept
{
    return _size;
}

inline void sprite::display() const
{
    auto [x0, y0, w, h] = _size;
    auto x1 = x0 + w * _frame_index;
    if (_frame_index >= _n_cols) {
        x1 = x0;
        _frame_index = 0;
    }
    auto [_x, _y] = _origin;
    auto pos  = SDLpp::rect{static_cast<int32_t>(_x), static_cast<int32_t>(_y), w, h};
    auto crop = SDLpp::rect{x1, y0, w, h};
    _ren->copy(_texture, {crop}, {pos});
    if (++_frame_counter == _cycles_per_sprite) {
        ++_frame_index;
        _frame_counter = 0;
    }
}




} // namespace SDLpp::paint

#endif /* SDLPP_PAINT_SPRITE_HPP */

