#ifndef _COLOR_H
#define _COLOR_H
#include "tuple.h"

namespace Mido{
    struct Color : Tuple
    {
        Color() : Tuple(0.0f,0.0f,0.0f,0.0f) {}

        Color(double r, double g, double b)
        : Tuple(r,g,b,0)
        {
        }

        Color(const Color& col)
            : Tuple(col.get_R(), col.get_G(), col.get_B(), 0)
        {
        }

        Color(const Tuple& col)
        : Tuple(col)
        {
        }

        inline double get_R() const{
            return _vals[0];
        }

        inline double get_G() const{
            return _vals[1];
        }

        inline double get_B() const{
            return _vals[2];
        }

    };

    inline Color createColor(double r, double g, double b){
        return Color(r,g,b);
    }
};
#endif
