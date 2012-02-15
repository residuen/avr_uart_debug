#include <avr/io.h>          // Einbinden einer Bibliotheksdatei
#include <util/delay.h>		// Einbinden einer Bibliotheksdatei
#include "adc.h"
#include "avr_uart_debug_lib.h"	// Zusatz für Debuggung-Ausgabe

void schwellwert();
void pegelanzeige();

int main()
{
	usart_init(9600);	// Initialisieren der seriellen Schnittstelle

	ADC_Init();

	DDRC = 0xff;

	while(1) {

		pegelanzeige();

	}
}

void schwellwert()
{
	uint16_t adcval;

	while(1) {

		//adcval = ADC_Read(0); // Kanal 0, Einzelmessung
		adcval = ADC_Read(0); // Kanal 0, Mittelwert aus 4 Messungen

		if(adcval >=512)
			PORTC = 0x01;
		else
			PORTC = 0x00;
			
		_delay_ms(100);
	}
}

void pegelanzeige()
{
	uint16_t adcval;

	while( 1 ) {

		//adcval = ADC_Read(0); // Kanal 0, Einzelmessung
		adcval = ADC_Read(0); // Kanal 0, Mittelwert aus 4 Messungen

		if(adcval >=0)
			PORTC = 1<<PINC0;
		
		if(adcval >=128)
			PORTC = 1<<PINC1 | 1<<PINC0;
		
		if(adcval >=256)
			PORTC = 1<<PINC2 | 1<<PINC1 | 1<<PINC0;

		if(adcval >=384)
			PORTC = 1<<PINC3 | 1<<PINC2 | 1<<PINC1 | 1<<PINC0;

		if(adcval >=512)
			PORTC = ~(1<<PINC7 | 1<<PINC6 | 1<<PINC5);

		if(adcval >=640)
			PORTC = ~(1<<PINC7 | 1<<PINC6);

		if(adcval >=768)
			PORTC = ~(1<<PINC7);

		if(adcval >=896)
			PORTC = 0xff;

		send_adc(adcval, 0);	// Zusatz für Debuggung-Ausgabe
		send_portc();

		_delay_ms(100);
	}
}


