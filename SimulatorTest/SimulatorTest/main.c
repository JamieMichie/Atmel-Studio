/*
 * SimulatorTest.c
 *
 * Created: 16/03/2022 10:19:48
 * Author : SS7U9741
 */ 
#define F_CPU 16000000
#define BAUD 9600
#define PRESCALER (((F_CPU / (BAUD * 16UL))) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

void uart_init(uint16_t BAUDRATE); 
void uart_putc(const char cdata);

uint8_t *u8p; //Utility pointer

void uart_init(uint16_t BAUDRATE){
	
	volatile uint16_t UBVAL = (((F_CPU / (BAUDRATE * 16UL)) - 1));
	UBRR0H = (UBVAL >> 8);
	UBRR0L = (UBVAL);
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

void uart_putc(const char cdata){
	/* Wait for empty transmit buffer */
	while(!(UCSR0A & (1<<UDRE0)))
	;
	/*Put data into the buffer and send */
	UDR0 = cdata;
}

int main(void)
{
    /* Replace with your application code */
	DDRB |= (1 << PB1);
	uart_init(9600);
	uart_putc('J');
	
	for(uint8_t i = 0; i < 255; i++){
		u8p = &i;
		eeprom_update_byte(*u8p, (i + 0x30));
	}
	
    while (1) 
    {
		PORTB ^= (1 << PB1);
	//	_delay_ms(500);
    }
}

