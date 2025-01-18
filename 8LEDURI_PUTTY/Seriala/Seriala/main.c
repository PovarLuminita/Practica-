#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL //clock speed
#define PORT_LED0	PORTB // led pt verificare
#define PIN_LED0	PB0
#define PORT_LED1	PORTB // led pt verificare
#define PIN_LED1	PB1
#define PORT_LED2	PORTB // led pt verificare
#define PIN_LED2	PB2
#define PORT_LED3	PORTB // led pt verificare
#define PIN_LED3	PB3
#define PORT_LED4	PORTB // led pt verificare
#define PIN_LED4	PB4
#define PORT_LED5	PORTB // led pt verificare
#define PIN_LED5	PB5
#define PORT_LED6	PORTB // led pt verificare
#define PIN_LED6	PB6
#define PORT_LED7	PORTB // led pt verificare
#define PIN_LED7	PB7

#define rs PC2			//RS Pin
#define en PC1 			//E Pin

#define lcd_pin_dir  DDRA		///ddr = data direction register ; 1 = output ; 0 = input
#define lcd_data_dir  DDRC

#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

void init_data(void);
void port_init(void);
void timer0_init(void);
void init_devices(void);

void init_data_contor(void);
void initialize (void);
void lcd_command( unsigned char cmnd );
void lcd_clear();
void lcd_print (char *str, int size);
void lcd_setCursor();

ISR(USART0_RX_vect);

uint8_t flag_rx = 0; //semafor
uint8_t flag_led = 0;
char buffer[16] = {};
uint16_t cnt = 0;
void USART_Transmit_string(char *string); //ia un sir de caractere si extrage pe rand fiecare caracter in parte
void USART_Transmit(unsigned char data);
void USART_Init(unsigned int ubrr); //initializare registrii si baud rate
void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

uint8_t data;
uint8_t pin;

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
	init_devices();
	USART_Init(MYUBRR);
	
	
	do{
	if(flag_rx == 1)
	{
	lcd_clear();
	lcd_setCursor();	
	lcd_print(buffer,16);
	//USART_Transmit_string(buffer);
	//METODA SWITCH/CASE
	
	
	if(buffer[0] == 0){
		PORTB |= (1<<0);
		break;
	}
	
	if(buffer[0] == 1){
		PORTB |= (1<< 1);
		break;
	}
	
	
	if(buffer[0] == 2){
		PORTB |= (1<< 2);
		break;
	}
	
	if(buffer[0] == 3){
		PORTB |= (1<< 3);
		break;
	}
	
	if(buffer[0] == 4){
		PORTB |= (1<< 4);
		break;
	}
	
	if(buffer[0] == 5){
		PORTB |= (1<< 5);
		break;
	}
	
	
	if(buffer[0] == 6){
		PORTB |= (1<< 6);
		break;
	}
	
	if(buffer[0] == 7){
		PORTB |= (1<< 7);
		break;
	}
	
	
	if(buffer[0] == 8){
		PORTB = 0x00;
		break;
	}
	
	if(buffer[0] == 9){
		PORTB = 0xFF;
		break;
	}
	
	
	 cnt = 0;
	 flag_rx = 0;

}}while(1);
	
	
	sleep_mode();
	return 0;
}

ISR(USART0_RX_vect)
{
	//citesc registru
	buffer[cnt] = UDR0;
	flag_rx = 1;
	cnt++;
	pinToggle(&PORT_LED0, PIN_LED0);
	
}

void USART_Init(unsigned int ubrr)
{
	///PENTRU USART 0
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

  
  void USART_Transmit(unsigned char data)
  {
  	//wait for empty transmit buffer
  	while(!(UCSR0A &(1<<UDRE0)));
  	
  	//put data into buffer, sends the data
  	UDR0 = data;//scriu in registru
  	
  }
 
 
 
// void USART_Transmit_sir0(char *string, int size)
// {
// 	//FUNCTIE CARE IA UN SIR DE CARACTERE SI EXTRAGE CATE UN CARACTER PE RAND, PANA LA TERMINAREA SIRULUI
// 	for(int i = 0; i < size; i++)
// 	{
// 		 
// 		USART_Transmit_char_0(*string); ///II MODIFIC VALOAREA
// 		 
// 		string++; //II MUT ADRESA!!!!
// 		 
// 	}
// } 
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



void lcd_setCursor()
{
	lcd_command(1<<1); //return home
	_delay_ms(20);
}


//clear lcd
void lcd_clear()
{
	lcd_command (0x01);		//clear LCD // 10110111 & 11110000 = 10110000
	_delay_ms(2);
	lcd_command (0x80);		//muta la linia 1, pozitia 1
}



void init_data_contor(void){
	lcd_data_dir = 0xFF;	//pin D4-D7
	lcd_pin_dir = 0xFF;	//pin D4-D7
}


void lcd_4bits( unsigned char cmnd )
{
	PORTA = (PORTA & 0x0F) | (cmnd << 4);
	PORTC|= (1<<en);
	_delay_us(1);
	PORTC &= ~ (1<<en);
	_delay_us(200);
}


//pentru a trimite comenzi catre lcd
void lcd_command( unsigned char cmnd )
{
	PORTA = (PORTA & 0x0F) | (cmnd & 0xF0);
	PORTC &= ~ (1<<rs);
	PORTC|= (1<<en);
	_delay_us(1);
	PORTC &= ~ (1<<en);
	_delay_us(200);
	PORTA = (PORTA & 0x0F) | (cmnd << 4);
	PORTC|= (1<<en);
	_delay_us(1);
	PORTC &= ~ (1<<en);
	_delay_us(200);
}


void initialize (void)
{
	lcd_data_dir = 0xFF;	//pin A4-A7
	lcd_pin_dir = 0xFF;
	
	_delay_ms(15);
	lcd_4bits((1<<4)|(1<<5));
	
	_delay_ms(5);
	lcd_4bits((1<<4)|(1<<5));
	
	_delay_us(150);
	lcd_4bits((1<<4)|(1<<5));
	

	
	lcd_4bits(0x02);
	lcd_command(0x28);
	lcd_command(0x08);
	lcd_command(0x01);
	lcd_command(0x03);
	_delay_ms(2);
}



void lcd_print (char *str, int size)
{
	char data;
	int i;
	
	for(i=0; i < size-1 ; i++)
	{
		data = str[i];
		PORTA = (PORTA & 0x0F) | (data & 0xF0); //11110000 ... 10101010
		PORTC |= (1<<2);
		PORTC |= (1<<1);
		_delay_us(1);
		/*_delay_us(200);*/
		PORTC &= ~ (1<<1);
		_delay_us(200);
		PORTA = (PORTA & 0x0F) | (data << 4);
		PORTC |= (1<<1);
		_delay_us(1);
		PORTC &= ~ (1<<1);
		_delay_ms(1);
	}
}

