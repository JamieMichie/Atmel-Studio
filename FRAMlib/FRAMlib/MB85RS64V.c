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
	return 0;
}

/*FRAM ID function
Function which checks the manufacturer ID 0x04 Fujitsu
Continuation code 0x7F
Product ID 0x03  = 64kbit
product Id2 0x02 
Confirms spi communication with the FRAM IC is working correctly
Returns 0 for success
Returns 1 for failure 
 */
uint8_t fram_id(void){
	volatile uint8_t retval;
	volatile uint32_t checkval = 0x00000000; 
	
	spi_CSLOW();
		retval = spi_send(FRAM_RDID);
		retval = spi_send(FRAM_RDID);
		checkval |= ((uint32_t)retval << 24);
		retval = spi_send(FRAM_RDID);
		checkval |= ((uint32_t)retval << 16);
		retval = spi_send(FRAM_RDID);
		checkval |= (retval << 8);
		retval = spi_send(FRAM_RDID);
		checkval |= (retval);
		retval = spi_send(FRAM_RDID);
	spi_CSHIGH();
	
	if(checkval == 0x047f0302){
		return 0;
	}else{
		return 1;
	}
}
/* Fram Status Function
Returns value from the Status register
*/
uint8_t fram_status(void){
	volatile uint8_t retval = 0;
	spi_CSLOW();
		retval = spi_send(FRAM_RDSR);
		retval = spi_send(FRAM_RDSR);
	spi_CSHIGH();
	return retval;
}

/* NEEDS WORK */
uint8_t fram_readByte(uint16_t address){
	uint8_t retval = 0;
	spi_CSLOW();
		//spi_send(FRAM_WRDI);
		spi_send(FRAM_READ);
		//Address is 16bits long
		spi_send((address << 8));
		spi_send(address);
		retval = spi_send(SPI_DUMMY);
		retval = spi_send(SPI_DUMMY);
	spi_CSHIGH();
	
	return retval;
}

/* NEEDS WORK */
uint8_t fram_writeByte(uint16_t address, uint8_t udata)
{
	spi_CSLOW();
		spi_send(FRAM_WREN);
		spi_send(FRAM_WRITE);
		spi_send((address << 8));
		spi_send(address);
		spi_send(udata);
	spi_CSHIGH(); 
	
	return 0;
}