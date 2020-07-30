//	Osto Vargas, Ryan Chuk
//	CSC 412 -- pthread Lab

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
//void serialMandelbrot(struct LocationInfo *info, int ***raster);
void *parallelMandelbrot(void*);

typedef struct {
	int quad_no;	//	debug
	int i_pos, height, j_pos, width;
	struct LocationInfo **infoPtr;
	int ***rasterPtr;
} image_quad;

/**
 * Main function, the starting point of the program.
 * @param argc The number of arguments received from the command line.
 * @param argv An array of the arguments pass from the command line.
 * @return A status code indicating success or failure.
 */
int main(int argc, char *argv[]) {

    struct LocationInfo *locationInfo = malloc(sizeof(struct LocationInfo));

    int **raster;

    if (argc == 1) {
        printf("This program requires three arguments in the following order: panX panY zoom\n");
        return -1;
    }

    locationInfo->panX = atof(argv[1]);
    locationInfo->panY = atof(argv[2]);
    locationInfo->zoom = atof(argv[3]);

    allocateArray(&raster);

    time_t start = time(NULL);
	
	image_quad **image = malloc(sizeof(image_quad*) * 4);
	//	top half
	for (int i = 0; i < 2; i++) {
		image[i] = malloc(sizeof(image_quad));
		
		image[i]->quad_no = i;
		
		image[i]->i_pos = 0;
		image[i]->height = SIZE_HEIGHT / 2;
		
		image[i]->j_pos = SIZE_WIDTH * i / 2;
		image[i]->width = SIZE_WIDTH * (i + 1) / 2;
		
		image[i]->infoPtr = &locationInfo;
		image[i]->rasterPtr = &raster;
	}
	//	bottom half
	for (int i = 2; i < 4; i++) {
		image[i] = malloc(sizeof(image_quad));
		
		image[i]->quad_no = i;
		
		image[i]->i_pos = 500;
		image[i]->height = SIZE_HEIGHT;
		
		image[i]->j_pos = SIZE_WIDTH * (i - 2) / 2;
		image[i]->width = SIZE_WIDTH * (i - 1) / 2;
		
		image[i]->infoPtr = &locationInfo;
		image[i]->rasterPtr = &raster;
	}
	
	/*
	//	==DEBUG==
	fprintf(stderr, "address of locationInfo: %p\n", (void*) locationInfo);
	fprintf(stderr, "address of raster: %p\n\n", (void*) raster);
	for (int i = 0; i < 4; i++) {
		fprintf(stderr, "image %i:\n", i);
		fprintf(stderr, "address of image: %p\n", (void*) &image[i]);
		fprintf(stderr, "quad no.:\t%d\n", image[i]->quad_no);
		fprintf(stderr, "\ti_pos:\t%d\n", image[i]->i_pos);
		fprintf(stderr, "\theight:\t%d\n", image[i]->height);
		fprintf(stderr, "\tj_pos:\t%d\n", image[i]->j_pos);
		fprintf(stderr, "\twidth:\t%d\n\n", image[i]->width);
		
		fprintf(stderr, "\taddress of locationInfo: %p\n", (void*) *image[i]->infoPtr);
		fprintf(stderr, "\taddress of raster: %p\n\n", (void*) *image[i]->rasterPtr);
	}
	fprintf(stderr, "\n");
	//	...	...	...
	*/
	
	pthread_t thread[4];
	for (int i = 0; i < 4; i++) {
		pthread_create(&thread[i], NULL, &parallelMandelbrot, image[i]);
	}
	
	for (int i = 0; i < 4; i++) {
		pthread_join(thread[i], NULL);
	}
	
    time_t end = time(NULL);

    writePPM("Mandelbrot Serial.ppm", SIZE_WIDTH, SIZE_HEIGHT, &raster);

    double serialTime = difftime(end, start);

    printf("The total serial execution time was: %f seconds.\n", serialTime);

    freeArray(&raster);

    return 0;

}

void* parallelMandelbrot(void* data) {
	image_quad *image = data;
	/*
	//	==DEBUG==
	fprintf(stderr, "thread no.: %d\n\n", image->quad_no);
	
	fprintf(stderr, "\taddress of locationInfo: %p\n", (void*) *image->infoPtr);
	fprintf(stderr, "\taddress of raster: %p\n", (void*) *image->rasterPtr);
	//	...	...	...
	*/
	
	struct ComplexNumber c;
	
    c.real = 0;
    c.imaginary = 0;

    for (int i = image->i_pos; i < image->height; i++) {
        c.imaginary = scalePixelYToImaginary(SIZE_HEIGHT, i) * (*image->infoPtr)->zoom + (*image->infoPtr)->panY;
        for (int j = image->j_pos; j < image->width; j++) {
            c.real = scalePixelXToReal(SIZE_WIDTH, j) * (*image->infoPtr)->zoom  + (*image->infoPtr)->panX;
            testBehavior(c, j, i, (*image->rasterPtr));
        }
    }
    
    pthread_exit(NULL);
}

/**
 * Calculates the mandelbrot set in a serial fashion.
 * @param info A struct reference which contains what part of the set to calculate.
 * @param raster A reference to the image raster.
 */
 /*
void serialMandelbrot(struct LocationInfo *info, int ***raster) {
    struct ComplexNumber c;

    c.real = 0;
    c.imaginary = 0;

    for (int i = is; i < ih; i++) {
        c.imaginary = scalePixelYToImaginary(SIZE_HEIGHT, i) * info->zoom + info->panY;
        for (int j = js; j < jw; j++) {
            c.real = scalePixelXToReal(SIZE_WIDTH, j) * info->zoom  + info->panX;
            testBehavior(c, j, i, (*raster));
        }
    }
}
*/

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
