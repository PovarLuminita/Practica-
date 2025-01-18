//TX PENTRU 128
//ACCESARE : 13.02.2023

// biblioteci
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

// defines
#define F_CPU 16000000UL //clock speed
#define PORT_LED_128	PORTB 
#define PIN_LED_128		PB0
#define PORT_LED_mesajj	    PORTB
#define PIN_LED_mesajj		PB1
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

// declarare variabile

//cnt
uint8_t contor = 0;

//flags
uint8_t flag_rx = 0,
		flag_mesaj = 0;

// data
uint8_t data;
char buffer[10];
char mesaj = 'C';
//char mesaj_seriala[] = {'A', 'M',' ', 'T', 'R', 'I', 'M', 'I', 'S', '\r', '\n'};

// inits
void init_data(void);
void port_init(void);
void timer0_init(void);
void init_devices(void);
void USART_Init(unsigned int ubrr); 


// intreruperi
ISR(USART1_RX_vect);
// todo ISR(USART0_RX_vect);


// functii led
void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);


// UART1

// transmitere un singur caracter 
void USART_Transmit(unsigned char data);

// transmitere string folosind USART_Transmit
void USART_Transmit_string(char *string); 

// verificare receptie
void aprinde_led_mesaj();

// UART0

void USART_Transmit_udr0(unsigned char data);
void test();



int main(void)
{
	init_devices();
	USART_Init(MYUBRR);
	
	do
	{
	
		//USART_Transmit_udr0(170);
		//_delay_ms(1000);
		//USART_Transmit(170);
		//_delay_ms(1000);
		//pinToggle(&PORT_LED_128, PIN_LED_128);
		//if(flag_rx == 1)
			//{
				//pinToggle(&PORT_LED_128, PIN_LED_128);
				//flag_rx = 0;
			//}
	
	test();	
	aprinde_led_mesaj();
	
	} while(1);
		
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

void USART_Init(unsigned int ubrr)
{
	UCSR1B = 0x00;
	UCSR1C = 0x00;
	
	//set baud rate
	UBRR1H = (unsigned char) (ubrr>>8);
	UBRR1L = (unsigned char) ubrr;
		
	//activ doar sa transmita si sa primeasca
	UCSR1B |= (1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
		
	//setez frame format : 8 data , 1 bit stop
	UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10);
	
	UCSR0B = 0x00;
	UCSR0C = 0x00;
	
	//set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	//activ doar sa transmita si sa primeasca
	UCSR0B |= (1<<TXEN0);
	
	//setez frame format : 8 data , 1 bit stop
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
		
	//enable global interrupts
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
}





// functii led:
void pinToggle(volatile uint8_t *port, uint8_t pin){
	*port ^=  1 << pin;
}

void pinSet(volatile uint8_t *port, uint8_t pin){
	*port |=  1 << pin;
}

void pinReset(volatile uint8_t *port, uint8_t pin)
{
	*port &=  ~(1 << pin);
}


// verificari:

test()
{
	if(flag_rx == 1)
	{
 		pinToggle(&PORT_LED_128, PIN_LED_128);
		 
		//USART_Transmit(contor + 48);
		USART_Transmit('A');
		
		 _delay_ms(100);
		 
		USART_Transmit_udr0(mesaj);
		
		flag_mesaj = 1;
		
		_delay_ms(100);
		
		flag_rx  = 0;
		contor++;
	}
}

void aprinde_led_mesaj()
{
	if((flag_mesaj == 1) && (data == 'A'))
	{
		pinToggle(&PORT_LED_mesajj, PIN_LED_mesajj);
		flag_mesaj = 0;
	}
}


// transmisii:
void USART_Transmit(unsigned char data)
{
	//wait for empty transmit buffer
	while(!(UCSR1A &(1<<UDRE1)));
	
	//put data into buffer, sends the data
	UDR1 = data;
}

void USART_Transmit_udr0(unsigned char mesaj)
{
	//wait for empty transmit buffer
	while(!(UCSR0A &(1<<UDRE0)));
	
	//put data into buffer, sends the data
	UDR0 = mesaj;
}
 
  void USART_Transmit_string(char *string)
  {
	  // pointam la fiecare caracter din string, pornind de la primul, folosind incrementarea indexului
  	while(*string!= 0x00)
  	{
  		USART_Transmit(*string);
  		string++;
  	}
  }
