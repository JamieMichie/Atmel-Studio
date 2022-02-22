/*
 * SerConsole.c
 *
 * Created: 16/12/2021 16:23:31
 * Author : Jamie
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/pgmspace.h>

#define BAUD 9600
#define PRESCALER (((F_CPU / (BAUD * 16UL))) - 1)


#define TRUE 1
#define FALSE 0
#define CHAR_NEWLINE '\n'
#define CHAR_RETURN '\r'
#define RETURN_NEWLINE "\r\n"
#define COLON ':'
#define CMDLEN 16

// The inputted commands are never going to be
// more than 8 chars long.
// volatile so the ISR can alter them
unsigned char data_in[CMDLEN];
char command_in[CMDLEN];
char last_command[CMDLEN];
volatile unsigned char data_count;
volatile unsigned char command_ready;

int volatile sensitivity = 0;

void uart_init(void);
void usart_putc(const char cdata);
void usart_puts(const char *send);
void usart_ok(void);
void command_copy(void);
void process_command(void);
void print_val(char id, int value);
int parse_assignment(void);
int16_t parse_query(void);


void uart_init(void){
	//Function to configure uart port 1 for asynchronous serial communication
	// PD2 = RXD1 PD3 = TXD1
	
	//enable receiver and transmitter
	UCSR1B |= (1 << RXEN1) | (1 << TXEN1);
	//Set frame format 8bit, 1 stop bits
	UCSR1C = (1 << UCSZ10) | (1 << UCSZ11);
	UCSR1B |=  (1 << RXCIE1);
	UBRR1H = (unsigned char)(PRESCALER >> 8);
	UBRR1L = (unsigned char)(PRESCALER);
	sei();
}
void usart_putc(const char cdata){
	/* Wait for empty transmit buffer */
	while(!(UCSR1A & (1<<UDRE1)))
	;
	/*Put data into the buffer and send */
	UDR1 = cdata;
}
void usart_puts(const char *send){
	while(*send){
		usart_putc(*send++);
	}
}
void usart_ok(void){
	usart_puts("OK\r\n");
}
ISR(USART1_RX_vect){
	data_in[data_count] = UDR1;
	usart_putc(UDR1);
	
	if(data_in[data_count] == '\n' || data_in[data_count] == '\r'){
		command_ready = TRUE;
		data_count = 0;
		}else{
		data_count++;
	}
}

void command_copy(void){
	ATOMIC_BLOCK(ATOMIC_FORCEON){
		memcpy(command_in, data_in, CMDLEN);
		//Clear data_in for next console command
		
		memset(data_in, 0, CMDLEN);
	}
}
int parse_assignment(void){
	char *pch;
	char cmdValue[CMDLEN] = {0};
	int retVal = 0;
	// Find the position the equals sign is
	// in the string, keep a pointer to it
	pch = strchr(command_in, '=');
	// Copy everything after that point into
	// the buffer variable
	strcpy(cmdValue, pch+1);
	// Now turn this value into an integer and
	// return it to the caller.
	retVal = atoi(cmdValue);
	//Copy current command for future queries
	strcpy(last_command, command_in);
	return retVal;
}
int parse_query(void){
	char *pch;
	char cmdValue[CMDLEN] = {0};
	int retVal = 0;
	// Find the position of the question mark is
	// in the string, keep a pointer to it
	pch = strchr(last_command, '=');
	// Copy everything after that point into
	// the buffer variable
	strcpy(cmdValue, pch+1);
	// Now turn this value into an integer and
	// return it to the caller.
	retVal = atoi(cmdValue);
//	memset(command_in, 0, CMDLEN);
	return retVal;
}
void print_val(char id, int value){
	char buffer[16];
	usart_puts(RETURN_NEWLINE);
	itoa(value, buffer, 10);
	usart_putc(id);
	usart_putc(COLON);
	usart_puts(buffer);
	usart_puts(RETURN_NEWLINE);
}

void process_command(void){

	switch(command_in[0])
	{
		case 'B':
		if (command_in[1] == '='){
			sensitivity = parse_assignment();
			print_val(command_in[0], sensitivity);
			
			} else if (command_in[1] == '?'){
			usart_puts(RETURN_NEWLINE);
			usart_puts("Brightness Query \n\r");
			sensitivity = parse_query();
			print_val(last_command[0], sensitivity);
			
			}else{
			usart_puts("Invalid command\n\r");
		}
		break;
		
		case 'C':
		if (command_in[1] == '='){
			sensitivity = parse_assignment();
			print_val(command_in[0], sensitivity);
			
			} else if (command_in[1] == '?'){
			usart_puts(RETURN_NEWLINE);
			usart_puts("C Query \n\r");
			sensitivity = parse_query();
			print_val(command_in[0], sensitivity);
			
			}else{
			usart_puts("Invalid command\n\r");
		}
		
		break;
		
		default:
		usart_puts("Invalid command\n\r");
		break;
	}
}


int main(void)
{
    /* Replace with your application code */
	uart_init();
	usart_puts("Hello, World!\n\r");
	usart_ok();
	
    while (1) 
    {
		if (command_ready == TRUE) {
			// Here is where we will copy
			command_copy();
			// and parse the command.
			process_command();
			command_ready = FALSE;
		}
    }
}

