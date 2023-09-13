#include "tuple.h"
#include "color.h"
#include "canvas.h"
#include "catch.hpp"

using namespace Mido;
TEST_CASE("test_canvas"){
    Canvas c(10, 20);
    Color zero;

    int width = c.getWidth();
    int height = c.getHeight();

    for(int col = 0; col < width; ++col){
        for(int row = 0; row < height; ++row){
            REQUIRE(c(col, row) == zero);
        }
    }
}
TEST_CASE("test_canvas_write_pixel"){
    Canvas c(10, 20);
    Color red(1, 0, 0);

    c(2,3) = red;
    REQUIRE(c(2,3) == red);
}

TEST_CASE("test_canvas_to_ppm"){
    Canvas c(5,3);
    Color c1(1.5, 0, 0), c2(0, 0.5, 0), c3(-0.5, 0, 1);
    c(0,0) = c1;
    c(2,1) = c2;
    c(4,2) = c3;

    REQUIRE(false);
}
