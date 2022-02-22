/*
 * adc.c
 *
 * Created: 06/03/2020 15:18:49
 *  Author: Jamie Michie
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"

void adcInit(void){
	/* This function is used to startup the adc for free running mode.
	*/
	
	//ADMUX |= ( 1 << REFS0); //reference voltage applied to AVCC pin. 5V ref onboard pcb
	///ADCSRA |= (1 << ADEN) |(1 << ADPS2); //1MHZ sample rate
	//ADCSRA |= (1 << ADEN) |(1 << ADPS1) | (1 << ADPS2); //250KHz sample rate
	ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); //125KHz sample rate
	ADCSRA |= (1 << ADSC); //Start Conversion
}

uint16_t adcRead(uint8_t channel){
	/* adcRead function is used by other functions to receive a reading form the adc channel required. The value is returned as an unsigned 16bit value for processing
	by the calling function. the adc is 12bits so a  maximum value of 1023 is equal to 5V.
	*/
	cli();
	volatile uint16_t adcValue = 0;
	uint16_t adcTotal = 0;
	switch(channel){
		//ADC control for DAC
		case 0 :
		ADMUX &= ~(0x1F); // channel 0 VSUPPLY
		ADCSRA |= (1 << ADSC); //Start Conversion
		break;
		//Read VSS ADC
		case 1 :
		ADMUX &= ~(0x1F); //
		ADMUX |= (1 << MUX0); //Channel 1 CURRENT
		ADCSRA |= (1 << ADSC); //Start Conversion
		break;
		//Read output voltage from DAC
		case 2 :
		ADMUX &= ~(0x1F);
		ADMUX |= (1 << MUX1); //Channel 2 TEMPERATURE of FET A
		ADCSRA |= (1 << ADSC); //Start Conversion
		break;
		
		case 3 :
		ADMUX &= ~(0x1F);
		ADMUX |= (1 << MUX1) | (1 << MUX0) ; //Channel 3 temperature of FET B
		ADCSRA |= (1 << ADSC); //Start Conversion
		break;
		
		case 6 :
		ADMUX &= ~(0x1F);
		ADMUX |= (1 << MUX1) | (1 << MUX2) ; //Channel 6 Gate A voltage
		ADCSRA |= (1 << ADSC); //Start Conversion
		break;
		
		case 7 :
		ADMUX &= ~(0x1F);
		ADMUX |= (1 << MUX0) | (1 << MUX1) | (1 << MUX2) ; //Channel 7 Gate B voltage
		ADCSRA |= (1 << ADSC); //Start Conversion
		break;
	}
	//DISGUARD FIRST ADC READ
	while(ADCBUSY);
	adcValue |= ADC;
	adcValue = 0; // Throw away first read after channel changes. Allow the adc to start a fresh cycle
	/* Take a 32 sample average */
	//for(int i = 0; i < 63; i++){
	ADCSRA |= (1 << ADSC); //Start Conversion
	while(ADCBUSY);
	adcValue |= ADC;
	//adcTotal += adcValue;
	//}
	//adcValue = (adcTotal >> 6);
	sei();
	return adcValue;
}