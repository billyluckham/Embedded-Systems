#include "mbed.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include <string.h>
#include <string>

using namespace std;

class DoubleNumber {
private:

protected:
    double _real;

public:
    //Designated constructor
    DoubleNumber(double r) {
        _real = r;
        cout << "This is the constructor of Base" << endl;
    }

    //Convenience constructor
    DoubleNumber() : DoubleNumber(0.0) { }

    //Magnitude
    double magnitude() {
        return fabs(_real);
    }

    //Three overloaded functions
    void setValue(double u) {
        _real = u;
    }
    void setValue(int u) {
        _real = (double)u;
    }
    void setValue(string strVal) {
        _real = stod(strVal);
    }

    void setValue(DoubleNumber n) {         // New function taking DoubleNumber as a parameter
        _real = n.getValue();
    }

    double getValue() {
        return _real;
    }

    string asString() {
        return to_string(_real);
    }
};


int main()
{
    //Constructor Function overloading 
    DoubleNumber n0(1.0);
    DoubleNumber n1;
    DoubleNumber n2;
    DoubleNumber n3;

    //setValue function overloading  
    n1.setValue(10);
    n2.setValue("-3.0");
    DoubleNumber n4(5.5);
    n3.setValue(n4);

    cout << n0.getValue() + n1.getValue() + n2.getValue() +n3.getValue() << endl;

    while (true) {

    }
}

