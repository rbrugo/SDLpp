/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : texture_node_impl
 * @created     : Monday Oct 22, 2018 10:21:11 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_TEXTURE_TEXTURE_NODE_IMPL_HPP
#define SDLPP_TEXTURE_TEXTURE_NODE_IMPL_HPP

#include "texture_node_definition.hpp"
#include "renderer_definition.hpp"

namespace SDLpp
{
inline texture_node::texture_node(renderer const & renderer, surface const & origin) :
    _handler{SDL_CreateTextureFromSurface(renderer.handler(), origin.handler())},//, detail::texture_node_deleter{}},
    _geom{origin.geometry()}
{
    ;
}

inline texture_node::texture_node(renderer const & renderer, std::string_view img_path)
{
    {
        auto surface = load(img_path);
        if (surface) {
            _handler.reset(SDL_CreateTextureFromSurface(renderer.handler(), surface->handler()));
            _geom = surface->geometry();
        }
        else {
            _handler.reset();
            _geom.reset();
        }
    }
}

inline auto texture_node::geometry() const -> tl::optional<rect> const &
{
    return _geom;
}

} // namespace SDLpp
#endif /* SDLPP_TEXTURE_TEXTURE_NODE_IMPL_HPP */

