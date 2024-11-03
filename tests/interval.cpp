#include "doctest/doctest.h"
#include "../include/interval.h"

using namespace spacely;

TEST_CASE("Interval Contains") {    
    Interval i1(0, 2);
    CHECK(!i1.contains(-1));
    CHECK(i1.contains(0));
    CHECK(i1.contains(1));
    CHECK(i1.contains(2));
    CHECK(!i1.contains(3));
}

TEST_CASE("Interval Intersects") {
    Interval i1(0, 2);
    Interval i2(1, 3);
    CHECK(i1.intersects(i2));

    Interval i3(3, 4);
    CHECK(!i1.intersects(i3));
}

TEST_CASE("Interval Clamp") {
    Interval i1(0, 2);
    CHECK(i1.clamp(1) == 1);
    CHECK(i1.clamp(3) == 2);
    CHECK(i1.clamp(-1) == 0);
}

TEST_CASE("Interval Expand") {
    Interval i1(0, 2);
    Interval i2 = i1.expand(1);
    CHECK(i2.min == -0.5);
    CHECK(i2.max == 2.5);
}

TEST_CASE("Interval Surrounds") {
    Interval i1(0, 2);
    CHECK(i1.surrounds(1));
    CHECK(!i1.surrounds(3));
}

TEST_CASE("Interval Size") {
    Interval i1(0, 2);
    CHECK(i1.size() == 2);

    Interval i2(2, 0);
    CHECK(i2.size() == -2);
}