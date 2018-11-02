/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : system_manager_singleton
 * @created     : Tuesday Mar 27, 2018 11:50:41 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_DETAIL_SYSTEM_MANAGER_SINGLETON_HPP
#define SDLPP_DETAIL_SYSTEM_MANAGER_SINGLETON_HPP

#include <utility>
#include <tl/optional.hpp>

#include "../meta/uniform_tuple_accumulate.hpp"
#include "../meta/is_sdlpp_flag.hpp"
#include "../meta/type_filter.hpp"
#include "../init_flags.hpp"

namespace SDLpp
{
namespace detail
{

struct _system_manager_singleton
{
    template <typename ...Fs>
    explicit _system_manager_singleton(Fs ...flags) : good{true}
    {
        if constexpr ( sizeof...(Fs) > 0 ) {
            static_assert(
                    (meta::is_sdlpp_flag<Fs> && ...),
                    "_system_manager_singleton::_system_manager_singleton(): neither flag::init nor"
                    "flag::img object passed as argument"
                );
            init(flags...);
        }
    }

    template <typename ...Fs>
    bool init(Fs &&... flags)
    {
        good = true;

        static_assert(
                (meta::is_sdlpp_flag<Fs> && ...),
                "_system_manager_singleton::init(): neither flag::init nor flag::img object passed "
                "as argument"
            );
        static_assert(
                sizeof...(Fs) > 0,
                "_system_manager_singleton::init(): at least one parameter is required"
            );

        auto init_flags = meta::type_filter<flag::init>(flags...);
        auto img_flags  = meta::type_filter<flag::img >(flags...);

        if constexpr ( std::tuple_size_v<decltype(init_flags)> > 0 ) {
            auto accumulated_flag = meta::uniform_tuple_accumulate(
                    init_flags,
                    flag::init{},
                    std::bit_or<flag::init>{}
                );
            good &= SDL_Init( static_cast<uint32_t>(accumulated_flag) ) == 0;
            std::get<0>(_last_result) = accumulated_flag;
        }
        else {
            std::get<0>(_last_result) = flag::init::none;
        }
        if constexpr ( std::tuple_size_v<decltype(img_flags)> > 0 ) {
            auto accumulated_flag = meta::uniform_tuple_accumulate(
                    img_flags,
                    flag::img{},
                    std::bit_or<flag::img>{}
                );
            good &=
                (
                    IMG_Init( static_cast<flag::_sdl_img_flag_t>(accumulated_flag) )
                    & static_cast<flag::_sdl_img_flag_t>(accumulated_flag)
                ) != 0;
            std::get<1>(_last_result) = accumulated_flag;
        }
        else {
            std::get<1>(_last_result) = flag::img::none;
        }

        return good;
    }

    ~_system_manager_singleton()
    {
        SDL_Quit();
    }

    explicit constexpr operator bool() const
    {
        return good;
    }

    auto last_result() const -> tl::optional<std::pair<flag::init, flag::img>>
    {
        return good ? tl::optional{_last_result} : tl::nullopt;
    }

private:
    bool good = true;
    std::pair<flag::init, flag::img> _last_result;
}; // struct _system_manager_singleton

} // namespace detail

} // namespace SDLpp

#endif /* SDLPP_DETAIL_SYSTEM_MANAGER_SINGLETON_HPP */

