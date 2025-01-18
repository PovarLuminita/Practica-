#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL //clock speed
#define PORT_LED_128	PORTB // led pt verificare
#define PIN_LED_128 	PB0
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

void init_data(void);
void port_init(void);
void timer0_init(void);
void init_devices(void);

ISR(USART1_RX_vect);

uint8_t flag_rx = 0; //semafor
uint8_t flag_led = 0;
void USART_Transmit_string(char *string); //ia un sir de caractere si extrage pe rand fiecare caracter in parte
void USART_Transmit(unsigned char data);
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
		
		//aprinde_led();
	if(flag_rx == 1)
	{	
//METODA SWITCH/CASE
switch(data){
	case 66: pinSet(&PORT_LED_128, PIN_LED_128);  //B
	break;
	case 85: pinReset(&PORT_LED_128, PIN_LED_128); //U
	break;
	case 78: UDR1 = 65; //N
	break;
	case 65: UDR1 = 65; //A
	break;
}

// 		if(data == 66)
// 		{
// 		UDR1 = 85;
// 		flag_rx = 0;
// 		}
	}}while(1);
	
	
// 	while(1){
// 		
// 		
// 	};
	
//  	while(1){
//  		aprinde_led();
//  		//pinSet(&PORT_LED, PIN_LED);
// 		PORT_LED |= (1<<PIN_LED);	// on
// 		
// 		_delay_ms(10000);
// 		
// 		//pinReset(&PORT_LED, PIN_LED);
// 		PORT_LED &= ~(1 << PIN_LED);     // off
// 		
// 		_delay_ms(10000);
//  	}
	sleep_mode();
	//nothing here interrupts are working
	return 0;
}

ISR(USART1_RX_vect)
{
	//citesc registru
	data = UDR1;
	flag_rx = 1;
	flag_led =1;
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


void pinToggle(volatile uint8_t *port, uint8_t pin){
	*port ^=  1 << pin;
}

void pinSet(volatile uint8_t *port, uint8_t pin){
	*port |=  1 << pin;
}

void pinReset(volatile uint8_t *port, uint8_t pin){
	*port &=  ~(1 << pin);
}

//
//#include <avr/io.h>
//#include <util/delay.h>
//
//
//#define F_CPU 16000000UL //clock speed
//#define BAUD 9600
//#define MYUBRR (F_CPU/16/BAUD)-1
//
//void USART_Init(unsigned int ubrr); //initializare registrii si baud rate
//void USART_Transmit_string(char *string); //ia un sir de caractere si extrage pe rand fiecare caracter in parte
//void USART_Transmit(unsigned char data);
//unsigned char USART_Receive( void );
//void USART_Receive_string(char *string);
//
//uint8_t data;
//char buff[16];
//
//int main(void){
	//USART_Init(MYUBRR);
	//
	//USART_Transmit(66);//B 
	//_delay_ms(1000);
	//USART_Transmit(85);//U
	//_delay_ms(1000);
	//USART_Transmit(78);//N
	//_delay_ms(1000);
	//USART_Transmit(65);//A
	//
	//while (1)
	//{	
//// 	data = USART_Receive(); //returneaza din functie valoarea
//// 	USART_Transmit(data);
//// 	_delay_ms(1000);
//
	//USART_Receive_string(buff); //returneaza din functie valoarea
	//USART_Transmit_string(buff);
	////_delay_ms(1000);
	//}
//}
//
//ISR(USART1_RX_vect)
//{
		////citesc registru 
		//data = UDR1;
//}
//
//
//void USART_Init(unsigned int ubrr)
//{
	////set baud rate
	//UBRR1H = (unsigned char) (ubrr>>8);
	//UBRR1L = (unsigned char) ubrr;
	//
	////activ doar sa transmita si sa primeasca
	//UCSR1B |= (1<<RXEN1)|(1<<TXEN1);
	//
	////setez frame format : 8 data , 1 bit stop
	//UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10);
//}
//
//
//void USART_Transmit(unsigned char data)
//{
	////wait for empty transmit buffer
	//while(!(UCSR1A &(1<<UDRE1))); 
	//
	////put data into buffer, sends the data
	//UDR1 = data;//scriu in registru	
//}
//
//
//
//void USART_Transmit_string(char *string)//functie care ia un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
//{
	//while(*string!= 0x00)
	//{
		//USART_Transmit(*string);
		//string++;
	//}
	//
//}
//
////m128 ex pag 180
//unsigned char USART_Receive(void)
//{
	///* Wait for data to be received */
	//while (!(UCSR1A & (1<<RXC1)));
	///* Get and return received data from buffer */
	//return UDR1;
//}
//
//
//
//void USART_Receive_string(char *string)
//{
	//char caracter = USART_Receive();
	//int a = 0;
	//
	//
	//while((caracter != '\n') && (a<16))
	//{
		//*string = caracter;
		//string++;
		//a++;
		//caracter = USART_Receive();
	//}
	//
	//return caracter;
//}
//
//










//
//#include <avr/io.h>
//
//#define FOSC 16000000// Clock Speed
//#define BAUD 9600
//#define MYUBRR FOSC/16/BAUD-1
//
//void USART_Init( unsigned int ubrr );
//void USART_Transmit( unsigned char data );
//unsigned char USART_Receive( void );
//
//int main( void )
//{
	//unsigned char str[18] = "\n\rExplore Embedded";
	//unsigned char strLenght = 18;
	//unsigned char i = 0;
	//
	//USART_Init ( MYUBRR );
	////USART_Transmit('S' );
	//while(1)
	//{
		//USART_Transmit( str[i++] );
		//if(i >= strLenght)
		//i = 0;
		//
	//}
	//return(0);
//}
//
//void USART_Init( unsigned int ubrr )
//{
	///* Set baud rate */
	//UBRR1H = (unsigned char)(ubrr>>8);
	//UBRR1L = (unsigned char)ubrr;
	///* Enable receiver and transmitter */
	//UCSR1B |= (1<<RXEN1)|(1<<TXEN1);
	///* Set frame format: 8data, 2stop bit */
	////UCSR0C = (1<<USBS)|(3<<UCSZ0);
	//UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10);
//}
//
//void USART_Transmit( unsigned char data )
//{
	///* Wait for empty transmit buffer */
	//while ( !( UCSR1A & (1<<UDRE1)) )
	//;
	///* Put data into buffer, sends the data */
	//UDR1 = data;
//}
//
//unsigned char USART_Receive( void )
//{
	///* Wait for data to be received */
	//while ( !(UCSR1A & (1<<RXC1)) )
	//;
	///* Get and return received data from buffer */
	//return UDR1;
//}

