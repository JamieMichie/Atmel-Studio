/*
 * encoder.c
 *
 * Created: 16/03/2020 16:49:20
 *  Author: Jamie Michie
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"
#define A PB1
#define B PB2
#define SWITCH PB0

#define ENCODERPORT PORTB
// PB1 is PCINT9
// PB2 is PCINT10
// PB0 is PCINT8
#define ACHANGED !(PINB & ( 1 << PB1))
#define BCHANGED !(PINB & ( 1 << PB2))
#define BUTTONPRESSED !(PINB & ( 1 << PB0))

//set A & B as Inputs and enable pinchange interrupts
void encoderInit(void);
volatile int16_t encoderValue = 0; //USed to track turns

void encoderInit(void){
	EICRA |= (1 << ISC10) | (1 << ISC11); //trigger on rising edge change only. Stopped a double interrupt on each turn
	PCICR |= (1 << PCIE1); // ENABLE PIN CHANGE INTERRUPTS ON ENCODER PORT
	PCMSK1 |= (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT8); //ENABLE INTERRUPTS ON EACH PIN
	PORTB |= (1 << SWITCH) | (1 << A) | (1 << B); //ACTIVATE PULLUP 
 }
 
 ISR(PCINT1_vect){
	 
 }