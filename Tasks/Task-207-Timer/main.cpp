#include "uop_msb.h"
#include "mbed.h"
using namespace uop_msb;

// Hardware Definitions
#define TRAF_RED1_PIN PC_2

// Inputs
DigitalIn SW_BLUE(USER_BUTTON);

// Storage for input devices
typedef enum {WAITING_FOR_PRESS, DEBOUNCE_1, WAITING_FOR_RELEASE, DEBOUNCE_2} SWITCH_STATE;

//Where we are in the sequence (Press - wait - release - wait)
SWITCH_STATE stateBlue = WAITING_FOR_PRESS;

// Outputs
DigitalOut ledRed(TRAF_RED1_PIN);

// Timer(modified version from Timer)
TimerCompat tmr1;

int main()
{
    //Time how long it takes to perform a printf
    tmr1.start();
    printf("Hello World How Are You\n");
    tmr1.stop();

    //Print out how long it took
    unsigned long long dur = tmr1.read_ms();
    printf("The time taken was %llu milliseconds\n", dur);    

    //Now to use a timer to implement a delay
    tmr1.start();
    while (true) {
        /*
        //Wait for switch press
        while (SW_BLUE == 0);

        //Turn on LED
        ledRed = 1;

        //Wait for 500ms
        tmr1.reset();
        while (tmr1.elapsed_time() < 500ms); //How about this for C++ magic :)

        wait_us(500000);

        //Turn off LED
        ledRed = 0;
        */

        // Input storage variables
    int btnBlue = 0;

    long long timeBtn = 0;  

        // ************************************
        // Read all inputs and store the result
        // ************************************
        btnBlue = SW_BLUE;
        timeBtn = tmr1.read_ms();

        // ***************************
        // UPDATE "STATE" for blue user button 
        // ***************************

        switch (stateBlue) {
            case WAITING_FOR_PRESS:
                if (btnBlue == 1) {
                    stateBlue = DEBOUNCE_1;
                    tmr1.reset();
                    tmr1.start();
                }
            break;

            case DEBOUNCE_1:
                if (timeBtn >= 250) {
                    stateBlue = WAITING_FOR_RELEASE;
                    tmr1.stop();
                    ledRed = 1;     //Turn on LED
                }
            break;

            case WAITING_FOR_RELEASE:
                if (btnBlue == 0) {
                    stateBlue = DEBOUNCE_2;
                    tmr1.reset();
                    tmr1.start();
                }
            break;

            case DEBOUNCE_2:
                if (timeBtn >= 250) {
                    stateBlue = WAITING_FOR_PRESS;
                    tmr1.stop();
                    ledRed = 0;     //Turn off LED
                }
            break;            
        }
        
    }
}




   

    