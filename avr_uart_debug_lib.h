/*
* Header-Datei fuer avr_uart_debug_lib.c
*/

// Datenrichtungsregister (DDR) senden
void send_ddr();	// Alle Datenrichtungsregister senden
void send_ddra();	// DDRA senden
void send_ddrb();	// DDRB senden
void send_ddrc();	// DDRC senden
void send_ddrd();	// DDRD senden

// Zustaende der Eingangspins (PIN) senden
void send_pins();	// Zustaende aller EIngangsadressen senden
void send_pina();	// PINA senden
void send_pinb();	// PINB senden
void send_pinc();	// PINC senden
void send_pind();	// PIND senden

// Zustaende der Datenregister (PORT) senden
void send_ports();	// Alle Portinhalte senden
void send_porta();	// PORTA senden
void send_portb();	// PORTB senden
void send_portc();	// PORTC senden
void send_portd();	// PORTD senden

void send_adc(uint16_t adcw, uint8_t channel);	// Inhalt des ADC (ADCL, ADCH & Kanal senden

// UART-Funktionen
void usart_init(uint16_t baud);
uint8_t usart_byte_avail(void);
uint8_t usart_getc(void);
void usart_gets(char *s);
void usart_putc(uint8_t byte);
void usart_puts(char *s);
void usart_puti(int zahl, int sges);
void usart_putf(float zahl, int sges, int snach);
void usart_putui(unsigned int zahl, int sges);
void usart_putui_0(unsigned int zahl, int sges);
void usart_putui_hex(unsigned int zahl, int sges);
void usart_putui_bin(unsigned int zahl, int sges);
void usart_putb(uint8_t a);


