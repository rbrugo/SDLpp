/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : math
 * @created     : Monday Oct 15, 2018 11:49:32 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_MATH_GRAPHIC_2D_HPP
#define SDLPP_MATH_GRAPHIC_2D_HPP

#include <array>
#include <cmath>

namespace SDLpp
{
namespace math
{

namespace detail
{
struct vector2d_tag { };
struct point2d_tag { };
template <typename Number, typename Tag>
struct _generic_math_2symbol
{
    using value_type = Number;
    using tag_type = std::decay_t<Tag>;
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

struct vector2d;
struct point2d;

struct vector2d : public detail::_generic_math_2symbol<double, detail::vector2d_tag>
{
    using _generic_math_2symbol::_generic_math_2symbol;
    using _generic_math_2symbol::get;
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
    constexpr auto operator+=(vector2d const & other) -> vector2d &
    {
        x() += other.x();
        y() += other.y();
        return *this;
    }

    constexpr auto operator-=(vector2d const & other) -> vector2d &
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

struct point2d  : public detail::_generic_math_2symbol<double, detail::point2d_tag>
{
    using _generic_math_2symbol<double, detail::point2d_tag>::_generic_math_2symbol;
    using _generic_math_2symbol::get;
    template <typename N> constexpr auto & operator*=(N const & factor)
    {
        x() *= factor;
        y() *= factor;
        return *this;
    }
    template <typename N> constexpr auto & operator/=(N const & factor)
    {
        return *this *= (1./factor);
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
    constexpr auto operator+=(vector2d const & vec) -> point2d &
    {
        x() += vec.x();
        y() += vec.y();
        return *this;
    }

    constexpr auto operator-=(vector2d const & vec) -> point2d &
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

constexpr auto operator+(point2d pt, vector2d const & vec) -> point2d
{
    return pt += vec;
}

constexpr auto operator-(point2d pt, vector2d const & vec) -> point2d
{
    return pt -= vec;
}

constexpr auto operator+(vector2d v1, vector2d const & v2) -> vector2d
{
    return v1 += v2;
}

constexpr auto operator-(vector2d v1, vector2d const & v2) -> vector2d
{
    return v1 -= v2;
}

constexpr auto operator-(point2d const & pt1, point2d const & pt2) -> vector2d
{
    return {pt1.x() - pt2.x(), pt1.y() - pt2.y()};
}


///


} // namespace math
} // namespace SDLpp

namespace std
{
template <typename N, typename T>
struct tuple_size<SDLpp::math::detail::_generic_math_2symbol<N, T>> : std::integral_constant<std::size_t, 2> { };
template <typename Num, typename T, std::size_t N>
struct tuple_element<N, SDLpp::math::detail::_generic_math_2symbol<Num, T>> {
    using type = Num;
};

/* template <typename N, typename T> */
template <>
struct tuple_size<SDLpp::math::vector2d> : std::integral_constant<std::size_t, 2> { };
template <std::size_t N>
struct tuple_element<N, SDLpp::math::vector2d> {
    using type = SDLpp::math::vector2d::value_type;
};

template <>
struct tuple_size<SDLpp::math::point2d> : std::integral_constant<std::size_t, 2> { };
template <std::size_t N>
struct tuple_element<N, SDLpp::math::point2d> {
    using type = SDLpp::math::point2d::value_type;
};
} // namespace std

#endif /* SDLPP_MATH_GRAPHIC_2D_HPP */

