#include "mbed.h"
#include "Complex_C.hpp"


// TASK - write and test complexConjugate, complexNegate, complexSubtract, complexMagnitude, complexMultiply and complexDivide

int main() {
    printf("\n\nTASK312\n");

    //Create instance of a complex number
    ComplexNumber_C p = {2.0, 3.0};
    ComplexNumber_C q = {1.0, 1.0};
    complexDisplay("p", p);
    complexDisplay("q", q);
 
    ComplexNumber_C sum = complexAdd(p, q);
    complexDisplay("p+q", sum);

    ComplexNumber_C subtract = complexSubtract(p, q);
    complexDisplay("p-q", subtract);

    ComplexNumber_C conjugate_P = complexConjugate(p);
    complexDisplay("p conjugate", conjugate_P);
     ComplexNumber_C conjugate_Q = complexConjugate(q);
    complexDisplay("q conjugate", conjugate_Q);

    ComplexNumber_C negate_P = complexNegate(p);
    complexDisplay("p negate", negate_P);
    ComplexNumber_C negate_Q = complexNegate(p);
    complexDisplay("q negate", negate_Q);

    ComplexNumber_C multiply = complexMultiply(p, q);
    complexDisplay("p*q", multiply);
    
    ComplexNumber_C divide = complexDivide(p, q);
    complexDisplay("p/q", divide);

    while (true) {
    }
}
