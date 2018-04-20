/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : window
 * @created     : Tuesday Dec 05, 2017 14:09:33 CET
 * @license     : MIT
 * */

#ifndef SDLPP_WINDOW_HPP
#define SDLPP_WINDOW_HPP

#include <SDL2/SDL.h>

#include <memory>

#include "rectangle.hpp"
#include "surface.hpp"

namespace SDLpp
{

namespace detail
{

/// Function object used to destroy an SDL_Window
struct window_deleter
{
    inline void operator()(SDL_Window * resource)
    {
        SDL_DestroyWindow(resource);
    }
};

} //namespace detail

/// Enum flags to substitute macros
enum class window_flag : uint32_t {
    fullscreen          = SDL_WINDOW_FULLSCREEN,
    fullscreen_desktop  = SDL_WINDOW_FULLSCREEN_DESKTOP,
    opengl              = SDL_WINDOW_OPENGL,
    shown               = SDL_WINDOW_SHOWN,
    hidden              = SDL_WINDOW_HIDDEN,
    borderless          = SDL_WINDOW_BORDERLESS,
    resizable           = SDL_WINDOW_RESIZABLE,
    minimized           = SDL_WINDOW_MINIMIZED,
    maximized           = SDL_WINDOW_MAXIMIZED,
    input_grabbed       = SDL_WINDOW_INPUT_GRABBED,
    allow_highDPI       = SDL_WINDOW_ALLOW_HIGHDPI
};

/* *
 * @brief Allow AND-combinations of window_flags
 * */
inline window_flag operator &(window_flag a, window_flag b)
{
    return static_cast<window_flag>( static_cast<uint32_t>(a) & static_cast<uint32_t>(b) );
}

/* *
 * @brief Allow AND-assignment of window_flags
 * */
inline window_flag & operator &=(window_flag & a, window_flag b)
{
    a = a & b;
    return a;
}

/* *
 * @brief Allow OR-combinations of window_flags
 * */

inline window_flag operator |(window_flag a, window_flag b)
{
    return static_cast<window_flag>( static_cast<uint32_t>(a) | static_cast<uint32_t>(b) );
}

/* *
 * @brief Allow OR-assignment of window_flags
 * */
inline window_flag & operator |=(window_flag & a, window_flag b)
{
    a = a | b;
    return a;
}
} // namespace SDLpp



namespace SDLpp
{
//ctags -R –c++-kinds=+p –fields=+iaS –extra=+q .
/// Secure wrapper implementing the SDL_Window
/// window(window const &) = default
/// window(window &&) = delete
/// window(std::string_view title, rectanlge const & geom, window_flag flags = window_flag::showm)

class window {
    std::unique_ptr<SDL_Window, detail::window_deleter> _handler;

    using surface_type = surface; //SDL_Surface;
    //using surface_ptr  = surface_type *;

public:
    window() = default;
    window(window const &) = delete;
    window(window &&) = default;
    explicit window(SDL_Window * const ptr) : _handler{ptr} { ; }
    window(std::string_view title, rectangle const & geom, window_flag flags = window_flag::shown);
    window(std::string_view title, int pos_x, int pos_y, int width, int height, window_flag flags);

    window & operator=(window const &) = delete;
    window & operator=(window &&) = default;

    ~window() = default;

    auto handler() const { return this->_handler.get(); }

    inline window & create(
            std::string_view title,
            rectangle const & geom,
            window_flag flags = window_flag::shown );
    inline window & create(
            std::string_view title,
            int pos_x, int pos_y, int width, int height,
            window_flag flags = window_flag::shown );

    inline auto get_surface() const -> std::optional<surface>;
        // -> surface_type { return *SDL_GetWindowSurface( this->handler() ); }
    inline auto update_surface() { return SDL_UpdateWindowSurface( this->handler() ); }

    void reset() { _handler.reset(); }

    bool valid() const { return static_cast<bool>( *this ); }
    explicit operator bool() const { return static_cast<bool>( _handler ); }

};

// Implementations...

window::window(std::string_view title, rectangle const & geom, window_flag flags)
    : window{title, geom.x, geom.y, geom.width, geom.height, flags}
{
    ;
}

window::window(std::string_view title, int pos_x, int pos_y, int width, int height, window_flag flags)
    : _handler{SDL_CreateWindow(title.data(), pos_x, pos_y, width, height, static_cast<uint32_t>(flags) )}
{
    ;
}

window & window::create(std::string_view title, rectangle const & geom, window_flag flags)
{
    return this->create(title, geom.x, geom.y, geom.width, geom.height, flags);
}

window & window::create(std::string_view title, int pos_x, int pos_y, int width, int height, window_flag flags)
{
    _handler.reset(
            SDL_CreateWindow(title.data(), pos_x, pos_y, width, height, static_cast<uint32_t>(flags) )
    );

    return *this;
}

inline auto window::get_surface() const -> std::optional<surface>
{
    auto res = SDL_GetWindowSurface( this->handler() );

    if ( res == nullptr ) return std::nullopt;
    return {*res};
}

} // namespace SDLpp

#endif /* SDLPP_WINDOW_HPP */

