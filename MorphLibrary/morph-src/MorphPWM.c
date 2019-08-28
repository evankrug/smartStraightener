/*
 * MorphPWM.c
 *
 * Created: 1/10/2019 11:41:58 AM
 *  Author: 243400
 */ 

#ifndef MORPH_IMPLICIT

#include "include/MorphPWM.h"

#include "include/MorphUtils.h"

void (*morph_start_pwm_function)(MorphPinNumber) = &MorphUtils_empty_callback;
void (*morph_stop_pwm_function)(MorphPinNumber) = &MorphUtils_empty_callback;
void (*morph_set_pwm_duty_float_function)(MorphPinNumber, float) = &MorphUtils_empty_callback;
void (*morph_set_pwm_duty_64bit_function)(MorphPinNumber, uint64_t) = &MorphUtils_empty_callback;
void (*morph_set_pwm_duty_32bit_function)(MorphPinNumber, uint32_t) = &MorphUtils_empty_callback;
void (*morph_set_pwm_duty_16bit_function)(MorphPinNumber, uint16_t) = &MorphUtils_empty_callback;
void (*morph_set_pwm_duty_8bit_function)(MorphPinNumber, uint8_t) = &MorphUtils_empty_callback;

void MorphPWM_register_start_pwm(void (*function)(MorphPinNumber))
{
	morph_start_pwm_function = function;
}

void MorphPWM_register_stop_pwm(void (*function)(MorphPinNumber))
{
	morph_stop_pwm_function = function;	
}

void MorphPWM_register_set_pwm_duty_float(void (*function)(MorphPinNumber, double))
{
	morph_set_pwm_duty_float_function = function;	
}

void MorphPWM_register_set_pwm_duty_64bit(void (*function)(MorphPinNumber, uint64_t))
{
	morph_set_pwm_duty_64bit_function = function;	
}

void MorphPWM_register_set_pwm_duty_32bit(void (*function)(MorphPinNumber, uint32_t))
{
	morph_set_pwm_duty_32bit_function = function;	
}

void MorphPWM_register_set_pwm_duty_16bit(void (*function)(MorphPinNumber, uint16_t))
{
	morph_set_pwm_duty_16bit_function = function;	
}

void MorphPWM_register_set_pwm_duty_8bit(void (*function)(MorphPinNumber, uint8_t))
{
	morph_set_pwm_duty_8bit_function = function;
}

#endif

// Sets up the PWM for a specific pin.
void MorphPWM_start_pwm(MorphPinNumber pn)
{
	#ifdef MORPH_IMPLICIT
		morph_config_pwm_start_pwm(pn);
	#else
		morph_start_pwm_function(pn);
	#endif	
}

// Releases any resources that have been used. Also disables PWM.
void MorphPWM_stop_pwm(MorphPinNumber pn)
{
	#ifdef MORPH_IMPLICIT
		morph_config_pwm_stop_pwm(pn);
	#else
		morph_stop_pwm_function(pn);
	#endif	
}

// Takes a float from 0.0 to 1.0 and sets the output accordingly.
void MorphPWM_set_pwm_duty_float(MorphPinNumber pn, double duty)
{
	#ifdef MORPH_IMPLICIT
		morph_config_pwm_set_pwm_duty_float(pn, duty);
	#else
		morph_set_pwm_duty_float_function(pn, duty);
	#endif	
}

// Takes a number from 0 to 2^64 - 1 and sets the output duty based on this.
// This allows the conversion to use integer math, rather than float math.
// Note: The underlying resolution may not be 64 bits.
void MorphPWM_set_pwm_duty_64bit(MorphPinNumber pn, uint64_t duty)
{
	#ifdef MORPH_IMPLICIT
	morph_config_pwm_set_pwm_duty_64bit(pn, duty);
	#else
	morph_set_pwm_duty_64bit_function(pn, duty);
	#endif	
}

// Takes a number from 0 to 2^32 - 1 and sets the output duty based on this.
// This allows the conversion to use integer math, rather than float math.
// Note: The underlying resolution may not be 32 bits.
void MorphPWM_set_pwm_duty_32bit(MorphPinNumber pn, uint32_t duty)
{
	#ifdef MORPH_IMPLICIT
	morph_config_pwm_set_pwm_duty_32bit(pn, duty);
	#else
	morph_set_pwm_duty_32bit_function(pn, duty);
	#endif	
}

// Takes a number from 0 to 2^16 - 1 and sets the output duty based on this.
// This allows the conversion to use integer math, rather than float math.
// Note: The underlying resolution may not be 16 bits.
void MorphPWM_set_pwm_duty_16bit(MorphPinNumber pn, uint16_t duty)
{
	#ifdef MORPH_IMPLICIT
	morph_config_pwm_set_pwm_duty_16bit(pn, duty);
	#else
	morph_set_pwm_duty_16bit_function(pn, duty);
	#endif	
}

// Takes a number from 0 to 2^8 - 1 and sets the output duty based on this.
// This allows the conversion to use integer math, rather than float math.
// Note: The underlying resolution may not be 8 bits.
void MorphPWM_set_pwm_duty_8bit(MorphPinNumber pn, uint8_t duty)
{
	#ifdef MORPH_IMPLICIT
	morph_config_pwm_set_pwm_duty_8bit(pn, duty);
	#else
	morph_set_pwm_duty_8bit_function(pn, duty);
	#endif	
}
