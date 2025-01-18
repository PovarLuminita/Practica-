// Seriala
// Raspuns - echo

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL 

//LED VERIFICARE
#define PORT_LED	PORTB 
#define PIN_LED 	PB0

//baud rate
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1 // modul 7 si datasheet

#define interval_transmisie 3000


uint8_t flag_rx = 0; // activat dupa ce se primesc date
uint8_t data;
char received_array[100] = {};

uint16_t decrement_timer;
uint8_t flag_receptie = 0;
uint8_t flag_echo =0;
void timer_init(void);
ISR(TIMER0_OVF_vect);
ISR(USART1_RX_vect);  

//inits
void port_init(void);
void USART_Init(unsigned int ubrr); 
void init_devices(void);


void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);


// buffer de rec data de 200 bytes
// contor care sa fie si indice, pt cand sare intreruperea
// timer (ISR - flag pt echo ) pt timeout - 5 ms - reset si transmitere echo

// functii transmisie date
void USART_Transmit_string(char *string);
void USART_Transmit(unsigned char data);
uint8_t receive_data(char *array_data);

void initializare_contor_timp(void);
void Response();
void verificare_putty();






int main(void)
{
	initializare_contor_timp();
	init_devices();
	USART_Init(MYUBRR);
	pinReset(&PORT_LED, PIN_LED);
	
	//char cnt = 48;
	do{	
		verificare_putty();
		
	} while(1);
	
	// sleep_mode(); // cat timp nu primeste date 
	return 0;
}

void init_devices(void)
{
	cli();
	port_init();
	timer_init();
	sei(); 
}

void port_init(void)
{
	DDRB  = 0xFF; 
	PORTB  = 0x00; 

	DDRC  = 0x7F;
	PORTC = 0x00;

	DDRD  = 0xFF;
	PORTD = 0x00;
	
	
}



void USART_Init(unsigned int ubrr)
{
	//BAUD RATE
	UBRR1H = (unsigned char) (ubrr>>8);
	UBRR1L = (unsigned char) ubrr;
	
	//transmit - recieve active
	UCSR1B |= (1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
	
	//8 biti de date, 1 bit de stop
	UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10);
	
	//enable intr
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
}

void USART_Transmit(unsigned char data)
{
	// UDRE --- data register empty
	while(!(UCSR1A &(1<<UDRE1)));
  
	//incarcam UDR1 cu datele de transmis
	UDR1 = data;
	
}
  
void USART_Transmit_string(char *string)
{
	while(*string!= 0x00)
	{
  		USART_Transmit(*string);
  		string++;
	}	
}


void verificare_putty(){
	
	
	
	if (flag_receptie == 1){
		
		USART_Transmit_string("ABCDEFG\n\r");
		pinToggle(&PORT_LED, PIN_LED);
		flag_receptie = 0;
	}
	
}
/// functie receptie buffer din seriala

uint8_t receive_data(char *received_array)
{
	uint8_t contor = 0;
	
	while(flag_receptie == 0)
	{
		received_array[contor] = data;
		contor ++;
	}
	
	return contor;
	
}
	
void Response()
{
	if ( flag_echo == 1)
	{	
	USART_Transmit_string(received_array);
	flag_echo = 0;
	flag_receptie = 0;
	}
	
}
	
	
// TIMER 

void timer_init(void)
{
	
	TCCR0 = 0x00;
	TCCR0 |= (0 << WGM01)|(0<<WGM00);
	TCCR0 |= (1 << CS02)|(0 << CS01)|(0 << CS00);

	OCR0 = 0x00;
	OCR0=0x7C;
	
	TIMSK = 0x00;
	TIMSK |= (1 << TOIE0);
}


void initializare_contor_timp(void){
	decrement_timer = interval_transmisie;
}


ISR(TIMER0_OVF_vect)
{
	decrement_timer--;
	if(decrement_timer == 0)
	{
		flag_receptie = 1; //flag timer
		//flag_echo = 1;
		decrement_timer = interval_transmisie;
		
	}
	
}

ISR(USART1_RX_vect)
{
	//citim datele din UDR1
	data = UDR1;
	// activam flagul de receptie
	flag_rx = 1;
	// UDR1 = data;
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








