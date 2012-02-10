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
	DDRB = 0xff;
	DDRA = 0xff;

	PORTC = 0;
	PORTB = 0;
	PORTA = 1;

	int i = 1;

	while(1)
	{
		// sinus();
		sendDebugMsg();

		blink();	// Blinklicht fuer Bit 6 auf PORTD
		PORTC++;	// Vorwaertzaehler PORTC
		PORTB--;	// Rueckwaertszaehler PORTB
		PORTA = (i==1) ? PORTA*2 : PORTA/2;	// Lauflicht auf PORTA

		if(PORTA & 1<<PA7)
			i = 0;
		else
			if(PORTA & 1)
				i = 1;

	
		_delay_ms(1000);		// Wartezeit bis zum naechsten Senden
	}
	
	return 0;

}

void sendDebugMsg()
{
	//send_ddr();
	//send_ports();
	send_porta();
	send_portb();
	send_portc();
	send_portd();
	//send_pins();
	
}

void sinus()
{
	usart_putf(x,6,4);		// Ausgabe von x
	usart_puts(",");		// Ausgabe des Kommas
	usart_putf(sin(x),6,4);	// Berechnen und ausgeben von Sinus x
	usart_puts("\n");		// Zeilenumbruch senden

	x+=pi_;
}
