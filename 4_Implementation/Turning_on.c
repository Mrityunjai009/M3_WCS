#include <avr/io.h>
#include "Turning_on.h"

void TIMER_Initialize()  // starting new function 
{

    TCNT0 =0x00; // ENABLING TURNING
    TCCR0A=0x00;
    TCCR0B |= ((1<<CS00)|((1<<CS01)));

}



