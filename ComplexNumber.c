//
// Created by Robert on 3/7/17.
//

#include "ComplexNumber.h"

/**
 * Adds two complex numbers together.
 * @param ComplexNumber1 A reference to a complex number struct.
 * @param ComplexNumber2 Another reference to a complex number struct.
 * @return A complex number struct.
 */
struct ComplexNumber add(struct ComplexNumber *ComplexNumber1, struct ComplexNumber *ComplexNumber2) {

    struct ComplexNumber temp;

    temp.real = 0;
    temp.imaginary = 0;

    temp.real = ComplexNumber1->real + ComplexNumber2->real;
    temp.imaginary = ComplexNumber1->imaginary + ComplexNumber2->imaginary;

    return temp;
}

/**
 * Squares a complex number.
 * @param complexNumber A reference to a complex number struct.
 * @return A complex number struct.
 */
struct ComplexNumber square(struct ComplexNumber *complexNumber) {

    struct ComplexNumber temp;

    temp.real = 0;
    temp.imaginary = 0;

    temp.real = complexNumber->real * complexNumber->real - complexNumber->imaginary * complexNumber->imaginary;
    temp.imaginary = complexNumber->real * complexNumber->imaginary + complexNumber->real * complexNumber->imaginary;

    return temp;
}

/**
 * Calculates the magnitude of a complex number.
 * @param complexNumber A reference to a complex number struct.
 * @return A complex number struct.
 */
double magnitude(struct ComplexNumber *complexNumber) {

    double real = complexNumber->real * complexNumber->real;
    double imaginary = complexNumber->imaginary * complexNumber->imaginary;

    return sqrt(real + imaginary);
}