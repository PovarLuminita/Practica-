

#include "main_func.h"




ISR(USART_RX_vect)
{
	//CITESC DATE DIN REGISTRU
	buffer_rx_usart0[inc_usart0] = UDR0;
	flag_start_usart0 = 1;
	
	inc_usart0++;	///incrementez pozitia
	
}

void USART0_tx_char(unsigned char data)
{
	//astept sa se goleasca buffer_rx_usart0ul de transmitere
	while(!(UCSR0A &(1<<UDRE0)));
	
	//pun date in registru, trimit datele
	UDR0 = data;//scriu in registru
}


///IN LOC DE WHILE SA PUN CONDITIE DE LUNGIME A SIRULUI SAU SA DAU VALOAREA MAX A POZITIEI ULTIMULUI CARACTER DIN TRANSMITERE TX
void USART0_tx_sir_size(char *string, int size)
{
	//luam un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
	// pointam la fiecare caracter din string, pornind de la primul, folosind incrementarea indexului
	for(int i = 0; i < size; i++)
	{
		
		USART0_tx_char(string[i]); ///II TRANSMIT DIRECT PENTRU CA SE SI INCREMENTEAZA
	}
}



ISR(TIMER0_COMPA_vect){
	if(flag_start_usart0 == 1){
		contor_timp_usart0--;
	}
	
	if(contor_timp_usart0 == 0){
		flag_stop_usart0 = 1;
		contor_timp_usart0 = timp_usart0;
	}

}

void Receptie_Transmisie_usart0(){
	if(flag_stop_usart0 == 1)
	{
		inc_usart0 = 0;
		flag_stop_usart0 = 0;
		flag_start_usart0 = 0;
		lcd_clear();
		lcd_setCursor();
		lcd_print(buffer_rx_usart0,16);
		memcpy(buffer_rx_usart0_copy, buffer_rx_usart0, strlen(buffer_rx_usart0) + 1);
		
		USART0_tx_sir_size(buffer_rx_usart0_copy, 17);
		pinToggle(&PORT_LED_tx, PIN_LED_tx);
		
	}
}

void pinToggle(volatile uint8_t *port, uint8_t pin)
{
	*port ^=  1 << pin;
}

void pinSet(volatile uint8_t *port, uint8_t pin)
{
	*port |=  1 << pin;
}

void pinReset(volatile uint8_t *port, uint8_t pin)
{
	*port &=  ~(1 << pin);
}




//initializare lcd
void init_lcd(void)
{
	lcd_data_dir = 0xFF;	//pin D4-D7
	
	_delay_ms(15);
	lcd_command((1<<4)|(1<<5));
	
	_delay_ms(5);
	lcd_command((1<<4)|(1<<5));
	
	_delay_us(150);
	lcd_command((1<<4)|(1<<5));
	
	lcd_command(0x02);
	lcd_command(0x28);
	lcd_command(0x01);
	
	lcd_command(1<<3);
	
	_delay_ms(2);
}

//pentru a trimite comenzi catre lcd
void lcd_command( unsigned char cmnd )
{
	lcd_port_pin = (lcd_port_pin & 0x0F) | (cmnd & 0xF0);
	lcd_port &= ~ (1<<rs);
	lcd_port|= (1<<en);
	_delay_us(1);
	lcd_port &= ~ (1<<en);
	_delay_us(200);
	lcd_port_pin = (lcd_port_pin & 0x0F) | (cmnd << 4);
	lcd_port|= (1<<en);
	_delay_us(1);
	lcd_port &= ~ (1<<en);
	_delay_us(200);
}


//clear lcd
void lcd_clear()
{
	lcd_command (0x01);		//clear LCD
	_delay_ms(2);
	lcd_command (0x80);		//muta la linia 1, pozitia 1
}

//afisare lcd
void lcd_print(char *str, int size)
{
	if(size > 16)
	{
		size == 16;
		
	}
	int i;
	
	for(i=0; i <size; i++)
	{
		lcd_port_pin = (lcd_port_pin & 0x0F) | (str[i] & 0xF0);
		lcd_port |= (1<<rs);
		lcd_port|= (1<<en);
		_delay_us(1);
		_delay_us(200);
		lcd_port &= ~ (1<<en);
		_delay_us(200);
		lcd_port_pin = (lcd_port_pin & 0x0F) | (str[i] << 4);
		lcd_port |= (1<<en);
		_delay_us(1);
		lcd_port &= ~ (1<<en);
		_delay_us(200);
	}
}


void lcd_setCursor()
{
	
	
	lcd_command(1<<1); //return home
	
	_delay_ms(20);

}