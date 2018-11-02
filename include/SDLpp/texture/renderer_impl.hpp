/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : renderer_impl
 * @created     : Monday Oct 22, 2018 10:19:07 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_TEXTURE_RENDERER_IMPL_HPP
#define SDLPP_TEXTURE_RENDERER_IMPL_HPP

#include "renderer_definition.hpp"
#include "texture_node_definition.hpp"
#include "texture_definition.hpp"

namespace SDLpp
{
inline renderer::renderer(window const & w, int index, flag_t flag) noexcept :
    _handler{ SDL_CreateRenderer( w.handler(), index, static_cast<flag::_renderer_flag_t>(flag) ) }
{
    ;
}

inline renderer::renderer(window const & w, flag_t flag) noexcept
    : renderer{w, -1, flag}
{
    ;
}

inline renderer & renderer::set_draw_color(color draw_color)
{
    return set_draw_color(draw_color.r, draw_color.g, draw_color.b, draw_color.a);
}

inline renderer & renderer::set_draw_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    SDL_SetRenderDrawColor(_handler.get(), red, green, blue, alpha);
    return *this;
}

inline renderer & renderer::clear()
{
    SDL_RenderClear( handler() );
    return *this;
}

inline renderer & renderer::copy(texture_node const & t, tl::optional<rect const &> src, tl::optional<rect const &> dst)
{
    auto address_of = [](auto const & opt) -> SDL_Rect const *{
        if ( opt ){
            return std::addressof(*opt);
        }
        return nullptr;
    };
    [[maybe_unused]] auto res = SDL_RenderCopy( handler(), t.handler(), address_of(src), address_of(dst) );
    /* if (res != 0) { */
        /* std::cerr << std::string(60, '#') << "\nERROR: " << SDL_GetError() << "\n" << std::string(60, '#') << "\n"; */
        /* std::cerr << "Texture is valid:  " << !!t.handler() << "\n" */
                  /* << "Renderer is valid: " << !!handler() << "\n"; */
        /* int w, h; */
        /* auto res2 = SDL_QueryTexture(t.handler(), nullptr, nullptr, &w, &h); */
        /* if (res2 != 0) { */
            /* std::cerr << "Invalid texture: " << SDL_GetError() << "\n"; */
        /* } */
        /* std::cerr << "SDL_QueryTexture: " << res2 << "\n" */
                  /* << "w, h:             " << w << ", " << h << "\n"; */
    /* } */
    return *this;
}

inline renderer & renderer::copy(texture const & t, tl::optional<rect const &> src, tl::optional<rect const &> dst)
{
    auto const & handler = *t._handler;
    return copy(handler, src, dst);
}

inline renderer & renderer::present()
{
    SDL_RenderPresent( handler() );
    return *this;
}

inline SDL_Renderer * renderer::handler() const noexcept
{
    return _handler.get();
}

inline renderer::operator bool() const noexcept
{
    return static_cast<bool>(_handler);
}


/* inline texture_node & renderer::_load_texture(std::string && name, texture_node && node) */
/* { */
/*     auto [iter, success] = _loaded_textures.try_emplace(std::move(name), std::move(node)); */
/*     return iter->second; */
/* } */

inline texture_node & renderer::_get_or_load(std::string && name, texture_node && node)
{
    auto [iter, success] = _loaded_textures.try_emplace(std::move(name), std::move(node));
    return iter->second;
}

inline texture_node & renderer::_get_or_load(std::string && name, surface const & origin)
{
    auto [iter, success] = _loaded_textures.try_emplace(std::move(name), *this, origin);
    return iter->second;
}

inline texture_node & renderer::_get_or_load(std::string const & filename)
{
    auto [iter, success] = _loaded_textures.try_emplace(filename, *this, filename);
    return iter->second;
}

} // namespace SDLpp

#endif /* SDLPP_TEXTURE_RENDERER_IMPL_HPP */

