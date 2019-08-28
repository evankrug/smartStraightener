#include <ElementConfig.h>
#include <ElementClock.h>


uint8_t month_codes[] = {
	1, // January
	4, // February
	4, // March
	0, // April
	2, // May
	5, // June
	0, // July
	3, // August
	6, // September
	1, // October
	4, // November
	6  // December 
};

uint8_t era_codes[] = {
	6, // 2000s
	4, // 2100s
	2, // 2200s
	0  // 2300s
};

int64_t ElementClock_get_date_number(int32_t year, int32_t month, int32_t day)
{
	//Using this algorithm: https://alcor.concordia.ca//~gpkatch/gdate-algorithm.html
	
	// The source algorithm uses 1 - 12 for months. We use 0 - 11. So simply add 1 here.
	month += 1;
	
	month = (month + 9) % 12;
	year = year - month/10;
	return 365 * year + year / 4 - year / 100 + year / 400 + (month * 306 + 5) / 10 + ( day - 1 );
}

void ElementClock_get_date_from_number(int64_t day_number, int32_t * year, int32_t * month, int32_t * day)
{
	//Using this algorithm: https://alcor.concordia.ca//~gpkatch/gdate-algorithm.html

	int32_t y = (10000 * day_number + 14780) / 3652425;
	
	int32_t ddd = day_number - (365*y + y/4 - y/100 + y/400);
	
	if(ddd < 0)
	{
		y = y - 1;
		ddd = day_number - (365*y + y/4 - y/100 + y/400);
	}
	
	int32_t mi = (100*ddd + 52)/3060;
	int32_t mm = (mi + 2) % 12 + 1;
	
	y = y + (mi + 2)/12;
	
	int32_t dd = ddd - (mi*306 + 5)/10 + 1;
	
	// Subtract 1 from mm to make this compatible with out stuff.
	mm -= 1;
	
	*year = y;
	*month = mm;
	*day = dd;
	
}

// This function pairs a clock value from the RTC to a wall clock time.
void ElementClock_set(MorphTimeValue val, ElementDateTime time)
{
	// Deep copy from the parameters.
	
	clock_master_config.date.year		 = time.year;
	clock_master_config.date.month		 = time.month;
	clock_master_config.date.day		 = time.day;
	clock_master_config.date.hour		 = time.hour;
	clock_master_config.date.minute		 = time.minute;
	clock_master_config.date.second		 = time.second;
	clock_master_config.date.millisecond = time.millisecond;
	
	clock_master_config.rtc_val = val;
	
}

int16_t ElementClock_get_year()
{
	
	MorphTimeValue unix_time = ElementClock_get_unix_time();
	
	// First, calculate the days since the start.
	int32_t days_since_start = ((((ElementClock_get_base_delta()/ELEMENTCLOCK_MILLI_IN_SECOND + clock_master_config.date.second) /
	ELEMENTCLOCK_SECOND_IN_MINUTE + clock_master_config.date.minute) /
	ELEMENTCLOCK_MINUTE_IN_HOUR) + clock_master_config.date.hour) /
	ELEMENTCLOCK_HOUR_IN_DAY;

	int64_t start_day_number = ElementClock_get_date_number(clock_master_config.date.year, clock_master_config.date.month, clock_master_config.date.day);

	int32_t result_day, result_month, result_year;
		
	ElementClock_get_date_from_number(start_day_number + days_since_start, &result_year, &result_month, &result_day);
		
	return result_year;
	
	
}

int16_t ElementClock_get_month()
{
	// First, calculate the days since the start.
	int32_t days_since_start = ((((ElementClock_get_base_delta()/ELEMENTCLOCK_MILLI_IN_SECOND + clock_master_config.date.second) /
	ELEMENTCLOCK_SECOND_IN_MINUTE + clock_master_config.date.minute) /
	ELEMENTCLOCK_MINUTE_IN_HOUR) + clock_master_config.date.hour) /
	ELEMENTCLOCK_HOUR_IN_DAY;

	int64_t start_day_number = ElementClock_get_date_number(clock_master_config.date.year, clock_master_config.date.month, clock_master_config.date.day);

	int32_t result_day, result_month, result_year;
		
	ElementClock_get_date_from_number(start_day_number + days_since_start, &result_year, &result_month, &result_day);
		
	return result_month;
	
}

int16_t ElementClock_get_day()
{
	// First, calculate the days since the start.
	int32_t days_since_start = ((((ElementClock_get_base_delta()/ELEMENTCLOCK_MILLI_IN_SECOND + clock_master_config.date.second) /
	ELEMENTCLOCK_SECOND_IN_MINUTE + clock_master_config.date.minute) /
	ELEMENTCLOCK_MINUTE_IN_HOUR) + clock_master_config.date.hour) /
	ELEMENTCLOCK_HOUR_IN_DAY;

	int64_t start_day_number = ElementClock_get_date_number(clock_master_config.date.year, clock_master_config.date.month, clock_master_config.date.day);

	int32_t result_day, result_month, result_year;
	
	ElementClock_get_date_from_number(start_day_number + days_since_start, &result_year, &result_month, &result_day);
	
	return result_day;
	
}

int16_t ElementClock_get_24_hour()
{
	return ((((ElementClock_get_base_delta()/ELEMENTCLOCK_MILLI_IN_SECOND + clock_master_config.date.second) / 
	ELEMENTCLOCK_SECOND_IN_MINUTE + clock_master_config.date.minute) / 
	ELEMENTCLOCK_MINUTE_IN_HOUR) + clock_master_config.date.hour) % 
	ELEMENTCLOCK_HOUR_IN_DAY; // Find remainder of hours.	
}

int16_t ElementClock_get_12_hour()
{
	int16_t value = ElementClock_get_24_hour();
	
	if(value == 0)
	{
		value = ELEMENTCLOCK_HOUR_IN_HALF_DAY;
	}
	else if(value >= 13)
	{
		value -= ELEMENTCLOCK_HOUR_IN_HALF_DAY;
	}
	
	return value;
	
}

bool ElementClock_get_is_pm()
{
	return ElementClock_get_24_hour() >= ELEMENTCLOCK_HOUR_IN_HALF_DAY;
}

int16_t ElementClock_get_minute()
{
	return ((ElementClock_get_base_delta()/ELEMENTCLOCK_MILLI_IN_SECOND + clock_master_config.date.second) / ELEMENTCLOCK_SECOND_IN_MINUTE + clock_master_config.date.minute) % ELEMENTCLOCK_MINUTE_IN_HOUR;	
}

int16_t ElementClock_get_second()
{
	
	return (ElementClock_get_base_delta()/ELEMENTCLOCK_MILLI_IN_SECOND + clock_master_config.date.second) % ELEMENTCLOCK_SECOND_IN_MINUTE;
	
}

int16_t ElementClock_get_millisecond()
{
	return (ElementClock_get_base_delta() + clock_master_config.date.millisecond) % ELEMENTCLOCK_MILLI_IN_SECOND;
}

MorphTimeValue ElementClock_get_base_delta()
{
	
	return MorphTime_millis() - clock_master_config.rtc_val;
	
}

MorphTimeValue ElementClock_get_unix_time()
{
	return MorphTime_millis();
}

void ElementClock_get_datetime(ElementDateTime * cur_date_time)
{
	// TODO: Make this efficient. 
	
	cur_date_time->year = ElementClock_get_year();
	cur_date_time->month = ElementClock_get_month();
	cur_date_time->day = ElementClock_get_day();
		
	MorphTimeValue base_delta = ElementClock_get_base_delta();
		
	cur_date_time->minute = (((base_delta + clock_master_config.date.millisecond)/ELEMENTCLOCK_MILLI_IN_SECOND + clock_master_config.date.second) / ELEMENTCLOCK_SECOND_IN_MINUTE + clock_master_config.date.minute) % ELEMENTCLOCK_MINUTE_IN_HOUR;	

	cur_date_time->second = ((base_delta + clock_master_config.date.millisecond)/ELEMENTCLOCK_MILLI_IN_SECOND + clock_master_config.date.second) % ELEMENTCLOCK_SECOND_IN_MINUTE;
	
	cur_date_time->millisecond = (base_delta + clock_master_config.date.millisecond) % ELEMENTCLOCK_MILLI_IN_SECOND;
		
	cur_date_time->hour = ElementClock_get_24_hour();
	//cur_date_time->minute = ElementClock_get_minute();
	//cur_date_time->second = ElementClock_get_second();
	//cur_date_time->millisecond = ElementClock_get_millisecond();

}

bool ElementClock_get_is_leap_year(int16_t year)
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0); 
}

// This returns the weekday. 0 is Saturday, 1 is Sunday... 
int8_t ElementClock_get_day_of_week()
{
	
	// This algorithm uses the Key Value Method
	// http://mathforum.org/dr.math/faq/faq.calendar.html
	
	uint16_t cur_year = ElementClock_get_year();
	
	uint16_t cur_month = ElementClock_get_month();
	
	bool is_leap_year = ElementClock_get_is_leap_year(cur_year);
	
	// TODO: Only apply on Jan and Feb
	uint8_t leap_correction = is_leap_year & cur_month <= 1 ? 1 : 0;
	
	uint16_t year_tens = (cur_year % 100);
	
	int16_t code = (year_tens / 4) + ElementClock_get_day() + month_codes[cur_month] - leap_correction + era_codes[cur_year % 400] + year_tens;

	return code % 7;	
		
}