#include "uop_msb.h"
using namespace uop_msb;

#include "string.h"
#include <stdio.h>
#include <ctype.h>
#include "sample_hardware.hpp"

#define SWITCH1_RELEASE 1

void thread1();
void thread2();
void switchISR();

AnalogIn ldr(AN_LDR_PIN);

//Threads
Thread t1;

// Mutex
Mutex mailMutex;

class enviro_Data {

public:
    float temp;
    float pres;
    float hum;
    float light;

    enviro_Data(float lightValue){
        light = ldr;
        lightValue = light;
    }

    //constructor
    enviro_Data() {
        temp = 0.0;
        pres = 0.0;
        hum = 0.0;
        light = 0.0;
    }
};


//EnvSensor env;
enviro_Data Sread;

//Class type
class message_t {
public:    
    float fValue;    
    int sw1State;
    int sw2State;
    
    //Constructor
    message_t(float f, int s1, int s2) {
        fValue = f;
        sw1State = s1;
        sw2State = s2;    
    }
};
 
//Memory Pool - with capacity for 16 message_t types
// MemoryPool<message_t, 16> mpool;

//Message queue - matched to the memory pool
// Queue<message_t, 16> queue;

//Mail<message_t, 16> mail_box;     ///Uncomment


// Call this on precise intervals
// void switchISR() {
    
//     //Read sample - make a copy
//     float sample = 0.01f*(float)(rand() % 100);

//     //Grab switch state
//     uint32_t switch1State = buttonA;
//     uint32_t switch2State = buttonB;
    
//     //Allocate a block from the memory pool (non blocking version)
//     //For a thread context, there is also a blocking version (with timeout)
//     message_t* message = mail_box.try_alloc();
//     if (message == NULL) {
//         //Out of memory
//         redLED = 1;
//         return;   
//     }
    
//     //Fill in the data
//     message->fValue   = sample;
//     message->sw1State = switch1State;
//     message->sw2State = switch2State;
    
//     //Write pointer to the queue
//     osStatus stat = mail_box.put(message);    //Note we are sending the "pointer" not the data
    
//     //Check if succesful
//     if (stat != osOK) {
//         redLED = 1; 
//         printf("mail_box.put() Error code: %4Xh, Resource not available\r\n", stat);   
//         mail_box.free(message);
//         return;
//     }
// }

//Normal priority thread (consumer)
// void thread1() 
// {      
//     while (true) {
//         Sread.light = ldr;

//         message_t* payload;

//         //Block on the queue
//         payload = mail_box.try_get();
        
//         //Also consider this
//         //payload = mail_box.try_get_for(10s);

//         mailMutex.lock();
//         //Check status
//         if (payload) {
//             //Make a copy
//             message_t msg(payload->fValue, payload->sw1State, payload->sw2State);
//             //We are done with this, so give back the memory to the pool
            
            
//             mail_box.free(payload);
            
//             //Echo to the terminal
//             printf("Float Value: %.2f\t",    msg.fValue);
//             printf("SW1: %u\t",              msg.sw1State);
//             printf("SW2: %u\t",            msg.sw2State);
//             printf("LDR value %f\n\r", Sread.light);
//         } else {
//             //ERROR HANDLER TO BE DONE

//         }
//         mailMutex.unlock();  

//     } //end while
// }



Mail<enviro_Data, 16> mail_box_sensor;

void switchISR() {

    //Grab switch state
    //uint32_t switch1State = buttonA;
    //Sread.light = ldr;
    
    //Allocate a block from the memory pool (non blocking version)
    //For a thread context, there is also a blocking version (with timeout)
    enviro_Data* message = mail_box_sensor.try_alloc();
    if (message == NULL) {
        //Out of memory
        redLED = 1;
        return;   
    }
    
    //Fill in the data
    //message->sw1State = switch1State;
    //message->light = Sread.light;
    
    //Write pointer to the queue
    osStatus stat = mail_box_sensor.put(message);    //Note we are sending the "pointer" not the data
    
    //Check if succesful
    if (stat != osOK) {
        redLED = 1; 
        printf("mail_box.put() Error code: %4Xh, Resource not available\r\n", stat);   
        mail_box_sensor.free(message);
        return;
    }
}

void thread1() 
{      
    while (true) {
        Sread.light = ldr;

        enviro_Data* payload;

        //Block on the queue
        payload = mail_box_sensor.try_get();
        
        //Also consider this
        //payload = mail_box.try_get_for(10s);

        mailMutex.lock();

        //Check status
        if (payload) {
            //Make a copy
            enviro_Data msg(payload->light);//fValue);
            //We are done with this, so give back the memory to the pool
            
            
            mail_box_sensor.free(payload);
            
            //Echo to the terminal
            printf("LDR value %f\n\r", msg.light);
        } else {
            //ERROR HANDLER TO BE DONE

        }
        mailMutex.unlock();  

    } //end while
}


// Main thread
int main() {
    redLED    = 0;
    yellowLED = 0;
    greenLED  = 0;
           
    //Start message
    printf("Welcome\n");           
   
    //Hook up interrupts   
    Ticker timer; 
    timer.attach(&switchISR, 250ms);
               
    //Threads
    t1.start(thread1);
    
    printf("Main Thread\n");
    while (true) {
        ThisThread::sleep_for(5s);
        puts("Main Thread Alive");
    }
}