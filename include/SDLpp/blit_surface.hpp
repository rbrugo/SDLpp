/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : blit_surface
 * @created     : Tuesday Feb 27, 2018 21:40:29 CET
 * @license     : MIT
 * */

#ifndef SDLPP_BLIT_SURFACE_HPP
#define SDLPP_BLIT_SURFACE_HPP

#include <memory>
#include <optional>
#include "rectangle.hpp"
#include "surface.hpp"
#include "meta/is_surface_or_optional.hpp"

namespace SDLpp
{

//namespace meta
//{
    //template < class T >
    //constexpr inline bool is_surface_or_optional =
        //std::is_convertible_v<T, surface> || std::is_convertible_v<T, std::optional<surface>>;
//} // namespace meta

namespace detail
{
    /// \exclude
    /// \group _get_surface
    /// \effects get a `SDLpp::surface` from another one, or from a `std::optional<SDLpp::surface>`.
    /// \returns The `surface` extracted.
    constexpr auto       & _get_surface(surface       & s) noexcept { return s; } /// \group _get_surface
    constexpr auto const & _get_surface(surface const & s) noexcept { return s; } /// \group _get_surface
    constexpr auto       & _get_surface(std::optional<surface>       & s) { return s.value(); } /// \group _get_surface
    constexpr auto const & _get_surface(std::optional<surface> const & s) { return s.value(); } /// \group _get_surface

    inline auto blit_surface_impl(surface const & src, std::optional<rectangle> src_rect,
                             surface       & dst, std::optional<rectangle> dst_rect)
    {
        std::unique_ptr<SDL_Rect> first = nullptr;
        std::unique_ptr<SDL_Rect> secnd = nullptr;

        if ( src_rect ) { first = std::make_unique<SDL_Rect>( *src_rect ); }
        if ( dst_rect ) { secnd = std::make_unique<SDL_Rect>( *dst_rect ); }

        return SDL_BlitSurface( src.handler(), first.get(), dst.handler(), secnd.get() );
    }
} // namespace detail


//Version with surfaces and sizes
/// \group blit_surface
/// \requires `T` and `U` must be convertible to `SDLpp::surface` or `std::optional<SDLpp::surface>`
/// \tparam T Type of the source
/// \tparam U Type of the destinstion surface
/// \param src the source `surface`
/// \param src_rect the source's geometry
/// \param dst the destination `surface`
/// \param dst_rect the destination's geometry
/// \effects blits the source surface onto the destination surface without scaling.
/// \returns `0` if successful, otherwise another number.
template <typename T, typename U, typename = std::enable_if
    <
        //( std::is_convertible_v<T, surface> || std::is_convertible_v<T, std::optional<surface>> ) &&
        //( std::is_convertible_v<U, surface> || std::is_convertible_v<U, std::optional<surface>> )
        meta::is_surface_or_optional<T> && meta::is_surface_or_optional<U>
    >
>
inline auto blit_surface(T const & src, std::optional<rectangle> const & src_rect,
                         U       & dst, std::optional<rectangle> const & dst_rect )
{
    return detail::blit_surface_impl(
            detail::_get_surface(src), src_rect,
            detail::_get_surface(dst), dst_rect
        );
}

//Version with only surfaces
/// \group blit_surface
/// \requires `T` and `U` must be convertible to `SDLpp::surface` or `std::optional<SDLpp::surface>`
/// \tparam T Type of the source
/// \tparam U Type of the destinstion surface
/// \param src the source `surface`
/// \param src_rect the source's geometry
/// \effects blits the source surface onto the destination surface without scaling.
/// \returns `0` if successful, otherwise another number.
template
<
    typename T = std::optional<surface>,
    typename U = std::optional<surface>,
    typename = std::enable_if< meta::is_surface_or_optional<T> && meta::is_surface_or_optional<U> >
>
inline auto blit_surface(T const & src, U & dst )
{
    return detail::blit_surface_impl(
            detail::_get_surface(src), {},
            detail::_get_surface(dst), {}
        );
}


namespace detail
{
    inline auto blit_scaled_impl(surface const & src, std::optional<rectangle> const & src_rect,
                                 surface       & dst, std::optional<rectangle> const & dst_rect)
    {
        std::unique_ptr<SDL_Rect> first = nullptr;
        std::unique_ptr<SDL_Rect> secnd = nullptr;

        if ( src_rect ) { first = std::make_unique<SDL_Rect>( *src_rect ); }
        if ( dst_rect ) { secnd = std::make_unique<SDL_Rect>( *dst_rect ); }

        return SDL_BlitScaled( src.handler(), first.get(), dst.handler(), secnd.get() );
    }
} // namespace detail

template < class T, class U, typename =
    std::enable_if< meta::is_surface_or_optional<T> && meta::is_surface_or_optional<U> >
>
inline auto blit_scaled(T const & src, std::optional<rectangle> const & src_rect,
                        U       & dst, std::optional<rectangle> const & dst_rect )
{
    return detail::blit_scaled_impl(detail::_get_surface(src), src_rect, detail::_get_surface(dst), dst_rect);
}

template < class T, class U, typename =
    std::enable_if< meta::is_surface_or_optional<T> && meta::is_surface_or_optional<U> >
>
inline auto blit_scaled(T const & src, U & dst)
{
    return detail::blit_scaled_impl(detail::_get_surface(src), {}, detail::_get_surface(dst), {});
}



} // namespace SDLpp

#endif /* SDLPP_BLIT_SURFACE_HPP */

