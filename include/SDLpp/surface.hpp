/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : surface
 * @created     : Monday Feb 26, 2018 19:36:25 CET
 * @license     : MIT
 * */

#ifndef surface_HPP
#define surface_HPP

//#include "surface.hpp"
//#include "owning_surface.hpp"
//#include "generic_surface.hpp"

#include <memory>
#include <SDL2/SDL.h>
#include <optional>
#include "rectangle.hpp"

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
    surface(surface const &) = default;
    surface(surface &&) = default;
    surface(SDL_Surface &);
    surface & operator=(surface const &) = default;
    surface & operator=(surface &&) = default;
    surface & operator=(SDL_Surface &);

    surface & load_bmp(std::string_view filename);

    surface & fill(color_t color, std::optional<std::reference_wrapper<rectangle const>> rect = {});

    decltype(auto) handler() const { return _handler.get(); }
    bool valid() const { return static_cast<bool>(_handler); }

private:
    inline auto _make_surface_ptr( SDL_Surface * s ) const
    {
        return std::unique_ptr<SDL_Surface, detail::surface_deleter>( s );
    }
};

surface::surface(SDL_Surface & s) :
    _handler{ _make_surface_ptr( std::addressof(s) ) }
{
    ;
}

auto surface::operator=(SDL_Surface & s) -> surface &
{
    _handler = _make_surface_ptr( std::addressof(s) );
    return *this;
}

auto surface::load_bmp( std::string_view filename ) -> surface &
{
    _handler.reset(SDL_LoadBMP(filename.data()));
    return *this;
}

auto surface::fill(color_t color, std::optional<std::reference_wrapper<rectangle const>> rect)
    -> surface &
{
    if ( rect.has_value() ) {
        auto temp = static_cast<SDL_Rect>(rect->get());
        SDL_FillRect( handler(), std::addressof(temp), color);
    }
    else SDL_FillRect( handler(), nullptr, color ); //SDL_FillRect should not own the pointer

    return *this;
}

} // namespace SDLpp

#endif /* surface_HPP */
