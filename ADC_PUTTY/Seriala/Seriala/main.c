
#define F_CPU 16000000UL //clock speed

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define PORT_LED_128	PORTB // led pt verificare
#define PIN_LED_128 	PB0
#define ADC_PORT PORTF
#define ADC_PIN PF0
#define ADC_PORT_1 PORTC
#define ADC_PIN_1 PC0

#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

uint8_t flag_rx = 0; //semafor
uint16_t data;
uint16_t adcValue;
char buffer[16];


void init_devices(void)
{

	cli();

	port_init();
	
	adc_init();
	
	sei();
}

void port_init(void)
{
	DDRB  = 0xFF;
	PORTB  = 0x00;

	DDRC  = 0x7F;
	PORTC = 0x00;
	
	DDRF  = 0x7F;
	PORTF = 0x00;
}

void adc_init(void){
	ADMUX = 0x00;
	ADCSRA = 0x00;
	

	ADMUX |=  (1<<REFS0); ///AVcc with external capacitor AREF pin
	ADCSRA |= (1<<ADIE); ///enable ADC
//	ADMUX |= (1 << MUX0);
	//ACSR = (1<< ACD); ///to diable the anallog comparator

	sei();
	
	ADCSRA |=  (1<<ADPS2) |(1<<ADPS1) | (1<<ADPS0) | (1<<ADFR);  //setez prescalarul 128
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1<<ADSC);
}

//uint16_t ADC_read(void)
//{
	//ADCSRA |= (1 << ADSC); // Start conversia ADC
	//while (ADCSRA & (1 << ADSC)); // A?tept? finalizarea conversiei
//
	//return ADC; // Returneaz? valoarea ADC citit?
//}

ISR(ADC_vect)
{
	adcValue = ADCL;
	adcValue |= (uint16_t)ADCH<<8;
	flag_rx = 1;
//	adcValue = ADC;
}


void pinToggle(volatile uint8_t *port, uint8_t pin){
	*port ^=  1 << pin;
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
//	data = adcValue;
	data = UDR1;
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
	//UDR1 = adcValue;
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
		//while (!(ADCSRA & (1 << ADIF)));
		if(flag_rx == 1)
		{
			pinToggle(&PORT_LED_128, PIN_LED_128);
			flag_rx = 0;
		}
		//adcValue = ADC;
		//adcValue = ADC_read();
		sprintf(buffer, "%d  ", adcValue);
		USART_Transmit_string(buffer);
		//ADCSRA |= (1 << ADIF);
		
		
		
		}
		
		sleep_mode();
		return 0;
}

//----------------------------------------------------------------
		//if(flag_rx == 1)
		//{
		////METODA SWITCH/CASE
		//switch(data){
		//case 66: pinSet(&PORT_LED_128, PIN_LED_128);  //B
		//break;
		//case 85: pinReset(&PORT_LED_128, PIN_LED_128); //U
		//break;
		//case 78: UDR1 = 65; //N
		//break;
		//case 65: UDR1 = 65; //A
		//break;
		//}











