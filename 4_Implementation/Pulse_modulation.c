#include "Pulse_modulation.C"

#include <avr/io.h>

void PWM_Initialize()            //performing new function
{
    SET_BIT(DDRD,PD6);
    TCNT0 =0x00;  // Permition to Turning &COUNTER
    TCCR0A |= ((1<<WGM00)|(1<<WGM01)|(1<<COM0A1)); //
    TCCR0B |= ((1<<CS00)|((1<<CS01))); //clock and WGM02
}
