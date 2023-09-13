#ifndef _TUPLE_H
#define _TUPLE_H

#include <cassert>
#include <cmath>
#include <iostream>

#include "constants.h"

namespace Mido{

    inline bool equal(double v1, double v2){
        return std::abs(v1 - v2) < constants::EPISILON;
    }
    // END OF TODO

    struct Tuple
    {
        float _vals[4];

        Tuple(float x, float y, float z, float w)
            : _vals{x, y, z, w}
        {
        }

        Tuple(const Tuple& t)
            : _vals{t._vals[0], t._vals[1], t._vals[2], t._vals[3]}
        {
        }

        Tuple(const float vals[4])
            : _vals{vals[0], vals[1], vals[2], vals[3]}
        {
        }
        Tuple& operator=(const Tuple& rhs){
            if(this == &rhs) return *this;

            this->_vals[0] = rhs._vals[0];
            this->_vals[1] = rhs._vals[1];
            this->_vals[2] = rhs._vals[2];
            this->_vals[3] = rhs._vals[3];

            return *this;
        }

        inline float get_val(int index) const {
            assert(index >= 0 && index <= 3 && "Index out of bounds (0-3)\n");
            return _vals[index];
        }

        inline float get_x() const {
            return this->_vals[0];
        }

        inline float get_y() const {
            return this->_vals[1];
        }

        inline float get_z() const {
            return this->_vals[2];
        }

        inline float get_w() const {
            return this->_vals[3];
        }

        inline float& set_x(){
            return this->_vals[0];
        }

        inline float& set_y(){
            return this->_vals[1];
        }

        inline float& set_z(){
            return this->_vals[2];
        }

        friend inline bool operator==(const Tuple& lhs, const Tuple& rhs){
            bool is_equal = true;
            for(int i = 0; i < 4; ++i){
                is_equal = equal(lhs._vals[i], rhs._vals[i]);
                if(!is_equal) break;
            }
            return is_equal;
        }

        friend inline Tuple operator+(const Tuple& lhs, const Tuple& rhs){
            return Tuple(lhs._vals[0] + rhs._vals[0],
                         lhs._vals[1] + rhs._vals[1],
                         lhs._vals[2] + rhs._vals[2],
                         lhs._vals[3] + rhs._vals[3]);
        }

        friend inline Tuple operator-(const Tuple& lhs, const Tuple& rhs){
            assert(!(lhs._vals[3] == 0 && rhs._vals[3] == 1)
                && "(Tuple::operator-): Attempting Vector - Point (illegal)");

            return Tuple(lhs._vals[0] - rhs._vals[0],
                         lhs._vals[1] - rhs._vals[1],
                         lhs._vals[2] - rhs._vals[2],
                         lhs._vals[3] - rhs._vals[3]);
        }

        friend inline Tuple operator-(const Tuple& rhs){
            return Tuple(-rhs._vals[0],
                         -rhs._vals[1],
                         -rhs._vals[2],
                         -rhs._vals[3]);
        }

        friend inline Tuple operator*(const Tuple& lhs, double rhs){
            return Tuple(lhs._vals[0] * rhs,
                         lhs._vals[1] * rhs,
                         lhs._vals[2] * rhs,
                         lhs._vals[3] * rhs);
        }

        friend inline Tuple operator*(const Tuple& lhs, const Tuple& rhs){
            return Tuple(lhs._vals[0] * rhs._vals[0],
                         lhs._vals[1] * rhs._vals[1],
                         lhs._vals[2] * rhs._vals[2],
                         lhs._vals[3] * rhs._vals[3]);
        }

        friend inline Tuple operator*(double lhs, const Tuple& rhs){
            return Tuple(rhs._vals[0] * lhs,
                         rhs._vals[1] * lhs,
                         rhs._vals[2] * lhs,
                         rhs._vals[3] * lhs);
        }

        friend inline Tuple operator/(const Tuple& lhs, double rhs){
            return Tuple(lhs._vals[0] / rhs,
                         lhs._vals[1] / rhs,
                         lhs._vals[2] / rhs,
                         lhs._vals[3] / rhs);
        }

        friend std::ostream& operator<<(std::ostream& os, const Tuple rhs){
            os << "Tuple("
               << rhs._vals[0] << ", " << rhs._vals[1] << ", "
               << rhs._vals[2] << ", " << rhs._vals[3] << ")";

            return os;
        }

    };

    inline Tuple create_point(double x, double y, double z){
        return Tuple(x,y,z,1);
    }

    inline Tuple create_vector(double x, double y, double z){
        return Tuple(x,y,z,0);
    }

    inline double tuple_magnitude(const Tuple& tup){
        using std::sqrt;

        assert(tup._vals[3] != 1
            && "(Tuple::magnitude): Attempting to get mag of a point");

        return sqrt( tup._vals[0] * tup._vals[0]
                   + tup._vals[1] * tup._vals[1]
                   + tup._vals[2] * tup._vals[2]
                   + tup._vals[3] * tup._vals[3] );
    }

    inline double tuple_dot(const Tuple& lhs, const Tuple& rhs){
        return (  lhs._vals[0] * rhs._vals[0]
                + lhs._vals[1] * rhs._vals[1]
                + lhs._vals[2] * rhs._vals[2]
                + lhs._vals[3] * rhs._vals[3] );
    }

    inline Tuple tuple_normalize(const Tuple& tup){
        double tup_mag = tuple_magnitude(tup);
        return Tuple( tup._vals[0] / tup_mag,
                      tup._vals[1] / tup_mag,
                      tup._vals[2] / tup_mag,
                      tup._vals[3] / tup_mag);
    }

    inline Tuple tuple_cross(const Tuple& lhs, const Tuple& rhs){
        return create_vector(
                     lhs._vals[1] * rhs._vals[2] - lhs._vals[2] * rhs._vals[1],
                     lhs._vals[2] * rhs._vals[0] - lhs._vals[0] * rhs._vals[2],
                     lhs._vals[0] * rhs._vals[1] - lhs._vals[1] * rhs._vals[0]
                     );
    }
}
#endif
