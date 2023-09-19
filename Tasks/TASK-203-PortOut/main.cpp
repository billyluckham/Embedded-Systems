#include "mbed.h"

// Hardware Definitions
#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2
#define LEDMASK 0b0000000001001100

#define TRAF_GRN2_PIN PB_0
#define TRAF_YEL2_PIN PB_7
#define TRAF_RED2_PIN PB_14


// Objects
PortOut ledsC(PortC, LEDMASK);  //BusOut ledsC(TRAF_RED1_PIN, TRAF_YEL1_PIN, TRAF_GRN1_PIN);
//PortOut ledsB(PortB);  //BusOut ledB(TRAF_RED2_PIN, TRAF_YEL2_PIN, TRAF_GRN2_PIN);

int main()
{
    while (true) {
        ledsC = ledsC ^ LEDMASK;   //Binary 000
        //ledsB = 0;
        wait_us(500000);
        //leds = 0xFF;   //Binary 11111111
        //ledsB = 0x1FFF;
        //wait_us(500000);    
    }
}




