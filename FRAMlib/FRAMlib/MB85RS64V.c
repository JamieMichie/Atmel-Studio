/*
 * MB85RS64V.c
 *
 * Created: 29/03/2022 12:50:45
 *  Author: SS7U9741
 */ 
#include "MB85RS64V.h"

uint8_t fram_init(void){
	//setup SPI 
	//setup gpio
	//initialise fram IC
	
}
uint8_t fram_status(void){
	//CS low
	//Send RDSR opcode
	//Read status byte - MSB - - - - - - LSB
	//CS High
	//return Status byte
}

uint32_t fram_readID(void){
	
}
uint8_t fram_readByte(uint16_t address){
	
}
uint8_t fram_writeByte(uint16_t address);