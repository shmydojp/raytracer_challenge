#ifndef _MAT_UTIL_H
#define _MAT_UTIL_H

#include "tuple.h"
#include "matrix.h"

#define MIDO_PI 3.141592653589793

namespace Mido{
    inline double to_radians(double degree){
        return (degree/180.0) * MIDO_PI;
    }

    Matrix4x4 translation(Tuple trans);
    Matrix4x4 translation(float, float, float);
    Matrix4x4 mat_scale(Tuple scale);
    Matrix4x4 mat_scale(float, float, float);
    Matrix4x4 mat_rotation_x(double);
    Matrix4x4 mat_rotation_y(double);
    Matrix4x4 mat_rotation_z(double);
    Matrix4x4 mat_shearing(float,float,float,
                           float,float,float);
}

#endif
