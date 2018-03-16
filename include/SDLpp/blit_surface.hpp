/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : blit_surface
 * @created     : Tuesday Feb 27, 2018 21:40:29 CET
 * @license     : MIT
 * */

#ifndef BLIT_SURFACE_HPP
#define BLIT_SURFACE_HPP

#include <memory>
#include <optional>
#include "rectangle.hpp"
#include "surface.hpp"

namespace SDLpp
{

namespace detail
{
    inline auto       & _get_surface(surface       & s) { return s; }
    inline auto const & _get_surface(surface const & s) { return s; }
    inline auto       & _get_surface(std::optional<surface>       & s) { return s.value(); }
    inline auto const & _get_surface(std::optional<surface> const & s) { return s.value(); }
} // namespace detail

auto blit_surface(surface const & src, std::optional<rectangle> src_rect,
                  surface       & dst, std::optional<rectangle> dst_rect)
{
    std::unique_ptr<SDL_Rect> first = nullptr;
    std::unique_ptr<SDL_Rect> secnd = nullptr;

    if ( src_rect ) { first = std::make_unique<SDL_Rect>( *src_rect ); }
    if ( dst_rect ) { secnd = std::make_unique<SDL_Rect>( *dst_rect ); }

    return SDL_BlitSurface( src.handler(), first.get(), dst.handler(), secnd.get() );
}

inline auto blit_surface(surface const & src, surface & dst)
{
    return blit_surface(src, {}, dst, {});
}

template <typename T, typename U, typename = std::enable_if
    <
        ( std::is_convertible_v<T, surface> || std::is_convertible_v<T, std::optional<surface>> ) &&
        ( std::is_convertible_v<U, surface> || std::is_convertible_v<U, std::optional<surface>> )
    >
>
inline auto blit_surface(T const & src, std::optional<rectangle> src_rect,
                         T       & dst, std::optional<rectangle> dst_rect )
{
    blit_surface(detail::_get_surface(src), src_rect, detail::_get_surface(dst), dst_rect);
}

template <typename T, typename U, typename = std::enable_if
    <
        ( std::is_convertible_v<T, surface> || std::is_convertible_v<T, std::optional<surface>> ) &&
        ( std::is_convertible_v<U, surface> || std::is_convertible_v<U, std::optional<surface>> )
    >
>
inline auto blit_surface(T const & src, U & dst )
{
    return blit_surface(detail::_get_surface(src), {}, detail::_get_surface(dst), {});
}




} // namespace SDLpp

#endif /* BLIT_SURFACE_HPP */

