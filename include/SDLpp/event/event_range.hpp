/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : event_range
 * @created     : Saturday Mar 21, 2020 02:03:22 CET
 * @license     : MIT
 * */

#ifndef SDLPP_EVENT_EVENT_RANGE_HPP
#define SDLPP_EVENT_EVENT_RANGE_HPP

#include "event.hpp"
#include "poll_event.hpp"
#ifdef __cpp_lib_ranges
#   include <iterator>
#endif

namespace SDLpp
{

namespace detail
{

class event_range_t;

struct event_iterator
{
    using iterator       = event_iterator;
    using const_iterator = event_iterator;
    using value_type     = SDLpp::event;
    using reference      = SDLpp::event &;
    using const_reference = SDLpp::event const &;
    using pointer         = SDLpp::event *;
    using const_pointer   = SDLpp::event const *;

    friend class event_range_t;

private:

    mutable tl::optional<SDLpp::event> _event = tl::nullopt;

    inline
    void read() const noexcept
    {
        _event = SDLpp::poll_event();
    }

    inline event_iterator() { read(); }
    inline event_iterator(tl::nullopt_t) {}
public:

    auto operator++() const
    {
        read();
        return *this;
    }

    auto operator++(int) const
    {
        auto copy = *this;
        ++*this;
        return copy;
    }

    auto operator*() const
        -> const_reference
    {
        return *_event;
    }

    auto operator->() const
        -> const_pointer
    {
        return std::addressof(*_event);
    }

    inline
    bool operator==(event_iterator const & other) const noexcept
    { return not _event and not other._event; }

    inline
    bool operator!=(event_iterator const & other) const noexcept
    { return _event or other._event; }

#ifdef __cpp_lib_ranges
    inline
    bool operator==(std::default_sentinel_t) const noexcept
    { return not _event.has_value(); }

    inline
    bool operator!=(std::default_sentinel_t) const noexcept
    { return _event.has_value(); }
#endif

};

class event_range_t
{
    using iterator = detail::event_iterator;
    using const_iterator = iterator;
    using value_type = iterator::value_type;
    using reference  = iterator::reference;
    using const_reference = iterator::const_reference;
    using pointer = iterator::pointer;
    using const_pointer = iterator::const_pointer;

public:
    iterator begin() const noexcept { return iterator{}; }
    iterator end()   const noexcept { return iterator{tl::nullopt}; }
};

} // namespace detail

constexpr detail::event_range_t event_range;

} // namespace SDLpp

#endif /* EVENT_RANGE_HPP */

