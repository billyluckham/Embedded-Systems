#include "mbed.h"
#include "TrafficLight.h"
#include <cstdio>

TrafficLight lights;
DigitalIn sw(USER_BUTTON);
DigitalIn btnA(Btn_A);
DigitalIn btnB(Btn_B);
DigitalIn btnC(Btn_C);
DigitalIn btnD(Btn_D);

int n = 0;

TrafficLight::LIGHT_STATE s;

int main()
{
    while (true) {
        
        if(btnB == 1){
            n = n + 10;
            printf("n = %i", n);
        } 
        if (btnC == 1) {
            n = n - 10;
            printf("n = %i", n);
        }
        
        //Wait for switch press
        while (sw==0);

        //Update lights
        s = lights.nextState();

        //Debounce switch
        wait_us(300000);

        //Wait for switch release
        while (sw==1);

        //Switch debounce
        wait_us(300000);

                
    }
}

