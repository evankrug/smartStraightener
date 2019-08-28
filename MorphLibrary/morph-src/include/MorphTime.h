/*
 * MorphTime.h
 *
 * Created: 12/3/2018 1:53:14 PM
 *  Author: 243400
 */ 


#ifndef MORPHTIME_H_
#define MORPHTIME_H_

#include <stddef.h>

#include "MorphTypes.h"
#include "MorphUtils.h"
#include "MorphOptions.h"

#ifndef MORPH_IMPLICIT

// MORPH_IMPLICIT means the functions will not be implemented with function pointers.
// Instead, it will call the (possibly) implemented functions directly.
// This is more dangerous, however it might see performance gains through compiler optimization.

void MorphTime_register_init_function(void (*)(MorphTimerNumber, MorphTimerResolution));

void MorphTime_register_init_rtc_function(void (*)(void));

void MorphTime_register_millis_function(MorphTimeValue (*)(void));

#endif

// FUNCTIONS! //

// This function sets up a timer to work as the millisecond time source. 
void MorphTime_init(MorphTimerNumber tn, MorphTimerResolution res);

// If there is a single rtc that should be used. This will set it up.
void MorphTime_init_rtc();

MorphTimeValue MorphTime_millis();


#endif /* MORPHTIME_H_ */