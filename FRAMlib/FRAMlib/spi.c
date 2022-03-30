/*
 * spi.c
 *
 * Created: 29/03/2022 13:53:55
 *  Author: SS7U9741
 */ 
#include "spi.h"

uint8_t spi_init(void){
	/* MOSI = OUTPUT, MISO = OUTPUT, SCK = OUTPUT */
	 SPI_DDR |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_CS); 
	 SPI_DDR &= ~(1 << SPI_MISO);
	 /* Enable SPI, Master Mode, Set Clock */
	 SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0); 
	 SPI_PORT |= (1 << SPI_CS);
}

uint8_t spi_send(uint8_t udata){
	SPDR = udata;
	while(!(SPSR & (1 << SPIF)))
		;
	return SPDR;
}

void spi_CSLOW(void){
	SPI_PORT &= ~(1 << SPI_CS);
}

void spi_CSHIGH(void){
	SPI_PORT |= (1 << SPI_CS);
}