/*
 * dac.c
 *
 * Created: 06/03/2020 20:21:31
 *  Author: Jamie Michie
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "i2cmaster.h"
#include "main.h"

void dacOut(int16_t output){
	volatile int8_t highByte = 0;
	volatile int8_t lowByte = 0;
	highByte = (output >> 4);
	lowByte |= (output << 4);
	i2c_start_wait(ADDW);
	i2c_write(0x40);
	i2c_write(highByte);
	i2c_write(lowByte);
	#ifdef DACDEBUG
	printf("Dac Reading : %d\n", output);
	#endif
}