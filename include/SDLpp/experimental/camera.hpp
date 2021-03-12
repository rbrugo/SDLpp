/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : camera
 * @created     : Monday Oct 29, 2018 12:29:38 CET
 * @license     : MIT
 * */

#ifndef SDLPP_EXPERIMENTAL_CAMERA_HPP
#define SDLPP_EXPERIMENTAL_CAMERA_HPP

#include <variant>
#include <experimental/memory>

#include "../rect.hpp"
#include "../texture.hpp"
#include "../math/a"

namespace SDLpp
{
//FWD class entity
struct entity { };
auto position(entity const &) -> rect const &;

namespace experimental
{

namespace detail
{
struct _camera_storage
{
    template <typename T> using obs_ptr = std::experimental::observer_ptr<T>;

    texture _texture;
    union {
        rect _position{0, 0};
        obs_ptr<entity const> _tracked_entity;
    };
    bool _tracking{false};

    inline void set_position(rect const & position) noexcept {
        _position = position;
        _tracking = false;
    }
    inline void set_tracked_entity(entity const & subj) noexcept {
        _tracked_entity = obs_ptr<entity const>{std::addressof(subj)};
        _tracking = true;
    }
    inline rect position() const noexcept
    {
        if (_tracking) {
            return _position;
        }
        return SDLpp::position(*_tracked_entity); //TODO: mettere apposto
    }
};

} // namespace detail

class camera
{
private:
    detail::_camera_storage _storage;

public:
    camera & move() noexcept;
    camera const & move() const noexcept;

    camera & track(entity const &) noexcept;
    camera & set_position(math::point2d

};

} // namespace experimental
} // namespace SDLpp

#endif /* SDLPP_EXPERIMENTAL_CAMERA_HPP */

