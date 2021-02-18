#include <avr/interrupt.h>
#include "gpio.h"

void pin_mode(uint8_t direction_register, uint8_t pin, uint8_t direction)
{
	// direction = 0 -> input
	// direction = 1 -> output
	
	switch (direction)
	{
		case OUTPUT:
		//direction_register |= (1 << pin);
		setBit(direction_register, pin);
		
		case INPUT:
		//direction_register &= ~(1 << pin);
		clearBit(direction_register, pin);
		break;
		
		default:
		break;
	}
	
}

uint8_t binary_mode(uint8_t values_read[] , size_t size)
{
	/* count the occurrences of 1 and zero and return whichever occurs more */
	
	uint8_t zero_count = 0;
	uint8_t ones_count = 0;
	
	for(size_t i = 0; i < size; i++)
	{
		if(values_read[i] == 0)
		{
			zero_count++;
		}
		else
		{
			ones_count++;
		}
		
	}
	
	return (zero_count > ones_count ? zero_count : ones_count);
}

uint8_t digital_read_n(uint8_t pin_reg, uint8_t pin, uint8_t n)
{
	// read a pin n times
	
	uint8_t *reads_tmp = malloc(sizeof(uint8_t) * n);
	uint8_t mode_val = 0;
	
	for(uint8_t i = 0; i < n; i++)
	{
		reads_tmp[i] = digitalRead(pin_reg, pin);
		
	}
	
	mode_val = binary_mode(reads_tmp, (size_t)n);
	free(reads_tmp);
	
	return mode_val;
}

void init_pcint(uint8_t port, uint8_t mask)
{
	/* Initializes the pin change interrupts on certain pins of a certain port
	
		Mask should be a byte (A [7:0] vector) that sets the pins of a port. 
		Examples: 
			- 0xFF all pins are interrupts
			- 0x00 no pins are interrupts
			- 0x04 only pin 3 is an interrupt
			- 0x01 only pin 1 is an interrupt
			
		If you don't know how or feel like making the mask use the helper function create_pcint_mask 
	 */
	
	cli();
	
	switch(port)
	{
		#ifdef PORTA
		case PA:
			PCICR |= (1 << PCIE0);
			PCMSK0 |= mask;
			break;
		#endif
		
		#ifdef PORTB
		case PB:
			PCICR  |= (1 << PCIE1); 
			PCMSK1 |= mask;
			break;
		#endif
		
		#ifdef PORTC
		case PC:
			PCICR |= (1 << PCIE2);
			PCMSK2 |= mask;
			break; 
		#endif
		
		#ifdef PORTD
		case PD:
			PCICR |= (1 << PCIE3);
			PCMSK3 |= mask;
			break;
		#endif
	}
	
	sei();
	
}

uint8_t create_pcint_mask(uint8_t pins[])
{
	/* Takes in an array of pins which define which pins on a port should be pcint enabled */
	
	uint8_t mask = 0;
	
	for(uint8_t i = 0; i < 8; i++)
	{
		mask |= (pins[i] >> i);
		
	}
	
	return mask;
}