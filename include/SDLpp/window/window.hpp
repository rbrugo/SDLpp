/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : window
 * @created     : Tuesday Dec 05, 2017 14:09:33 CET
 * @license     : MIT
 * */

#ifndef SDLPP_WINDOW_WINDOW_HPP
#define SDLPP_WINDOW_WINDOW_HPP

#include <SDL2/SDL.h>

#include <memory>

#include "../rect.hpp"
#include "../surface/surface.hpp"

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

/*enum class window_flag : uint32_t {
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
*/
namespace flag
{

/// Enum flags to substitute macros
using _window_flag_t = std::underlying_type_t<decltype(SDL_WINDOW_FULLSCREEN)>;
enum class window : _window_flag_t {
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
 * @brief Allow AND-combinations of flag::windows
 * */
inline flag::window operator &(flag::window a, flag::window b)
{
    return static_cast<flag::window>( static_cast<_window_flag_t>(a) & static_cast<_window_flag_t>(b) );
}

/* *
 * @brief Allow AND-assignment of flag::windows
 * */
inline flag::window & operator &=(flag::window & a, flag::window b)
{
    a = a & b;
    return a;
}

/* *
 * @brief Allow OR-combinations of flag::windows
 * */
inline flag::window operator |(flag::window a, flag::window b)
{
    return static_cast<flag::window>( static_cast<_window_flag_t>(a) | static_cast<_window_flag_t>(b) );
}

/* *
 * @brief Allow OR-assignment of flag::windows
 * */
inline flag::window & operator |=(flag::window & a, flag::window b)
{
    a = a | b;
    return a;
}

/* *
 * @brief Allow XOR-combinations of flag::windows
 * */
inline flag::window operator ^(flag::window a, flag::window b)
{
    return static_cast<flag::window>( static_cast<_window_flag_t>(a) ^ static_cast<_window_flag_t>(b) );
}

/* *
 * @brief Allow XOR-assignment of flag::windows
 * */
inline flag::window & operator ^=(flag::window & a, flag::window b)
{
    a = a ^ b;
    return a;
}

} // namespace flag

} // namespace SDLpp



namespace SDLpp
{
//ctags -R –c++-kinds=+p –fields=+iaS –extra=+q .
/// Secure wrapper implementing the SDL_Window
/// window(window const &) = default
/// window(window &&) = delete
/// window(std::string_view title, rect const & geom, flag_t flags = flag_t::showm)

class window {
    std::unique_ptr<SDL_Window, detail::window_deleter> _handler;

    using surface_type = surface;

public:
    using flag_t = flag::window;
    window() = default;
    window(window const &) = delete;
    window(window &&) = default;
    explicit window(SDL_Window * const ptr) : _handler{ptr} { ; }
    window(std::string_view title, rect const & geom, flag_t flags = flag_t::shown);
    window(std::string_view title, int pos_x, int pos_y, int width, int height, flag_t flags);

    window & operator=(window const &) = delete;
    window & operator=(window &&) = default;

    ~window() = default;

    auto handler() const { return this->_handler.get(); }

    inline window & create(
            std::string_view title,
            rect const & geom,
            flag_t flags = flag_t::shown );
    inline window & create(
            std::string_view title,
            int pos_x, int pos_y, int width, int height,
            flag_t flags = flag_t::shown );

    inline auto get_surface() const -> tl::optional<surface>;
    inline auto update_surface() { return SDL_UpdateWindowSurface( this->handler() ); }

    void reset() { _handler.reset(); }

    bool valid() const { return static_cast<bool>( *this ); }
    explicit operator bool() const { return static_cast<bool>( _handler ); }

};

// Implementations...

inline window::window(std::string_view title, rect const & geom, flag_t flags)
    : window{title, geom.x, geom.y, geom.w, geom.h, flags}
{
    ;
}

inline window::window(std::string_view title, int pos_x, int pos_y, int width, int height, flag_t flags)
    : _handler{SDL_CreateWindow(title.data(), pos_x, pos_y, width, height, static_cast<uint32_t>(flags) )}
{
    ;
}

window & window::create(std::string_view title, rect const & geom, flag_t flags)
{
    return this->create(title, geom.x, geom.y, geom.w, geom.h, flags);
}

window & window::create(
        std::string_view title,
        int pos_x, int pos_y,
        int width, int height,
        flag_t flags
    )
{
    _handler.reset(
            SDL_CreateWindow(title.data(), pos_x, pos_y, width, height, static_cast<uint32_t>(flags) )
    );

    return *this;
}

inline auto window::get_surface() const -> tl::optional<surface>
{
    auto res = SDL_GetWindowSurface( this->handler() );

    if ( res == nullptr ) {
        return { tl::nullopt };
    }
    return { surface{*res} };
}

} // namespace SDLpp

#endif /* SDLPP_WINDOW_WINDOW_HPP */

