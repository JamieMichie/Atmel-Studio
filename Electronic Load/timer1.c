/*
 * timer1.c
 *
 * Created: 06/03/2020 19:48:21
 *  Author: Jamie Michie
 */ 
//Timer 1 functions. Used to count seconds
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "main.h"
#include "globals.h"

void timer1Init(void);
void displaySeconds(uint16_t seconds);
volatile uint16_t numberSeconds = 1; // variable to track the passing seconds.
void increaseSeconds(void);

void timer1Init(void){
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10); //1024 prescaler CTC mode
	TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B) ; //Interrupt on compare match
	OCR1A = 25624; //1 second counter - compare register value 15624 = 1 second update lcd every 1 second
	OCR1B = 10000; // read values every 500ms 
	sei();
}
/*
Function which increases the value of the global variable numberSeconds up to 60 seconds
*/
void increaseSeconds(void){
	if(numberSeconds < 60){
		numberSeconds++;
	}else{
		numberSeconds = 1;
	}
	readValues();
	#ifdef PIDLOOP
	currentLoop(desiredSetPoint);
	#endif
	//displaySeconds(numberSeconds);
}
/*
Function used to display the number of seconds on the lcd display. Mostly for debugging/testing. Minute and seconds timer will be needed for
psu testing functions
*/
void displaySeconds(uint16_t seconds){
	lcd_gotoxy(16,3);
	lcd_puts("    ");
	lcd_gotoxy(16,3);
	int2string(seconds);
}
ISR(TIMER1_COMPA_vect){
	//increaseSeconds();
	updateLCD();
}

ISR(TIMER1_COMPB_vect){
	readValues();
}