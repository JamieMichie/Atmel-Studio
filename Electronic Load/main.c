/*
 * Electronic Load.c
 *
 * Created: 06/03/2020 09:26:57
 * Author : Jamie Michie
 */ 
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "main.h"
#include "lcd.h"
#include "pins.h"
#include "i2cmaster.h"
#include "globals.h"

//define global variables
volatile int16_t currentA = 0;
volatile int16_t psuVoltage = 0;
volatile int16_t thermistorA = 0;
volatile int16_t thermistorB = 0;
volatile int16_t gateA = 0;
volatile int16_t gateB = 0;
volatile int16_t pidControlValue = 0;
volatile int16_t currentDacValue = 0;
volatile int16_t desiredSetPoint = 0;

volatile double dbVoltage = 0;
volatile double dbCurrent = 0;
volatile double dbThermistorA = 0;
volatile double dbThermistorB = 0;
volatile double dbGateA = 0;
volatile double dbGateB = 0;

static char buffer[BUFFERSIZE];
static uint16_t bufferCount = 0; // Used to track the number of characters in the buffer
uint16_t intCommand = 1100;

/*--------------------------------------------------------------------------------------*/

/*--------------------------- Declarations required for serial comms -------------------*/
static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_RW);
/*--------------------------------------------------------------------------------------*/

/* Function to initalise all peripheral hardware */
void peripheralStartup(void){
	//Fan pin as an output
	FANDDR |= (1 << FANPIN); 
	
	//LCD startup call
	lcdStart();
	//i2c interface startup
	i2c_init();
	//Ensure DAC is zero for start up. 
	dacOut(0);
	//adc startup
	adcInit();
	//timer 1 - seconds
	timer1Init();
	//Uart Begin
	uart_init();
	
	
	//encoderInit();
	
}
void lcdStart(void){
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_gotoxy(0,0);
	lcd_gotoxy(0,0);
	lcd_puts("PSU:");
	lcd_gotoxy(0,1);
	lcd_puts("Amps:");
	lcd_gotoxy(0,2);
	lcd_puts("TA:");
	lcd_gotoxy(10,2);
	lcd_puts("TB:");
	lcd_gotoxy(0,3);
	lcd_puts("GA:");
	lcd_gotoxy(10,3);
	lcd_puts("GB:");
}

void readValues(void){
	cli();
	psuVoltage = 0;
	currentA = 0;
	thermistorA = 0;
	thermistorB = 0;
	gateA = 0;
	gateB = 0;
	currentA = (adcRead(CURRENT));
//	printf("Current ADC : %d \n", currentA);
	psuVoltage = adcRead(VSUPPLY);
	thermistorA = adcRead(TEMPERATUREA);
	thermistorB = adcRead(TEMPERATUREB);
	//gateA = adcRead(GATEA);
	//gateB = adcRead(GATEB);
	
	dbVoltage = ((psuVoltage * 0.02652) + 0.273139921);
	dbCurrent = ((currentA * 0.005351) - 0.05895);
	
	dbThermistorA = ((thermistorA * 0.146047) - 54.1087);
	dbThermistorB = ((thermistorB * 0.15623) - 59.75);
	//dbGateA = ((gateA * 0.027691198680) + 0.021573037337);
	//dbGateB = ((gateB * 0.026898326874) + 0.084724831331);
	if(thermistorA > 500 || thermistorB > 500){
		fanStart();
	}
	if(thermistorA < 510 || thermistorB < 510){
		fanStop();
	}
	#ifdef SUPPLYDEBUG
	printf("PSU : %d %2.3f \t",psuVoltage, dbVoltage);
	printf("Current : %d %2.3f \n",currentA, dbCurrent);
	#endif
	#ifdef TEMPDEBUG
	printf("TEMPA : %d \t", thermistorA);
	printf("TEMPB : %d \n", thermistorB);
	#endif
	//currentLoop(desiredSetPoint);
	//updateLCD();
	sei();
}
void updateLCD(void){
	cli();
	lcd_gotoxy(5,0);
	lcd_puts("    ");
	lcd_gotoxy(5,0);
	int2string(psuVoltage);
	lcd_gotoxy(11,0);
	lcd_puts("    ");
	lcd_gotoxy(11,0);
	int2string(pidControlValue);
	float2string(dbVoltage);
	
	lcd_gotoxy(5,1);
	lcd_puts("    ");
	lcd_gotoxy(5,1);
	int2string(currentA);
	lcd_gotoxy(12,1);
	lcd_puts("    ");
	lcd_gotoxy(12,1);
	//int2string(currentA);
	float2string(dbCurrent);
	
	lcd_gotoxy(14,2);
	lcd_puts("    ");
	lcd_gotoxy(14,2);
	//int2string(thermistorB);
	float2string(dbThermistorB);
	
	lcd_gotoxy(4,2);
	lcd_puts("    ");
	lcd_gotoxy(4,2);
	//int2string(thermistorA);
	float2string(dbThermistorA);
/*	
	lcd_gotoxy(4,3);
	lcd_puts("   ");
	lcd_gotoxy(4,3);
	int2string(gateA);
	//float2string(dbGateA);
	
	lcd_gotoxy(14,3);
	lcd_puts("   ");
	lcd_gotoxy(14,3);
	int2string(gateB);
	//float2string(dbGateA);
*/
	sei();
}
void fanStart(void){
	FANPORT |= (1 << FANPIN);
}
void fanStop(void){
	
	FANPORT &= ~(1 << FANPIN);
}
void currentLoop(int16_t targetCurrent){
	pidControlValue = pidCalc(targetCurrent, currentA);
	dacOut(currentDacValue + pidControlValue);
	currentDacValue = currentDacValue + pidControlValue; // update global dac value
}
int main(void)
{
    /* Replace with your application code */
	stdout = &mystdout; //redirect stout to serial port
	peripheralStartup();
	
    while (1) 
    {
		
		//_delay_ms(1000);
		//readValues();
    }
}
/* -------------------- UART FUNCTIONS ----------------------------------------------------*/
void uart_init(void)
{
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);   // Turn on the transmission and reception circuitry & receive interrupt
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes

	UBRR0H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRR0L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
	printf("We have Comms! Electronic Load Project\n");
	sei();
}
static int uart_putchar(char c, FILE *stream)
{
	//handles character transmission throu stout and printf
	if (c == '\n')
	uart_putchar('\r', stream);
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = c;
	return 0;
}

void uart_receive(char data)
{
	
	if(bufferCount != BUFFERSIZE){
		buffer[bufferCount] = data;
		bufferCount++;
		}else{
		//clear the buffer and print warning to start again
		for(int i = 0; i < BUFFERSIZE; i++){
			buffer[i] = NULL;
		}
		bufferCount = 0; //reset buffer
	}
	
	if(data == 13){ //ascii for caridge return

		printf("Data Received : %s\n", buffer);
		intCommand = atoi(buffer);
		printf("Command : %d\n", intCommand);
		#ifdef PIDLOOP
		desiredSetPoint = intCommand;
		#endif
		#ifdef SERCOMMAND
		dacOut(intCommand);
		#endif
		for(int i = 0; i < BUFFERSIZE; i++){
			buffer[i] = NULL;
		}
		bufferCount = 0; //reset buffer
	}
	
}
ISR(USART0_RX_vect){
	uart_receive(UDR0);
}