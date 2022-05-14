/*****************************************************************************************************
 * @file Car_Wiper_System.h
 * @author Mrityunjai singh
 * @brief These are the Header files for Performing the car wiper system
 ****************************************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Pulse_modulation.C"
#include "Turning_on.h"
/****************************************************************************************************
 * @brief These are the Header files which is showing and taking permitions to use 
 * register from a specific point of place
 ****************************************************************************************************/
#define INTERRUPT_INIT  SREG |= (1<<7)
#define ADC_PIN	0
#define SET_BIT(PORT,PIN)  PORT |= (1<<PIN)
#define CLR_BIT(PORT,PIN)  PORT &= ~(1<<PIN)
#define READ_BIT(PORT,PIN) PORT & (1<<PIN)
/****************************************************************************************************
*@brief  here we are Taking the variables for using conditions 
*****************************************************************************************************/
uint16_t Turning_out=0;
uint16_t Adc_values=0;
volatile uint8_t Table=0;
/****************************************************************************************************
* @brief from here main function starts
******************************************************************************************************/ 
int main()
{
    uint16_t Result=0;
    //uint8_t Button=0;
/*****************************************************************************************************
* @brief from here we are taking input from user and enabling pull up requests
*****************************************************************************************************/
    CLR_BIT(DDRD,PD2);   // Taking I/p
    SET_BIT(PORTD,PD2);  //Enabling pull up

    TIMER_init();
    PWM_init();
    INTERRUPT_INIT;
/*******************************************************************************************************
*@brief starting while loop and performing if and else conditions
********************************************************************************************************/
    while(1)
    {
        if(!(READ_BIT(PIND,PD2)))  // Condition of switching
        {
            START_TIMER;  // ENABLING THE INTERRUPT
            if(Table==1)   // complete some(5) sec
            {
                Result = READ_ADC(ADC_PIN);  // reading value

                if(Result>25 && Result <=250)
                    SET_PWM_VALUE(63);
                else if(Result>251 && Result <=750)
                    SET_PWM_VALUE(127);
                 else if(Result>751 && Result <=1023)
                    SET_PWM_VALUE(191);
                Table=0;
            }
        }
        else
        {
            STOP_TIMER;
            SET_PWM_VALUE(0);
        }
      }

    return 0;
}
/*************************************************************************************************************
*@brief performing new function
*************************************************************************************************************/
ISR(TIMER0_OVF_vect)
{
    Turning_out++;
    if(Turning_out>=2930)
    {
        Turning_out=0;
        Table=1;
    }
}
