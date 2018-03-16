/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : load_bmp
 * @created     : Tuesday Feb 27, 2018 21:53:23 CET
 * @license     : MIT
 * */

#ifndef LOAD_BMP_HPP
#define LOAD_BMP_HPP

#include <string_view>
#include <optional>

#include "surface.hpp"

namespace SDLpp
{

std::optional<surface> load_bmp(std::string_view filename)
{
    surface res;
    res.load_bmp(filename);

    if (res.valid()) return std::optional{std::move(res)};
    return std::nullopt;
}

} // namespace SDLpp

#endif /* LOAD_BMP_HPP */

