/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : blit_surface
 * @created     : Tuesday Feb 27, 2018 21:40:29 CET
 * @license     : MIT
 * */

#ifndef SDLPP_SURFACE_BLIT_SURFACE_HPP
#define SDLPP_SURFACE_BLIT_SURFACE_HPP

#include <memory>
#include <tl/optional.hpp>
#include "../rect.hpp"
#include "surface.hpp"
#include "../meta/is_surface_or_optional.hpp"

namespace SDLpp
{

namespace detail
{
    /// \exclude
    /// \group _get_surface
    /// \effects get a `SDLpp::surface` from another one, or from a `tl::optional<SDLpp::surface>`.
    /// \returns The `surface` extracted.
    constexpr auto       & _get_surface(surface       & s) noexcept { return s; } /// \group _get_surface
    constexpr auto const & _get_surface(surface const & s) noexcept { return s; } /// \group _get_surface
    constexpr auto       & _get_surface(tl::optional<surface>       & s) { return s.value(); } /// \group _get_surface
    constexpr auto const & _get_surface(tl::optional<surface> const & s) { return s.value(); } /// \group _get_surface

    inline auto blit_surface_impl(surface const & src, tl::optional<rect> src_rect,
                                  surface       & dst, tl::optional<rect> dst_rect)
    {
        auto first = src_rect ? std::addressof(src_rect.value()) : nullptr;
        auto secnd = dst_rect ? std::addressof(dst_rect.value()) : nullptr;

        return SDL_BlitSurface( src.handler(), first, dst.handler(), secnd );
    }
} // namespace detail


//Version with surfaces and sizes
/// \group blit_surface
/// \requires `T` and `U` must be convertible to `SDLpp::surface` or `tl::optional<SDLpp::surface>`
/// \tparam T Type of the source
/// \tparam U Type of the destination surface
/// \param src the source `surface`
/// \param src_rect the source's geometry
/// \param dst the destination `surface`
/// \param dst_rect the destination's geometry
/// \effects blits the source surface onto the destination surface without scaling.
/// \returns `0` if successful, otherwise another number.
template <typename T, typename U, typename = std::enable_if
    <
        meta::is_surface_or_optional<T> && meta::is_surface_or_optional<U>
    >
>
inline auto blit_surface(T const & src, tl::optional<rect> const & src_rect,
                         U       & dst, tl::optional<rect> const & dst_rect )
{
    return detail::blit_surface_impl(
            detail::_get_surface(src), src_rect,
            detail::_get_surface(dst), dst_rect
        );
}

//Version with only surfaces
/// \group blit_surface
/// \requires `T` and `U` must be convertible to `SDLpp::surface` or `tl::optional<SDLpp::surface>`
/// \tparam T Type of the source
/// \tparam U Type of the destination surface
/// \param src the source `surface`
/// \param src_rect the source's geometry
/// \effects blits the source surface onto the destination surface without scaling.
/// \returns `0` if successful, otherwise another number.
template
<
    typename T /*= tl::optional<surface>*/,
    typename U /*= tl::optional<surface>*/,
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
    inline auto blit_scaled_impl(surface const & src, tl::optional<rect> const & src_rect,
                                 surface       & dst, tl::optional<rect> const & dst_rect)
    {
        std::unique_ptr<SDL_Rect> first = nullptr;
        std::unique_ptr<SDL_Rect> secnd = nullptr;

        if ( src_rect ) { first = std::make_unique<SDL_Rect>( *src_rect ); }
        if ( dst_rect ) { secnd = std::make_unique<SDL_Rect>( *dst_rect ); }

        return SDL_BlitScaled( src.handler(), first.get(), dst.handler(), secnd.get() );
    }
} // namespace detail

//Version with surfaces and sizes
/// \group blit_scaled
/// \requires `T` and `U` must be convertible to `SDLpp::surface` or `tl::optional<SDLpp::surface>`
/// \tparam T Type of the source
/// \tparam U Type of the destination surface
/// \param src the source `surface`
/// \param src_rect the source's geometry
/// \param dst the destination `surface`
/// \param dst_rect the destination's geometry
/// \effects blits the source surface onto the destination surface scaling to fit in.
/// \returns `0` if successful, otherwise another number.
template < class T, class U, typename =
    std::enable_if< meta::is_surface_or_optional<T> && meta::is_surface_or_optional<U> >
>
inline auto blit_scaled(T const & src, tl::optional<rect> const & src_rect,
                        U       & dst, tl::optional<rect> const & dst_rect )
{
    return detail::blit_scaled_impl(
            detail::_get_surface(src), src_rect,
            detail::_get_surface(dst), dst_rect
        );
}

//Version with surfaces and sizes
/// \group blit_surface
/// \requires `T` and `U` must be convertible to `SDLpp::surface` or `tl::optional<SDLpp::surface>`
/// \tparam T Type of the source
/// \tparam U Type of the destination surface
/// \param src the source `surface`
/// \param src_rect the source's geometry
/// \effects blits the source surface onto the destination surface scaling to fit in.
/// \returns `0` if successful, otherwise another number.
template < class T, class U, typename =
    std::enable_if< meta::is_surface_or_optional<T> && meta::is_surface_or_optional<U> >
>
inline auto blit_scaled(T const & src, U & dst)
{
    return detail::blit_scaled_impl(detail::_get_surface(src), {}, detail::_get_surface(dst), {});
}



} // namespace SDLpp

#endif /* SDLPP_SURFACE_BLIT_SURFACE_HPP */

