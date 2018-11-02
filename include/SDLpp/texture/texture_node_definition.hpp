/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : texture_node
 * @created     : Tuesday Jul 17, 2018 00:45:14 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_TEXTURE_TEXTURE_NODE_DEFINITION_HPP
#define SDLPP_TEXTURE_TEXTURE_NODE_DEFINITION_HPP

#include <SDL2/SDL_render.h>
#include "../surface/surface.hpp"
#include "../surface/load_bmp.hpp"

namespace SDLpp
{
class renderer;

namespace detail
{
    struct texture_deleter
    {
        inline void operator()(SDL_Texture * target) const
        {
            SDL_DestroyTexture(target);
        }
    };
} // namespace detail

class texture_node
{
    using handler_ptr = std::unique_ptr<SDL_Texture, detail::texture_deleter>;
    handler_ptr _handler;
    tl::optional<rect> _geom;

public:
    texture_node() noexcept = default;
    texture_node(texture_node const & other) noexcept = delete;
    texture_node(texture_node      &&      ) noexcept = default;
    texture_node & operator=(texture_node const & other) noexcept = delete;
    texture_node & operator=(texture_node      &&      ) noexcept = default;
    ~texture_node() = default;
    explicit texture_node(renderer const & renderer, surface const & origin);
    explicit texture_node(renderer const & renderer, std::string_view img_path);

    tl::optional<rect> const & geometry() const;

    auto handler() const noexcept { return _handler.get(); }
    explicit operator bool() const { return static_cast<bool>(_handler); }
};
} // namespace SDLpp

#endif /* SDLPP_TEXTURE_TEXTURE_NODE_DEFINITION_HPP */

