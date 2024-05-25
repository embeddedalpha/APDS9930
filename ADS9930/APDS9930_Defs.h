/*
 * APDS9930_Defs.h
 *
 *  Created on: Jan 31, 2024
 *      Author: kunal
 */

#ifndef APDS9930_DEFS_H_
#define APDS9930_DEFS_H_


#include "APDS9930.h"


static const struct APDS9930_Regs{
	uint8_t		ENABLE		;	//	Enable of states and interrupts
	uint8_t		ATIME		;	//	ALS ADC time
	uint8_t		PTIME		;	//	Proximity ADC time
	uint8_t		WTIME		;	//	Wait time
	uint8_t		AILTL		;	//	ALS interrupt low threshold low byte
	uint8_t		AILTH		;	//	ALS interrupt low threshold hi byte
	uint8_t		AIHTL		;	//	ALS interrupt hi threshold low byte
	uint8_t		AIHTH		;	//	ALS interrupt hi threshold hi byte
	uint8_t		PILTL		;	//	Proximity interrupt low threshold low byte
	uint8_t		PILTH		;	//	Proximity interrupt low threshold hi byte
	uint8_t		PIHTL		;	//	Proximity interrupt hi threshold low byte
	uint8_t		PIHTH		;	//	Proximity interrupt hi threshold hi byte
	uint8_t		PERS		;	//	Interrupt persistence filters
	uint8_t		CONFIG		;	//	Configuration
	uint8_t		PPULSE		;	//	Proximity pulse count
	uint8_t		CONTROL		;	//	Gain control register
	uint8_t		ID		    ;	//	Device ID
	uint8_t		STATUS		;	//	Device status
	uint8_t		Ch0DATAL	;	//	Ch0 ADC low data register
	uint8_t		Ch0DATAH	;	//	Ch0 ADC high data register
	uint8_t		Ch1DATAL	;	//	Ch1 ADC low data register
	uint8_t		Ch1DATAH	;	//	Ch1 ADC high data register
	uint8_t		PDATAL		;	//	Proximity ADC low data register
	uint8_t		PDATAH		;	//	Proximity ADC high data register
	uint8_t		POFFSET		;	//	Proximity offset register

}APDS9930_Regs = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1E};



#endif /* APDS9930_DEFS_H_ */
