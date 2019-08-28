/*
 * MorphGPIO.h
 *
 * Created: 11/13/2018 3:19:36 PM
 *  Author: 243400
 */ 


#ifndef MORPHGPIO_H_
#define MORPHGPIO_H_

#include "MorphUtils.h"
#include "MorphOptions.h"
#include "MorphTypes.h"


#ifndef MORPH_IMPLICIT

// MORPH_IMPLICIT means the functions will not be implemented with function pointers.
// Instead, it will call the (possibly) implemented functions directly. 
// This is more dangerous, however, it might see performance gains through compiler optimization.

void MorphGPIO_register_set_pin_value_function(void (*function)(MorphPinNumber, enum MorphPinValue));

void MorphGPIO_register_get_pin_value_function(enum MorphPinValue (*function)(MorphPinNumber));

void MorphGPIO_register_set_pin_direction_function(void (*function)(MorphPinNumber, enum MorphPinDirection));

void MorphGPIO_register_get_pin_direction_function(enum MorphPinDirection (*function)(MorphPinNumber));

void MorphGPIO_register_set_pin_pull_state_function(void (*function)(MorphPinNumber, enum MorphPinPullState));

void MorphGPIO_register_get_pin_pull_state_function(enum MorphPinPullState (*function)(MorphPinNumber));

void MorphGPIO_register_set_pin_interrupt_function(void (*function)(void (*)(void), MorphPinNumber, enum MorphExternalInterruptType));

void MorphGPIO_register_unset_pin_interrupt_function(void (*function)(MorphPinNumber, enum MorphPinValue));



#endif

// FUNCTIONS! //

void MorphGPIO_set_pin_value(MorphPinNumber pn, enum MorphPinValue pv);

enum MorphPinValue MorphGPIO_get_pin_value(MorphPinNumber pn);

void MorphGPIO_set_pin_direction(MorphPinNumber pn, enum MorphPinDirection pd);

enum MorphPinDirection MorphGPIO_get_pin_direction(MorphPinNumber pn);

void MorphGPIO_set_pin_pull_state(MorphPinNumber pn, enum MorphPinPullState ps);

enum MorphPinPullState MorphGPIO_get_pin_pull_state(MorphPinNumber pn);

void MorphGPIO_set_pin_interrupt(void (*function)(void), MorphPinNumber pn,  enum MorphExternalInterruptType it);

void MorphGPIO_unset_pin_interrupt(MorphPinNumber pn, enum MorphPinValue pv);

void MorphGPIO_imp_test();


#endif /* MORPHGPIO_H_ */