
#include "main_mcu_init.h"



void initializare_timer0(void){
	
	TCCR0 = 0x00;
	TCCR0 |= (0 << WGM01)|(0<<WGM00);
	TCCR0 |= (1 << CS02)|(0 << CS01)|(0 << CS00);

	OCR0 = 0x00;
	OCR0=0x7C;
	
	TIMSK = 0x00;
	TIMSK |= (1 << TOIE0);
}

void initializari(void){
	contor_usart1 = timp_usart1;
	contor_usart0 = timp_usart0;
	flag_start_usart1 = 0;
	flag_stop_usart1 = 0;

	cnt_usart1 = 0 ;
	cnt_usart0 = 0;
	flag_start_usart0 = 0; //flag pentru usart0
	flag_stop_usart0 = 0;

}


void initializare_porturi()
{
	DDRB  = 0xFF; // output
	PORTB  = 0x00; // low

	DDRC  = 0x7F;
	PORTC = 0x00;

	DDRD  = 0xFF;
	PORTD = 0x00;
}

void initializare_devices()
{
	cli();

	initializare_porturi();
	initializare_timer0();
	USART0_init(MYUBRR);
	USART1_init(MYUBRR);
	sei();
}

void USART0_init(unsigned int ubrr)
{
	///PENTRU USART 0
	//set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	//activ doar sa transmita si sa primeasca
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	
	//setez frame format : 8 data , 1 bit stop
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
}


void USART1_init(unsigned int ubrr){
	
	///PENTRU USART 1
	//set baud rate
	UBRR1H = (unsigned char) (ubrr>>8);
	UBRR1L = (unsigned char) ubrr;
	
	//activ doar sa transmita si sa primeasca
	UCSR1B |= (1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
	
	//setez frame format : 8 data , 1 bit stop
	UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10);
	
	
}