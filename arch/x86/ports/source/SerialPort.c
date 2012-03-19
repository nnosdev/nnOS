#include "../include/SerialPort.h"

/*
 *
 */
void SerialPort_Initialize(SerialPort *self, uint16 base, uint16 baud,
		byte parity, byte bits) {

	// Store configuration
	self->base = base;
	self->baud = baud;
	self->parity = parity;
	self->bits = bits;

	union {
		uint8 b[2];
		uint16 w;
	} divisor;

	divisor.w = 115200 / baud;

	// Disable all interrupts
	outb(self->base + IER, 0x00);

	// Set DLAP bit
	outb(self->base + LCR, 0x80);

	// Set divisor (low)
	//outb(self->base, divisor.b[0]);
	outb(self->base, 0x03);

	// Set divisor (high)
	//outb(self->base + 1, divisor.b[1]);
	outb(self->base + 1, 0x00);

	// Set amount of bits, parity, .. and reset DLAB
	//outb(self->base + LCR, ((parity & 0x7) << 3) | ((bits - 5) & 0x3));
	outb(self->base + LCR, 0x03);

	// Complete initialization
	outb(base + FCR, 0xC7);
	outb(base + MCR, 0x0B);
}

/*
 *
 */
uint8 SerialPort_Read(SerialPort *self) {
	while (SerialPort_Received(self)) { /* Do nothing */
	}

	return inb(self->base);
}

/*
 *
 */
void SerialPort_Write(SerialPort *self, byte bits) {
	while (SerialPort_TransmitEmpty(self) == 0) { /* Do nothing */
	}

	outb(self->base, bits);
}

/*
 *
 */
uint8 SerialPort_Received(SerialPort *self) {
	return inb(self->base + LSR) & 0x1;
}

/*
 *
 */
uint8 SerialPort_TransmitEmpty(SerialPort *self) {
	return inb(self->base + LSR) & 0x20;
}