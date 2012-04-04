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
	uint16_t m_base;

	/* Baud rate */
	uint16_t m_baud;

	/* Parity */
	byte_t m_parity;

	/* Bits */
	byte_t m_bits;

} SerialPort;

/*
 *
 */
void SerialPort_Initialize(SerialPort *self, uint16_t base, uint16_t baud, byte_t parity, byte_t bits);

/*
 *
 */
uint8_t SerialPort_Read(SerialPort *self);

/*
 *
 */
void SerialPort_Write(SerialPort *self, byte_t bits);

/*
 *
 */
uint8_t SerialPort_Received(SerialPort *self);

/*
 *
 */
uint8_t SerialPort_TransmitEmpty(SerialPort *self);


#endif // #ifndef _SERIAL_PORT_H_
