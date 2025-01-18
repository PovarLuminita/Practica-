
#define F_CPU 16000000UL //clock speed

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define PORT_LED_128	PORTB // led pt verificare
#define PIN_LED_128 	PB4
#define ADC_PORT PORTF
#define ADC_PIN PF7
#define ADC_PORT_1 PORTC
#define ADC_PIN_1 PC0

#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

uint8_t flag_usart = 0; //semafor
uint16_t data;
uint16_t adcValue;
uint8_t duty = 0x00;
char buffer[16];


void init_devices(void)
{

	cli();

	port_init();
	
	adc_init();
	
	timer0_init();
	
	sei();
}

void port_init(void)
{
	DDRB  = 0xFF;
	PORTB  = 0x00;

	DDRC  = 0x7F;
	PORTC = 0x00;
	
	DDRF  = (0<< PF7);
	PORTF = 0x00;
}

void adc_init(void){
	ADMUX = 0x00;
	ADCSRA = 0x00;
	

	ADMUX |=  (1<<REFS0); ///AVcc with external capacitor AREF pin
	ADCSRA |= (1<<ADIE); ///enable ADC
	ADMUX |= 0x07;
	sei();
	
	ADCSRA |=  (1<<ADPS2) |(1<<ADPS1) | (1<<ADPS0) | (1<<ADFR);  //setez prescalarul 128
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1<<ADSC);
}

void timer0_init(void){
		DDRB  |= (1 << PIN_LED_128);
		PORTB &= ~(1 << PIN_LED_128);
		TCCR0 = 0x00;
		TCCR0 |= (1 << WGM01)|(1<<WGM00); // fast PWM
		TCCR0 |= (1<< COM01); //non inverting mode
		
		///PRESCALAR 8 - frecv la iesire mare si executia instructiunilor MAI RAPIDA
		///PRESCALAR 128 - frecv de iesire mica si executia instructiunilor MAI LENTA
		TCCR0 |= (1 << CS02)|(1<<CS00); ///prescalar 8  ---- 512us
										///prescalar 128 ----- 2ms
		
		OCR0 = 0x00;
		
		///intrerupere de comparatie
		//TIMSK |= (1 << OCIE0);
		
		 // Pornire Timer0
		 TCCR0 |= (1 << CS00);
}

ISR(ADC_vect)
{
	adcValue = ADCL;
	adcValue |= (uint16_t)ADCH<<8;
	
	///convertesc la 8 biti
	adcValue = (uint8_t)(adcValue/4);
	
	flag_usart = 1;
}

void pinToggle(volatile uint8_t *port, uint8_t pin){
	*port ^=  1 << PB4;
}

void pinSet(volatile uint8_t *port, uint8_t pin){
	*port |=  1 << pin;
}

void pinReset(volatile uint8_t *port, uint8_t pin){
	*port &=  ~(1 << pin);
}

ISR(USART1_RX_vect)
{
	//citesc registru
	data = UDR1;
	//flag_usart = 1;
}

void USART_Init(unsigned int ubrr)
{
	//set baud rate
	UBRR1H = (unsigned char) (ubrr>>8);
	UBRR1L = (unsigned char) ubrr;
	
	//activ doar sa transmita si sa primeasca
	UCSR1B |= (1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
	
	//setez frame format : 8 data , 1 bit stop
	UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10);
	
	//enable global interrupts
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
}

void USART_Transmit(unsigned char data)
{
	//wait for empty transmit buffer
	while(!(UCSR1A &(1<<UDRE1)));
	
	//put data into buffer, sends the data
	UDR1 = data;//scriu in registru
}

void USART_Transmit_string(char *string)//functie care ia un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
{
	while(*string!= 0x00)
	{
		USART_Transmit(*string);
		string++;
	}
	
}

int main(void)
{
	init_devices();
	USART_Init(MYUBRR);
	while(1){
		
		if(flag_usart == 1)
		{
			OCR0 = adcValue;
			flag_usart = 0;
		}
		
		sprintf(buffer, "%d  ", adcValue);
		USART_Transmit_string(buffer);
		}
		
		sleep_mode();
		return 0;
}










