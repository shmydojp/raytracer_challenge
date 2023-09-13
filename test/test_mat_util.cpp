#include "mat_util.h"
#include "tuple.h"
#include "catch.hpp"

using namespace Mido;
TEST_CASE("test mat_util_translation"){
    Matrix4x4 trans = translation(5.0, -3.0, 2.0);
    Tuple point = create_point(-3, 4, 5);
    Tuple result = mat_mult(trans, point);

    REQUIRE(equal(result.get_x(), 2.0));
    REQUIRE(equal(result.get_y(), 1.0));
    REQUIRE(equal(result.get_z(), 7.0));
    REQUIRE(equal(result.get_w(), 1.0));
}
TEST_CASE("test mat_util_inv_translation"){
    Matrix4x4 trans = translation(5.0, -3.0, 2.0);
    Matrix4x4 inv = mat_inverse(trans);
    Tuple point = create_point(-3.0, 4.0, 5.0);

    Tuple result = mat_mult(inv,point);
    REQUIRE(equal(result.get_x(), -8.0));
    REQUIRE(equal(result.get_y(),  7.0));
    REQUIRE(equal(result.get_z(),  3.0));
}

TEST_CASE("test mat_util_vec_translation"){
    Matrix4x4 trans = translation(5.0, -3.0, 2.0);
    Tuple vector = create_vector(-3, 4, 5);
    Tuple result = mat_mult(trans, vector);

    REQUIRE(vector == result);
}

TEST_CASE("test mat_util_scale"){
    Matrix4x4 scale = mat_scale(2, 3, 4);
    Tuple point = create_point(-4, 6, 8);
    Tuple result = mat_mult(scale, point);

    REQUIRE(result == create_point(-8, 18, 32));

    Tuple vector = create_vector(-4, 6, 8);
    result = mat_mult(scale, vector);

    REQUIRE(result == create_vector(-8, 18, 32));

    Matrix4x4 inv = mat_inverse(scale);
    result = mat_mult(inv, vector);

    REQUIRE(result == create_vector(-2, 2, 2));

    scale = mat_scale(-1, 1, 1);
    point = create_point(2,3,4);
    result = mat_mult(scale, point);

    REQUIRE(result == create_point(-2,3,4));

}

TEST_CASE("test mat_util_axes_rotations"){
    Matrix4x4 half_quarter = mat_rotation_x(MIDO_PI/4);
    Matrix4x4 full_quarter = mat_rotation_x(MIDO_PI/2);
    double root_2 = std::sqrt(2) / 2;

    // x-axis rotation first
    Tuple point = create_point(0, 1, 0);
    Tuple result = mat_mult(half_quarter, point);
    REQUIRE(result == create_point(0, root_2 , root_2));

    result = mat_mult(full_quarter, point);
    REQUIRE(result == create_point(0,0,1));

    // inverse of x rotation rotates in opposite direction
    Matrix4x4 inv = mat_inverse(half_quarter);
    result = mat_mult(inv, point);
    REQUIRE(result == create_point(0, root_2, -root_2));

    // y-axis rotation
    point = create_point(0, 0, 1);
    half_quarter = mat_rotation_y(MIDO_PI/4);
    full_quarter = mat_rotation_y(MIDO_PI/2);
    result = mat_mult(half_quarter, point);

    REQUIRE(result == create_point(root_2, 0, root_2));

    result = mat_mult(full_quarter, point);
    REQUIRE(result == create_point(1, 0, 0));

    // z-axis rotation
    point = create_point(0, 1, 0);
    half_quarter = mat_rotation_z(MIDO_PI/4);
    full_quarter = mat_rotation_z(MIDO_PI/2);

    result = mat_mult(half_quarter, point);
    REQUIRE(result == create_point(-root_2, root_2, 0));

    result = mat_mult(full_quarter, point);
    REQUIRE(result == create_point(-1, 0, 0));

}

TEST_CASE("test mat_util_shearing"){
    Tuple point = create_point(2,3,4);
    Matrix4x4 mat = mat_shearing(1,0,0,0,0,0);

    Tuple result = mat_mult(mat, point);
    REQUIRE(result == create_point(5,3,4));

    mat = mat_shearing(0,1,0,0,0,0);
    result = mat_mult(mat, point);
    REQUIRE(result == create_point(6,3,4));

    mat = mat_shearing(0,0,1,0,0,0);
    result = mat_mult(mat, point);
    REQUIRE(result == create_point(2,5,4));

    mat = mat_shearing(0,0,0,1,0,0);
    result = mat_mult(mat, point);
    REQUIRE(result == create_point(2,7,4));

    mat = mat_shearing(0,0,0,0,1,0);
    result = mat_mult(mat, point);
    REQUIRE(result == create_point(2,3,6));

    mat = mat_shearing(0,0,0,0,0,1);
    result = mat_mult(mat, point);
    REQUIRE(result == create_point(2,3,7));
}
