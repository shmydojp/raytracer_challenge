#include <cmath>
#include "catch.hpp"
#include "tuple.h"

using namespace Mido;
TEST_CASE("Test Tuple ctor and make sure memebers are initalized properly"){
    Tuple _test = Tuple(4.3, -4.2, 3.1, 1.0);

    REQUIRE(equal(_test.get_x(),  4.3));
    REQUIRE(equal(_test.get_y(), -4.2));
    REQUIRE(equal(_test.get_z(),  3.1));
    REQUIRE(equal(_test.get_w(),  1.0));
}

TEST_CASE("test create_point"){
    Tuple _test = create_point(4.3, -4.2, 3.1);

    REQUIRE(equal(_test.get_x(),  4.3));
    REQUIRE(equal(_test.get_y(), -4.2));
    REQUIRE(equal(_test.get_z(),  3.1));
    REQUIRE(equal(_test.get_w(),  1.0));
}

TEST_CASE("test create_vector"){
    Tuple _test = create_vector(4.3, -4.2, 3.1);

    REQUIRE(equal(_test.get_x(),  4.3));
    REQUIRE(equal(_test.get_y(), -4.2));
    REQUIRE(equal(_test.get_z(),  3.1));
    REQUIRE(equal(_test.get_w(),  0.0));
}

TEST_CASE("test tuple_equal_operator"){
    Tuple lhs =   Tuple(1.0, 2.0, 3.0, 1.0);
    Tuple rhs_1 = Tuple(1.0, 2.0, 3.0, 1.0);
    Tuple rhs_2 = Tuple(2.0, 1.0, 4.0, 0.0);

    REQUIRE(lhs == rhs_1);
    REQUIRE(!(lhs == rhs_2));
}

TEST_CASE("test tuple_add_operator"){
    Tuple point  = Tuple(3.0, -2.0, 5.0, 1.0);
    Tuple vector = Tuple(-2.0, 3.0, 1.0, 0.0);
    Tuple result = Tuple(1.0, 1.0, 6.0, 1.0);

    REQUIRE(point + vector == result);
}

TEST_CASE("test tuple_sub_operator"){
    // first test
    Tuple tup_one  = create_point(3, 2, 1);
    Tuple tup_two  = create_point(5, 6, 7);
    Tuple result   = create_vector(-2, -4, -6);

    REQUIRE(tup_one - tup_two == result);
    tup_one = create_point(3, 2, 1);
    tup_two = create_vector(5, 6, 7);
    result  = create_point(-2, -4, -6);

    REQUIRE(tup_one - tup_two == result);

    // third test
    tup_one = create_vector(3, 2, 1);
    tup_two = create_vector(5, 6, 7);
    result  = create_vector(-2 , -4, -6);

    REQUIRE(tup_one - tup_two == result);
}

TEST_CASE("test tuple_negate"){
    Tuple tup    = create_vector(1, -2, 3);
    Tuple result = create_vector(-1, 2, -3);

    REQUIRE(-tup == result
            );
}
TEST_CASE("test tuple_multiply"){
    Tuple tup = Tuple(1, -2, 3, -4);

    Tuple result_one = Tuple(3.5, -7, 10.5, -14);
    Tuple result_two = Tuple(0.5, -1, 1.5, -2);

    double scalar = 3.5;
    double fract  = 0.5;

    REQUIRE((tup * scalar == result_one));
    REQUIRE((scalar * tup == result_one));
    REQUIRE((fract * tup == result_two));
    REQUIRE((tup * fract == result_two));
 }

TEST_CASE("test tuple_divide"){
    Tuple tup = Tuple(1, -2, 3, -4);
    Tuple result = Tuple(0.5, -1, 1.5, -2);

    double scalar = 2.0;

    REQUIRE(tup / scalar == result);
}

TEST_CASE("test tuple_magnitude"){
    Tuple tup = create_vector(1, 0, 0);

    REQUIRE(equal(tuple_magnitude(tup), 1.0));

    tup = create_vector(0, 1, 0);
    REQUIRE(equal(tuple_magnitude(tup), 1.0));

    tup = create_vector(0, 0, 1);
    REQUIRE(equal(tuple_magnitude(tup), 1.0));

    tup = create_vector(1, 2, 3);
    REQUIRE(equal(tuple_magnitude(tup), std::sqrt(14)));

    tup = create_vector(-1, -2, -3);
    REQUIRE(equal(tuple_magnitude(tup), std::sqrt(14)));
}

TEST_CASE("test tuple_normalize"){
    Tuple tup = create_vector(4, 0, 0);
    Tuple unit_tup = create_vector(1, 0, 0);

    REQUIRE(tuple_normalize(tup) == unit_tup);
    tup = create_vector(1, 2, 3);
    unit_tup = create_vector(0.26726, 0.53452, 0.80178);
    REQUIRE(tuple_normalize(tup) == unit_tup);
}

TEST_CASE("test tuple_dot"){
    Tuple tup_one = create_vector(1, 2, 3);
    Tuple tup_two = create_vector(2, 3, 4);
    double result = 20.0;

    REQUIRE(equal(tuple_dot(tup_one, tup_two), result));
 }

TEST_CASE("test tuple_cross"){
    Tuple tup_one = create_vector(1, 2, 3);
    Tuple tup_two = create_vector(2, 3, 4);
    Tuple result = create_vector(-1, 2, -1);

    REQUIRE(tuple_cross(tup_one, tup_two) == result);
    result = -result;
    REQUIRE(tuple_cross(tup_two, tup_one) == result);
 }
