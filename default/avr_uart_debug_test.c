#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include "avr_uart_debug_lib.h"

double x=0;		// Variablen 

double pi_ =  M_PI / 25.0;

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);

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
	ADC_Init();

	DDRD = 1<<PD6;		// Bit6 PortD als Ausgang festlegen
	DDRC = 0xff;
	DDRB = 0xff;

	PORTC = 0;
	PORTB = 1;

	int i = 1;

	// uint16_t = adcValue;

	while(1)
	{
		// sinus();
		sendDebugMsg();

		blink();	// Blinklicht fuer Bit 6 auf PORTD

		PORTC++;	// Vorwaertzaehler PORTC
		PORTB = (i==1) ? PORTB*2 : PORTB/2;	// Lauflicht auf PORTA

		if(PORTB & 1<<PB7)
			i = 0;
		else
			if(PORTB & 1)
				i = 1;

	
		_delay_ms(100);		// Wartezeit bis zum naechsten Senden
	}
	
	return 0;

}

void sendDebugMsg()
{
	//send_ddr();
	//send_ports();
	//send_porta();
	send_portb();
	send_portc();
	send_portd();
	send_adc(ADC_Read(0), 0);
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

void ADC_Init(void)
{
	uint16_t result;

	ADMUX = (0<<REFS1) | (1<<REFS0); // AVcc (5V) als Referenz festlegen
	//ADMUX = (1<<REFS1) | (1<<REFS0); // interne Referenzspannung benutzen

	// Da Bit ADFR (free running) in Register ADCSRA beim Einschalten
	// schon auf 0 steht, befindet sich der Controller im single conversion Modus
	ADCSRA  = (1<<ADPS1) | (1<<ADPS0); // Frequenzvorteiler einstellen
	ADCSRA |= (1<<ADEN); // ADC wird aktiviert

	/* Wird der ADC aktiviert, sollte ein ein "Dummy-Readout" durchgeführt werden.
	Ein Wert wird also gelsen und direkt verworfen, damit der ADC "warmlaufen kann" */
	ADCSRA |= (1<<ADSC); // eine ADC-Wandlung durchführen

	while (ADCSRA & (1<<ADSC)) {} // Warte auf Abschluss der Konvertierung

	/* ADCW muss ausgelesen werden, damit dasErgebnis der nächsten
	Wandlung übernommen werden kann. */
	result = ADCW;
}

/* ADC Einzelmessung durchführen */
uint16_t ADC_Read(uint8_t channel)
{
	// Auswahl des Kanals, andere Bits dabei nicht beeinflussen
	ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
	ADCSRA |= (1<<ADSC); // Durchführen einer Wandlung im "single conversion" Modus

	while (ADCSRA & (1<<ADSC)) {} // Warten bis Konvertierung abgeschlossen ist

	return ADCW; // Auslesen und zurückgeben des ADC als ganzes Wort
}

