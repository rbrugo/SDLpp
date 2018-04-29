/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : is_surface_or_optional
 * @created     : Friday Apr 06, 2018 16:27:15 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_META_IS_SURFACE_OR_OPTIONAL_HPP
#define SDLPP_META_IS_SURFACE_OR_OPTIONAL_HPP

#include "../surface.hpp"
#include <tl/optional.hpp>

//#if (__cplusplus >= 201703)
//#if __has_include(<optional>)
//#   include <optional>
//#   define STD_OPTIONAL std::optional
//#elif __has_include(<experimental/optional>)
//#   include <experimental/optional>
//#   define STD_OPTIONAL std::experimental::optional
//#endif //__has_include
//#endif //__cplusplus

namespace SDLpp
{
namespace meta
{
    /// \effect This trait_v is true if the type passed as template parameter is `SDLpp::surface` or
    ///     `tl::optional<SDLpp::surface>`.
    /// \tparam T type to check.
    /// \returns `true` if `T` is convertible to `SDLpp::surface` or to
    ///     `std/tl::optional<SDLpp::surface>`; `false` otherwise.
    template < class T >
    constexpr inline bool is_surface_or_optional =
        std::is_convertible_v<T, surface> || std::is_convertible_v<T, tl::optional<surface>>
//#ifdef STD_OPTIONAL
        //|| std::is_convertible_v<T, STD_OPTIONAL<surface>>
//#endif
        ;
    //TODO: tl::optional<T> o tl::optional<T &>?

} // namespace meta
} // namespace SDLpp

#endif /* SDLPP_META_IS_SURFACE_OR_OPTIONAL_HPP */

