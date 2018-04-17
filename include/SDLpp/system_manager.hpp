/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : system_manager_test
 * @created     : Saturday Mar 31, 2018 23:14:44 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_SYSTEM_MANAGER_HPP
#define SDLPP_SYSTEM_MANAGER_HPP

#include <vector>
#include <optional>
#include "detail/system_manager_singleton.hpp"
#include "init_flags.hpp"

#include <SDL2/SDL.h>

namespace SDLpp
{

class system_manager
{
private:
    std::vector<flag::init> _init_on;
    //std::vector<flag::img > _img_on; //useless: cannot uninitialize single imgs with flags
    static inline std::optional<detail::_system_manager_singleton> _instance = {};

private:
    template <typename ...Fs> constexpr inline decltype(auto) _just_init(Fs &&... flags) noexcept;

public:
    //system_manager() = default;
    template <typename ...Fs> explicit system_manager(Fs &&...flags) noexcept;
    ~system_manager() noexcept;

    template <typename ...Fs> constexpr inline decltype(auto) init(Fs &&... flags) noexcept;
    template <typename ...Fs> constexpr inline decltype(auto) init_subsystem(Fs &&... flags) noexcept;
    template <typename ...Fs> constexpr inline decltype(auto) init_permanent(Fs &&... flags) noexcept;

    explicit constexpr operator bool() const;
    constexpr bool good() const;
};

/// Constructor.
/// \requires If at least an object of type flag::{init,img} is passed as argument, SDL or IMG
///     will be initialized with that flag.
/// \param flags One or more arguments of tipe flag::{init,img}.
template <typename ...Fs>
system_manager::system_manager(Fs &&... flags) noexcept
{
    if constexpr ( sizeof...(Fs) > 0 ) {
        static_assert(
                (meta::is_sdlpp_flag<Fs> && ...),
                "system_manager::system_manager(): neither flag::init nor flag::img object passed "
                "as argument"
            );
        init( std::forward<Fs>(flags)... );
    }
}

/// Destructor.
/// \effects Uninitialize every SDL subsystem initialized by the instance (except for the one initialized
///     by [SDLpp::system_manager::init_permanent]()).
/// \notes The destructor cannot uninitialize IMG subsystems.
system_manager::~system_manager() noexcept
{
    for ( auto flag : _init_on ) {
        SDL_QuitSubSystem( static_cast<uint32_t>(flag) );
    }
}

/// \exclude
/// Base method called by all other `init' functions.
/// \param flags A flag object (zero or more).
/// \requires flag's type to be flag::{init,img}.
/// \returns [self](SDLpp::system_manager)
template <typename ...Fs>
constexpr inline decltype(auto) system_manager::_just_init(Fs &&... flags) noexcept
{
    if ( ! _instance ) {
        _instance = std::move(detail::_system_manager_singleton{flags...});
    }
    else {
        _instance->init(flags...);
    }
    return *this;
}

/// \group sysmgr_init
/// \effects Initializes SDL or IMG with flags passed as argument. Subsystems will be uninitialized on
///     destruction.
/// \tparam Fs `flags`' pack type.
/// \param flags At least a flag object.
/// \requires `flags`' type to be `flag::`{`init`,`img`}.
/// \requires `sizeof...(Fs) > 0`
/// \returns [SDLpp::system_manager](self)
template <typename ...Fs>
constexpr inline decltype(auto) system_manager::init(Fs &&... flags) noexcept
{
    static_assert(
            (meta::is_sdlpp_flag<Fs> && ...),
            "system_manager::init(): neither flag::init nor flag::img object passed as argument"
        );
    static_assert(
            sizeof...(Fs) > 0,
            "system_manager::init(): at least one parameter is required"
        );

    _just_init(std::forward<Fs>(flags)...);

    if ( auto done = _instance->last_result(); done.has_value() ) {
        auto [inits, imgs] = *done;
        _init_on.push_back(inits);
        //_img_on .push_back(imgs);
    }

    return *this;
}

/// \group sysmgr_init
/// \effects Initializes SDL or IMG with flags passed as argument. Subsystems will be uninitialized on
///     destruction.
/// \param flags At least a flag object
/// \requires `flags`' type to be `flag::`{`init`,`img`}.
/// \returns [SDLpp::system_manager](self)
template <typename ...Fs>
constexpr inline decltype(auto) system_manager::init_subsystem(Fs &&... flags) noexcept
{
    static_assert(
            (meta::is_sdlpp_flag<Fs> && ...),
            "system_manager::init_subsystem(): neither flag::init nor flag::img object passed as"
            "argument"
        );
    static_assert(
            sizeof...(Fs) > 0,
            "system_manager::init_subsystem(): at least one parameter is required"
        );
    return init(std::forward<Fs>(flags)...);
}

/// \effects Initializes SDL or IMG with flags passed as argument. Subsystems will _not_ be uninitialized
///     on destruction.
/// \param flags At least a flag object
/// \requires `flags`' type to be `flag::`{`init`,`img`}
/// \returns [SDLpp::system_manager](self)
template <typename ...Fs>
constexpr inline decltype(auto) system_manager::init_permanent(Fs &&... flags) noexcept
{
    static_assert(
            (meta::is_sdlpp_flag<Fs> && ...),
            "system_manager::init_permanent(): neither flag::init nor flag::img object passed as"
            "argument"
        );
    static_assert(
            sizeof...(Fs) > 0,
            "system_manager::init_permanent(): at least one parameter is required"
        );
    return _just_init(std::forward<Fs>(flags)...);
}

/// \effects Returns `true` if at least a `flag::`{`init`,`img`} has been initialized, _and_ if the last
///     initialization worked well
/// \returns a boolean value about the good state of the initialization
constexpr system_manager::operator bool() const
{
    return (_instance && *_instance);
}

/// \effects Check if the last initialization worked well
/// \returns `true` if the last passed flags worked well, `false` otherwise.
/// \notes if no flag has been passed yet, returns `false`.
constexpr bool system_manager::good() const
{
    return static_cast<bool>(*this);
}


} // namespace SDLpp

#endif /* SDLPP_SYSTEM_MANAGER_HPP */

