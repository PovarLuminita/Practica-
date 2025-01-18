

#include "main_mcu_init.h"

void TIMER0_INIT(void){
	
	TCCR0 = 0x00;
	TCCR0 |= (0 << WGM01)|(0<<WGM00);
	TCCR0 |= (1 << CS02)|(0 << CS01)|(0 << CS00);

	OCR0 = 0x00;
	OCR0=0x7C;
	
	TIMSK = 0x00;
	TIMSK |= (1 << TOIE0);
}

void CONTOR_INIT(void){
	contor_start_USART1 = timp_USART1;
	contor_start_USART0 = timp_USART0;
}


void PORTURI_INIT()
{
	DDRB  = 0xFF; // output
	PORTB  = 0x00; // low

	DDRC  = 0x7F;
	PORTC = 0x00;

	DDRD  = 0xFF;
	PORTD = 0x00;
}

void DEVICES_INIT()
{
	cli();

	PORTURI_INIT();
	TIMER0_INIT();
	
	sei();
}

void USART0_INIT(unsigned int ubrr)
{
	//set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	//activ doar sa transmita si sa primeasca
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	
	//setez frame format : 8 data , 1 bit stop
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
	//enable global interrupts
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
}

void USART1_INIT(unsigned int ubrr)
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
