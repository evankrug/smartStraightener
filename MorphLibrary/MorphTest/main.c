/*
 * MorphTest.c
 *
 * Created: 11/15/2018 5:50:45 PM
 * Author : 243400
 */ 

// Including Morph library
#include <Morph.h>
#include <MorphGPIO.h>
#include <MorphPWM.h>
#include <MorphConfig.h>
#include <MorphTimer.h>
#include <MorphTime.h>

#include <inttypes.h>

#include <math.h>

// Including assert.h for testing.
#include <assert.h>

bool pin_on = false;

void callback_test()
{

	pin_on = !pin_on;
	
//	MorphGPIO_set_pin_value(19, pin_on ? High : Low);
	
}

int main(void)
{
	
	MorphConfig_init();
	
	MorphGPIO_set_pin_direction(19, Output);
	
//	MorphGPIO_set_pin_value(19, High);

	MorphGPIO_set_pin_value(19, Low);

	MorphGPIO_set_pin_pull_state(19, PullHigh);

	//MorphTimer_acquire_timer(0, 8);
//
	//MorphTimer_set_rate(0, 8, 24);
	//
	MorphPWM_start_pwm(12);
	
	MorphTimer_set_timer_callback(0, 8, &callback_test);
	
	MorphTime_init(1, 8);
	
	//MorphGPIO_set_pin_value(19, High);
//
	//uint8_t pin_value = MorphGPIO_get_pin_value(1);	
//
	//MorphGPIO_set_pin_value(1, Low);
//
	//pin_value = MorphGPIO_get_pin_value(1);
//
	//MorphGPIO_set_pin_direction(1, Input);
//
	//uint8_t direction = MorphGPIO_get_pin_direction(1);
//
	//MorphGPIO_set_pin_direction(1, Output);
//
	//direction = MorphGPIO_get_pin_direction(1);		
//
	//MorphGPIO_set_pin_direction(1, Output);
	//
	//MorphGPIO_imp_test();

    /* Replace with your application code */
    while (1) 
    {
		MorphTimeValue cur_time = MorphTime_millis();

		if(cur_time % 2000 > 1000)
		{
			
			MorphGPIO_set_pin_value(19, Low);
			
		}
		else
		{
			
			MorphGPIO_set_pin_value(19, High);
		}
		
	
		float duty = ((sin((cur_time / 10000.0f) * 3.141f) + 1.0f)/2.0f);
		
		//float duty = ((cur_time % 5000) / 1000) * (1.0f / 5.0f);
		//
		MorphPWM_set_pwm_duty_float(12, duty);
		
    }
}