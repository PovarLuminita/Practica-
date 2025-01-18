/*

*/
//COMUNICARE 128 PROIECT OFICIAL
///ACESTA ESTE MASTER!!!!!

//------------- PROIECT ACCESAT 10.03.2023 -------------------------------------------------

#define F_CPU 16000000UL //FRECVENTA CEAS

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <string.h>

#define PORT_LED_128	PORTB ///SE APRINDE DUPA CE SE TRANSMITE BUFFERUL
#define PIN_LED_128	PB0
#define PORT_LED_RX	PORTB
#define PIN_LED_RX PB1
#define PORT_PUTTY	PORTB ///SE APRINDE CAND PRIMESTE CEVA DIN PUTTY
#define PIN_PUTTY PB2

#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

#define timp_pentru_activare_led 100
#define timp_pentru_usart0 20
#define timp_rx 30
uint16_t contor_rx;
uint16_t contor0;
uint16_t flag_start_timer = 0;
uint16_t flag_stop = 0;

uint8_t data; ///VARIABILA IN CARE LUAM/SALVAM CE ESTE IN REGISTRUL UDR
uint8_t data0; ///variabila in care iau ce e in registrul UDR0
uint16_t contor_decrementare_timp;

///FLAGURI SEMNALIZARE
uint8_t flag_timp; //flag care se activeaza dupa ce s-a decrementat contorul (este apelata intreruperea la 1 ms)
uint8_t flag_rx = 0; //flag care se activeaza in intreruperea rx dupa ce a primit un caracter
uint8_t a = 0 ;
uint8_t cnt = 0;
uint8_t b = 0;
uint16_t flag_start_0 = 0; //flag pentru usart0
uint16_t flag_0_led = 0; //flag pentru led putty
uint16_t flag_time_out_0 = 0;
///INITIALIZARI
void initializare_porturi(void); ///porturi de intrare/iesire
void initializare_devices(void); ///folosim cli; sei;
void USART_Initializare_registrii(unsigned int ubrr);

///FUNCTII PENTRU TIMER
void initializare_timer0(void);
void initializare_contor_timp(void);


//uint8_t Receive_Buffer(char *buffer);
char buffer[16] = {};	///acesta se incarca cu valorile primite de la transmit_sir; dupa ce nu mai primeste acesta activeaza flagul timer_expired
char buffer_usart0[16] = {}; ///acesta se incarca cu valorile primite de la putty , dupa ce nu mai primeste acesta activeaza flagul time out
char buffer_receptie_usart[16] = {};
char buffer_receptie_usart2[] = "test";
char buffer_total[36] = {};
char buffer_contor[8] = {};
///INTRERUPERE PENTRU TIMER
ISR(TIMER0_OVF_vect);

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

///FUNCTII TRANSMITERE
void USART_Transmit_sir(char *string, int size); //ia un sir de caractere (STRING) si extrage pe rand fiecare caracter in parte
void USART_Transmit_caracter(unsigned char data);

void USART_Transmit_0(char *string); //ia un sir de caractere si extrage pe rand fiecare caracter in parte
void USART_Transmit_char_0(unsigned char data);
void USART_Transmit_sir0(char *string, int size);


void Receive_Buffer(char *buffer);
///INTRERUPERE RECEPTIE 128
ISR(USART1_RX_vect);
ISR(USART0_RX_vect);

//FUNCTIE CARE APRINDE LEDUL DUPA CE A PRIMIT UN CARACTER; TRIMITE UN CARACTER CU TIMER DE 1 SECUNDA
void verificare_led_primire_caracter();


///--------------------------------- COD --------------------------------------

int main(void)
{
	initializare_contor_timp();
	initializare_devices();
	USART_Initializare_registrii(MYUBRR);
	pinReset(&PORT_LED_RX,PIN_LED_RX);
	pinReset(&PORT_LED_128,PIN_LED_128);
	pinReset(&PORT_PUTTY,PIN_PUTTY);
	do{
		if(flag_stop == 1)
		{
			
			///bufferul pe care-l primesc , pe o anumita pozitie sa ii schimb valoarea
			memcpy(buffer_receptie_usart, buffer, strlen(buffer) + 1);
			//buffer_receptie_usart[6] = buffer_receptie_usart[6] + 1;
			
			USART_Transmit_sir0(buffer_receptie_usart, strlen(buffer_receptie_usart));
			
			a = 0;
			flag_stop = 0;
			flag_start_timer = 0;
			memset(buffer, 0, sizeof(buffer));
			memset(buffer_receptie_usart, 0, sizeof(buffer_receptie_usart)); 
			memset(buffer_total, 0, sizeof(buffer_total));
			USART_Transmit_sir0("\n\r",4);
			pinToggle(&PORT_LED_RX, PIN_LED_RX);
			
		}
		
		if(flag_0_led == 1){
			pinToggle(&PORT_PUTTY, PIN_PUTTY);
			flag_0_led = 0;
			
		}
		
		if(flag_time_out_0 == 1){
			if(cnt > 16)
			{
			cnt = 16;
			}
			
			flag_time_out_0 = 0;
			flag_start_0 = 0;
			USART_Transmit_sir(buffer_usart0, cnt);
			cnt = 0;
			pinToggle(&PORT_LED_128, PIN_LED_128);
			
		}
		
		///TEST USART0 PUTTY
		if(flag_start_0 == 1)
		{
			//METODA SWITCH/CASE
			switch(data0){
				case 66: pinSet(&PORT_PUTTY, PIN_PUTTY);  //B
				break;
				case 85: pinReset(&PORT_PUTTY, PIN_PUTTY); //U
				break;
			}
		}

	}while(1);
	
	sleep_mode();
	return 0;
}


void initializare_timer0(void){
	
	TCCR0 = 0x00;
	TCCR0 |= (0 << WGM01)|(0<<WGM00);
	TCCR0 |= (1 << CS02)|(0 << CS01)|(0 << CS00);

	OCR0 = 0x00;
	OCR0=0x7C;
	
	TIMSK = 0x00;
	TIMSK |= (1 << TOIE0);
}

void initializare_contor_timp(void){
	contor_decrementare_timp = timp_pentru_activare_led;
	contor_rx = timp_rx;
	contor0 = timp_pentru_usart0;
}

ISR(TIMER0_OVF_vect){
	if(flag_start_timer == 1){
		contor_rx--;
	}
	
	if(flag_start_0 == 1){
		contor0--;
	}
	
	if(contor_rx == 0){
		flag_stop = 1;
		contor_rx = timp_rx;
	}
	
	if(contor0 == 0){
		flag_time_out_0 = 1;
		contor0 = timp_pentru_usart0;
	}
	
	contor_decrementare_timp--;
	
	if(contor_decrementare_timp == 0){
		flag_timp = 1;
		contor_decrementare_timp = timp_pentru_activare_led;
	}
		
}

void USART_Transmit_caracter(unsigned char data)
{
	//ASTEPT SA SE GOLEASCA BUFFERUL PENTRU TRANSMIS
	while(!(UCSR1A &(1<<UDRE1)));
	
	//PUN DATE IN BUFFER, TRIMIT DATELE
	UDR1 = data;//SCRIU IN REGISTRU
	
}

void USART_Transmit_sir(char *string, int size)
{
	//FUNCTIE CARE IA UN SIR DE CARACTERE SI EXTRAGE CATE UN CARACTER PE RAND, PANA LA TERMINAREA SIRULUI
	for(int i = 0; i < size; i++)
	{
		
		USART_Transmit_caracter(*string); ///II MODIFIC VALOAREA
		
		string++; //II MUT ADRESA!!!!
		
	}	
}

	
ISR(USART1_RX_vect)
{
  	buffer[a] = UDR1;
 	flag_start_timer = 1;
  	a++;	///incrementez pozit	

}

ISR(USART0_RX_vect)
{
	///data0 = UDR0; nu mai incarc in data0 pentru ca vreau sa incarc intr un buffer
	buffer_usart0[cnt] = UDR0;
	flag_start_0 = 1;
	flag_0_led = 1; 
	cnt++;
}


void USART_Transmit_sir0(char *string, int size)
{
	//FUNCTIE CARE IA UN SIR DE CARACTERE SI EXTRAGE CATE UN CARACTER PE RAND, PANA LA TERMINAREA SIRULUI
	for(int i = 0; i < size; i++)
	{
		
		USART_Transmit_char_0(*string); ///II MODIFIC VALOAREA
		
		string++; //II MUT ADRESA!!!!
		
	}
}

void USART_Transmit_char_0(unsigned char data)
{
	//wait for empty transmit buffer
	while(!(UCSR0A &(1<<UDRE0)));
	  
	//put data into buffer, sends the data
	UDR0 = data;//scriu in registru
	  
}
  
  
  
void USART_Transmit_0(char *string)//functie care ia un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
{
	while(*string!= 0x00)
	{
		USART_Transmit_char_0(*string);
		string++;
	}
	  
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
	
	sei();
}

void USART_Initializare_registrii(unsigned int ubrr)
{
	///PENTRU USART 0
	//set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	//activ doar sa transmita si sa primeasca
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	
	//setez frame format : 8 data , 1 bit stop
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
	///PENTRU USART 1
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

void pinToggle(volatile uint8_t *port, uint8_t pin){
	*port ^=  1 << pin;
}

void pinSet(volatile uint8_t *port, uint8_t pin){
	*port |=  1 << pin;
}

void pinReset(volatile uint8_t *port, uint8_t pin){
	*port &=  ~(1 << pin);
}


