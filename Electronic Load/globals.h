/*
 * globals.h
 *
 * Created: 14/03/2020 18:10:15
 *  Author: Jamie Michie
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_


//define global variables
extern volatile int16_t currentA;
extern volatile int16_t psuVoltage;
extern volatile int16_t thermistorA;
extern volatile int16_t thermistorB;
extern volatile int16_t gateA;
extern volatile int16_t gateB;
extern volatile int16_t pidControlValue;
extern volatile int16_t currentDacValue;
extern volatile int16_t desiredSetPoint;

extern volatile double dbVoltage;
extern volatile double dbCurrent;
extern volatile double dbThermistorA ;
extern volatile double dbThermistorB;
extern volatile double dbGateA;
extern volatile double dbGateB;


#endif /* GLOBALS_H_ */