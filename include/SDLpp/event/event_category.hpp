/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : inline constexpr event_category
 * @created     : Thursday Apr 26, 2018 20:57:37 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_EVENT_EVENT_CATEGORY_HPP
#define SDLPP_EVENT_EVENT_CATEGORY_HPP

#include <SDL2/SDL_events.h>

namespace SDLpp
{

namespace event_category
{

struct base_event_category{};

template <typename T, auto VALUE, auto PTR>
struct event_category;

} // namespace event_category

namespace meta
{
template <typename C>
struct is_event_category
{
    constexpr static bool value = std::is_base_of_v<event_category::base_event_category, C>;
};
template <class C>
inline constexpr bool is_event_category_v = is_event_category<C>::value;
} // namespace meta


namespace event_category
{

template <typename T, auto VALUE, auto PTR>
struct event_category : base_event_category, T
{
    using type = T;
    static inline auto member = PTR;
    constexpr static auto value = VALUE;

    explicit event_category(T const & t) : T{t} { };
    explicit event_category(T      && t) : T{std::move(t)} { };
};

//perldo s/\[\[maybe_unused\]\] constexpr (\S+)\s+(\S+);/using \2 = \1;/g
//perldo s/\[\[maybe_unused\]\] constexpr (\S+)\s+(\S+);/using \2 = \1;\nconstexpr inline \2 \2;/g
//perldo s/using (\S+) = (\S+);/inline constexpr \2\t\t\1;/g
using audio_device_added = event_category<SDL_AudioDeviceEvent, SDL_AUDIODEVICEADDED, &SDL_Event::adevice>;
using audio_device_removed = event_category<SDL_AudioDeviceEvent, SDL_AUDIODEVICEREMOVED, &SDL_Event::adevice>;

using controller_axis_motion = event_category<SDL_ControllerAxisEvent, SDL_CONTROLLERAXISMOTION, &SDL_Event::caxis>;

using controller_button_down = event_category<SDL_ControllerButtonEvent, SDL_CONTROLLERBUTTONDOWN, &SDL_Event::cbutton>;
using controller_button_up = event_category<SDL_ControllerButtonEvent, SDL_CONTROLLERBUTTONUP, &SDL_Event::cbutton>;

using controller_device_added = event_category<SDL_ControllerDeviceEvent, SDL_CONTROLLERDEVICEADDED, &SDL_Event::cdevice>;
using controller_device_removed = event_category<SDL_ControllerDeviceEvent, SDL_CONTROLLERDEVICEREMOVED, &SDL_Event::cdevice>;
using controller_device_remapped = event_category<SDL_ControllerDeviceEvent, SDL_CONTROLLERDEVICEREMAPPED, &SDL_Event::cdevice>;

using dollar_gesture =  event_category<SDL_DollarGestureEvent, SDL_DOLLARGESTURE, &SDL_Event::dgesture>;
using dollar_record = event_category<SDL_DollarGestureEvent, SDL_DOLLARRECORD, &SDL_Event::dgesture>;

using drop_file = event_category<SDL_DropEvent, SDL_DROPFILE, &SDL_Event::drop>;
using dropext = event_category<SDL_DropEvent, SDL_DROPTEXT, &SDL_Event::drop>;
using drop_begin = event_category<SDL_DropEvent, SDL_DROPBEGIN, &SDL_Event::drop>;
using drop_complete = event_category<SDL_DropEvent, SDL_DROPCOMPLETE, &SDL_Event::drop>;

using finger_motion = event_category<SDL_TouchFingerEvent, SDL_FINGERMOTION, &SDL_Event::tfinger>;
using finger_down = event_category<SDL_TouchFingerEvent, SDL_FINGERDOWN, &SDL_Event::tfinger>;
using finger_up = event_category<SDL_TouchFingerEvent, SDL_FINGERUP, &SDL_Event::tfinger>;

using key_down = event_category<SDL_KeyboardEvent, SDL_KEYDOWN, &SDL_Event::key>;
using key_up = event_category<SDL_KeyboardEvent, SDL_KEYUP, &SDL_Event::key>;

using joy_axis_motion = event_category<SDL_JoyAxisEvent, SDL_JOYAXISMOTION, &SDL_Event::jaxis>;

using joy_ball_motion = event_category<SDL_JoyBallEvent, SDL_JOYBALLMOTION, &SDL_Event::jball>;

using joy_hat_motion = event_category<SDL_JoyHatEvent, SDL_JOYHATMOTION, &SDL_Event::jhat>;

using joy_button_down = event_category<SDL_JoyButtonEvent, SDL_JOYBUTTONDOWN, &SDL_Event::jbutton>;
using joy_button_up = event_category<SDL_JoyButtonEvent, SDL_JOYBUTTONUP, &SDL_Event::jbutton>;

using joy_device_added = event_category<SDL_JoyDeviceEvent, SDL_JOYDEVICEADDED, &SDL_Event::jdevice>;
using joy_device_removed = event_category<SDL_JoyDeviceEvent, SDL_JOYDEVICEREMOVED, &SDL_Event::jdevice>;

using mouse_motion = event_category<SDL_MouseMotionEvent, SDL_MOUSEMOTION, &SDL_Event::motion>;

using mouse_button_down = event_category<SDL_MouseButtonEvent, SDL_MOUSEBUTTONDOWN, &SDL_Event::button>;
using mouse_button_up = event_category<SDL_MouseButtonEvent, SDL_MOUSEBUTTONUP, &SDL_Event::button>;

using mouse_wheel = event_category<SDL_MouseWheelEvent, SDL_MOUSEWHEEL, &SDL_Event::wheel>;

using multigesture = event_category<SDL_MultiGestureEvent, SDL_MULTIGESTURE, &SDL_Event::mgesture>;

using quit = event_category<SDL_QuitEvent, SDL_QUIT, &SDL_Event::quit>;

using sys_wm_event = event_category<SDL_SysWMEvent, SDL_SYSWMEVENT, &SDL_Event::syswm>;

using text_editing = event_category<SDL_TextEditingEvent, SDL_TEXTEDITING, &SDL_Event::edit>;

using text_input = event_category<SDL_TextInputEvent, SDL_TEXTINPUT, &SDL_Event::text>;

using user_event = event_category<SDL_UserEvent, SDL_USEREVENT, &SDL_Event::user>;

using window_event = event_category<SDL_WindowEvent, SDL_WINDOWEVENT, &SDL_Event::window>;

} // namespace event_category

} // namespace SDLpp

#endif /* SDLPP_EVENT_EVENT_CATEGORY_HPP */

