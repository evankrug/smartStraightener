/*
 * MorphTimer.c
 *
 * Created: 1/8/2019 4:04:09 PM
 *  Author: 243400
 */ 

#include "include/MorphTimer.h"
#include "include/MorphUtils.h"
#include "include/MorphTypes.h"

#ifndef MORPH_IMPLICIT

void (*morph_aquire_timer_function)(MorphTimerNumber, MorphTimerResolution) = &MorphUtils_empty_callback;
void (*morph_release_timer_function)(MorphTimerNumber, MorphTimerResolution) = &MorphUtils_empty_callback;
void (*morph_set_timer_rate_function)(MorphTimerNumber, MorphTimerResolution, MorphTimerRate) = &MorphUtils_empty_callback;
void (*morph_set_timer_callback_function)(MorphTimerNumber, MorphTimerResolution, void (*)(void)) = &MorphUtils_empty_callback;
void (*morph_unset_timer_callback_function)(MorphTimerNumber, MorphTimerResolution, void (*)(void)) = &MorphUtils_empty_callback;
bool (*morph_timer_is_in_use_function)(MorphTimerNumber, MorphTimerResolution) = &MorphUtils_empty_callback;

void MorphTimer_register_acquire_timer_function(void (*function)(MorphTimerNumber, MorphTimerResolution))
{
	morph_aquire_timer_function = function;
}

void MorphTimer_register_release_timer_function(void (*function)(MorphTimerNumber, MorphTimerResolution))
{
	morph_release_timer_function = function;	
}

void MorphTimer_register_set_rate_function(void (*function)(MorphTimerNumber, MorphTimerResolution, MorphTimerRate))
{
	morph_set_timer_rate_function = function;
}

void MorphTimer_register_set_timer_callback_function(void (*function)(MorphTimerNumber, MorphTimerResolution, void (*)(void)))
{
	morph_set_timer_callback_function = function;	
}

void MorphTimer_register_unset_timer_callback_function(void (*function)(MorphTimerNumber, MorphTimerResolution))
{
	morph_unset_timer_callback_function = function;	
}

void MorphTimer_register_is_in_use_function(bool (*function)(MorphTimerNumber, MorphTimerResolution))
{
	morph_timer_is_in_use_function = function;	
}


#endif

// FUNCTIONS! //

// The "timer number" here refers to the number of the certain resolution.
// This function claims a timer and does not allow subsequent calls to setup the same timer.
void MorphTimer_acquire_timer(MorphTimerNumber tn, MorphTimerResolution res)
{
	#ifdef MORPH_IMPLICIT
		morph_config_timer_acquire_timer(tn, res);
	#else
		morph_aquire_timer_function(tn, res);
	#endif
}

// This function will allow other processes to acquire this timer.
void MorphTimer_release_timer(MorphTimerNumber tn, MorphTimerResolution res)
{
	#ifdef MORPH_IMPLICIT
	morph_config_timer_release_timer(tn, res);
	#else
	morph_release_timer_function(tn, res);
	#endif	
}

void MorphTimer_set_rate(MorphTimerNumber tn, MorphTimerResolution res, MorphTimerRate rate)
{
	#ifdef MORPH_IMPLICIT
	morph_config_timer_set_rate(tn, res, rate);
	#else
	morph_set_timer_rate_function(tn, res, rate);
	#endif
}

void MorphTimer_set_timer_callback(MorphTimerNumber tn, MorphTimerResolution res, void (*callback)(void))
{
	#ifdef MORPH_IMPLICIT
	morph_config_timer_set_timer_callback(tn, res, callback);
	#else
	morph_set_timer_callback_function(tn, res, callback);
	#endif	
}

void MorphTimer_unset_timer_callback(MorphTimerNumber tn, MorphTimerResolution res, void (*callback)(void))
{
	#ifdef MORPH_IMPLICIT
	morph_config_timer_unset_timer_callback(tn, res, callback);
	#else
	morph_unset_timer_callback_function(tn, res, callback);
	#endif	
}

// Checks if the current timer has been claimed.
bool MorphTimer_is_in_use(MorphTimerNumber tn, MorphTimerResolution res)
{
	#ifdef MORPH_IMPLICIT
	return morph_config_timer_is_in_use(tn, res);
	#else
	return morph_timer_is_in_use_function(tn, res);
	#endif	
}
