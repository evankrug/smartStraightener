/*
 * MorphUART.c
 *
 * Created: 11/27/2018 3:49:01 PM
 *  Author: 243400
 */ 



#include "include/MorphTypes.h"
#include "include/MorphADC.h"
#include "include/MorphUtils.h"
#include "include/MorphOptions.h"


#ifndef MORPH_IMPLICIT

MorphADCValue (*morph_get_adc_value_function)(MorphADCChannel, MorphADCResolution) = &MorphUtils_empty_callback;

MorphADCValue (*morph_get_adc_pin_function)(MorphPinNumber, MorphADCResolution) = &MorphUtils_empty_callback;

void (*morph_init_adc_function)(MorphPinNumber) = &MorphUtils_empty_callback;

MorphADCValue (*morph_read_function)(MorphPinNumber) = &MorphUtils_empty_callback;

int8_t (*morph_set_resolution_function)(MorphPinNumber, MorphADCResolution) = &MorphUtils_empty_callback;

void (*morph_set_reference_function)(MorphPinNumber, enum MorphADCReference, uint8_t) = &MorphUtils_empty_callback;

void (*morph_set_prescaler_function)(MorphPinNumber, uint16_t) = &MorphUtils_empty_callback;

MorphADCValue (*morph_get_maximum_value_function)(MorphPinNumber) = &MorphUtils_empty_callback;


MorphADCValue MorphADC_register_get_adc_value_function(void (*function)(MorphADCChannel, MorphADCResolution))
{
	morph_get_adc_value_function = function;
}

MorphADCValue MorphADC_register_get_adc_pin_function(void (*function)(MorphPinNumber, MorphADCResolution))
{
	morph_get_adc_pin_function = function;
}


void MorphADC_register_init_adc_function(void (*function)(MorphPinNumber))
{
	morph_init_adc_function = function;
}

void MorphADC_register_read_function(MorphADCValue (*function)(MorphPinNumber))
{
	morph_read_function = function;
}

void MorphADC_register_set_resolution_function(int8_t (*function)(MorphPinNumber, MorphADCResolution))
{
	morph_set_resolution_function = function;
}

void MorphADC_register_set_reference_function(void (*function)(MorphPinNumber, enum MorphADCReference, uint8_t))
{
	morph_set_reference_function = function;	
}

void MorphADC_register_set_prescaler_function(void (*function)(MorphPinNumber, uint16_t))
{
	morph_set_prescaler_function = function;
}

void MorphADC_register_get_maximum_value(void (*function)(MorphPinNumber))
{
	morph_get_maximum_value_function = function;
}

#endif

// FUNCTIONS! //

MorphADCValue MorphADC_get_adc_value(MorphADCChannel c, MorphADCResolution res)
{
	#ifdef MORPH_IMPLICIT
		return morph_config_adc_get_adc_value(c, res);	
	#else
		return morph_get_adc_value_function(c, res);
	#endif
}

MorphADCValue MorphADC_get_adc_pin(MorphPinNumber p, MorphADCResolution res)
{
	#ifdef MORPH_IMPLICIT
	return morph_config_adc_get_adc_pin(p, res);
	#else
	return morph_get_adc_pin_function(p, res);
	#endif
}

// This does all the up-front work to get an ADC to function.
void MorphADC_init_adc(MorphPinNumber p)
{
	#ifdef MORPH_IMPLICIT
	return morph_config_adc_init_adc(p);
	#else
	return morph_init_adc_function(p);
	#endif
}

// This function attempts to read from the ADC and return a value.
MorphADCValue MorphADC_read(MorphPinNumber p)
{
	#ifdef MORPH_IMPLICIT
	return morph_config_adc_read(p);
	#else
	return morph_read_function(p);
	#endif	
}

// Attempts to set the resolution of the ADC.
// Returns the actual ADC resolution.
int8_t MorphADC_set_resolution(MorphPinNumber p, MorphADCResolution res)
{
	#ifdef MORPH_IMPLICIT
	return morph_config_adc_set_resolution(p, res);
	#else
	return morph_set_resolution_function(p, res);
	#endif	
}

// This function sets the reference of a given ADC input.
// The reference may be set to Internal or External, then a number that identifies which external or internal ref.
// Since external and internal reference options change wildly between processors, take a look at the datasheet for this one.
void MorphADC_set_reference(MorphPinNumber p, enum MorphADCReference ref, uint8_t ref_num)
{
	#ifdef MORPH_IMPLICIT
	return morph_config_adc_set_reference(p, ref, ref_num);
	#else
	return morph_set_reference_function(p, ref, ref_num);
	#endif	
}

// This function sets the prescaler for the given ADC input.
// You need to be aware of the clock speed of your system for this to make any sense.
void MorphADC_set_prescaler(MorphPinNumber p, uint16_t prescaler)
{
	#ifdef MORPH_IMPLICIT
	return morph_config_adc_set_prescaler(p, prescaler);
	#else
	return morph_set_prescaler_function(p, prescaler);
	#endif	
}

// This function will get the maximum value an ADC channel may return.
MorphADCValue MorphADC_get_maximum_value(MorphPinNumber p)
{
	#ifdef MORPH_IMPLICIT
	return morph_config_adc_get_maximum_value(p);
	#else
	return morph_get_maximum_value_function(p);
	#endif	
}