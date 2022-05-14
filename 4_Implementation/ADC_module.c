#include <avr/io.h>
#include <stdint.h>
#define ADC_PIN			0
#define	LED_PIN			PB0
uint16_t reading_value(uint8_t adcx); // taking variables 

uint16_t reading_value(uint8_t adcx)  // taking variables
{
    DDRD = (1<<6);
    ADMUX &=0x00;
    ADCSRA|= (1<< ADEN);
    ADMUX |= (1<<REFS0);
	ADCSRA |= (1 << ADSC);
	ADCSRA |= ((1<<ADPS1)|(1<<ADPS2));

	while (ADCSRA & (1 << ADSC));
	return ADC;                           // returning the value of ADC to use in different function
}
