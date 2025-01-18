#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL //clock speed
#define PORT_LED_128	PORTB // led pt verificare
#define PIN_LED_128		PB0
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

void init_data(void);
void port_init(void);
void timer0_init(void);
void init_devices(void);

ISR(USART1_RX_vect);

uint8_t flag_rx = 0; //semafor
void USART_Init(unsigned int ubrr); //initializare registrii si baud rate
void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

uint8_t data;


void init_devices(void)
{
	//stop errant interrupts until set up. Disable all interrupts while we init the peripherals.
	cli();
	port_init();
	sei(); //re-enable interrupts. All peripherals are now initialized.
}

void port_init(void)
{
	DDRB  = 0xFF; // output
	PORTB  = 0x00; // low

	DDRC  = 0x7F;
	PORTC = 0x00;

	DDRD  = 0xFF;
	PORTD = 0x00;
}


int main(void){
	//init_data();
	init_devices();
	USART_Init(MYUBRR);
	do{
		if(flag_rx == 1)
		{
			//METODA SWITCH/CASE
			// 		switch(data){
			// 			case 66: UDR1 = 65;
			// 			break;
			// 			case 85: UDR1 = 65;
			// 			break;
			// 			case 78: UDR1 = 65;
			// 			break;
			// 			case 65: UDR1 = 65;
			// 			break;
			// 		}

			if(data == 66)
			{
				pinToggle(&PORT_LED_128, PIN_LED_128);
				flag_rx = 0;
			}
		}}while(1);
		
		sleep_mode();
		//nothing here interrupts are working
		return 0;
	}

	ISR(USART1_RX_vect)
	{
		//citesc registru
		data = UDR1;
		flag_rx = 1;
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
		//set_sleep_mode(SLEEP_MODE_IDLE);
		sei();
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