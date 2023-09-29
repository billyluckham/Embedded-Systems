#include "stdio.h"
#include "Complex_C.hpp"

void complexDisplay(const char *strName, const ComplexNumber_C u) {
    printf("%s = %f + j%f\n", strName, u.real, u.imag);
}

ComplexNumber_C complexAdd(const ComplexNumber_C a, const ComplexNumber_C b) {
    ComplexNumber_C y = a;
    y.real += b.real;
    y.imag += b.imag;
    return y;
}

ComplexNumber_C complexConjugate(const ComplexNumber_C a) {
    ComplexNumber_C y = a;
    y.real = a.real;
    y.imag = -a.imag;
    return y;
}

ComplexNumber_C complexNegate(const ComplexNumber_C a){
    ComplexNumber_C y = a;
    y.real = -a.real;
    y.imag = -a.imag;
    return y;
}

ComplexNumber_C complexSubtract(const ComplexNumber_C a, const ComplexNumber_C b) {
    ComplexNumber_C y = a;
    y.real -= b.real;
    y.imag -= b.imag;
    return y;
}


ComplexNumber_C complexMultiply(const ComplexNumber_C a, const ComplexNumber_C b) {
    ComplexNumber_C y;
    y.real = (a.real * b.real) - (a.imag * b.imag);
    y.imag = (a.real * b.imag) + (a.imag * b.real);
    return y;
}

ComplexNumber_C complexDivide(const ComplexNumber_C a, const ComplexNumber_C b) {
    ComplexNumber_C y = a;
    y.real = ((a.real * b.real) + (a.imag * b.imag)) / ((b.real * b.real) + (b.imag * b.imag));
    y.imag = ((a.imag * b.real) - (a.real * b.imag)) / ((b.real * b.real) + (b.imag * b.imag));
    return y;
}

