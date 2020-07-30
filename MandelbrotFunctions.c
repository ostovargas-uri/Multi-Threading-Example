//
// Created by robert on 3/13/17.
//

#include "MandelbrotFunctions.h"

#ifndef DIVERGENCE_LIMIT
#define DIVERGENCE_LIMIT 1002
#endif

/**
 * Tests whether a point lies within the mandelbrot set.
 * @param c - The point in the complex plane we want to test.
 * @param xPosition - The x position on the image raster.
 * @param yPosition - The y position on the image raster.
 */
void testBehavior(struct ComplexNumber c, int xPosition, int yPosition, int **raster) {
    // Two structs to hold our complex values.
    struct ComplexNumber z;
    struct ComplexNumber m;

    // Zero out the values of the struct, since the compiler might not do it for us.
    z.real = 0;
    z.imaginary = 0;

    m.real = 0;
    m.imaginary = 0;

    // Square z
    z = square(&z);

    // Add z and c
    m = add(&z, &c);

    // Iterate over this point 1000 times to see if it diverges to infinity.
    for (int i = 1; i < DIVERGENCE_LIMIT; i++) {
        if (magnitude(&m) > 2) {
            raster[yPosition][xPosition] = (0x567F7F / (i));
            break;
        }

        z = square(&z);
        m = add(&z, &c);
        z = m;

        if (i == DIVERGENCE_LIMIT - 1) {
            raster[yPosition][xPosition] = 0x000000;
        }
    }

}