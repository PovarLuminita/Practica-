
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "adc.h"

#define ADC_PORT PORTC
#define ADC_PIN PINC0

#define LED_ADC_PORT PORTB
#define LED_ADC_PIN PINB0

#define ADC_mijloc	120
uint8_t valoare;

void adc_init(){

	ADMUX |=  (0<<REFS1)|  (1<<REFS0); 
	ADCSRA |=  (1<<ADPS2) |(1<<ADPS1) | (1<<ADPS0);  //setez prescalarul 128
	ADCSRA |=  (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) ;                   //ADC enable + incepe conversia
	
}


ISR(ADC_vect)
{
	uint8_t valoare = ADCL;
	
	if(valoare > ADC_mijloc)
	{
		LED_ADC_PORT |= (1 << LED_ADC_PIN);
	}else{
		LED_ADC_PORT &= ~(1 <<LED_ADC_PIN);
	}
}
