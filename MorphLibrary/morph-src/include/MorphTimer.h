/*
 * MorphTimer.h
 *
 * Created: 11/13/2018 3:19:54 PM
 *  Author: 243400
 */ 


#ifndef MORPHTIMER_H_
#define MORPHTIMER_H_

#include <stdbool.h>

#include "MorphTypes.h"

#ifndef MORPH_IMPLICIT

// MORPH_IMPLICIT means the functions will not be implemented with function pointers.
// Instead, it will call the (possibly) implemented functions directly.
// This is more dangerous, however it might see performance gains through compiler optimization.

void MorphTimer_register_acquire_timer_function(void (*function)(MorphTimerNumber, MorphTimerResolution));

void MorphTimer_register_release_timer_function(void (*function)(MorphTimerNumber, MorphTimerResolution));

void MorphTimer_register_set_rate_function(void (*function)(MorphTimerNumber, MorphTimerResolution, MorphTimerRate));

void MorphTimer_register_set_timer_callback_function(void (*function)(MorphTimerNumber, MorphTimerResolution, void (*)(void)));

void MorphTimer_register_unset_timer_callback_function(void (*function)(MorphTimerNumber, MorphTimerResolution));

void MorphTimer_register_is_in_use_function(bool (*function)(MorphTimerNumber, MorphTimerResolution));

#endif

// The "timer number" here refers to the number of the certain resolution. 
// This function claims a timer and does not allow subsequent calls to setup the same timer.
void MorphTimer_acquire_timer(MorphTimerNumber tn, MorphTimerResolution res);

// This function will allow other processes to acquire this timer.
void MorphTimer_release_timer(MorphTimerNumber tn, MorphTimerResolution res);

void MorphTimer_set_rate(MorphTimerNumber tn, MorphTimerResolution res, MorphTimerRate rate);

void MorphTimer_set_timer_callback(MorphTimerNumber tn, MorphTimerResolution res, void (*callback)(void));

void MorphTimer_unset_timer_callback(MorphTimerNumber tn, MorphTimerResolution res, void (*callback)(void));

// Checks if the current timer has been claimed.
bool MorphTimer_is_in_use(MorphTimerNumber tn, MorphTimerResolution res);

#endif /* MORPHTIMER_H_ */