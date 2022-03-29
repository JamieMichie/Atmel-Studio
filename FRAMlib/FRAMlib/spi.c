/*
 * spi.c
 *
 * Created: 29/03/2022 13:53:55
 *  Author: SS7U9741
 */ 
#include "spi.h"

uint8_t spi_init(void){
	/* MOSI = OUTPUT, MISO = OUTPUT, SCK = OUTPUT */
	 SPI_DDR |= (1 << SPI_MISO) | (1 << SPI_SCK) | (1 << SPI_CS); 
	 /* Enable SPI, Master Mode, Set Clock */
	 SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0); 
}

uint8_t spi_send(uint8_t udata){
	SPI_PORT &= ~(1 << SPI_CS);
	SPDR = udata;
	while(!(SPSR & (1 << SPIF)))
		;
	SPI_PORT |= (1 << SPI_CS);
	return SPDR;
}
uint8_t spi_receive(uint8_t udata){
	
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
		;
	/* Return Data Register */
	return SPDR;
}