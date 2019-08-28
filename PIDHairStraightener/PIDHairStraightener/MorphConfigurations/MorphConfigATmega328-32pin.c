/*
 * MorphConfigATmega328.c
 * 
 * This is an example configuration file for the ATmega328 chip from Atmel.
 *
 * Created: 11/15/2018 6:20:52 PM
 *  Author: 243400
 */ 



#ifdef ENABLE_ATMEGA328_32PIN_CONFIG

#include <MorphGPIO.h>
#include <MorphUtils.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <MorphConfig.h>

#define PIN_COUNT 32

void morph_config_gpio_set_pin_value(MorphPinNumber pn, enum MorphPinValue pv)
{
	
	uint8_t value = (pv == High ? 1 : 0);
	
	// Figure out what pin we are talking about.
	
	// This is for the 32 pin package of the 328
	switch(pn)
	{
		
		case 1:
		// PD3
		PORTD =  (PORTD & ~(0x1 << 3)) | (value << 3);
		break;
		
		case 2:
		
		// PD4
		PORTD =  (PORTD & ~(0x1 << 4)) | (value << 4);

		break;
		
		case 3:
		// GND
		break;
		
		case 4:
		// VCC
		break;
		
		case 5:
		// GND
		break;
		
		case 6:
		// VCC
		break;
		
		case 7:
		
		// PB6
		PORTB =  (PORTB & ~(0x1 << 6)) | (value << 6);
		break;
		
		case 8:
		
		// PB7
		PORTB =  (PORTB & ~(0x1 << 7)) | (value << 7);
		break;
		
		case 9:
		
		// PD5
		PORTD =  (PORTD & ~(0x1 << 5)) | (value << 5);
		break;
		
		case 10:
		
		// PD6
		PORTD =  (PORTD & ~(0x1 << 6)) | (value << 6);
		break;
		
		case 11:
		
		// PD7
		PORTD =  (PORTD & ~(0x1 << 7)) | (value << 7);
		break;
		
		case 12:
		
		// PB0
		PORTB =  (PORTB & ~(0x1 << 0)) | (value << 0);
		break;
		
		case 13:
		
		// PB1
		PORTB =  (PORTB & ~(0x1 << 1)) | (value << 1);
		break;
		
		case 14:
		
		// PB2
		PORTB =  (PORTB & ~(0x1 << 2)) | (value << 2);
		break;
		
		case 15:
		
		// PB3
		PORTB =  (PORTB & ~(0x1 << 3)) | (value << 3);
		break;

		case 16:
		
		// PB4
		PORTB =  (PORTB & ~(0x1 << 4)) | (value << 4);
		break;

		case 17:
		
		// PB5
		PORTB =  (PORTB & ~(0x1 << 5)) | (value << 5);
		break;
		
		case 18:
		
		// AVCC
		break;
		
		case 19:
		
		// ADC6
		break;

		case 20:
		
		// AREF
		break;
		
		case 21:
		
		// GND
		break;
		
		case 22:
		
		// ADC7
		break;
		
		case 23:
		
		// PC0
		PORTC =  (PORTC & ~(0x1 << 0)) | (value << 0);
		break;

		case 24:
		
		// PC1
		PORTC =  (PORTC & ~(0x1 << 1)) | (value << 1);
		break;
		
		case 25:
		
		// PC2
		PORTC =  (PORTC & ~(0x1 << 2)) | (value << 2);
		break;

		case 26:
		
		// PC3
		PORTC =  (PORTC & ~(0x1 << 3)) | (value << 3);
		break;
		
		case 27:
		
		// PC4
		PORTC =  (PORTC & ~(0x1 << 4)) | (value << 4);
		break;

		case 28:
		
		// PC5
		PORTC =  (PORTC & ~(0x1 << 5)) | (value << 5);
		break;

		case 29:
		
		// PC6
		PORTC =  (PORTC & ~(0x1 << 6)) | (value << 6);
		break;

		case 30:
		
		// PD0
		PORTD =  (PORTD & ~(0x1 << 0)) | (value << 0);
		break;

		case 31:
		
		// PD1
		PORTD =  (PORTD & ~(0x1 << 1)) | (value << 1);
		break;

		case 32:
		
		// PD2
		PORTD =  (PORTD & ~(0x1 << 2)) | (value << 2);
		break;
		
	}
	
}

enum MorphPinValue morph_config_gpio_get_pin_value(MorphPinNumber pn)
{
	
	uint8_t value = 0;
	
	switch(pn)
	{
				
		case 1:
		
		// PD3
		value = ((PORTD >> 3) & 0x1);
		
		break;
				
		case 2:
				
		// PD4
		value = ((PORTD >> 4) & 0x1);

		break;
				
		case 3:
		// GND
		break;
				
		case 4:
		// VCC
		break;
				
		case 5:
		// GND
		break;
				
		case 6:
		// VCC
		break;
				
		case 7:
				
		// PB6
		value = ((PORTB >> 6) & 0x1);
		break;
				
		case 8:
				
		// PB7
		value = ((PORTB >> 7) & 0x1);
		break;
				
		case 9:
				
		// PD5
		value = ((PORTD >> 5) & 0x1);
		break;
				
		case 10:
				
		// PD6
		value = ((PORTD >> 6) & 0x1);
		break;
				
		case 11:
				
		// PD7
		value = ((PORTD >> 7) & 0x1);
		break;
				
		case 12:
				
		// PB0
		value = ((PORTB >> 0) & 0x1);
		break;
				
		case 13:
				
		// PB1
		value = ((PORTB >> 1) & 0x1);
		break;
				
		case 14:
				
		// PB2
		value = ((PORTB >> 2) & 0x1);
		break;
				
		case 15:
				
		// PB3
		value = ((PORTB >> 3) & 0x1);
		break;

		case 16:
				
		// PB4
		value = ((PORTB >> 4) & 0x1);
		break;

		case 17:
				
		// PB5
		value = ((PORTB >> 5) & 0x1);
		break;
				
		case 18:
				
		// AVCC
		break;
				
		case 19:
				
		// ADC6
		break;

		case 20:
				
		// AREF
		break;
				
		case 21:
				
		// GND
		break;
				
		case 22:
				
		// ADC7
		break;
				
		case 23:
				
		// PC0
		value = ((PORTC >> 0) & 0x1);
		break;

		case 24:
				
		// PC1
		value = ((PORTC >> 1) & 0x1);
		break;
				
		case 25:
				
		// PC2
		value = ((PORTC >> 2) & 0x1);
		break;

		case 26:
				
		// PC3
		value = ((PORTC >> 3) & 0x1);
		break;
				
		case 27:
				
		// PC4
		value = ((PORTC >> 4) & 0x1);
		break;

		case 28:
				
		// PC5
		value = ((PORTC >> 5) & 0x1);
		break;

		case 29:
				
		// PC6
		value = ((PORTC >> 6) & 0x1);
		break;

		case 30:
				
		// PD0
		value = ((PORTD >> 0) & 0x1);
		break;

		case 31:
				
		// PD1
		value = ((PORTD >> 1) & 0x1);
		break;

		case 32:
				
		// PD2
		value = ((PORTD >> 2) & 0x1);
		break;
				
	}
	
	return value == 1 ? High : Low;
	
}

void morph_config_gpio_set_pin_direction(MorphPinNumber pn, enum MorphPinDirection pd)
{

	uint8_t value = (pd == Output ? 1 : 0);
	
	// Figure out what pin we are talking about.
	
	// This is for the 32 pin package of the 328
	switch(pn)
	{
		
		case 1:
		// PD3
		DDRD =  (DDRD & ~(0x1 << 3)) | (value << 3);
		break;
		
		case 2:
		
		// PD4
		DDRD =  (DDRD & ~(0x1 << 4)) | (value << 4);

		break;
		
		case 3:
		// GND
		break;
		
		case 4:
		// VCC
		break;
		
		case 5:
		// GND
		break;
		
		case 6:
		// VCC
		break;
		
		case 7:
		
		// PB6
		DDRB =  (DDRB & ~(0x1 << 6)) | (value << 6);
		break;
		
		case 8:
		
		// PB7
		DDRB =  (DDRB & ~(0x1 << 7)) | (value << 7);
		break;
		
		case 9:
		
		// PD5
		DDRD =  (DDRD & ~(0x1 << 5)) | (value << 5);
		break;
		
		case 10:
		
		// PD6
		DDRD =  (DDRD & ~(0x1 << 6)) | (value << 6);
		break;
		
		case 11:
		
		// PD7
		DDRD =  (DDRD & ~(0x1 << 7)) | (value << 7);
		break;
		
		case 12:
		
		// PB0
		DDRB =  (DDRB & ~(0x1 << 0)) | (value << 0);
		break;
		
		case 13:
		
		// PB1
		DDRB =  (DDRB & ~(0x1 << 1)) | (value << 1);
		break;
		
		case 14:
		
		// PB2
		DDRB =  (DDRB & ~(0x1 << 2)) | (value << 2);
		break;
		
		case 15:
		
		// PB3
		DDRB =  (DDRB & ~(0x1 << 3)) | (value << 3);
		break;

		case 16:
		
		// PB4
		DDRB =  (DDRB & ~(0x1 << 4)) | (value << 4);
		break;

		case 17:
		
		// PB5
		DDRB =  (DDRB & ~(0x1 << 5)) | (value << 5);
		break;
		
		case 18:
		
		// AVCC
		break;
		
		case 19:
		
		// ADC6
		break;

		case 20:
		
		// AREF
		break;
		
		case 21:
		
		// GND
		break;
		
		case 22:
		
		// ADC7
		break;
		
		case 23:
		
		// PC0
		DDRC =  (DDRC & ~(0x1 << 0)) | (value << 0);
		break;

		case 24:
		
		// PC1
		DDRC =  (DDRC & ~(0x1 << 1)) | (value << 1);
		break;
		
		case 25:
		
		// PC2
		DDRC =  (DDRC & ~(0x1 << 2)) | (value << 2);
		break;

		case 26:
		
		// PC3
		DDRC =  (DDRC & ~(0x1 << 3)) | (value << 3);
		break;
		
		case 27:
		
		// PC4
		DDRC =  (DDRC & ~(0x1 << 4)) | (value << 4);
		break;

		case 28:
		
		// PC5
		DDRC =  (DDRC & ~(0x1 << 5)) | (value << 5);
		break;

		case 29:
		
		// PC6
		DDRC =  (DDRC & ~(0x1 << 6)) | (value << 6);
		break;

		case 30:
		
		// PD0
		DDRD =  (DDRD & ~(0x1 << 0)) | (value << 0);
		break;

		case 31:
		
		// PD1
		DDRD =  (DDRD & ~(0x1 << 1)) | (value << 1);
		break;

		case 32:
		
		// PD2
		DDRD =  (DDRD & ~(0x1 << 2)) | (value << 2);
		break;
		
	}

}

enum MorphPinDirection morph_config_gpio_get_pin_direction(MorphPinNumber pn)
{
	
	uint8_t value = 0;
	
	switch(pn)
	{
		
		case 1:
		
		// PD3
		value = (DDRD >> 3) & 0x1;
		
		break;
		
		case 2:
		
		// PD4
		value = (DDRD >> 4) & 0x1;

		break;
		
		case 3:
		// GND
		break;
		
		case 4:
		// VCC
		break;
		
		case 5:
		// GND
		break;
		
		case 6:
		// VCC
		break;
		
		case 7:
		
		// PB6
		value = (DDRB >> 6) & 0x1;
		break;
		
		case 8:
		
		// PB7
		value = (DDRB >> 7) & 0x1;
		break;
		
		case 9:
		
		// PD5
		value = (DDRD >> 5) & 0x1;
		break;
		
		case 10:
		
		// PD6
		value = (DDRD >> 6) & 0x1;
		break;
		
		case 11:
		
		// PD7
		value = (DDRD >> 7) & 0x1;
		break;
		
		case 12:
		
		// PB0
		value = (DDRB >> 0) & 0x1;
		break;
		
		case 13:
		
		// PB1
		value = (DDRB >> 1) & 0x1;
		break;
		
		case 14:
		
		// PB2
		value = (DDRB >> 2) & 0x1;
		break;
		
		case 15:
		
		// PB3
		value = (DDRB >> 3) & 0x1;
		break;

		case 16:
		
		// PB4
		value = (DDRB >> 4) & 0x1;
		break;

		case 17:
		
		// PB5
		value = (DDRB >> 5) & 0x1;
		break;
		
		case 18:
		
		// AVCC
		break;
		
		case 19:
		
		// ADC6
		break;

		case 20:
		
		// AREF
		break;
		
		case 21:
		
		// GND
		break;
		
		case 22:
		
		// ADC7
		break;
		
		case 23:
		
		// PC0
		value = (DDRC >> 0) & 0x1;
		break;

		case 24:
		
		// PC1
		value = (DDRC >> 1) & 0x1;
		break;
		
		case 25:
		
		// PC2
		value = (DDRC >> 2) & 0x1;
		break;

		case 26:
		
		// PC3
		value = (DDRC >> 3) & 0x1;
		break;
		
		case 27:
		
		// PC4
		value = (DDRC >> 4) & 0x1;
		break;

		case 28:
		
		// PC5
		value = (DDRC >> 5) & 0x1;
		break;

		case 29:
		
		// PC6
		value = (DDRC >> 6) & 0x1;
		break;

		case 30:
		
		// PD0
		value = (DDRD >> 0) & 0x1;
		break;

		case 31:
		
		// PD1
		value = (DDRD >> 1) & 0x1;
		break;

		case 32:
		
		// PD2
		value = (DDRD >> 2) & 0x1;
		break;
		
	}
	
	return value == 1 ? Output : Input;
	
}

void morph_config_gpio_set_pin_pull_state(MorphPinNumber pn, enum MorphPinPullState ps)
{

	// Figure out what pin we are talking about.
	
	uint8_t value = ps == PullHigh ? 1 : 0;

	// This is for the 32 pin package of the 328
	switch(pn)
	{
	
		case 1:
		// PD3

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 3) & 0x1) == 0)
			PORTD = (PORTD & ~(0x1 << 3)) | (value << 3);

		break;
	
		case 2:
	
		// PD4
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 4) & 0x1) == 0)
			PORTD = (PORTD & ~(0x1 << 4)) | (value << 4);

		break;
	
		case 3:
		// GND
		break;
	
		case 4:
		// VCC
		break;
	
		case 5:
		// GND
		break;
	
		case 6:
		// VCC
		break;
	
		case 7:
	
		// PB6
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 6) & 0x1) == 0)
			PORTB = (PORTB & ~(0x1 << 6)) | (value << 6);
		break;
	
		case 8:
	
		// PB7

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 7) & 0x1) == 0)
			PORTB = (PORTB & ~(0x1 << 7)) | (value << 7);
		break;
	
		case 9:
	
		// PD5

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 5) & 0x1) == 0)
			PORTD = (PORTD & ~(0x1 << 5)) | (value << 5);
		break;
	
		case 10:
	
		// PD6

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 6) & 0x1) == 0)
			PORTD = (PORTD & ~(0x1 << 6)) | (value << 6);
		break;
	
		case 11:
	
		// PD7

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 7) & 0x1) == 0)
			PORTD = (PORTD & ~(0x1 << 7)) | (value << 7);
		break;
	
		case 12:
	
		// PB0

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 0) & 0x1) == 0)
			PORTB = (PORTB & ~(0x1 << 0)) | (value << 0);
		break;
	
		case 13:
	
		// PB1

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 1) & 0x1) == 0)
			PORTB = (PORTB & ~(0x1 << 1)) | (value << 1);
		break;
	
		case 14:
	
		// PB2

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 2) & 0x1) == 0)
			PORTB = (PORTB & ~(0x1 << 2)) | (value << 2);
		break;
	
		case 15:
	
		// PB3

		// We can only have a pin pull if the pin is set to an input.
		if((((DDRB >> 3) & 0x1)) == 0)
			PORTB = (PORTB & ~(0x1 << 3)) | (value << 3);
		break;

		case 16:
	
		// PB4

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 4) & 0x1) == 0)
			PORTB = (PORTB & ~(0x1 << 4)) | (value << 4);
		break;

		case 17:
	
		// PB5

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 5) & 0x1) == 0)
			PORTB = (PORTB & ~(0x1 << 5)) | (value << 5);
		break;
	
		case 18:
	
		// AVCC
		break;
	
		case 19:
	
		// ADC6
		break;

		case 20:
	
		// AREF
		break;
	
		case 21:
	
		// GND
		break;
	
		case 22:
	
		// ADC7
		break;
	
		case 23:
	
		// PC0

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 0) & 0x1) == 0)
			PORTC = (PORTC & ~(0x1 << 0)) | (value << 0);
		break;

		case 24:
	
		// PC1

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 1) & 0x1) == 0)
			PORTC = (PORTC & ~(0x1 << 1)) | (value << 1);
		break;
	
		case 25:
	
		// PC2

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 2) & 0x1) == 0)
			PORTC = (PORTC & ~(0x1 << 2)) | (value << 2);
		break;

		case 26:
	
		// PC3

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 3) & 0x1) == 0)
			PORTC = (PORTC & ~(0x1 << 3)) | (value << 3);
		break;
	
		case 27:
	
		// PC4

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 4) & 0x1) == 0)
			PORTC = (PORTC & ~(0x1 << 4)) | (value << 4);
		break;

		case 28:
	
		// PC5

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 5) & 0x1) == 0)
			PORTC = (PORTC & ~(0x1 << 5)) | (value << 5);
		break;

		case 29:
	
		// PC6

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 6) & 0x1) == 0)
			PORTC = (PORTC & ~(0x1 << 6)) | (value << 6);
		break;

		case 30:
	
		// PD0

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 0) & 0x1) == 0)
			PORTD = (PORTD & ~(0x1 << 0)) | (value << 0);
		break;

		case 31:
	
		// PD1

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 1) & 0x1) == 0)
			PORTD = (PORTD & ~(0x1 << 1)) | (value << 1);
		break;

		case 32:
	
		// PD2

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 2) & 0x1) == 0)
			PORTD = (PORTD & ~(0x1 << 2)) | (value << 2);
		break;
	
	}
	
	
}

enum MorphPinPullState morph_config_gpio_get_pin_pull_state(MorphPinNumber pn)
{

	// Figure out what pin we are talking about.
	
	enum MorphPinPullState value = PullNone;

	// This is for the 32 pin package of the 328
	switch(pn)
	{
		
		case 1:
		// PD3

		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 3) & 0x1) == 0 && ((PORTD >> 3) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;
		
		case 2:
		
		// PD4
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 4) & 0x1) == 0 && ((PORTD >> 4) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 3:
		// GND
		break;
		
		case 4:
		// VCC
		break;
		
		case 5:
		// GND
		break;
		
		case 6:
		// VCC
		break;
		
		case 7:
		
		// PB6
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 6) & 0x1) == 0 && ((PORTB >> 6) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 8:
		
		// PB7
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 7) & 0x1) == 0 && ((PORTB >> 7) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 9:
		
		// PD5
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 5) & 0x1) == 0 && ((PORTD >> 5) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 10:
		
		// PD6
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 6) & 0x1) == 0 && ((PORTD >> 6) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 11:
		
		// PD7
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 7) & 0x1) == 0 && ((PORTD >> 7) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 12:
		
		// PB0
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 0) & 0x1) == 0 && ((PORTB >> 0) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 13:
		
		// PB1
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 1) & 0x1) == 0 && ((PORTB >> 1) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 14:
		
		// PB2
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 2) & 0x1) == 0 && ((PORTB >> 2) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 15:
		
		// PB3
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 3) & 0x1) == 0 && ((PORTB >> 3) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;


		case 16:
		
		// PB4
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 4) & 0x1) == 0 && ((PORTB >> 4) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;


		case 17:
		
		// PB5
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRB >> 5) & 0x1) == 0 && ((PORTB >> 5) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 18:
		
		// AVCC
		break;
		
		case 19:
		
		// ADC6
		break;

		case 20:
		
		// AREF
		break;
		
		case 21:
		
		// GND
		break;
		
		case 22:
		
		// ADC7
		break;
		
		case 23:
		
		// PC0
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 0) & 0x1) == 0 && ((PORTC >> 0) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;


		case 24:
		
		// PC1
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 1) & 0x1) == 0 && ((PORTC >> 1) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 25:
		
		// PC2
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 2) & 0x1) == 0 && ((PORTC >> 2) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;


		case 26:
		
		// PC3
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 3) & 0x1) == 0 && ((PORTC >> 3) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
		case 27:
		
		// PC4
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 4) & 0x1) == 0 && ((PORTC >> 4) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;


		case 28:
		
		// PC5
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 5) & 0x1) == 0 && ((PORTC >> 5) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;


		case 29:
		
		// PC6
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRC >> 6) & 0x1) == 0 && ((PORTC >> 6) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;


		case 30:
		
		// PD0
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 0) & 0x1) == 0 && ((PORTD >> 0) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;


		case 31:
		
		// PD1
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 1) & 0x1) == 0 && ((PORTD >> 1) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;


		case 32:
		
		// PD2
		// We can only have a pin pull if the pin is set to an input.
		if(((DDRD >> 2) & 0x1) == 0 && ((PORTD >> 2) & 0x1) == 1)
		{
			value = PullHigh;
		}

		break;

		
	}
	
	return value;
	
}


void (*morph_config_pin_interrupt_functions[PIN_COUNT])(void) = {&MorphUtils_empty_callback};

enum MorphPinValue morph_config_pin_interrupt_setting[PIN_COUNT] = {NoInterrupt};

ISR(PCINT0_vect)
{
	
	
}

ISR(PCINT1_vect)
{
	
	
}

ISR(PCINT2_vect)
{

}

void morph_config_uart_set_tx_pin(MorphUARTChannel c, MorphPinNumber p_tx){}

void morph_config_uart_set_rx_pin(MorphUARTChannel c, MorphPinNumber p_rx){}

void morph_config_uart_set_rts_pin(MorphUARTChannel c, MorphPinNumber p_rts){}

void morph_config_uart_set_cts_pin(MorphUARTChannel c, MorphPinNumber p_cts){}

void morph_config_uart_purge_input(MorphUARTChannel c){}
	
void morph_config_uart_send_data(MorphUARTChannel c, MorphUARTData data){}
	
void morph_config_uart_setup_channel(MorphUARTChannel c, MorphUARTBaudRate br, MorphUARTByteSize bs, enum MorphUARTParity pc, MorphUARTStopBits sb){}


void morph_config_gpio_set_pin_interrupt(void (*function)(void), MorphPinNumber pn, enum MorphExternalInterruptType  pv)
{
	
	// Only Pin 1 and Pin 32 are capable of differentiating falling/rising edges in interrupts. 
	
	// All other pins are capable of "pin change" interrupts only. For these interrupts, a check will be made in the
	// ISR to determine which pin was interrupted and if the interrupt was falling or rising edge. 
	// Some pins are not capable of any interrupts and will be ignored.

}

// Performs any configuration this config file requires.
void morph_config_init()
{
	

	
}


void morph_implementation_test()
{
	
	uint8_t i = 0;
	
	i ++;
	
	i ++; 
	
	i ++;
	
}

#endif