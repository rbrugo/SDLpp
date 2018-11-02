/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : surface
 * @created     : Monday Feb 26, 2018 19:36:25 CET
 * @license     : MIT
 * */

#ifndef SDLPP_SURFACE_SURFACE_HPP
#define SDLPP_SURFACE_SURFACE_HPP

#include <memory>
#include <SDL2/SDL_surface.h>
#include <tl/optional.hpp>
#include "../rect.hpp"
#include "../color.hpp"

#ifndef SDLPP_NO_SDL_IMG
#   include <SDL2/SDL_image.h>
#endif //SDLPP_NO_SDL_IMG

namespace SDLpp
{

namespace detail
{
    ///Function-object used to delete surfaces in std::unique_ptr
    struct surface_deleter
    {
        inline void operator()(SDL_Surface * s)
        {
            //SDL_FreeSurface "knows" whether free the surface
            SDL_FreeSurface(s);
        }
    };
} // namespace detail

///A wrapper around the SDL_Surface
class surface
{
    using color_t = uint32_t;
    std::unique_ptr<SDL_Surface, detail::surface_deleter> _handler;

public:
    surface() = default;
    surface(surface const &) = delete;
    surface(surface &&) noexcept = default;
    explicit surface(SDL_Surface & src);
    surface & operator=(surface const &) = delete;
    surface & operator=(surface &&) noexcept = default;
    surface & operator=(SDL_Surface & src);

    ~surface() = default;

    surface & load_bmp(std::string_view filename) &;
    surface   load_bmp(std::string_view filename) &&;
#ifndef SDLPP_NO_SDL_IMG
    surface & load(std::string_view filename) &;
    surface   load(std::string_view filename) &&;
#endif //SDLPP_NO_SDL_IMG
    /* surface & fill(color_t color, tl::optional<rect const &> rect = {}); */
    surface & fill(color fill_color, tl::optional<rect const &> rect = {});
    auto geometry() const;

    auto pixel_format() const -> tl::optional<SDL_PixelFormat &>;
    surface & convert(tl::optional<SDL_PixelFormat &> const & fmt) &;
    surface   convert(tl::optional<SDL_PixelFormat &> const & fmt) &&;

    decltype(auto) handler() noexcept { return _handler.get(); }
    decltype(auto) handler() const noexcept { return _handler.get(); }
    bool valid() const { return static_cast<bool>(_handler); }

private:
    inline auto _make_surface_ptr( SDL_Surface * s ) const
    {
        return std::unique_ptr<SDL_Surface, detail::surface_deleter>( s );
    }
};

inline surface::surface(SDL_Surface & src) :
    _handler{ _make_surface_ptr( std::addressof(src) ) }
{
    ;
}

inline auto surface::operator=(SDL_Surface & src) -> surface &
{
    _handler = _make_surface_ptr( std::addressof(src) );
    return *this;
}

inline auto surface::load_bmp( std::string_view filename ) & -> surface &
{
    _handler.reset(SDL_LoadBMP(filename.data()));
    return *this;
}

inline auto surface::load_bmp( std::string_view filename ) && -> surface
{
    return std::move(this->load_bmp(filename));
}

#ifndef SDLPP_NO_SDL_IMG
inline auto surface::load(std::string_view filename) & -> surface &
{
    _handler.reset(IMG_Load(filename.data()));
    return *this;
}

inline auto surface::load(std::string_view filename) && -> surface
{
    return std::move(this->load(filename));
}
#endif //SDLPP_NO_SDL_IMG

/* inline auto surface::fill(color_t color, tl::optional<rect const &> rect) */
inline auto surface::fill(color fill_color, tl::optional<rect const &> rect)
    -> surface &
{
    if ( rect.has_value() ) {
        SDL_FillRect( handler(), std::addressof(*rect), static_cast<uint32_t>(fill_color));
    }
    else {
        //SDL_FillRect should not own the pointer
        SDL_FillRect( handler(), nullptr, static_cast<uint32_t>(fill_color) );
    }

    return *this;
}

inline auto surface::geometry() const
{
    return static_cast<rect>( handler()->clip_rect );
}

inline auto surface::pixel_format() const -> tl::optional<SDL_PixelFormat &> //SDL_PixelFormat *
{
    if ( ! _handler ) {
        return { tl::nullopt };
    }

    return { *(_handler->format) };
}

/* inline auto surface::convert(SDL_PixelFormat const & fmt) -> surface & */
inline auto surface::convert(tl::optional<SDL_PixelFormat &> const & fmt) & -> surface &
{
    if ( ! _handler ) { return *this; }
    /* auto res = SDL_ConvertSurface(_handler.get(), std::addressof(fmt), 0); */
    auto res = SDL_ConvertSurface(_handler.get(), std::addressof(*fmt), 0);
    if ( res != nullptr ) {
        _handler.reset(res);
    }
    return *this;
}

inline auto surface::convert(tl::optional<SDL_PixelFormat &> const & fmt) && -> surface
{
    /* return this->convert(fmt); */
    auto && tmp = std::move(*this);
    tmp.convert(fmt);
    return std::move(tmp);
}

} // namespace SDLpp

#endif /* SDLPP_SURFACE_SURFACE_HPP */
