/*
 * main.h
 *
 * Created: 06/03/2020 15:19:57
 *  Author: Jamie Michie
 */ 


#ifndef MAIN_H_
#define MAIN_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "lcd.h"
#include "pins.h"
#include "i2cmaster.h"

#define BUFFERSIZE 12
#define NEWLINE \n
#define CUTOFFTEMP 100
#define FANSTARTTEMP 550
#define FANSTOPTEMP 450

// debugging defines. Enables printf statements
#define DACDEBUG // print out dac value 
#define SERCOMMAND // enables serial control so that dac output can be controlled via uart
//#define TEMPDEBUG // Prints ADC uints for each thermistor
#define SUPPLYDEBUG // prints current and voltage values. Doubles and uints
//#define PIDLOOP // Enables pid loop mode to control current

#define ADCBUSY (ADCSRA & (1<<ADSC))

//Timer 1 prototypes
void timer1Init(void);

void peripheralStartup(void);
void lcdStart(void);
void fanStart(void);
void fanStop(void);
void dacOut(int16_t output);
void adcInit(void);
void readSupVoltage(void);
uint16_t adcRead(uint8_t channel);
double getTemperature(void);
void displayCurrent(void);
void readValues(void);
void updateLCD(void);
void uart_init(void);
void currentLoop(int16_t targetCurrent);



#endif /* MAIN_H_ */