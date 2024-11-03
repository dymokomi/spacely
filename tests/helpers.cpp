#include "doctest/doctest.h"
#include "../include/helpers.h"

using namespace spacely;

TEST_CASE("Linear to Gamma") {
    CHECK(linear_to_gamma(1.0, 2.2) == std::pow(1.0, 1/2.2));
    CHECK(linear_to_gamma(0.0, 2.2) == 0);
    CHECK(linear_to_gamma(-1.0, 2.2) == 0);
    CHECK(linear_to_gamma(1.0, 2.2) == 1);
    CHECK(linear_to_gamma(0.5, 2.2) == std::pow(0.5, 1/2.2));
}
