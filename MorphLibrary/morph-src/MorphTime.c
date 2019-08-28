/*
 * MorphTime.c
 *
 * Created: 12/3/2018 4:10:32 PM
 *  Author: 243400
 */ 

#include "include/MorphTime.h"
#include "include/MorphUtils.h"
#include "include/MorphOptions.h"
#include "include/MorphTypes.h"
#include "include/MorphConfig.h"

#ifndef MORPH_IMPLICIT

void (*morph_init_function)(MorphTimerNumber, MorphTimerResolution) = &MorphUtils_empty_callback;

void (*morph_init_rtc_function)(void) = &MorphUtils_empty_callback;

MorphTimeValue (*morph_millis_function)(void) = &MorphUtils_empty_callback;


void MorphTime_register_init_function(void (*function)(MorphTimerNumber, MorphTimerResolution))
{
	morph_init_function = function;
}

void MorphTime_register_init_rtc_function(void (*function)(void))
{
	morph_init_rtc_function = function;
}

void MorphTime_register_millis_function(MorphTimeValue (*function)(void))
{
	morph_millis_function = function;
}


#endif

// FUNCTIONS! //
void MorphTime_init(MorphTimerNumber tn, MorphTimerResolution res)
{
	#ifdef MORPH_IMPLICIT
		morph_config_time_init(tn, res);
	#else
		morph_init_function(tn, res);
	#endif
	
}

void MorphTime_init_rtc()
{
	#ifdef MORPH_IMPLICIT
		morph_config_time_init_rtc();
	#else
		morph_init_rtc_function();
	#endif
}

MorphTimeValue MorphTime_millis()
{
	volatile MorphTimeValue value = 0;
	#ifdef MORPH_IMPLICIT
		value = morph_config_time_millis();
	#else
		value = morph_millis_function();
	#endif
	
	return value;
}

