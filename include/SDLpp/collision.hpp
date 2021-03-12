/**
 * @author      : Riccardo Brugo (brugo.riccardo@gmail.com)
 * @file        : collision
 * @created     : Friday Sep 07, 2018 00:02:49 CEST
 * @license     : MIT
 * */

#ifndef SDLPP_COLLISION_HPP
#define SDLPP_COLLISION_HPP

/* #include <vector.hpp> */
/* #include "math.hpp" */
#include "math.hpp"
/* #include <algorithm> */
/* #include <numeric> */
#include <range/v3/numeric.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/view/zip.hpp>
#include <range/v3/view/drop.hpp>
#include <range/v3/view/transform.hpp>
#include <memory> //std::shared_from_this
#include <cstdint>
#include <cmath>

#include <vector> //namespace test

#include <tl/optional.hpp>

namespace SDLpp
{

namespace collision
{

struct shape {
    shape() = default;
    shape(shape const &) = default;
    shape(shape      &&) = default;
    shape & operator=(shape const &) = default;
    shape & operator=(shape      &&) = default;
    ~shape() = default;
    explicit shape(std::vector<point2d> pts) : points{std::move(pts)}, updated{false} { };
    shape(std::initializer_list<point2d> pts) : points{pts}, updated{false} { };

    std::vector<point2d> points;
    /*int16_t*/double top{}, bottom{}, left{}, right{};
    bool updated = false;
    void update()
    {
        if (!points.empty()) {
            bottom = right = std::numeric_limits</*int16_t*/double>::min();
            top = left = std::numeric_limits</*int16_t*/double>::max();

            for (auto pt : points) {
                right = std::max(pt.x(), right);
                top = std::min(pt.y(), top);
                left = std::min(pt.x(), left);
                bottom = std::max(pt.y(), bottom);
            }
        }
        updated = true;
    }
};

struct base : public std::enable_shared_from_this<base> {
private:
    point2d _origin = {0, 0};
    mutable shape _shape;

    inline void update() const
    {
        _shape.update();
    }
public:
    base() = delete;
    base(base const &) = default;
    base(base      &&) = default;
    base & operator=(base const &) = default;
    base & operator=(base      &&) = default;
    virtual ~base() = default;
    explicit base(point2d origin, shape sh = {}) : _origin{origin}, _shape{std::move(sh)} { }

    auto origin() const -> point2d { return _origin; }
    auto origin() -> point2d & { return _origin; }

    virtual void move(double dx, double dy) { _origin.x() += dx; _origin.y() += dy; }
    virtual void move(vector2d const & dr) { origin() += dr; }
    virtual double left() const
    {
        if (!_shape.updated) {
            update();
        }
        return _shape.left + _origin.x();
    }
    virtual double right() const
    {
        if (!_shape.updated) {
            update();
        }
        return _shape.right + _origin.x();
    }
    virtual double top() const
    {
        if (!_shape.updated) {
            update();
        }
        return _shape.top + _origin.y();
    }
    virtual double bottom() const
    {
        if (!_shape.updated) {
            update();
        }
        return _shape.bottom + _origin.y();
    }
    virtual point2d center() const
    {
        if (!_shape.updated) {
            update();
        }
        return point2d{left() + right(), top() + bottom()} * 0.5;
    }

    template <typename T, typename = std::enable_if_t<std::is_base_of_v<base, std::decay_t<T>>>>
    /* bool collides(T const & rhs) const */
    tl::optional<double> collides(T const & rhs) const
    {
        if ( std::addressof(rhs) == this ) {
            /* return false; */
            return tl::nullopt;
        }
        base const & other = rhs;
        if (!_shape.updated) {
            update();
        }
        if (!other._shape.updated) {
            other.update();
        }

        //First phase
        if (
            (left() >= other.right() || right() <= other.left()) ||
            (top() >= other.bottom() || bottom() <= other.top())
        ) {
            /* return false; */
            return tl::nullopt;
        }

        //Second phase
        //NB: _separating axis theorem_
        namespace view = ranges::view;
        auto sum_points = [](auto const & a, auto const & b) {
            auto const & [xa, ya] = a;
            auto const & [xb, yb] = b;
            return point2d{xa + xb, ya + yb};
        };


        auto const & first  = _shape.points;
        auto const & second = other._shape.points;
        auto avg_first = ranges::accumulate(first, point2d{0, 0}, sum_points) / size(first);
        auto avg_secnd = ranges::accumulate(second, point2d{0, 0}, sum_points) / size(second);

        auto test_collision = [&first, &second, avg_first, avg_secnd](auto const& pta, auto const& ptb) {
            auto const diff = ptb - pta;
            auto const theta = std::atan2(diff.y(), diff.x());
            auto project = [theta](auto n) {
                return n.rotate(-theta).x();
            };
            auto [min_f, max_f] = ranges::minmax(first  | view::transform(project));
            auto [min_s, max_s] = ranges::minmax(second | view::transform(project));

            if (project(avg_first) <= project(avg_secnd)) {
                return !(max_f < min_s);
                /* if (not (max_f < min_s)) { */
                    /* return tl::optional{theta}; */
                /* } */
            }
            return !(min_f > max_s);
            /* return !(min_f > max_s) ? tl::optional{theta} : {tl::nullopt}; */
            /* if (!(min_f > max_s)) { */
                /* return tl::optional{theta}; */
            /* } */
            /* return tl::optional<double>{}; */
        };


        for (auto const & [pta, ptb] : view::zip(first, first | view::drop(1))) {
            /* if (test_collision(pta, ptb)) { */
                /* return true; */
            /* } */
            if (auto res = test_collision(pta, ptb); res.has_value()) {
                return res;
            }
        }
        return test_collision(first.back(), first.front());
    }
};

} // namespace collision
} // namespace SDLpp

#endif /* SDLPP_COLLISION_HPP */

