#include "matrix.h"
#include "tuple.h"
#include "catch.hpp"

using namespace Mido;
TEST_CASE("test_matrix_create"){
    Matrix4x4 mat4(1.0, 5.5, 9.0, 13.5,
                   2.0, 6.5, 10.0, 14.5,
                   3.0, 7.5, 11.0, 15.5,
                   4.0, 8.5, 12.0, 16.5);

    Matrix3x3 mat3(-3.0, 1.0, 0.0,
                   5.0,-2.0,-1.0,
                   0.0,-7.0, 1.0);

    Matrix2x2 mat2(-3.0, 1.0,
                   5.0,-2.0);

    // test for Matrix4x4
    REQUIRE(equal(mat4(0,0), 1.0));

    REQUIRE(equal(mat4(0,3), 4.0));

    REQUIRE(equal(mat4(1,0), 5.5));

    REQUIRE(equal(mat4(1,2), 7.5));

    REQUIRE(equal(mat4(2,2), 11.0));

    REQUIRE(equal(mat4(3,0), 13.5));

    REQUIRE(equal(mat4(3,2), 15.5));

    // test for Matrix3x3
    REQUIRE(equal(mat3(0,0), -3.0));

    REQUIRE(equal(mat3(0,0), -3.0));

    REQUIRE(equal(mat3(0,0), -3.0));

    // test for Matrix2x2
    REQUIRE(equal(mat2(0,0), -3.0));
    REQUIRE(equal(mat2(0,1), 5.0));
    REQUIRE(equal(mat2(1,0), 1.0));
    REQUIRE(equal(mat2(1,1), -2.0));
}

TEST_CASE("test_matrix_equal"){
    Matrix4x4 mat4(1.0, 5.5, 9.0, 13.5,
                   2.0, 6.5, 10.0, 14.5,
                   3.0, 7.5, 11.0, 15.5,
                   4.0, 8.5, 12.0, 16.5);

    Matrix3x3 mat3(-3.0, 1.0, 0.0,
                   5.0,-2.0,-1.0,
                   0.0,-7.0, 1.0);

    Matrix2x2 mat2(-3.0, 1.0,
                   5.0,-2.0);

    REQUIRE(mat4 == mat4);
    REQUIRE(mat3 == mat3);
    REQUIRE(mat2 == mat2);

}

TEST_CASE("test_matrix_mult"){
    Matrix4x4 mat_one(1.0, 5.0, 9.0, 5.0,
                      2.0, 6.0, 8.0, 4.0,
                      3.0, 7.0, 7.0, 3.0,
                      4.0, 8.0, 6.0, 2.0);

    Matrix4x4 mat_two(-2.0, 3.0, 4.0, 1.0,
                      1.0, 2.0, 3.0, 2.0,
                      2.0, 1.0, 6.0, 7.0,
                      3.0, -1.0, 5.0, 8.0);

    Matrix4x4 mat_result(20, 44, 40, 16,
                         22, 54, 58, 26,
                         50, 114, 110, 46,
                         48, 108, 102, 42);

    REQUIRE(mat_mult(mat_one, mat_two) == mat_result);
}

TEST_CASE("test_mat_tup_mult"){
    Matrix4x4 mat_one(1, 2, 8, 0,
                      2, 4, 6, 0,
                      3, 4, 4, 0,
                      4, 2, 1, 1);

    Tuple tup_one(1, 2, 3, 1);
    Tuple results(18, 24, 33, 1);

    REQUIRE(mat_mult(mat_one, tup_one) == results);
}

TEST_CASE("test_mat_transpose"){
    Matrix4x4 mat_one(0, 9, 1, 0,
                      9, 8, 8, 0,
                      3, 0, 5, 5,
                      0, 8, 3, 8);
    Matrix4x4 mat_trans(0, 9, 3, 0,
                        9, 8, 0, 8,
                        1, 8, 5, 3,
                        0, 0, 5, 8);

    REQUIRE(mat_transpose(mat_one) == mat_trans);
}

TEST_CASE("test_mat_determinant"){
    Matrix2x2 mat(1, -3, 5, 2);
    REQUIRE(equal(mat_determinant(mat), 17.0f));
}

TEST_CASE("test_mat_submatrix"){
    Matrix4x4 mat_t1(-6, -8, -1, -7,
                     1,  5,  0,  1,
                     1,  8,  8, -1,
                     6,  6,  2,  1);
    Matrix3x3 mat_r1(-6, -8, -7,
                     1,  8, -1,
                     6,  6,  1);

    Matrix3x3 mat_t2(1, -3,  0,
                     5,  2,  6,
                     0,  7, -3 );
    Matrix2x2 mat_r2(-3,  0,
                     2,  6);


    REQUIRE((submatrix(mat_t1, 2, 1) == mat_r1));
}

TEST_CASE("test_mat_minor"){
    Matrix3x3 mat_t1(3, 2, 6,
                     5,-1,-1,
                     0,-7, 5);
    REQUIRE(equal(mat_minor(mat_t1, 1, 0), 25.0f));
}

TEST_CASE("test_mat_cofactor"){
    Matrix3x3 mat_t1(3, 2, 6,
                     5,-1,-1,
                     0,-7, 5);
    REQUIRE(equal(mat_minor(mat_t1, 0, 0), -12));
    REQUIRE(equal(mat_minor(mat_t1, 1, 0), 25));

}

TEST_CASE("test_mat_determinant_two"){
    Matrix3x3 mat_t1(1,-5, 2,
                     2, 8, 6,
                     6,-4, 4);
    Matrix4x4 mat_t2(-2,-3, 1,-6,
                     -8, 1, 2, 7,
                     3, 7,-9, 7,
                     5, 3, 6,-9);

    REQUIRE(equal(mat_cofactor(mat_t1, 0, 0), 56));
    REQUIRE(equal(mat_cofactor(mat_t1, 0, 1), 12));
    REQUIRE(equal(mat_cofactor(mat_t1, 0, 2), -46));
    REQUIRE(equal(mat_determinant(mat_t1), -196));

    REQUIRE(equal(mat_cofactor(mat_t2, 0, 0), 690));
    REQUIRE(equal(mat_cofactor(mat_t2, 0, 1), 447));
    REQUIRE(equal(mat_cofactor(mat_t2, 0, 2), 210));
    REQUIRE(equal(mat_cofactor(mat_t2, 0, 3), 51));
    REQUIRE(equal(mat_determinant(mat_t2), -4071));
}

TEST_CASE("test_mat_inverse"){
    Matrix4x4 mat_t1(8, 7,-6,-3,
                     -5, 5, 0, 0,
                     9, 6, 9,-9,
                     2, 1, 6,-4);
    Matrix4x4 inv(-0.15385, -0.07692,  0.35897, -0.69231,
                  -0.15385,  0.12308,  0.35897, -0.69231,
                  -0.28205,  0.02564,  0.43590, -0.76923,
                  -0.53846,  0.03077,  0.92308, -1.92308);

    REQUIRE(mat_inverse(mat_t1) == inv);

}
