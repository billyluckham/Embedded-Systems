#include "mbed.h"
#include <chrono>
using namespace std::chrono;

class Switch_Timer_State_Machine {
public: 
    typedef enum {UP = 1, DOWN = -1} DIRECTION;

private:
    typedef enum {WAITING_FOR_PRESS, DEBOUNCE_1, WAITING_FOR_RELEASE, DEBOUNCE_2} SWITCH_STATE;
    DigitalIn _switch;
    Timer _tmr;
    SWITCH_STATE _state;
    DIRECTION _dir;
    uint8_t _switchValue;
    microseconds _timerVal;

    int UpdateCount (int count){
        int newCount = count + _dir;
        if((count<0) || (count>99)){
            return count;
        } else {
            return newCount;
        }
    }
    

protected:

public: 
    Switch_Timer_State_Machine(PinName switchPin, DIRECTION dir) : _switch(switchPin), _dir(dir) {
        _state = WAITING_FOR_PRESS;
    }
void readInputs() {
        _timerVal = _tmr.elapsed_time();
        _switchValue = _switch;
    }

    void updateState(int& count)
    {
        switch (_state) {
            case WAITING_FOR_PRESS:
            if (_switchValue == 1) {
                count = UpdateCount(count);
                _tmr.reset();
                _tmr.start();
                _state = DEBOUNCE_1;
            }
            break;

            case DEBOUNCE_1:
            if (_timerVal >= 50ms) {
                _tmr.stop();
                _state = WAITING_FOR_RELEASE;
            }
            break;

            case WAITING_FOR_RELEASE:
            if (_switchValue == 0) {
                _tmr.reset();
                _tmr.start();
                _state = DEBOUNCE_2;
            }
            break;

            case DEBOUNCE_2:
            if (_timerVal >= 50ms) {
                _tmr.stop();
                _state = WAITING_FOR_PRESS;
            }
            break;
        }
    }
    
};