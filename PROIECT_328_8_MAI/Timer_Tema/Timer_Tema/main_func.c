

#include "main_func.h"

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