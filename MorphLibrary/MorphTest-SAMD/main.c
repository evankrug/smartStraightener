/*
 * MorphTest-SAMD.c
 *
 * Created: 11/26/2018 2:46:37 PM
 * Author : 243400
 */ 


#include "sam.h"

#include <Morph.h>
#include <MorphConfig.h>
#include <MorphGPIO.h>
#include <MorphUART.h>
#include <MorphTime.h>

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();

	MorphConfig_init();

	MorphGPIO_set_pin_direction(19, Input);
	MorphGPIO_set_pin_pull_state(19, PullLow);
	
//	MorphGPIO_set_pin_direction(19, Output);
	
	
	//MorphUART_set_tx_pin(5, 41);
	//MorphUART_set_rx_pin(5, 42);
		//
	//MorphUART_setup_channel(5, 9600, 8, MorphNoParity, 1);

	//MorphUART_set_tx_pin(0, 19);
	//MorphUART_set_rx_pin(0, 20);
	//
	//MorphUART_setup_channel(0, 9600, 8, MorphNoParity, 1);
//
	//MorphTime_init_rtc();

	uint8_t count = 0;

	uint16_t data[10] = {0};


    while (1) 
    {

		//uint64_t cur_time = MorphTime_millis();
//
		//int8_t i = 0;
//
		//do 
		//{
			//uint16_t remainder = cur_time % 10;
			//cur_time = cur_time / 10;
//
			//data[i++] = remainder;
//
		//} while (cur_time > 0);
		//
		//for(; i >= 0; i --)
		//{
			//MorphUART_send_data(0, data[i] + '0');
		//}
//
		//MorphUART_send_data(0, '\n');

    }
}
