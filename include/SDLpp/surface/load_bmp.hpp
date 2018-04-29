/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : load_bmp
 * @created     : Tuesday Feb 27, 2018 21:53:23 CET
 * @license     : MIT
 * */

#ifndef SDLPP_LOAD_BMP_HPP
#define SDLPP_LOAD_BMP_HPP

#include <string_view>
#include <tl/optional.hpp>

#include "surface.hpp"

namespace SDLpp
{

inline tl::optional<surface> load_bmp(std::string_view filename)
{
    surface res;
    res.load_bmp(filename);

    if (res.valid()) {
        return tl::optional{std::move(res)};
    }
    return tl::nullopt;
}

} // namespace SDLpp

#endif /* SDLPP_LOAD_BMP_HPP */

