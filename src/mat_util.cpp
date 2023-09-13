#include <cmath>
#include "mat_util.h"

using namespace Mido;

Matrix4x4 Mido::translation(Mido::Tuple trans){
    Matrix4x4 mat(1.0f);
    mat(0,3) = trans.get_x();
    mat(1,3) = trans.get_y();
    mat(2,3) = trans.get_z();
    return mat;
}

Matrix4x4 Mido::translation(float x, float y, float z){
    Matrix4x4 mat(1.0f);
    mat(0,3) = x;
    mat(1,3) = y;
    mat(2,3) = z;
    return mat;
}

Matrix4x4 Mido::mat_scale(Tuple scale){
    Matrix4x4 mat(1.0f);
    mat(0,0) = scale.get_x();
    mat(1,1) = scale.get_y();
    mat(2,2) = scale.get_z();
    return mat;
}

Matrix4x4 Mido::mat_scale(float x, float y, float z){
    Matrix4x4 mat(1.0f);
    mat(0,0) = x;
    mat(1,1) = y;
    mat(2,2) = z;
    return mat;
}

Matrix4x4 Mido::mat_rotation_x(double radians){
    using std::cos, std::sin;
    Matrix4x4 rot(
        1, 0, 0, 0,
        0, cos(radians), sin(radians), 0,
        0, -sin(radians),  cos(radians), 0,
        0, 0, 0, 1
        );

    return rot;
}

Matrix4x4 Mido::mat_rotation_y(double radians){
    using std::cos, std::sin;
    Matrix4x4 rot(
        cos(radians), 0, -sin(radians), 0,
        0, 1, 0, 0,
        sin(radians), 0, cos(radians), 0,
        0, 0, 0, 1
        );

    return rot;
}

Matrix4x4 Mido::mat_rotation_z(double radians){
    using std::cos, std::sin;
    Matrix4x4 rot(
        cos(radians), sin(radians), 0, 0,
        -sin(radians), cos(radians), 0, 0,
        0,0,1,0,
        0,0,0,1
        );

    return rot;
}

Matrix4x4 Mido::mat_shearing(float xy, float xz, float yx,
                             float yz, float zx, float zy){
    Matrix4x4 mat(1, yx, zx, 0,
                  xy, 1, zy, 0,
                  xz, yz, 1, 0,
                  0, 0, 0, 1);
    return mat;
}
