/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : is_surface_or_optional
 * @created     : Friday Apr 06, 2018 16:27:15 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_META_IS_SURFACE_OR_OPTIONAL_HPP
#define SDLPP_META_IS_SURFACE_OR_OPTIONAL_HPP

#include <optional>
#include "../surface.hpp"

namespace SDLpp
{
namespace meta
{
    /// \effect This trait_v is true if the type passed as template parameter is `SDLpp::surface` or
    ///     `std::optional<SDLpp::surface>`.
    /// \tparam T type to check.
    /// \returns `true` if `T` is convertible to `SDLpp::surface` or to
    ///     `std::optional<SDLpp::surface>`; `false` otherwise.
    template < class T >
    constexpr inline bool is_surface_or_optional =
        std::is_convertible_v<T, surface> || std::is_convertible_v<T, std::optional<surface>>;

} // namespace meta
} // namespace SDLpp

#endif /* SDLPP_META_IS_SURFACE_OR_OPTIONAL_HPP */

