

#include "main_func.h"



ISR(USART_RX_vect)
{
	//CITESC DATE DIN REGISTRU
	buffer[inc_ch] = UDR0;
	flag_start_timer = 1;
	
	inc_ch++;	///incrementez pozitia
	
}

void USART1_Tx_char(unsigned char data)
{
	//astept sa se goleasca bufferul de transmitere
	while(!(UCSR0A &(1<<UDRE0)));
	
	//pun date in registru, trimit datele
	UDR0 = data;//scriu in registru
}


///IN LOC DE WHILE SA PUN CONDITIE DE LUNGIME A SIRULUI SAU SA DAU VALOAREA MAX A POZITIEI ULTIMULUI CARACTER DIN TRANSMITERE TX
void USART1_Tx_size(char *string, int size)
{
	//luam un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
	// pointam la fiecare caracter din string, pornind de la primul, folosind incrementarea indexului
	for(int i = 0; i < size; i++)
	{
		
		USART1_Tx_char(string[i]); ///II TRANSMIT DIRECT PENTRU CA SE SI INCREMENTEAZA
	}
	//USART_Transmit_caracter('\0');
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




ISR(TIMER0_COMPA_vect){
	if(flag_start_timer == 1){
		contor_rx--;
	}
	
	if(contor_rx == 0){
		flag_stop = 1;
		contor_rx = timp_rx;
	}

}

void receive(){
	if(flag_stop == 1)
	{
		inc_ch = 0;
		flag_stop = 0;
		flag_start_timer = 0;
		lcd_clear();
		lcd_setCursor();
		lcd_print(buffer,16);
		memcpy(buffer_copy, buffer, strlen(buffer) + 1);
		
		USART1_Tx_size(buffer_copy, 17);
		pinToggle(&PORT_LED_328, PIN_LED_328);
		
	}
}

//initializare lcd
void initialize (void)
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
	//lcd_port &= ~ (1<<en);
	//_delay_us(200);
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
void lcd_print (char *str, int size)
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