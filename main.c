//Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <unistd.h>
#endif


//User defined headers
#include "ComplexNumber.h"
#include "ImageWriter.h"
#include "MandelbrotFunctions.h"

#ifndef SIZE_WIDTH
#define SIZE_WIDTH 1000
#endif

#ifndef SIZE_HEIGHT
#define SIZE_HEIGHT 1000
#endif

//Function prototypes
void allocateArray(int ***raster);
void freeArray(int ***raster);
void serialMandelbrot(struct LocationInfo *info, int ***raster);

/**
 * Main function, the starting point of the program.
 * @param argc The number of arguments received from the command line.
 * @param argv An array of the arguments pass from the command line.
 * @return A status code indicating success or failure.
 */
int main(int argc, char *argv[]) {

    struct LocationInfo locationInfo;

    int **raster;

    if (argc == 1) {
        printf("This program requires three arguments in the following order: panX panY zoom\n");
        return -1;
    }

    locationInfo.panX = atof(argv[1]);
    locationInfo.panY = atof(argv[2]);
    locationInfo.zoom = atof(argv[3]);

    allocateArray(&raster);

    time_t start = time(NULL);

    serialMandelbrot(&locationInfo, &raster);

    time_t end = time(NULL);

    writePPM("Mandelbrot Serial.ppm", SIZE_WIDTH, SIZE_HEIGHT, &raster);

    double serialTime = difftime(end, start);

    printf("The total serial execution time was: %f seconds.\n", serialTime);

    freeArray(&raster);

    return 0;

}

/**
 * Calculates the mandelbrot set in a serial fashion.
 * @param info A struct reference which contains what part of the set to calculate.
 * @param raster A reference to the image raster.
 */
void serialMandelbrot(struct LocationInfo *info, int ***raster) {
    struct ComplexNumber c;

    c.real = 0;
    c.imaginary = 0;

    for (int i = 0; i < SIZE_HEIGHT; i++) {
        c.imaginary = scalePixelYToImaginary(SIZE_HEIGHT, i) * info->zoom + info->panY;
        for (int j = 0; j < SIZE_WIDTH; j++) {
            c.real = scalePixelXToReal(SIZE_WIDTH, j) * info->zoom  + info->panX;
            testBehavior(c, j, i, (*raster));
        }
    }
}

/**
 * Allocates an array of SIZE_HEIGHT by SIZE_WIDTH.
 * @param raster A reference to the first location in the array.
 */
void allocateArray(int ***raster){

    (*raster) = calloc(SIZE_HEIGHT, sizeof(int *));

    for (int i = 0; i < SIZE_HEIGHT; ++i) {
        (*raster)[i] = calloc(SIZE_WIDTH, sizeof(int));
    }

}

/**
 * Frees an array of SIZE_HEIGHT by SIZE_WIDTH.
 * @param raster A reference to the first location in the array.
 */
void freeArray(int ***raster) {

    for (int i = 0; i < SIZE_HEIGHT; ++i) {
        free((*raster)[i]);
    }

    free((*raster));

}
