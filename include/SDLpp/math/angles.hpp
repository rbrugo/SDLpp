/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : angles
 * @created     : Monday Oct 15, 2018 12:40:08 CEST
 * @license     : MIT
 * */

#ifndef ANGLES_HPP
#define ANGLES_HPP

#include <cmath>

namespace SDLpp
{

namespace math
{
class radians;
class degrees;

class radians
{
    double _value;
public:
    explicit constexpr radians(double val = 0.f) : _value{val} { }
    explicit constexpr radians(degrees val);
    constexpr auto count() const noexcept { return _value; }
    constexpr auto operator=(double val) -> radians & { _value = val; return *this; }
    constexpr auto operator==(radians other) { return _value == other._value; }
    constexpr auto operator!=(radians other) { return _value != other._value; }
    constexpr auto operator< (radians other) { return _value <  other._value; }
    constexpr auto operator<=(radians other) { return _value <= other._value; }
    constexpr auto operator> (radians other) { return _value >  other._value; }
    constexpr auto operator>=(radians other) { return _value >= other._value; }
    /* constexpr operator double() const noexcept { return _value; } */
    /* constexpr operator double &() noexcept { return _value; } */
};

class degrees
{
    double _value;
public:
    explicit constexpr degrees(double val = 0.f) : _value{val} { }
    explicit constexpr degrees(radians val) : _value{val.count() * 180. / M_PI} { }
    constexpr auto count() const noexcept { return _value; }
    constexpr auto operator=(double val) -> degrees & { _value = val; return *this; }
    constexpr auto operator==(degrees other) { return _value == other._value; }
    constexpr auto operator!=(degrees other) { return _value != other._value; }
    constexpr auto operator< (degrees other) { return _value <  other._value; }
    constexpr auto operator<=(degrees other) { return _value <= other._value; }
    constexpr auto operator> (degrees other) { return _value >  other._value; }
    constexpr auto operator>=(degrees other) { return _value >= other._value; }
};

constexpr radians::radians(degrees val) : _value{val.count() * M_PI / 180.} { }

inline double sin(radians r) { return std::sin(r.count()); }
inline double sin(degrees d) { return sin(radians{d}); }

inline double cos(radians r) { return std::cos(r.count()); }
inline double cos(degrees d) { return cos(radians{d}); }

inline double tan(radians r) { return std::tan(r.count()); }
inline double tan(degrees d) { return tan(radians{d}); }

inline radians asin(double x) { return radians{std::asin(x)}; }
inline radians acos(double x) { return radians{std::acos(x)}; }
inline radians atan(double x) { return radians{std::atan(x)}; }
inline radians atan2(double y, double x) { return radians{std::atan2(y, x)}; }

namespace literals {
constexpr degrees operator""_deg(long double value)
{
    return degrees{static_cast<double>(value)};
}

constexpr radians operator""_rad(long double value)
{
    return radians{static_cast<double>(value)};
}
} // namespace literals
} // namespace math

} // namespace SDLpp

#endif /* ANGLES_HPP */

