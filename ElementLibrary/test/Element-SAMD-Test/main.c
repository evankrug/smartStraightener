/*
 * Element-SAMD-Test.c
 *
 * Created: 12/3/2018 10:28:44 AM
 * Author : 243400
 */ 


#include "sam.h"

#include <ElementConfig.h>
#include <ElementDirectButton.h>
#include <ElementClock.h>

#include <MorphConfig.h>
#include <MorphUART.h>
#include <MorphTime.h>

#include "app.h"

void button_down_test()
{
	
	MorphUART_send_data(0, blink.cal_anim->bit_depth);
	
}

void button_up_test()
{
	
	MorphUART_send_data(0, 'u');
	
}

void button_press_test()
{
	
	MorphUART_send_data(0, 'p');
	
}

void button_short_test()
{
	
	MorphUART_send_data(0, 's');
	
}

void button_long_test()
{
	
	MorphUART_send_data(0, 'l');
	
}


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	
	MorphConfig_init();

//	MorphUART_set_tx_pin(0, 19);
//	MorphUART_set_rx_pin(0, 20);
	
//	MorphUART_setup_channel(0, 9600, 8, MorphNoParity, 1);

	MorphTime_init_rtc();

	uint8_t count = 0;

	uint16_t data[10] = {0};
		
	ElementDirectButton_init();

	ElementDirectButton_register_callback(&button_down_test, 0, ElementButtonEventDown);
	ElementDirectButton_register_callback(&button_up_test, 0, ElementButtonEventUp);
	ElementDirectButton_register_callback(&button_press_test, 0, ElementButtonEventPress);
	ElementDirectButton_register_callback(&button_short_test, 0, ElementButtonEventShort);
	ElementDirectButton_register_callback(&button_long_test, 0, ElementButtonEventLong);		

	// Give the animation engine the LED buffer.
	ElementAnimationEngine_add_buffer(&led_buffer);

	// Push the blink animation onto the blink animation stack.
	ElementAnimationEngine_push_animation(&led_buffer, &blink);

	// Give the animation engine the seven segment buffer.
	ElementAnimationEngine_add_buffer(&seven_seg_buffer);

	// Push the time animation onto the seven segment buffer stack.
//	ElementAnimationEngine_push_animation(&seven_seg_buffer, &print_7_seg_time_anim);

	ElementAnimationEngine_push_animation(&seven_seg_buffer, &print_name_anim);


								//     a, b, c, d, e, f, g, period
	MorphPinNumber seven_seg_pins[] = {20, 19, 31, 18, 17, 32, 41, 15};

	MorphPinNumber seven_seg_mux_pins[] = {16, 37, 35};

	Element7SegGPIODriver_init(&seven_seg_pins, 8, &seven_seg_mux_pins, 3, &seven_seg_buffer);

	ElementDateTime cur_date;

	cur_date.year = 2019;	
	cur_date.month = 0;	
	cur_date.day = 1;

	cur_date.hour = 12;
	cur_date.minute = 00;
	cur_date.second = 0;

	ElementClock_set(MorphTime_millis(), cur_date);

	uint8_t string_buffer[50];

    while (1) 
    {
		
		//uint8_t hour = ElementClock_get_24_hour();
		//
		//uint8_t hours_one = hour / 10 + '0';
		//uint8_t hours_two = hour % 10 + '0';
//
		//uint8_t minute = ElementClock_get_minute();
		//
		//uint8_t minute_one = minute / 10 + '0';
		//uint8_t minute_two = minute % 10 + '0';
//
		//uint8_t second = ElementClock_get_second();
		//
		//uint8_t seconds_one = second / 10 + '0';
		//uint8_t seconds_two = second % 10 + '0';
//
		//int16_t day = ElementClock_get_day();
//
		//uint8_t day_one = day / 10 + '0';
		//uint8_t day_two = day % 10 + '0';
//
		//int16_t month = ElementClock_get_month() + 1;
//
		//uint8_t month_one = month / 10 + '0';
		//uint8_t month_two = month % 10 + '0';
//
		//int16_t year = ElementClock_get_year();
//
		//uint8_t year_one = (year / 10) % 10 + '0';
		//uint8_t year_two = year % 10 + '0';

		/*MorphUART_send_data(0, hours_one);
		MorphUART_send_data(0, hours_two);

		MorphUART_send_data(0, ':');

		MorphUART_send_data(0, minute_one);
		MorphUART_send_data(0, minute_two);

		MorphUART_send_data(0, ':');
		
		MorphUART_send_data(0, seconds_one);
		MorphUART_send_data(0, seconds_two);

		MorphUART_send_data(0, ' ');
		MorphUART_send_data(0, ' ');
		MorphUART_send_data(0, ' ');

		MorphUART_send_data(0, day_one);
		MorphUART_send_data(0, day_two);		

		MorphUART_send_data(0, '/');

		MorphUART_send_data(0, month_one);
		MorphUART_send_data(0, month_two);		

		MorphUART_send_data(0, '/');

		MorphUART_send_data(0, year_one);
		MorphUART_send_data(0, year_two);
		MorphUART_send_data(0, '\n');*/
		
		Element7SegGPIODriver_update();
				
		ElementAnimationEngine_update();
		
		//ElementDirectButton_update();
		
		
		
    }

}
