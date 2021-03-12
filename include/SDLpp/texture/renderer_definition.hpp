/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : renderer
 * @created     : Saturday May 19, 2018 14:27:52 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_TEXTURE_RENDERER_DEFINITION_HPP
#define SDLPP_TEXTURE_RENDERER_DEFINITION_HPP

#include <SDL2/SDL_render.h>
#include <tl/optional.hpp>
#include <memory>
#include <map>

#include "../window/window.hpp"

namespace SDLpp
{

namespace detail{
struct renderer_destroyer
{
    void operator()(SDL_Renderer * r) { SDL_DestroyRenderer(r); }
}; // struct renderer_destroyer
} // namespace detail

namespace flag
{
    using _renderer_flag_t = std::underlying_type_t<decltype(SDL_RENDERER_SOFTWARE)>;
    enum class renderer : _renderer_flag_t {
        none           = 0,
        software       = SDL_RENDERER_SOFTWARE,
        accelerated    = SDL_RENDERER_ACCELERATED,
        present_vsync  = SDL_RENDERER_PRESENTVSYNC,
        target_texture = SDL_RENDERER_TARGETTEXTURE
    };

    using _renderer_blend_mode_t = std::underlying_type_t<decltype(SDL_BLENDMODE_NONE)>;
    enum class blend_mode : _renderer_blend_mode_t {
        none  = SDL_BLENDMODE_NONE,
        blend = SDL_BLENDMODE_BLEND,
        add   = SDL_BLENDMODE_ADD,
        mod   = SDL_BLENDMODE_MOD
    };

    inline flag::renderer operator &(flag::renderer a, flag::renderer b)
    {
        return static_cast<flag::renderer>(
                static_cast<_renderer_flag_t>(a) & static_cast<_renderer_flag_t>(b)
            );
    }

    inline flag::renderer & operator &=(flag::renderer & a, flag::renderer b)
    {
        a = a & b;
        return a;
    }

    inline flag::renderer operator |(flag::renderer a, flag::renderer b)
    {
        return static_cast<flag::renderer>(
                static_cast<_renderer_flag_t>(a) | static_cast<_renderer_flag_t>(b)
            );
    }

    inline flag::renderer & operator |=(flag::renderer & a, flag::renderer b)
    {
        a = a | b;
        return a;
    }

    inline flag::renderer operator ^(flag::renderer a, flag::renderer b)
    {
        return static_cast<flag::renderer>(
                static_cast<_renderer_flag_t>(a) ^ static_cast<_renderer_flag_t>(b)
            );
    }

    inline flag::renderer & operator ^=(flag::renderer & a, flag::renderer b)
    {
        a = a ^ b;
        return a;
    }
} // namespace flag

class texture_node;
class texture;

///A wrapper around the SDL_Renderer
class renderer {
    friend class texture;
    std::unique_ptr<SDL_Renderer, detail::renderer_destroyer> _handler;
    std::map<std::string, texture_node> _loaded_textures;

public:
    using flag_t = flag::renderer;
    explicit renderer(window const & w, int index = -1, flag_t flag = flag_t::none) noexcept;
    explicit renderer(window const & w, flag_t flag) noexcept;

    renderer() = delete;
    renderer(renderer const &) = delete;
    renderer(renderer && other) noexcept = default;
    renderer & operator=(renderer const &) = delete;
    renderer & operator=(renderer && other) noexcept = default;
    ~renderer() = default;

    rect size() const noexcept;

    renderer & blend_mode(flag::blend_mode const mode) noexcept;

    renderer & set_draw_color(color draw_color);
    renderer & set_draw_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) noexcept;

    renderer & clear() noexcept; //Clear the screen
    //Copy the texture on the surface
    renderer & copy(texture_node const & t, tl::optional<rect const &> src = {}, tl::optional<rect const &> dst = {});
    renderer & copy(texture const & t, tl::optional<rect const &> src = {}, tl::optional<rect const &> dst = {});

    renderer & present();
    SDL_Renderer * handler() const noexcept;
    explicit operator bool() const noexcept;

private:
    /* texture_node & _load_texture(std::string && name, texture_node && node); */
    texture_node & _get_or_load(std::string && name, texture_node && node);
    texture_node & _get_or_load(std::string && name, surface const & origin);
    texture_node & _get_or_load(std::string const & filename);
}; // class renderer

} // namespace SDLpp


#endif /* SDLPP_TEXTURE_RENDERER_DEFINITION_HPP */

