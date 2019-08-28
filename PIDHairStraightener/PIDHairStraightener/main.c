/*
 * PIDHairStraightener.c
 *
 * Created: 5/29/2019 1:48:47 PM
 * Author : 245845
 */ 

#include <avr/io.h>

#include <Morph.h>
#include <MorphGPIO.h>
#include <MorphPWM.h>
#include <MorphConfig.h>
#include <MorphTimer.h>
#include <MorphTime.h>
#include <MorphUART.h>
#include <MorphSPI.h>
#include <stdio.h>  // Evan 5/30

// Evan 5/30 for git 
//#include <lclib.h>
char *sbrk(size_t bytes);


// ********************************************************************************
// Function Prototypes
// ********************************************************************************
void usart_putchar( char data );
int usart_putchar_printf(char var, FILE *stream);

//**************************************************************************************************************************
// Global variables
//***************************************************************************************************************************
static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE); //Evan 5/30 define stream; variable mystdout gets created as a stream

int _mneed = 2000;       /* Define default size of sbrk area. */

int main(void)
{
	
	//set up stdio stream
	stdout = &mystdout; //Evan 5/30

	MorphConfig_init();

	MorphTime_init(0, 16);


	MorphGPIO_set_pin_direction(19, Output);

	MorphUART_setup_channel(0, 9600, 8, MorphNoParity, 2);

    /* Replace with your application code */
    while (1) 
    {
		MorphTimeValue cur_time = MorphTime_millis();
		
		//MorphUART_send_byte(0, 'a');
		
		if(cur_time % 1000 < 100)
		{	
			MorphGPIO_set_pin_value(19, High);
		}
		else
		{
			MorphGPIO_set_pin_value(19, Low);			
		}

        printf("current time is: %d\n", cur_time);
		//sprintf();
				
    }

}
	
	//Evan 5/30
	int usart_putchar_printf(char var, FILE *stream) {
		if (var == '\n') usart_putchar('\r');
		usart_putchar(var);
		return 0;
	}
	
	// Evan 5/30
	void usart_putchar(char data) {

		MorphUART_send_byte(0, data);

	}


