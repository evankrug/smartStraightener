/*
 * MorphADC.h
 *
 * Created: 11/13/2018 3:24:16 PM
 *  Author: 243400
 */ 


#ifndef MORPHADC_H_
#define MORPHADC_H_

#include <stdint.h>

#include "MorphTypes.h"


#ifndef MORPH_IMPLICIT

// MORPH_IMPLICIT means the functions will not be implemented with function pointers.
// Instead, it will call the (possibly) implemented functions directly.
// This is more dangerous, however it might see performance gains through compiler optimization.

MorphADCValue MorphADC_register_get_adc_value_function(void (*function)(MorphADCChannel, MorphADCResolution));

MorphADCValue MorphADC_register_get_adc_pin_function(void (*function)(MorphPinNumber, MorphADCResolution));

void MorphADC_register_init_adc_function(void (*function)(MorphPinNumber));

void MorphADC_register_read_function(MorphADCValue (*function)(MorphPinNumber));

void MorphADC_register_set_resolution_function(int8_t (*function)(MorphPinNumber, MorphADCResolution));

void MorphADC_register_set_reference_function(void (*function)(MorphPinNumber, enum MorphADCReference, uint8_t));

void MorphADC_register_set_prescaler_function(void (*function)(MorphPinNumber, uint16_t));

void MorphADC_register_get_maximum_value(void (*function)(MorphPinNumber));

#endif


// Gets the ADC value from the cth channel that is capable of the resolution stated.
MorphADCValue MorphADC_get_adc_value(MorphADCChannel c, MorphADCResolution res);

// This does all the up-front work to get an ADC to function.
void MorphADC_init_adc(MorphPinNumber p);

// This function attempts to read from the ADC and return a value.
MorphADCValue MorphADC_read(MorphPinNumber p);

// Attempts to set the resolution of the ADC.
// Returns the actual ADC resolution.
int8_t MorphADC_set_resolution(MorphPinNumber p, MorphADCResolution res);

// This function sets the reference of a given ADC input.
// The reference may be set to Internal or External, then a number that identifies which external or internal ref.
// Since external and internal reference options change wildly between processors, take a look at the datasheet for this one.
void MorphADC_set_reference(MorphPinNumber p, enum MorphADCReference ref, uint8_t ref_num);

// This function sets the prescaler for the given ADC input. 
// You need to be aware of the clock speed of your system for this to make any sense.
void MorphADC_set_prescaler(MorphPinNumber p, uint16_t prescaler);

// This function will get the maximum value an ADC channel may return.
MorphADCValue MorphADC_get_maximum_value(MorphPinNumber p);

// Sets the prescaler on the specified channel.
//MorphADCValue MorphADC_set_adc_prescaler(MorphADCChannel c, );

//void MorphADC_set_channel_resolution(MorphADCChannel c, MorphADCResolution res);

#endif /* MORPHADC_H_ */