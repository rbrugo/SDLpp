/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : texture
 * @created     : Monday Oct 22, 2018 09:47:23 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_TEXTURE_TEXTURE_IMPL_HPP
#define SDLPP_TEXTURE_TEXTURE_IMPL_HPP

/* #include "texture_node_impl.hpp" */
/* #include "texture_node_definition.hpp" */
/* #include "renderer_impl.hpp" //<--? */
#include "texture_definition.hpp"
#include "renderer_definition.hpp"

namespace SDLpp
{
inline texture::texture(renderer & renderer, surface const & origin) :
    _handler{std::addressof(renderer._get_or_load(_make_name_for_unnamed(), origin))}
{
    ;
}

inline texture::texture(renderer & renderer, std::string const & img_path) :
    _handler{std::addressof(renderer._get_or_load(img_path))}
{
    ;
}

inline tl::optional<rect> const & texture::geometry() const
{
    return _handler->geometry();
}

inline std::string texture::_make_name_for_unnamed()
{
    auto name = std::string{"___Unn@meD_"}.append(std::to_string(_unnamed_counter++)).append("__");
    return name;
}

} // namespace SDLpp

#endif /* SDLPP_TEXTURE_TEXTURE_IMPL_HPP */

