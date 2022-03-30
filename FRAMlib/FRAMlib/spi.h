/*
 * spi.h
 *
 * Created: 29/03/2022 13:54:06
 *  Author: SS7U9741
 */ 


#ifndef SPI_H_
#define SPI_H_
#include <avr/io.h>

#define SPI_DDR  DDRB
#define SPI_PORT PORTB
#define SPI_MOSI PORTB2
#define SPI_SCK  PORTB1
#define SPI_MISO PORTB3
#define SPI_CS   PORTB5

#define SPI_DUMMY 0x00

uint8_t spi_init(void);
uint8_t spi_send(uint8_t udata);
uint8_t spi_receive(void);
void spi_CSLOW(void);
void spi_CSHIGH(void);

#endif /* SPI_H_ */