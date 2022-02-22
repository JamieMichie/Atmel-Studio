/*
 * pidLoop.c
 *
 * Created: 14/03/2020 09:42:34
 *  Author: jampot
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int16_t pidCalc(int16_t setPoint, int16_t measuredCurrent);

volatile int8_t kp = 1;
volatile int8_t ki = 1;
volatile int8_t kd = 1;
volatile int16_t integral = 0;
volatile int16_t lastError = 0;

int16_t pidCalc(int16_t setPoint, int16_t measuredCurrent){
	int16_t error = 0;
	int16_t controlOutput = 0; // Value to be applied to the dacOut
	int16_t dirivative = 0;
	error = setPoint - measuredCurrent;
	dirivative = error - lastError;
	if(integral < 32767){
		integral = integral + error;
	}else{
		integral = error;
	}
	controlOutput = (kp * error); //+ (ki * integral) + (kd * dirivative));
	lastError = error;
	return controlOutput;
}