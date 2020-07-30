//
// Created by Robert on 3/7/17.
//

#ifndef CSC_412_MANDELBROT_COMPLEXNUMBER_H
#define CSC_412_MANDELBROT_COMPLEXNUMBER_H

#include <math.h>

struct ComplexNumber {
    double real;
    double imaginary;
};

struct ComplexNumber add(struct ComplexNumber *ComplexNumber1, struct ComplexNumber *ComplexNumber2);

struct ComplexNumber square(struct ComplexNumber *complexNumber);

double magnitude(struct ComplexNumber *complexNumber);

#endif //CSC_412_MANDELBROT_COMPLEXNUMBER_H
