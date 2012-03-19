/*
 * SERIAL PORT
 */
#include "../include/Ports.h"
#include "../../../../library/include/types.h"



#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_

#define IER 1 // Interrupt Enable Register
#define IIR 2 // Interrupt Identification Register
#define FCR 2 // FIFO Control Register
#define LCR 3 // Line Control Register
#define MCR 4 // Modem Control Register
#define LSR 5 // Line Status Register
#define MSR 6 // Modem Status Register
#define SCR 7 // Scratch Register


typedef struct
{
	/* Base address of port */
	uint16 base;

	/* Baud rate */
	uint16 baud;

	/* Parity */
	byte parity;

	/* Bits */
	byte bits;

} SerialPort;

/*
 *
 */
void SerialPort_Initialize(SerialPort *self, uint16 base, uint16 baud, byte parity, byte bits);

/*
 *
 */
uint8 SerialPort_Read(SerialPort *self);

/*
 *
 */
void SerialPort_Write(SerialPort *self, byte bits);

/*
 *
 */
uint8 SerialPort_Received(SerialPort *self);

/*
 *
 */
uint8 SerialPort_TransmitEmpty(SerialPort *self);


#endif // #ifndef _SERIAL_PORT_H_
