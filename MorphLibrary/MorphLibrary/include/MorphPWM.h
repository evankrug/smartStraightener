/*
 * MorphPWM.h
 *
 * Created: 1/10/2019 11:41:45 AM
 *  Author: 243400
 */ 


#ifndef MORPHPWM_H_
#define MORPHPWM_H_

#include <stdint.h>

#include "MorphUtils.h"
#include "MorphOptions.h"
#include "MorphTypes.h"


#ifndef MORPH_IMPLICIT

// MORPH_IMPLICIT means the functions will not be implemented with function pointers.
// Instead, it will call the (possibly) implemented functions directly.
// This is more dangerous, however, it might see performance gains through compiler optimization.

void MorphPWM_register_start_pwm(void (*function)(MorphPinNumber));

void MorphPWM_register_stop_pwm(void (*function)(MorphPinNumber));

void MorphPWM_register_set_pwm_duty_float(void (*function)(MorphPinNumber, double));

void MorphPWM_register_set_pwm_duty_64bit(void (*function)(MorphPinNumber, uint64_t));

void MorphPWM_register_set_pwm_duty_32bit(void (*function)(MorphPinNumber, uint32_t));

void MorphPWM_register_set_pwm_duty_16bit(void (*function)(MorphPinNumber, uint16_t));

void MorphPWM_register_set_pwm_duty_8bit(void (*function)(MorphPinNumber, uint8_t));

#endif

// Sets up the PWM for a specific pin. 
void MorphPWM_start_pwm(MorphPinNumber pn);

// Releases any resources that have been used. Also disables PWM.
void MorphPWM_stop_pwm(MorphPinNumber pn);

// Takes a float from 0.0 to 1.0 and sets the output accordingly.
void MorphPWM_set_pwm_duty_float(MorphPinNumber pn, double duty);

// Takes a number from 0 to 2^64 - 1 and sets the output duty based on this.
// This allows the conversion to use integer math, rather than float math.
// Note: The underlying resolution may not be 64 bits.
void MorphPWM_set_pwm_duty_64bit(MorphPinNumber pn, uint64_t duty);

// Takes a number from 0 to 2^32 - 1 and sets the output duty based on this.
// This allows the conversion to use integer math, rather than float math.
// Note: The underlying resolution may not be 32 bits.
void MorphPWM_set_pwm_duty_32bit(MorphPinNumber pn, uint32_t duty);

// Takes a number from 0 to 2^16 - 1 and sets the output duty based on this.
// This allows the conversion to use integer math, rather than float math.
// Note: The underlying resolution may not be 16 bits.
void MorphPWM_set_pwm_duty_16bit(MorphPinNumber pn, uint16_t duty);

// Takes a number from 0 to 2^8 - 1 and sets the output duty based on this.
// This allows the conversion to use integer math, rather than float math.
// Note: The underlying resolution may not be 8 bits.
void MorphPWM_set_pwm_duty_8bit(MorphPinNumber pn, uint8_t duty);

#endif /* MORPHPWM_H_ */