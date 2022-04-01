/*
 * MB85RS64V.h
 *
 * Created: 29/03/2022 12:50:56
 *  Author: SS7U9741
 */ 


#ifndef MB85RS64V_H_
#define MB85RS64V_H_
#include <avr/io.h>
#include "spi.h"

/* CONSTANTS */
#define FRAM_SIZE 8192

/* OP CODES */
#define FRAM_WREN  0X06
#define FRAM_WRDI  0X04
#define FRAM_RDSR  0X05
#define FRAM_WRSR  0X01
#define FRAM_READ  0X03
#define FRAM_WRITE 0X02
#define FRAM_RDID  0X9F

/* FUNCTION PROTOTYPES */
uint8_t fram_init(void);
uint8_t fram_id(void);
uint8_t fram_status(void);
uint8_t fram_WREN(void);
uint8_t fram_readByte(uint16_t address);
uint8_t fram_writeByte(uint16_t address, uint8_t udata);
uint8_t fram_write(uint16_t address, uint8_t *udata, uint8_t nbytes);
uint8_t fram_WRDI(void);
uint8_t fram_eraseAll(void);
#endif /* MB85RS64V_H_ */