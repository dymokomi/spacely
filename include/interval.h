#pragma once
#include "constants.h"
namespace spacely {
    class Interval {
        public:
            double min, max;

            Interval();

            Interval(double min, double max);
            Interval(const Interval& a, const Interval& b);
            double size() const;
            bool contains(double x) const ;
            bool surrounds(double x) const;
            bool intersects(const Interval& other) const;
            double clamp(double x) const ;
            Interval expand(double delta) const;
            static const Interval empty, universe;
    };
}