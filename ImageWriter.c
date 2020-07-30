//
// Created by robert on 3/13/17.
//

#include "ImageWriter.h"

/**
 * Performs scaling of the image dimensions to an interval of [-2, 2] along the real axis.
 * @param imageWidth The width of the image, alternatively the number of elements in one row of the array.
 * @param imageX A X value of the image raster (2D array).
 * @return A scaled value for the input imageX.
 */
double scalePixelXToReal(int imageWidth, int imageX) {
    return (imageX - (imageWidth / 2.0)) * (1.0 / (imageWidth / 4.0));
}

/**
 * Performs scaling of the image dimensions to an interval of [-2, 2] along the imaginary axis.
 * @param imageHeight The height of the image, alternatively the number of elements in one column of the array.
 * @param imageY A Y value of the image raster (2D array).
 * @return A scaled value for the input imageY.
 */
double scalePixelYToImaginary(int imageHeight, int imageY) {
    return -1 * (imageY - (imageHeight / 2.0)) * (1.0 / (imageHeight / 4.0));
}

/**
 * Perhaps the simplest image file format in existence. The PPM format consists of a header specifying:
 * The type of image: BitMap(P1 for ASCII encoding or P4 for binary), GreyMap(P2 for ASCII or P5 for binary), or PixMap(P3 for ASCII or P6 for binary)
 * The width and height of the image.
 * If using P3 or P6, a range also needs to be given for each color.
 *
 * The only other necessary data is a 2D array or image raster containing the color values for each pixel.
 *
 * Code sourced from with minor modifications made afterwards:
 * https://rosettacode.org/wiki/Bitmap/Write_a_PPM_file#C
 *
 * More information about PPM:
 * https://en.wikipedia.org/wiki/Netpbm_format
 *
 * @param fileName An array of characters the gives the name of the file to write.
 * @param imageWidth The width of the image to be written.
 * @param imageHeight The height of the image to be written.
 * @param raster An array containing the color values of each pixel.
 */
void writePPM(char *fileName, int imageWidth, int imageHeight, int ***raster) {

    //Open or create a file with the given name.
    FILE *fp = fopen(fileName, "wb");

    //Write the header information to that file.
    fprintf(fp, "P6\n%d %d\n 255\n", imageWidth, imageHeight);

    //Go through the array and write each pixel value.
    for (int k = 0; k < imageHeight; ++k) {
        for (int i = 0; i < imageWidth; ++i) {
            //Dereference the array and get the integer value at location raster(k,i).
            int pixelColor = (*raster)[k][i];

            //Even though the value stored in the raster has a hex component, we don't use it.
            int alpha = pixelColor >> 24;

            //Pull out the color values stored.
            int red = pixelColor >> 16;
            int green = pixelColor >> 8;
            int blue = pixelColor;

            //Create an array for the colors and store the values in the array.
            unsigned char color[3];

            color[0] = red % 256;
            color[1] = green % 256;
            color[2] = blue % 256;

            //Write the pixel value to the file.
            fwrite(color, 1, 3, fp);
        }
    }

    fclose(fp);

}