#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "avr_uart_debug_lib.h"

double x=0;		// Variablen 

double pi_ =  M_PI / 25.0;


// Wechselt den Zustand an PORTD Pin6
void blink()
{
	if(PIND&(1<<PD6))
		PORTD &= ~(1<<PD6);
	else
		PORTD |= 1<<PD6;
}

int main(void)
{
	usart_init(9600);	// Initialisieren der seriellen Schnittstelle

	DDRD = 1<<PD6;		// Bit6 PortD als Ausgang festlegen

	DDRC = 0xff;

	PORTC = 0;

	while(1)
	{
		//send_ddr();
		send_ports();
		//send_pins();
		// sinus();

		blink();				// Signal wechseln	

		PORTC ++;

		_delay_ms(1000);		// Wartezeit bis zum naechsten Senden
	}
	
	return 0;

}

void sinus()
{
	usart_putf(x,6,4);		// Ausgabe von x
	usart_puts(",");		// Ausgabe des Kommas
	usart_putf(sin(x),6,4);	// Berechnen und ausgeben von Sinus x
	usart_puts("\n");		// Zeilenumbruch senden

	x+=pi_;
}
