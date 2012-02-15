/* ADC initialisieren */
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
	Ein Wert wird also gelesen und direkt verworfen, damit der ADC "warmlaufen kann" */
	ADCSRA |= (1<<ADSC); // eine ADC-Wandlung durchführen

	while (ADCSRA & (1<<ADSC)) {} // Warte auf Abschluss der Konvertierung

	/* ADCW muss ausgelesen werden, damit das Ergebnis der nächsten
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

/* Mehrfachmessung mit Mittelwertbbildung durchführen */
uint16_t ADC_Read_Avg(uint8_t channel, uint8_t average)
{
	uint32_t result = 0;

	for (uint8_t i = 0; i < average; ++i )
		result += ADC_Read(channel);

	return (uint16_t)(result / average);
}
