/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : system_manager
 * @created     : Monday Mar 12, 2018 00:06:00 CET
 * @license     : MIT
 * */

#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <SDL2/SDL.h>
#include <initializer_list>
#include <optional>
#include <numeric>
#include <set>

#include "init_flags.hpp"

namespace SDLpp
{

namespace detail
{

    struct _system_manager_singleton
    {
        explicit _system_manager_singleton(init flag)
        {
            good = (SDL_Init( static_cast<uint32_t>(flag) )== 0);
        }

        _system_manager_singleton(std::initializer_list<init> flags)
        {
            uint32_t flag = std::accumulate(flags.begin(), flags.end(), uint32_t{}, [](auto f, auto g)
                    {
                        return static_cast<uint32_t>(f) + static_cast<uint32_t>(g);
                    });
            good = ( SDL_Init(flag) == 0 );
        }

        _system_manager_singleton() = delete;
        _system_manager_singleton(_system_manager_singleton const &) = delete;
        _system_manager_singleton(_system_manager_singleton &&) = default;
        _system_manager_singleton & operator=(_system_manager_singleton const &) = delete;
        _system_manager_singleton & operator=(_system_manager_singleton &&) = default;
        ~_system_manager_singleton() { SDL_Quit(); }

        bool init_subsystem(init flag)
        {
            good = (SDL_InitSubSystem(static_cast<uint32_t>(flag)) == 0);
            return good;
        }

        bool good = true;
    };

} // namespace detail

class system_manager
{
private:
    std::set<init> _flags_on;
    static inline std::optional<detail::_system_manager_singleton> instance = {};
public:
    system_manager() = default;
    explicit system_manager(init flag);
    system_manager(std::initializer_list<init> flags);
    system_manager(system_manager const &) = delete;
    system_manager(system_manager &&) = default;
    system_manager & operator=(system_manager const &) = delete;
    system_manager & operator=(system_manager &&) = default;
    ~system_manager();

    decltype(auto) init_subsystem(init flag);
    template <class... Init> decltype(auto) init_subsystem(init first, Init&& ...flags);

    explicit operator bool() const { return instance->good; }
    bool good() const { return static_cast<bool>(*this); }
};

system_manager::system_manager(init flag) :
    _flags_on{flag}
{
    if ( ! instance ) {
        instance = detail::_system_manager_singleton{flag};
    }
    else {
        instance->init_subsystem(flag);
    }
}

system_manager::system_manager(std::initializer_list<init> flags) :
    _flags_on{flags}
{
    if ( ! instance ) {
        instance = detail::_system_manager_singleton{flags};
    }
    else {
        instance->init_subsystem( std::accumulate(flags.begin(), flags.end(), *flags.begin(), std::bit_and<init>{} ) );
    }
}

system_manager::~system_manager()
{
    for ( auto flag : _flags_on ) {
        SDL_QuitSubSystem(static_cast<uint32_t>(flag));
    }
}

decltype(auto) system_manager::init_subsystem(init flag)
{
    bool ok = false;

    if ( ! instance ) {
        instance = detail::_system_manager_singleton{flag};
        ok = instance->good;
    }
    else {
        ok = instance->init_subsystem(flag);
    }
    if ( ok ) { _flags_on.insert(flag); }

    return *this;
}

template <class ...Init>
decltype(auto) system_manager::init_subsystem(init first, Init&& ...flags)
{
    static_assert(std::conjunction_v< std::is_same<init, Init> ... >,
            "Arguments passed to init_subsystem have to be SDLpp::init!");
    //auto flag = (static_cast<uint32_t>(first) & ... & static_cast<uint32_t>(flags) );
    auto flag = (first & ... & flags);
    if ( ! instance ) {
        instance = detail::_system_manager_singleton{flag};
    }
    else {
        instance->init_subsystem(flag);
    }
    if ( instance->good ) {
        _flags_on.insert(first);
        if constexpr ( sizeof...(Init) > 0 ) {
            (_flags_on.insert(flags),...);
        }
    }

    return *this;
}

} // namespace SDLpp

#endif /* SYSTEM_MANAGER_HPP */

