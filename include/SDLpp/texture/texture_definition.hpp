/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : texture
 * @created     : Monday Oct 22, 2018 09:47:23 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_TEXTURE_TEXTURE_DEFINITION_HPP
#define SDLPP_TEXTURE_TEXTURE_DEFINITION_HPP

/* #include "texture_node_impl.hpp" */
#include "texture_node_definition.hpp"
/* #include "renderer_impl.hpp" //<--? */

namespace SDLpp
{

class texture
{
private:
    friend class renderer;
    static inline int16_t _unnamed_counter = 0;
    texture_node * _handler;
public:
    texture() noexcept = delete;
    texture(texture const & other) noexcept = default;
    texture(texture      &&      ) noexcept = default;
    texture & operator=(texture const & other) noexcept = default;
    texture & operator=(texture      &&      ) noexcept = default;
    ~texture() = default;
    explicit texture(renderer & renderer, surface const & origin);
    explicit texture(renderer & renderer, std::string const & img_path);

    tl::optional<rect> const & geometry() const;

    auto handler() const noexcept { return  _handler->handler(); }
    explicit operator bool() const { return static_cast<bool>(handler()); }

private:
    static std::string _make_name_for_unnamed();
};

} // namespace SDLpp

#endif /* SDLPP_TEXTURE_TEXTURE_DEFINITION_HPP */

