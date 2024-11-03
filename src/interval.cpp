#include "interval.h"

namespace spacely {
    Interval::Interval() : min(+infinity), max(-infinity) {}
    Interval::Interval(double min, double max) : min(min), max(max) {}
    Interval::Interval(const Interval& a, const Interval& b) {
        // Create the interval tightly enclosing the two input intervals.
        min = a.min <= b.min ? a.min : b.min;
        max = a.max >= b.max ? a.max : b.max;
    }
    double Interval::size() const {
        return max - min;
    }

    bool Interval::contains(double x) const {
        return min <= x && x <= max;
    }
    bool Interval::intersects(const Interval& other) const {
        return min <= other.max && max >= other.min;
    }
    bool Interval::surrounds(double x) const {
        return min < x && x < max;
    }
    double Interval::clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
    Interval Interval::expand(double delta) const {
        auto padding = delta/2;
        return Interval(min - padding, max + padding);
    }
    const Interval Interval::empty    = Interval(+infinity, -infinity);
    const Interval Interval::universe = Interval(-infinity, +infinity);
}