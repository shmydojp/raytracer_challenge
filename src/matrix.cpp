#include <iomanip>
#include "matrix.h"

using namespace Mido;

Matrix4x4::Matrix4x4()
: m_val{1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f}
{
}

Matrix4x4::Matrix4x4(float val)
: m_val{val, 0.0f, 0.0f, 0.0f,
        0.0f, val, 0.0f, 0.0f,
        0.0f, 0.0f, val, 0.0f,
        0.0f, 0.0f, 0.0f, val}
{
}

Matrix4x4::~Matrix4x4(){}

Matrix4x4::Matrix4x4(float x0, float x1, float x2, float x3,
                     float y0, float y1, float y2, float y3,
                     float z0, float z1, float z2, float z3,
                     float w0, float w1, float w2, float w3)
: m_val{x0, y0, z0, w0,
        x1, y1, z1, w1,
        x2, y2, z2, w2,
        x3, y3, z3, w3}
{
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& rhs){
    if(this != &rhs){
        for(int c = 0; c < SIZE; ++c){
            for(int r = 0; r < SIZE; ++r){
                m_val[r][c] = rhs(r,c);
            }
        }
    }
    return *this;
}

float& Matrix4x4::operator()(int r, int c){
    assert((r >= 0 && r <= 3) && (c >= 0 && c <= 3)
        && "(Matrix4x4): index out of bounds");
    return m_val[r][c];
}

float Matrix4x4::operator()(int r, int c) const {
    assert((r >= 0 && r <= 3) && (c >= 0 && c <= 3)
        && "(Matrix4x4): index out of bounds");
    return m_val[r][c];
}

Matrix3x3::Matrix3x3()
: m_val{1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f}
{
}

Matrix3x3::Matrix3x3(float val)
: m_val{val, 0.0f, 0.0f,
        0.0f, val, 0.0f,
        0.0f, 0.0f, val}
{
}

Matrix3x3::~Matrix3x3(){}

Matrix3x3::Matrix3x3(float x0, float x1, float x2,
                     float y0, float y1, float y2,
                     float z0, float z1, float z2)
: m_val{x0, y0, z0,
        x1, y1, z1,
        x2, y2, z2}
{
}

float& Matrix3x3::operator()(int r, int c){
    assert((r >= 0 && r <= 2) && (c >= 0 && c <= 2)
        && "(Matrix3x3): index out of bounds");

    return m_val[r][c];
}

float Matrix3x3::operator()(int r, int c) const{
    assert((r >= 0 && r <= 2) && (c >= 0 && c <= 2)
        && "(Matrix3x3): index out of bounds");

    return m_val[r][c];
}

Matrix2x2::Matrix2x2()
: m_val{1.0f, 0.0f,
        0.0f, 1.0f}
{
}

Matrix2x2::Matrix2x2(float val)
: m_val{val,  0.0f,
        0.0f, val}
{
}

Matrix2x2::~Matrix2x2(){}

Matrix2x2::Matrix2x2(float x0, float x1,
                     float y0, float y1)
: m_val{x0, y0,
        x1, y1}
{
}

float& Matrix2x2::operator()(int r, int c){
    assert((r >= 0 && r <= 1) && (c >= 0 && c <= 1)
        && "(Matrix2x2): index out of bounds");

    return m_val[r][c];
}

float Matrix2x2::operator()(int r, int c) const {
    assert((r >= 0 && r <= 1) && (c >= 0 && c <= 1)
        && "(Matrix2x2): index out of bounds");

    return m_val[r][c];
}

Tuple Mido::mat_mult(const Matrix4x4& mat_one, const Tuple& tup_one){
    float result[4]{0};

    for(int r = 0; r < 4; ++r){
        for(int i = 0; i < 4; ++i){
            result[r] += (mat_one(r,i) * tup_one.get_val(i));
        }
    }

    return Tuple(result);
}

Matrix4x4 Mido::mat_transpose(const Matrix4x4& mat){
    Matrix4x4 trans(0.0f);
    for(int r = 0; r < 4; ++r){
        for(int i = 0; i < 4; ++i){
            trans(i,r) = mat(r,i);
        }
    }
    return trans;
}

Matrix3x3 Mido::submatrix(const Matrix4x4& mat, int row, int col){
    Matrix3x3 mat3;
    int m_c = 0, m_r = 0;

    for(int i = 0; i < 4; ++i){
        if(i == row) continue;
        for(int j = 0; j < 4; ++j){
            if(j == col) continue;
            mat3(m_r, m_c) = mat(i, j);
            ++m_c;
        }
        m_c = 0;
        ++m_r;
    }
    return mat3;
}

Matrix2x2 Mido::submatrix(const Matrix3x3& mat, int row, int col){
    Matrix2x2 mat2;
    int m_c = 0, m_r = 0;

    for(int i = 0; i < 3; ++i){
        if(i == row) continue;
        for(int j = 0; j < 3; ++j){
            if(j == col) continue;
            mat2(m_r, m_c) = mat(i, j);
            ++m_c;
        }
        m_c = 0;
        ++m_r;
    }
    return mat2;
}

float Mido::mat_minor(const Matrix3x3& mat, int row, int col){
    return mat_determinant(submatrix(mat, row, col));
}

float Mido::mat_minor(const Matrix4x4& mat, int row, int col){
    return mat_determinant(submatrix(mat, row, col));
}

float Mido::mat_determinant(const Matrix2x2& mat){
        return mat(0,0)*mat(1,1) - mat(0,1)*mat(1,0);
}

float Mido::mat_determinant(const Matrix3x3& mat){
    return mat_cofactor(mat, 0, 0) * mat(0,0)
        +  mat_cofactor(mat, 0, 1) * mat(0,1)
        +  mat_cofactor(mat, 0, 2) * mat(0,2);
}

float Mido::mat_determinant(const Matrix4x4& mat){
    return mat_cofactor(mat, 0, 0) * mat(0,0)
        +  mat_cofactor(mat, 0, 1) * mat(0,1)
        +  mat_cofactor(mat, 0, 2) * mat(0,2)
        +  mat_cofactor(mat, 0, 3) * mat(0,3);
}

float Mido::mat_cofactor(const Matrix3x3& mat, int row, int col){
    return (((row + col) % 2 == 0) ? 1 : -1) * mat_minor(mat, row, col);
}

float Mido::mat_cofactor(const Matrix4x4& mat, int row, int col){
    return (((row + col) % 2 == 0) ? 1 : -1) * mat_minor(mat, row, col);
}

Matrix4x4 Mido::mat_inverse(const Matrix4x4& mat){
    auto det = mat_determinant(mat);
    assert(det != 0 &&
            "Matrix is not inversible, det(mat) = 0");
    Matrix4x4 cofacts(0.0f);

    for(int row = 0; row < mat.SIZE; ++row){
        for(int col = 0; col < mat.SIZE; ++col){
            cofacts(row, col) = mat_cofactor(mat, row, col);
        }
    }
    Matrix4x4 inv = mat_transpose(cofacts);
    {}
    for(int row = 0; row < mat.SIZE; ++row){
        for(int col = 0; col < mat.SIZE; ++col){
            inv(row, col) = inv(row, col) / det;
        }
    }
    return inv;
}

namespace Mido{
bool operator==(const Matrix4x4& lhs, const Matrix4x4& rhs){
    bool is_equal = true;

    for(int c = 0; c < lhs.get_col(); ++c){
        for(int r = 0; r < lhs.get_row(); ++r){
            is_equal = equal(lhs(r,c), rhs(r,c));
            if(!is_equal) break;
        }
        if(!is_equal) break;
    }
    return is_equal;
}

bool operator==(const Matrix3x3& lhs, const Matrix3x3& rhs){
    bool is_equal = true;

    for(int c = 0; c < lhs.get_col(); ++c){
        for(int r = 0; r < lhs.get_row(); ++r){
            is_equal = equal(lhs(r,c), rhs(r,c));
            if(!is_equal) break;
        }
        if(!is_equal) break;
    }
    return is_equal;
}


bool operator==(const Matrix2x2& lhs, const Matrix2x2& rhs){
    bool is_equal = true;

    for(int c = 0; c < lhs.get_col(); ++c){
        for(int r = 0; r < lhs.get_row(); ++r){
            is_equal = equal(lhs(r,c), rhs(r,c));
            if(!is_equal) break;
        }
        if(!is_equal) break;
    }
    return is_equal;
}


std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat){
    os << std::fixed << std::setw(4) \
       << std::setprecision(4) << std::setfill('0');

    os << "Mat4(\n";
    for(int r = 0; r < Matrix4x4::SIZE; ++r){
        for(int c = 0; c < Matrix4x4::SIZE; ++c){
            os << mat(r,c) << ' ';
        }
        os << '\n';
    }
    os << ")\n";
    return os;
}

}
