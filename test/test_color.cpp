#include <cassert>
#include "catch.hpp"
#include "color.h"

using namespace Mido;
TEST_CASE("test_create_color"){
    Color c = createColor(-0.5, 0.4, 1.7);

    REQUIRE(equal(c.get_R(), -0.5));
    REQUIRE(equal(c.get_G(),  0.4));
    REQUIRE(equal(c.get_B(),  1.7));
}

TEST_CASE("test_color_add_operator"){
    Color c1 = createColor(0.9, 0.6, 0.75);
    Color c2 = createColor(0.7, 0.1, 0.25);
    Color result = createColor(1.6, 0.7, 1.0);

    REQUIRE(c1 + c2 == result);
}

TEST_CASE("test_color_sub_operator"){
    Color c1 = createColor(0.9, 0.6, 0.75);
    Color c2 = createColor(0.7, 0.1, 0.25);
    Color result = createColor(0.2, 0.5, 0.5);

    REQUIRE(c1 - c2 == result);
}

TEST_CASE("test_color_mult_operator"){
    Color c1 = createColor(0.2, 0.3, 0.4);
    double scalar = 2;
    Color result = createColor(0.4, 0.6, 0.8);

    REQUIRE(c1 * scalar == result);
    REQUIRE(scalar * c1 == result);

    c1 = createColor(1, 0.2, 0.4);

    Color c2 = createColor(0.9, 1.0, 0.1);
    result = c1 * c2;
    REQUIRE(c1 * c2 == result);
}
