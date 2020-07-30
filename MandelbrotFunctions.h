//
// Created by robert on 3/13/17.
//

#ifndef CSC_412_MANDELBROT_MANDELBROTFUNCTIONS_H
#define CSC_412_MANDELBROT_MANDELBROTFUNCTIONS_H

#include "ComplexNumber.h"
#include <pthread.h>

struct LocationInfo {
    double panX;
    double panY;
    double zoom;
};

void testBehavior(struct ComplexNumber complexNumber, int xPosition, int yPosition, int** raster);

#endif //CSC_412_MANDELBROT_MANDELBROTFUNCTIONS_H
