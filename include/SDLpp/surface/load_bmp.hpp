/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : load_bmp
 * @created     : Tuesday Feb 27, 2018 21:53:23 CET
 * @license     : MIT
 * */

#ifndef SDLPP_SURFACE_LOAD_BMP_HPP
#define SDLPP_SURFACE_LOAD_BMP_HPP

#include <string_view>
#include <tl/optional.hpp>
#ifndef SDLPP_NO_SDL_IMG
#   include <SDL2/SDL_image.h>
#endif //SDLPP_NO_SDL_IMG

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

#ifndef SDLPP_NO_SDL_IMG
inline tl::optional<surface> load(std::string_view filename)
{
    surface res;
    res.load(filename);
    if (res.valid()) {
        return tl::optional{std::move(res)};
    }
    return tl::nullopt;
}
#else
inline tl::optional<surface> load(std::string_view filename)
{
    return load_bmp(filename);
}
#endif //SDLPP_NO_SDL_IMG

} // namespace SDLpp

#endif /* SDLPP_SURFACE_LOAD_BMP_HPP */

