/*
 * Element7SegGPIODriver.c
 *
 * Created: 12/12/2018 3:19:18 PM
 *  Author: 243400
 */ 

#include <MorphTypes.h>
#include <MorphGPIO.h>


#include "include/ElementConfig.h"
#include "include/Element7SegGPIODriver.h"

Element7SegGPIODriverStruct segment_configs[MAX_CONCURRENT_DISPLAYS] = {0};

uint8_t current_display_count = 0;

// When a new display is created, a couple pieces of information are needed.
// 1. The location of all 7-8 GPIO pins, driving A - G and DP respectively.
// 2. The location of all multiplexing GPIO pins, along with how many.
void Element7SegGPIODriver_init(MorphPinNumber * bit_gpios, uint8_t bit_count, MorphPinNumber * digit_locations, uint8_t digit_count, ElementAnimationBufferConfigStruct * buffer)
{
	
	if(current_display_count >= MAX_CONCURRENT_DISPLAYS)
	{
		// Please leave.
		return;
	}
	
	segment_configs[current_display_count].buffer = buffer;
	
	segment_configs[current_display_count].num_bits = bit_count;
	
	for(uint8_t i = 0; i < bit_count && i < MAX_ELEMENT_7SEG_GPIO_BITS; i++)
	{
		// Populate the bit array.
		segment_configs[current_display_count].bit_locations[i] = bit_gpios[i];	
		
		// Ensure the GPIOs are setup for output.
		MorphGPIO_set_pin_direction(bit_gpios[i], Output);
		
		// High turns them off.
		MorphGPIO_set_pin_value(bit_gpios[i], High);
		
	}

	segment_configs[current_display_count].num_digits = digit_count;

	for(uint8_t i = 0; i < digit_count && i < MAX_ELEMENT_7SEG_GPIO_DIGITS; i++)
	{
		// Populate the display array.
		segment_configs[current_display_count].digit_location[i] = digit_locations[i];

		// Ensure the GPIOs are setup for output.
		MorphGPIO_set_pin_direction(digit_locations[i], Output);
	}
	
	current_display_count++;
	
}

void Element7SegGPIODriver_update()
{
	
	for(uint8_t i = 0; i < current_display_count; i ++)
	{

		Element7SegGPIODriverStruct * driver_struct = &segment_configs[i];

		// Turn off the current digit.
		MorphGPIO_set_pin_value(driver_struct->digit_location[driver_struct->current_digit], Low);

		// Update the current digit to the correct digit.
		driver_struct->current_digit = (int16_t)(driver_struct->current_digit + 1) < driver_struct->num_digits ? driver_struct->current_digit + 1 : 0; 

		uint8_t new_byte = Element7Seg_get_byte(driver_struct->buffer, driver_struct->current_digit);			


		
		// Now, update the output
		for(uint8_t i = 0; i < driver_struct->num_bits; i ++)
		{

			// Throw the pin to High before setting it officially.
			MorphGPIO_set_pin_value(driver_struct->bit_locations[i], High);

			enum MorphPinValue val = Element7Seg_get_bit(driver_struct->buffer, driver_struct->current_digit, i) == 0 ? Low : High;

			MorphGPIO_set_pin_value(driver_struct->bit_locations[i], val);

		}

		// Turn the new digit on.
		MorphGPIO_set_pin_value(driver_struct->digit_location[driver_struct->current_digit], High);


	}
	
	
}
