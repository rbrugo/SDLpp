/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : window_free_functions
 * @created     : Sunday Apr 22, 2018 18:28:44 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_WINDOW_FREE_FUNCTIONS_HPP
#define SDLPP_WINDOW_FREE_FUNCTIONS_HPP

#include "window.hpp"
#include <tl/optional.hpp>

namespace SDLpp
{

inline auto get_surface(window const & w)
{
    return w.get_surface();
}

inline auto get_surface(tl::optional<window> const & opt_w)
{
    return opt_w->get_surface();
}


} // namespace SDLpp

#endif /* SDLPP_WINDOW_FREE_FUNCTIONS_HPP */

