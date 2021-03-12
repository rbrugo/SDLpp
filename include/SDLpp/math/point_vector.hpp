/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : math
 * @created     : Monday Oct 15, 2018 11:49:32 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_MATH_POINT_VECTOR_HPP
#define SDLPP_MATH_POINT_VECTOR_HPP

#include <array>
#include <cmath>

namespace SDLpp
{
namespace math
{

namespace detail
{
template <typename Number>
struct _generic_math_2symbol
{
    using value_type = Number;
    using this_t = _generic_math_2symbol;
    constexpr value_type & x() noexcept { return _data[0]; }
    constexpr value_type & y() noexcept { return _data[1]; }
    constexpr value_type const & x() const noexcept { return _data[0]; }
    constexpr value_type const & y() const noexcept { return _data[1]; }

    template <std::size_t N>
    constexpr decltype(auto) get()
    {
        return std::get<N>(_data);
    }

    template <std::size_t N>
    constexpr decltype(auto) get() const
    {
        return std::get<N>(_data);
    }

    constexpr _generic_math_2symbol(value_type const & x, value_type const & y)
        noexcept(noexcept(std::is_nothrow_constructible_v<value_type>)) :
         _data{x, y} { }
    constexpr _generic_math_2symbol()
        noexcept(noexcept(std::is_nothrow_constructible_v<value_type>)) :
        _generic_math_2symbol{value_type{}, value_type{}} { }

    constexpr auto operator-() noexcept { return this_t{ -x(), -y()}; }
    template <typename N> constexpr auto & operator*=(N const & factor)
    {
        x() *= factor;
        y() *= factor;
        return *this;
    }
    template <typename N> constexpr auto & operator/=(N const & factor)
    {
        return *this * (1./factor);
    }
    template <typename N> constexpr auto operator*(N const & factor) const
    {
        auto temp = *this;
        return temp *= factor;
    }
    template <typename N> constexpr auto operator/(N const & factor) const
    {
        auto temp = *this;
        return temp /= factor;
    }

    constexpr auto length() const noexcept { return std::hypot(x(), y()); }
    constexpr auto modulus() const noexcept { return length(); }

    constexpr auto unit() const { return *this / length(); }

private:
    std::array<value_type, 2> _data;
};
} // namespace detail

template <typename N = double>
struct basic_vector2d;
template <typename N = double>
struct basic_point2d;

template <typename N>
struct basic_vector2d : public detail::_generic_math_2symbol<N>
{
    using parent_t = detail::_generic_math_2symbol<N>;
    using parent_t::_generic_math_2symbol;
    using parent_t::get;
    using parent_t::x;
    using parent_t::y;

    template <typename T> constexpr auto & operator*=(T const & factor)
    {
        x() *= factor;
        y() *= factor;
        return *this;
    }
    template <typename T> constexpr auto & operator/=(T const & factor)
    {
        return *this * (1./factor);
    }
    template <typename T> constexpr auto operator*(T const & factor) const
    {
        auto temp = *this;
        return temp *= factor;
    }
    template <typename T> constexpr auto operator/(T const & factor) const
    {
        auto temp = *this;
        return temp /= factor;
    }
    constexpr auto operator+=(basic_vector2d const & other) -> basic_vector2d &
    {
        x() += other.x();
        y() += other.y();
        return *this;
    }

    constexpr auto operator-=(basic_vector2d const & other) -> basic_vector2d &
    {
        x() -= other.x();
        y() -= other.y();
        return *this;
    }


    /*constexpr*/ auto & rotate(double theta) {
        auto const temp = x()*std::sin(theta) + y()*std::cos(theta);
        y() = x()*std::cos(theta) - y()*std::sin(theta);
        x() = temp;
        return *this;
    }

};

template <typename N>
struct basic_point2d  : public detail::_generic_math_2symbol<N>
{
    
    using parent_t = detail::_generic_math_2symbol<N>;
    using parent_t::_generic_math_2symbol;
    using parent_t::get;
    using parent_t::x;
    using parent_t::y;
    template <typename T> constexpr auto & operator*=(T const & factor)
    {
        x() *= factor;
        y() *= factor;
        return *this;
    }
    template <typename T> constexpr auto & operator/=(T const & factor)
    {
        return *this *= (1./factor);
    }
    template <typename T> constexpr auto operator*(T const & factor) const
    {
        auto temp = *this;
        return temp *= factor;
    }
    template <typename T> constexpr auto operator/(T const & factor) const
    {
        auto temp = *this;
        return temp /= factor;
    }
    template <typename T>
    constexpr auto operator+=(basic_vector2d<T> const & vec) -> basic_point2d &
    {
        x() += vec.x();
        y() += vec.y();
        return *this;
    }

    template <typename T>
    constexpr auto operator-=(basic_vector2d<T> const & vec) -> basic_point2d &
    {
        x() -= vec.x();
        y() -= vec.y();
        return *this;
    }

    /*constexpr*/ auto & rotate(double theta) {
        auto const temp = x()*std::sin(theta) + y()*std::cos(theta);
        y() = x()*std::cos(theta) - y()*std::sin(theta);
        x() = temp;
        return *this;
    }
};

//Don't work, dunno
/*template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr auto operator*(T && c, detail::_generic_math_2symbol<U> const & x)
{
    return x * std::forward<T>(c);
}*/

template <typename T, typename U>
constexpr auto operator+(basic_point2d<T> pt, basic_vector2d<U> const & vec) -> basic_point2d<std::common_type_t<T, U>>
{
    return pt += vec;
}

template <typename T, typename U>
constexpr auto operator-(basic_point2d<T> pt, basic_vector2d<U> const & vec) -> basic_point2d<std::common_type_t<T, U>>
{
    return pt -= vec;
}

template <typename T, typename U>
constexpr auto operator+(basic_vector2d<T> v1, basic_vector2d<U> const & v2) -> basic_vector2d<std::common_type_t<T, U>>
{
    return v1 += v2;
}

template <typename T, typename U>
constexpr auto operator-(basic_vector2d<T> v1, basic_vector2d<U> const & v2) -> basic_vector2d<std::common_type_t<T, U>>
{
    return v1 -= v2;
}

template <typename T, typename U>
constexpr auto operator-(basic_point2d<T> const & pt1, basic_point2d<U> const & pt2) -> basic_vector2d<std::common_type_t<T, U>>
{
    return {pt1.x() - pt2.x(), pt1.y() - pt2.y()};
}


///


} // namespace math

using vector2d = math::basic_vector2d<double>;
using point2d = math::basic_point2d<double>;

} // namespace SDLpp

namespace std
{
template <typename N>
struct tuple_size<SDLpp::math::detail::_generic_math_2symbol<N>> : std::integral_constant<std::size_t, 2> { };
template <typename Num, std::size_t N>
struct tuple_element<N, SDLpp::math::detail::_generic_math_2symbol<Num>> {
    using type = Num;
};

/* template <typename N, typename T> */
template <typename T>
struct tuple_size<SDLpp::math::basic_vector2d<T>> : std::integral_constant<std::size_t, 2> { };
template <typename T, std::size_t N>
struct tuple_element<N, SDLpp::math::basic_vector2d<T>> {
    using type = typename SDLpp::math::basic_vector2d<T>::value_type;
};

template <typename T>
struct tuple_size<SDLpp::math::basic_point2d<T>> : std::integral_constant<std::size_t, 2> { };
template <typename T, std::size_t N>
struct tuple_element<N, SDLpp::math::basic_point2d<T>> {
    using type = typename SDLpp::math::basic_point2d<T>::value_type;
};
} // namespace std

#endif /* SDLPP_MATH_POINT_VECTOR_HPP */

