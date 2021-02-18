#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>
#include <stdlib.h>
#include <stdint.h>

// direction = 0 -> input
// direction = 1 -> output
#define INPUT  (0)
#define OUTPUT (1)


#define clearBit(REG, BIT)	(REG &= ~(1 << BIT))
#define setBit(REG, BIT)		(REG |= (1 << BIT)) 
#define maskRegister(REG, MASK) (REG |= MASK)
enum port_enumeration
{
	PA,
	PB,
	PC,
	PD
};

static inline uint8_t digitalRead(uint8_t pin_reg,uint8_t pin)
{
	return ((pin_reg & (1 << pin)) >> pin);
}

static inline void digitalWriteHigh(uint8_t port, uint8_t pin) 
{
	port |= (1 << pin);
}

static inline void digitalWriteLow(uint8_t port, uint8_t pin)
{
	   port &= ~(1 << pin);
}

void pin_mode(uint8_t direction_register, uint8_t pin, uint8_t direction); // sets pin as input or output

void init_pcint(uint8_t port, uint8_t mask);

uint8_t binary_mode(uint8_t values_read[], size_t size);
uint8_t digital_read_n(uint8_t pin_reg, uint8_t pin, uint8_t n);

uint8_t init_pcint(uint8_t port, uint8_t mask);
uint8_t create_pcint_mask(uint8_t pins[]);

#endif