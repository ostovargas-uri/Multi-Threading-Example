//
// Created by robert on 3/13/17.
//

#ifndef CSC_412_MANDELBROT_IMAGEWRITER_H
#define CSC_412_MANDELBROT_IMAGEWRITER_H

#include <stdio.h>

double scalePixelXToReal(int imageWidth, int imageX);
double scalePixelYToImaginary(int imageHeight, int imageY);
void writePPM(char *fileName, int imageWidth, int imageHeight, int ***raster);

#endif //CSC_412_MANDELBROT_IMAGEWRITER_H
