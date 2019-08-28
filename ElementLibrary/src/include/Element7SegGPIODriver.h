/*
 * Element7SegGPIODriver.h
 * This driver is made to drive 7-segment displays that are 
 * connected directly with GPIO pins, and are also multiplexed.
 * Created: 12/12/2018 3:01:55 PM
 *  Author: 243400
 */ 


#ifndef ELEMENT7SEGGPIODRIVER_H_
#define ELEMENT7SEGGPIODRIVER_H_

#include <inttypes.h>

#include <MorphGPIO.h>

#define MAX_CONCURRENT_DISPLAYS 2 

#define MAX_ELEMENT_7SEG_GPIO_BITS 8
 
#define MAX_ELEMENT_7SEG_GPIO_DIGITS 10

typedef struct element_7_seg_gpio_driver_struct{
	uint8_t num_bits; // This basically just signifies if the 8th bit will be used.
	uint8_t num_digits; // How many displays will be driven?
	MorphPinNumber bit_locations[MAX_ELEMENT_7SEG_GPIO_BITS];
	MorphPinNumber digit_location[MAX_ELEMENT_7SEG_GPIO_DIGITS];
	uint8_t current_digit; //The digit currently being displayed.
	ElementAnimationBufferConfigStruct * buffer; // The buffer for this display.
} Element7SegGPIODriverStruct;



// When a new display is created, a couple pieces of information are needed.
// 1. The location of all 7-8 GPIO pins, driving A - G and DP respectively. 
// 2. The location of all multiplexing GPIO pins, along with how many.
void Element7SegGPIODriver_init(MorphPinNumber * bit_gpios, uint8_t bit_count, MorphPinNumber * digit_locations, uint8_t digit_count, ElementAnimationBufferConfigStruct * buffer);

// This function moves the currently displayed digit over by 1 (and wraps, duh).
// This would be a great function to call through an interrupt.
void Element7SegGPIODriver_update();



#endif /* ELEMENT7SEGGPIODRIVER_H_ */