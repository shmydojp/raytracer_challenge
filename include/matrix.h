#ifndef _MATRIX_H
#define _MATRIX_H
#include <cassert>
#include <iostream>
#include "tuple.h"

namespace Mido{

    class Matrix4x4{
    public:
        Matrix4x4();
        Matrix4x4(float val);
        Matrix4x4(float x0, float x1, float x2, float x3,
                  float y0, float y1, float y2, float y3,
                  float z0, float z1, float z2, float z3,
                  float w0, float w1, float w2, float w3);
       ~Matrix4x4();

        float& operator()(int r, int c);
        float operator()(int r, int c) const;

        inline int get_row() const  { return SIZE; }
        inline int get_col() const { return SIZE; }

        Matrix4x4& operator=(const Matrix4x4& rhs);
        friend bool operator==(const Matrix4x4& lhs, const Matrix4x4& rhs);
        friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat);

        static constexpr int SIZE = 4;

    private:
        float m_val[4][4];
    };

    class Matrix3x3{
    public:
        Matrix3x3();
        Matrix3x3(float val);
        Matrix3x3(float x0, float x1, float x2,
                  float y0, float y1, float y2,
                  float z0, float z1, float z2);
       ~Matrix3x3();

        float& operator()(int r, int c);
        float operator()(int r, int c) const;

        inline int get_row() const { return SIZE; }
        inline int get_col() const { return SIZE; }

        friend bool operator==(const Matrix3x3&, const Matrix3x3&);
    private:
        float m_val[3][3];

        static constexpr int SIZE = 3;
    };

    class Matrix2x2{
    public:
        Matrix2x2();
        Matrix2x2(float val);
        Matrix2x2(float x0, float x1,
                  float y0, float y1);
       ~Matrix2x2();

        float& operator()(int r, int c);
        float operator()(int r, int c) const;

        inline int get_row() const { return SIZE; }
        inline int get_col() const { return SIZE; }

        friend bool operator==(const Matrix2x2&, const Matrix2x2&);

    private:
        float m_val[2][2];
        static constexpr int SIZE = 2;
    };

    template<typename Mat>
    Mat mat_mult(const Mat& mat_one, const Mat& mat_two){
        Mat result(0.0f);

        int row = mat_one.get_row();
        int col = mat_one.get_col();

        for(int r = 0; r < row; ++r){
            for(int c = 0; c < col; ++c){
                for(int i = 0; i < col; ++i){
                    result(r,c) += mat_one(r,i) * mat_two(i,c);
                }
            }
        }
        return result;
    }

    Tuple mat_mult(const Matrix4x4& mat_one, const Tuple& tup_one);

    Matrix4x4 mat_transpose(const Matrix4x4& mat);

    float mat_determinant(const Matrix2x2& mat);
    float mat_determinant(const Matrix3x3& mat);
    float mat_determinant(const Matrix4x4& mat);

    Matrix2x2 submatrix(const Matrix3x3& mat, int row, int col);
    Matrix3x3 submatrix(const Matrix4x4& mat, int row, int col);

    float mat_minor(const Matrix3x3&, int row, int col);
    float mat_minor(const Matrix4x4&, int row, int col);

    float mat_cofactor(const Matrix3x3&, int row, int col);
    float mat_cofactor(const Matrix4x4&, int row, int col);

    Matrix4x4 mat_inverse(const Matrix4x4& mat);
}

#endif
