/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : meta
 * @created     : Tuesday Mar 27, 2018 11:53:11 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_META_IS_SDLPP_FLAG_HPP
#define SDLPP_META_IS_SDLPP_FLAG_HPP

#include <type_traits>

#include "../init_flags.hpp"
#include "../img_flags.hpp"

namespace SDLpp
{

namespace meta
{
    template <class T>
    constexpr bool is_sdlpp_flag = 
        std::is_same_v<std::decay_t<T>,flag::init> ||
        std::is_same_v<std::decay_t<T>,flag::img>;
} // namespace meta

} // namespace SDLpp

#endif /* SDLPP_META_IS_SDLPP_FLAG_HPP */

