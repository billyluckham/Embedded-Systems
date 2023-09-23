#include "mbed.h"
#include <cstdio>

// Date Type ComplexNumber_C
typedef struct {
  double real;
  double imag;
} ComplexNumber_C;


int main() {

    //Create instance of a complex number
    ComplexNumber_C p;

    //Initialise each attribute 
    p.real = 2.0;
    p.imag = 3.0;
    
    //Create and Initialise 
    ComplexNumber_C q = {1.0, 1.0};
    
    // TASK:
    // Create another complex number y
    //ComplexNumber_C y = {.real = 3.6, .imag = 2.8};
    // Calculate the complex sum of p and q and store in y
    ComplexNumber_C y;
    y = {(p.real + q.real), (p.imag + q.imag)};
    
    // Use printf to display as a complex number (hint: you need two placeholders)
    printf("\n y real = %.1f, y imag = %.1f \n", y.real, y.imag);
    while (true) {
    }
}
