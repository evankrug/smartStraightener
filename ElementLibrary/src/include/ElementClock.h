#include <MorphTime.h>

#ifndef ELEMENTCLOCK_H_
#define ELEMENTCLOCK_H_

#define ELEMENTCLOCK_MILLI_IN_SECOND	1000
#define ELEMENTCLOCK_SECOND_IN_MINUTE	60
#define ELEMENTCLOCK_MINUTE_IN_HOUR		60
#define ELEMENTCLOCK_HOUR_IN_DAY		24
#define ELEMENTCLOCK_HOUR_IN_HALF_DAY   12


// This function pairs a clock value from the RTC to a wall clock time.
void ElementClock_set(MorphTimeValue val, ElementDateTime time);

int16_t ElementClock_get_year();

int16_t ElementClock_get_month();

int16_t ElementClock_get_day();

int16_t ElementClock_get_24_hour();

int16_t ElementClock_get_12_hour();

bool ElementClock_get_is_pm();

int16_t ElementClock_get_minute();

int16_t ElementClock_get_second();

int16_t ElementClock_get_millisecond();

MorphTimeValue ElementClock_get_base_delta();

MorphTimeValue ElementClock_get_unix_time();

void ElementClock_get_datetime(ElementDateTime * cur_date_time);

bool ElementClock_get_is_leap_year(int16_t year);

// This returns the weekday. 0 is Saturday, 1 is Sunday...
int8_t ElementClock_get_day_of_week();

#endif