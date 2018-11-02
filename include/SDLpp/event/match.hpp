/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : match
 * @created     : Sunday Apr 29, 2018 14:34:33 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_MATCH_HPP
#define SDLPP_MATCH_HPP

#include "event.hpp"
#include <functional>

namespace SDLpp
{

namespace detail
{

/* template <typename E, typename R, typename C, typename A> */
/* inline bool is_invocable_by(E && e, R(C::*f)(A) const) */
/* { */
/*     return e.is_invocable_by(f); */
/* } */

/* template <typename E, typename R, typename A> */
/* inline bool is_invocable_by(E && e, R(*f)(A)) */
/* { */
    /* return e.is_invocable_by(f); */
/* } */

/* template <typename E, typename F> */
/* inline bool is_invocable_by(E && e, [[maybe_unused]] F && f) */
/* { */
/*     //return e.is_invocable_by(f); */
/*     /1* return is_invocable_by(e, &std::add_const_t<std::decay_t<decltype(f)>>::operator()); *1/ */

/*     switch(e.handler().type) { */
/*         case SDL_KEYDOWN: */
/*             return std::is_invocable_v<F, SDLpp::event_category::key_down>; */
/*         case SDL_KEYUP: */
/*             return std::is_invocable_v<F, SDLpp::event_category::key_up>; */
/*         case SDL_QUIT: */
/*             return std::is_invocable_v<F, SDLpp::event_category::quit>; */
/*         default: */
/*             return false; */
/*     } */
/* } */

template <typename E, typename F>
inline bool call_if_possible(E && e, F && f)
{
/* #define SDLPP_MATCH_CHECK(T) if constexpr(std::is_invocable_v<F, T>) {\ */
/*     std::forward<F>(f)(std::forward<E>(e).handler().*(std::decay_t<T>::member));\ */
/*     return true; }\ */
/*     else { return false; } */

#define CASE_MATCH_CHECK(T) \
    case std::decay_t<T>::value:\
        if constexpr(std::is_invocable_v<F, T>) {\
            std::forward<F>(f)(T{std::forward<E>(e).handler().*(std::decay_t<T>::member)});\
            return true;\
        }\
        else {\
            return false;\
        }


#define SDLPP_MATCH_CHECK(T) if constexpr(std::is_invocable_v<F, T>) {\
    std::forward<F>(f)((T){std::forward<E>(e).handler().*(std::decay_t<(T)>::member)});\
    return true; }\
    else { return false; }

    using namespace SDLpp::event_category; //NOLINT
    switch(e.handler().type) {
        /* case SDL_KEYDOWN: */
        /*     SDLPP_MATCH_CHECK(SDLpp::event_category::key_down); */
        /* case SDL_KEYUP: */
        /*     SDLPP_MATCH_CHECK(SDLpp::event_category::key_up); */
        /* case SDL_QUIT: */
        /*     /1* return std::is_invocable_v<F, SDLpp::event_category::quit>; *1/ */
        /*     SDLPP_MATCH_CHECK(SDLpp::event_category::quit); */
        /* CASE_MATCH_CHECK(key_down); */
        /* CASE_MATCH_CHECK(key_up); */
        /* CASE_MATCH_CHECK(quit); */


        CASE_MATCH_CHECK(audio_device_added);
        CASE_MATCH_CHECK(audio_device_removed);
        CASE_MATCH_CHECK(controller_axis_motion);
        CASE_MATCH_CHECK(controller_button_down);
        CASE_MATCH_CHECK(controller_button_up);
        CASE_MATCH_CHECK(controller_device_added);
        CASE_MATCH_CHECK(controller_device_removed);
        CASE_MATCH_CHECK(controller_device_remapped);
        CASE_MATCH_CHECK(dollar_gesture);
        CASE_MATCH_CHECK(dollar_record);
        CASE_MATCH_CHECK(drop_file);
        CASE_MATCH_CHECK(dropext);
        CASE_MATCH_CHECK(drop_begin);
        CASE_MATCH_CHECK(drop_complete);
        CASE_MATCH_CHECK(finger_motion);
        CASE_MATCH_CHECK(finger_down);
        CASE_MATCH_CHECK(finger_up);
        CASE_MATCH_CHECK(key_down);
        CASE_MATCH_CHECK(key_up);
        CASE_MATCH_CHECK(joy_axis_motion);
        CASE_MATCH_CHECK(joy_ball_motion);
        CASE_MATCH_CHECK(joy_hat_motion);
        CASE_MATCH_CHECK(joy_button_down);
        CASE_MATCH_CHECK(joy_button_up);
        CASE_MATCH_CHECK(joy_device_added);
        CASE_MATCH_CHECK(joy_device_removed);
        CASE_MATCH_CHECK(mouse_motion);
        CASE_MATCH_CHECK(mouse_button_down);
        CASE_MATCH_CHECK(mouse_button_up);
        CASE_MATCH_CHECK(mouse_wheel);
        CASE_MATCH_CHECK(multigesture);
        CASE_MATCH_CHECK(quit);
        CASE_MATCH_CHECK(sys_wm_event);
        CASE_MATCH_CHECK(text_editing);
        CASE_MATCH_CHECK(text_input);
        CASE_MATCH_CHECK(user_event);
        CASE_MATCH_CHECK(window_event);
        default:
            return false;
    }
#undef SDLPP_MATCH_CHECK
}

/*template <typename E, typename C, typename A>
inline auto match_impl(E && event, void (C::*f)(A) const, C && callable)
{
    if ( detail::is_invocable_by(event, f) ) {
        event.call(std::forward<C>(callable), f);
    }
}

template < typename E, typename F >
inline auto match_impl(E && event, F && f)
{
    match_impl(
            std::forward<E>(event),
            &std::add_const_t<std::decay_t<decltype(f)>>::operator(),
            std::forward<F>(f)
        );
}*/


/* //Version for function objects - function object */
/* template <typename E, typename C, typename A, typename ...Fs>//, typename = void> */
/* inline auto match_impl(E && event, void (C::*f)(A), C && callable, Fs&&... fs) */
/* { */
/*     if ( ! detail::is_invocable_by(event, f) ) { */
/*         if constexpr ( sizeof...(Fs) == 0 ) { */
/*             return; */
/*         } */
/*         else { */
/*             match_impl(std::forward<E>(event), std::forward<Fs>(fs)...); */
/*             return; */
/*         } */
/*     } */
/*     event.call(std::forward<C>(callable), f); */
/* } */

/* //Version for function objects - pointer-to-function-member */
/* template < typename E, typename F, typename ...Fs > */
/* inline auto match_impl(E && event, F && f, Fs&&... fs) */
/* { */
/*     match_impl( */
/*             std::forward<E>(event), */
/*             &std::add_const_t<std::decay_t<decltype(f)>>::operator(), */
/*             std::forward<F>(f), */
/*             std::forward<Fs>(fs)... */
/*         ); */
/* } */

template <typename E, typename F, typename ...Fs>
inline auto match_impl(E && event, F && f, Fs&&... fs)
{
    /* if ( ! detail::is_invocable_by(event, f) ) { */
    if (! detail::call_if_possible(event, f)) {
        if constexpr (sizeof...(Fs) == 0) {
            return;
        }
        else {
            return match_impl(std::forward<E>(event), std::forward<Fs>(fs)...);
        }
    }
    /* event.call(std::forward<F>(f)); */
    /* detail::call(event, f); */
}

} // namespace detail

template <typename E, typename... Fs>
inline auto match(E && e, Fs&&... fs)
{
    static_assert(
            std::is_same_v<std::decay_t<E>, event>,
            "`match's first argument must be an event"
        );
    detail::match_impl(std::forward<E>(e), std::forward<Fs>(fs)...);
}

} // namespace SDLpp

#endif /* SDLPP_MATCH_HPP */

