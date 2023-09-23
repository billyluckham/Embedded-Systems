#include "uop_msb.h"
using namespace uop_msb;

// Inputs
DigitalIn SW2(BTN1_PIN);
DigitalIn SW3(BTN2_PIN);
DigitalIn BlueBtn(BTN1_PIN);

// Outputs
DigitalOut ledRed(TRAF_RED1_PIN);
DigitalOut ledYel(TRAF_YEL1_PIN);
DigitalOut ledGrn(TRAF_GRN1_PIN);

// Storage for input devices
typedef enum {WAITING_FOR_PRESS, DEBOUNCE_1, WAITING_FOR_RELEASE, DEBOUNCE_2} SWITCH_STATE;

//Where we are in the sequence (Press - wait - release - wait)
SWITCH_STATE stateSW2 = WAITING_FOR_PRESS;
SWITCH_STATE stateSW3 = WAITING_FOR_PRESS;
SWITCH_STATE stateBlueBtn = WAITING_FOR_PRESS;

// Timers (modified version from Timer)
TimerCompat tmr_flash;
TimerCompat tmr_debounce2;
TimerCompat tmr_debounce3;
TimerCompat tmr_debounceBlue;

// THE CODE BELOW IS NOT A SOLUTION
//
// IT IS FUNDAMENTALLY FLAWED (AND INCOMPLETE)
//
//

int main()
{
    //Start flashing timer
    tmr_flash.start();

    while (true) {

        //Wait for switch press and release (by BLOCKING)
        //while (SW2.read() == 0);
        //ledRed = !ledRed;
        //wait_us(300000);

        //while (SW2.read() == 1);
        //wait_us(300000);        

        //Toggle Yellow LED
        //ledYel = !ledYel;
        //wait_us(500000);
        //while (tmr_flash.read_ms() < 500);
        //tmr_flash.reset();

        // Input storage variables
        int SW_2 = 0;
        long long timeSW2 = 0;  
        int SW_3 = 0;
        long long timeSW3 = 0;  
        int Blue_Btn = 0;
        long long timeBlueBtn = 0;  

        // Read all inputs and store the result
        SW_2 = SW2;
        timeSW2 = tmr_debounce2.read_ms();
        SW_3 = SW3;
        timeSW3 = tmr_debounce3.read_ms();
        long long flash_time = tmr_flash.read_ms();
        timeBlueBtn = tmr_debounceBlue.read_ms();
        

        //********************* Automamously toggle yellow LED *****************//
        if (flash_time >= 500) {
            ledYel = !ledYel;
            tmr_flash.reset();
        }

        //********************** Debounce for SW2 ******************************//

        switch (stateSW2) {
            case WAITING_FOR_PRESS:
                if (SW_2 == 1) {
                    stateSW2 = DEBOUNCE_1;
                    tmr_debounce2.start();
                    ledRed = !ledRed;
                }
            break;

            case DEBOUNCE_1:
                if (timeSW2 >= 250) {
                    stateSW2 = WAITING_FOR_RELEASE;
                    tmr_debounce2.stop();
                    tmr_debounce2.reset();
                }
            break;

            case WAITING_FOR_RELEASE:
                if (SW_2 == 0) {
                    stateSW2 = DEBOUNCE_2;
                    tmr_debounce2.start();
                }
            break;

            case DEBOUNCE_2:
                if (timeSW2 >= 250) {
                    stateSW2 = WAITING_FOR_PRESS;
                    tmr_debounce2.stop();
                    tmr_debounce2.reset();
                }
            break;

            default:  stateSW2 = WAITING_FOR_PRESS;
                           
        }



        //********************** Debounce for SW3 ******************************//

        switch (stateSW3) {
            case WAITING_FOR_PRESS:
                if (SW_3 == 1) {
                    stateSW3 = DEBOUNCE_1;
                    tmr_debounce3.start();
                    ledGrn = !ledGrn;
                }
            break;

            case DEBOUNCE_1:
                if (timeSW3 >= 250) {
                    stateSW3 = WAITING_FOR_RELEASE;
                    tmr_debounce3.stop();
                    tmr_debounce3.reset();
                }
            break;

            case WAITING_FOR_RELEASE:
                if (SW_3 == 0) {
                    stateSW3 = DEBOUNCE_2;
                    tmr_debounce3.start();
                }
            break;

            case DEBOUNCE_2:
                if (timeSW3 >= 250) {
                    stateSW3 = WAITING_FOR_PRESS;
                    tmr_debounce3.stop();
                    tmr_debounce3.reset();
                }
            break;  

            default:  stateSW3 = WAITING_FOR_PRESS;          
        }

        //********************** Debounce for Blue Button ******************************//
        
        switch (stateBlueBtn) {
            case WAITING_FOR_PRESS:
                if (Blue_Btn == 1) {
                    stateBlueBtn = DEBOUNCE_1;
                    tmr_debounceBlue.start();
                    printf("\n\nTo set the delay (in ms), type in an integer number and press return\n");
                    //printf("You entered %d correct integer values. The value was %dms\n", parsed, delay_ms);
                }
            break;

            case DEBOUNCE_1:
                if (timeBlueBtn >= 250) {
                    stateBlueBtn = WAITING_FOR_RELEASE;
                    tmr_debounceBlue.stop();
                    tmr_debounceBlue.reset();
                }
            break;

            case WAITING_FOR_RELEASE:
                if (Blue_Btn == 0) {
                    stateBlueBtn = DEBOUNCE_2;
                    tmr_debounceBlue.start();
                }
            break;

            case DEBOUNCE_2:
                if (timeBlueBtn >= 250) {
                    stateBlueBtn = WAITING_FOR_PRESS;
                    tmr_debounceBlue.stop();
                    tmr_debounceBlue.reset();
                }
            break;  

            default:  stateBlueBtn = WAITING_FOR_PRESS;          
        }
    }
}





