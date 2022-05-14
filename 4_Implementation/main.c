#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Pulse_modulation.C"
#include "Turning_on.h"

#define INTERRUPT_INIT  SREG |= (1<<7)
#define ADC_PIN	0
#define SET_BIT(PORT,PIN)  PORT |= (1<<PIN)
#define CLR_BIT(PORT,PIN)  PORT &= ~(1<<PIN)
#define READ_BIT(PORT,PIN) PORT & (1<<PIN)

uint16_t Turning_out=0;
uint16_t Adc_values=0;
volatile uint8_t Table=0;

int main()
{
    uint16_t Result=0;
    //uint8_t Button=0;

    CLR_BIT(DDRD,PD2);   // Taking I/p
    SET_BIT(PORTD,PD2);  //Enabling pull up

    TIMER_init();
    PWM_init();
    INTERRUPT_INIT;

    while(1)
    {
        if(!(READ_BIT(PIND,PD2)))  // Condition of switching and first if condition
        {
            START_TIMER;  // ENABLING THE INTERRUPT
            if(Table==1)   // complete some(5) sec and starting new if condition
            {
                Result = READ_ADC(ADC_PIN);  // reading value

                if(Result>25 && Result <=250)   //comparing the values and putting a condition in between 25 to 250
                    SET_PWM_VALUE(63);          // setting the value of 63
                else if(Result>251 && Result <=750)   // now putting a condition in between 251 to 750 values
                    SET_PWM_VALUE(127);                    // setting the value of 127
                 else if(Result>751 && Result <=1023)       // again putting the condition between 751 to 1023 values
                    SET_PWM_VALUE(191);                   // setting the value of 191
                Table=0;                                 // assigining the table value as zero
            }
        }
        else                                           // now finally putting else condition to stop timer 
        {
            STOP_TIMER;
            SET_PWM_VALUE(0);
        }
      }

    return 0;
}

ISR(TIMER0_OVF_vect)                                         //form here new function starts 
{
    Turning_out++;
    if(Turning_out>=2930)
    {
        Turning_out=0;
        Table=1;
    }
}
