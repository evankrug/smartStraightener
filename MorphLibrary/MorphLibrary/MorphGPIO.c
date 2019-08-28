/*
 * MorphGPIO.c
 *
 * Created: 11/15/2018 5:46:43 PM
 *  Author: 243400
 */ 

#include "include/MorphGPIO.h"
#include "include/MorphConfig.h"
#include "include/MorphUtils.h"


#ifndef MORPH_IMPLICIT

// VALUE

// PIN VALUE SET
void (*morph_set_pin_value_function)(MorphPinNumber, enum MorphPinValue) = &MorphUtils_empty_callback;

// PIN VALUE GET
enum MorphPinValue (*morph_get_pin_value_function)(MorphPinNumber) = &MorphUtils_empty_callback;

// DIRECTION

// PIN Direction SET
void (*morph_set_pin_direction_function)(MorphPinNumber, enum MorphPinDirection) = &MorphUtils_empty_callback;

// PIN Direction GET
enum MorphPinDirection (*morph_get_pin_direction_function)(MorphPinNumber) = &MorphUtils_empty_callback;

// PULL STATE

// PULL STATE SET
void (*morph_set_pin_pull_state_function)(MorphPinNumber, enum MorphPinPullState) = &MorphUtils_empty_callback;

// PULL STATE GET
enum MorphPinPullState (*morph_get_pin_pull_state_function)(MorphPinNumber) = &MorphUtils_empty_callback;

// INTERRUPT SET
void (*morph_set_pin_interrupt_function)(void (*)(void), MorphPinNumber, enum MorphExternalInterruptType) = &MorphUtils_empty_callback;

// INTERRUPT UNSET
void (*morph_unset_pin_interrupt_function)(MorphPinNumber, enum MorphPinValue) = &MorphUtils_empty_callback;


void MorphGPIO_register_set_pin_value_function(void (*function)(MorphPinNumber, enum MorphPinValue))
{
	morph_set_pin_value_function = function;	
}

void MorphGPIO_register_get_pin_value_function(enum MorphPinValue (*function)(MorphPinNumber))
{
	morph_get_pin_value_function = function;
}

void MorphGPIO_register_set_pin_direction_function(void (*function)(MorphPinNumber, enum MorphPinDirection))
{
	morph_set_pin_direction_function = function;
}

void MorphGPIO_register_get_pin_direction_function(enum MorphPinDirection (*function)(MorphPinNumber))
{
	morph_get_pin_direction_function = function;
}

void MorphGPIO_register_set_pin_pull_state_function(void (*function)(MorphPinNumber, enum MorphPinPullState))
{
	morph_set_pin_pull_state_function = function;
}

void MorphGPIO_register_get_pin_pull_state_function(enum MorphPinPullState (*function)(MorphPinNumber))
{
	morph_get_pin_pull_state_function = function;	
}

void MorphGPIO_register_set_pin_interrupt_function(void (*function)(void (*)(void), MorphPinNumber, enum MorphExternalInterruptType))
{
	
	morph_set_pin_interrupt_function = function;
	
}

void MorphGPIO_register_unset_pin_interrupt_function(void (*function)(MorphPinNumber, enum MorphPinValue))
{
	
	morph_unset_pin_interrupt_function = function;	
	
}

#endif

// FUNCTIONS! //

void MorphGPIO_set_pin_value(MorphPinNumber pn, enum MorphPinValue pv)
{
	#ifdef MORPH_IMPLICIT
		morph_config_gpio_set_pin_value(pn, pv);
	#else
		morph_set_pin_value_function(pn, pv);
	#endif
}

enum MorphPinValue MorphGPIO_get_pin_value(MorphPinNumber pn)
{

	#ifdef MORPH_IMPLICIT
		return morph_config_gpio_get_pin_value(pn);
	#else
		return morph_get_pin_value_function(pn);
	#endif
}

void MorphGPIO_set_pin_direction(MorphPinNumber pn, enum MorphPinDirection pd)
{
	#ifdef MORPH_IMPLICIT
		morph_config_gpio_set_pin_direction(pn, pd);
	#else
		morph_set_pin_direction_function(pn, pd);
	#endif
}

enum MorphPinDirection MorphGPIO_get_pin_direction(MorphPinNumber pn)
{
	#ifdef MORPH_IMPLICIT
		return morph_config_gpio_get_pin_direction(pn);
	#else
		return morph_get_pin_direction_function(pn);
	#endif
}

void MorphGPIO_set_pin_pull_state(MorphPinNumber pn, enum MorphPinPullState ps)
{
	#ifdef MORPH_IMPLICIT
		morph_config_gpio_set_pin_pull_state(pn, ps);
	#else
		morph_set_pin_pull_state_function(pn, ps);
	#endif
}

enum MorphPinPullState MorphGPIO_get_pin_pull_state(MorphPinNumber pn)
{
	#ifdef MORPH_IMPLICIT
		return morph_config_gpio_get_pin_pull_state(pn);
	#else
		return morph_get_pin_pull_state_function(pn);
	#endif
}

void MorphGPIO_set_pin_interrupt(void (*function)(void), MorphPinNumber pn, enum MorphExternalInterruptType it)
{
	#ifdef MORPH_IMPLICIT
		morph_config_gpio_get_pin_pull_state(pn);
	#else
		morph_get_pin_pull_state_function(pn);
	#endif
}

void MorphGPIO_unset_pin_interrupt(MorphPinNumber pn, enum MorphPinValue pv)
{
	#ifdef MORPH_IMPLICIT
		morph_config_gpio_get_pin_pull_state(pn);
	#else
		morph_get_pin_pull_state_function(pn);
	#endif
}

void MorphGPIO_imp_test()
{
	
	morph_implementation_test();
	
}