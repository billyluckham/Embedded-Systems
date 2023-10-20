#include "mbed.h"
#include "ComplexNumber.hpp"

// main() runs in its own thread in the OS
int main()
{
    ComplexNumber c1(2.0,3.0);
    ComplexNumber c2(1.0,-1.0);
    ComplexNumber c1_copy = c1;
    c1.add(c2);   //c1 = c1 + c2
    c1.display();
    c1_copy.display();
    c1.subtract(c2);
    c1.display();
    
    ComplexNumber c3 = c1.addedTo(c2);
    c3.conjugate();
    c3.display();

    ComplexNumber c4 = c2.subtractFrom(c1);
    c4.negate();
    c4.display();

    ComplexNumber c5_copy = c1;
    ComplexNumber c6_copy = c2;
    c5_copy.multiply(c6_copy);
    c5_copy.display();
    

    //Create new scope
    {
        ComplexNumber test(1.0);
        test.display();
    }
    //test is now out of scope and should be destroyed

    while (true);
}

