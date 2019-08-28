/*
 * MorphConfigATmega328.c
 * 
 * This is an example configuration file for the ATmega328 chip from Atmel.
 *
 * Created: 11/15/2018 6:20:52 PM
 *  Author: 243400
 */ 



#ifdef ENABLE_SAMD21E18A_CONFIG

#include "sam.h"

#include <MorphGPIO.h>

#include <MorphConfig.h>

#include <inttypes.h>

#include <stdbool.h>

#define PIN_COUNT 64

typedef struct morph_config_pin_def{
	int8_t pinGroup;
	int8_t pinNumInGroup;
	int8_t sercomUnit;
	int8_t sercomPad;
	int8_t sercomAltUnit;
	int8_t sercomAltPad;
	int8_t adcUnit;
} MorphConfigPinDefinition ;

MorphConfigPinDefinition pin_defs[] = {
	//Pin Group, Pin Number, sercomUnit, sercomPad, sercomAltUnit, sercomAltPad
	{0, 0, -1, -1, 1, 0    , -1},
	{0, 1, -1, -1, 1, 1    , -1},
	{0, 2, -1, -1, -1, -1  , 0},
	{0, 3, -1, -1, -1, -1  , 1},
	{0, 4, -1, -1, 0, 0    , 4},
	{0, 5, -1, -1, 0, 1    , 5},
	{0, 6, -1, -1, 0, 2    , 6},
	{0, 7, -1, -1, 0, 3    , 7},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{0, 8, 0, 0, 2, 0      , 16},
	{0, 9, 0, 1, 2, 1      , 17},
	{0, 10, 0, 2, 2, 2     , 18},
	{0, 11, 0, 3, 2, 3     , 19},
	{0, 14, 2, 2, 4, 2     , -1},
	{0, 15, 2, 3, 4, 3     , -1},
	{0, 16, 1, 0, 3, 0     , -1},
	{0, 17, 1, 1, 3, 1     , -1},
	{0, 18, 1, 2, 3, 2     , -1},
	{0, 19, 1, 3, 3, 3     , -1},
	{0, 22, 3, 0, 5, 0     , -1},
	{0, 23, 3, 1, 5, 1     , -1},
	{0, 24, 3, 2, 5, 2     , -1},
	{0, 25, 3, 3, 5, 3     , -1},
	{0, 27, -1, -1, -1, -1 , -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{0, 28, -1, -1, -1, -1 , -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1},
	{0, 30, -1, -1, 1, 2   , -1},
	{0, 31, -1, -1, 1, 3   , -1},


};

enum PMUXTypes {EIC_PMUX = 0, ADC_PMUX = 1, SERCOM_PMUX = 2, SERCOM_ALT_PMUX = 3, TC_PMUX=4, TCC_PMUX=5, COM_PMUX = 6, GCLK_PMUX = 7};



void morph_config_gpio_set_pin_value(MorphPinNumber pn, enum MorphPinValue pv)
{
	
	uint8_t value = (pv == High ? 1 : 0);
	
	if(pn >= 1 && pn <= PIN_COUNT)
	{
	
		int8_t pin_group = pin_defs[pn - 1].pinGroup;
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;
	
		if(pin_group >= 0)
		{
	
			if(value == 1)
			{
				PORT->Group[pin_group].OUTSET.reg = (1ul << pin_num);	
			}
			else
			{
				PORT->Group[pin_group].OUTCLR.reg = (1ul << pin_num);
			}
		
		}
		
	}
	
}

enum MorphPinValue morph_config_gpio_get_pin_value(MorphPinNumber pn)
{
	
	int8_t pin_group = pin_defs[pn - 1].pinGroup;
	int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;
	
	
	if (pin_defs[pn].pinGroup >= 0)
	{
		
		// Verify the input enable has been enabled
		PORT->Group[pin_group].PINCFG[pin_num].bit.INEN = 1;
		
		if((PORT->Group[pin_group].IN.reg >> pin_num) & 0x1 == 1)
			return High;
		
	}
	
	return Low;
	
}

void morph_config_gpio_set_pin_direction(MorphPinNumber pn, enum MorphPinDirection pd)
{
	
	uint8_t value = (pd == Output ? 1 : 0);
	
	if(pn >= 1 && pn <= PIN_COUNT)
	{
		
		int8_t pin_group = pin_defs[pn - 1].pinGroup;
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;
		
		if(pin_group >= 0)
		{
			
			if(value == 1)
			{
				PORT->Group[pin_group].DIRSET.reg = (1ul << pin_num);
				
				// We probably won't need input enabled at this time.
				// Disable it.
				// Input reading ensures it is on if that is ever called.
				PORT->Group[pin_group].PINCFG[pin_num].bit.INEN = 0;
			}
			else
			{
				// This is an input!
				// Set the direction to input!
				PORT->Group[pin_group].DIRCLR.reg = (1ul << pin_num);
				// Set the input enable to enabled!
				PORT->Group[pin_group].PINCFG[pin_num].bit.INEN = 1;
			}
			
		}
		
	}

}

enum MorphPinDirection morph_config_gpio_get_pin_direction(MorphPinNumber pn)
{

	if(pn >= 1 && pn <= PIN_COUNT)
	{
		
		int8_t pin_group = pin_defs[pn - 1].pinGroup;
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;
		
		if(pin_group >= 0)
		{
			
			return PORT->Group[pin_group].DIR.reg >> pin_num & 0x1 == 0 ? Input : Output;
			
		}
		
	}
	
	return Input;
	
}

void morph_config_gpio_set_pin_pull_state(MorphPinNumber pn, enum MorphPinPullState ps)
{
	
	if(pn >= 1 && pn <= PIN_COUNT)
	{
			
		int8_t pin_group = pin_defs[pn - 1].pinGroup;
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;
			
		if(pin_group >= 0)
		{

			// These all need the input set
			// This will set the port for input.
			PORT->Group[pin_group].DIRCLR.reg = (1ul << pin_num);
				
			switch(ps)
			{

				case PullHigh:
				
					// Ensure the pullups are enabled.
					
					// First, set output to the correct value (1 in this case).
					PORT->Group[pin_group].OUTSET.reg = (1ul << pin_num);

					// Next, pull enable!
					PORT->Group[pin_group].PINCFG[pin_num].bit.PULLEN = 1;
				
					break;
				
				case PullLow:

					// Ensure the pulldowns are enabled.

					// First, set output to the correct value (1 in this case).
					PORT->Group[pin_group].OUTCLR.reg = (1ul << pin_num);

					// Next, pull enable!
					PORT->Group[pin_group].PINCFG[pin_num].bit.PULLEN = 1;
									
					break;
				
				case PullNone:
				default:
				
					//Disable pulling in either direction.
					PORT->Group[pin_group].PINCFG[pin_num].bit.PULLEN = 0;
					// Also clear output just in case.
					PORT->Group[pin_group].OUTCLR.reg = (1ul << pin_num);

			}
	
		}
			
	}

}

enum MorphPinPullState morph_config_gpio_get_pin_pull_state(MorphPinNumber pn)
{
	
	if(pn >= 1 && pn <= PIN_COUNT)
	{
	
		int8_t pin_group = pin_defs[pn - 1].pinGroup;
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;
	
		if(PORT->Group[pin_group].PINCFG[pin_num].bit.PULLEN == 1 && PORT->Group[pin_group].DIR.reg >> pin_num & 0x1 == 0)
		{
			
			//This pin is configured for input and pulling is enabled!
			if(PORT->Group[pin_group].OUT.reg >> pin_num & 0x1 == 1)
			{
				
				// The output is set to 1. This is a pullup!
				return PullHigh;
				
			}
			else
			{
				// The output is set to 0. This is a pulldown!	
				return PullLow;
				
			}

			
		}
	}
	
	return PullNone;
	
}

void set_mux_group_config(enum PMUXTypes t, uint8_t group, uint8_t pin)
{
	
	// Is this an even or odd pin?
	if(pin % 2 == 0)
	{
		//It's an even pin.
		//Enable the PMUX 
		PORT->Group[group].PMUX[pin/2].bit.PMUXE = t;
	}
	else
	{
		//It's an odd pin.
		//Enable the PMUX.
		PORT->Group[group].PMUX[pin/2].bit.PMUXO = t;


	}	

	PORT->Group[group].PINCFG[pin].bit.PMUXEN = 1;
	
}

Sercom * get_sercom_channel_ptr(uint8_t c)
{
	
	switch(c)
	{
		case 0:
			return SERCOM0;
		case 1:
			return SERCOM1;
		case 2:
			return SERCOM2;
		case 3:
			return SERCOM3;
		default:
			return SERCOM0;
	}
	
}

typedef struct sercom_uart_rx_config{
	int8_t rx_pad_num;
} SercomUartRxConfig ;

typedef struct sercom_uart_tx_config{
	int8_t tx_pad_num;
	int8_t xck_pad_num;
	int8_t rts_pad_num;
	int8_t cts_pad_num;
	uint8_t txpo_reg_val;
	
} SercomUartTxConfig ;

SercomUartTxConfig uart_tx_defs[] =
{
	{ 0, 1, -1, -1, 0x0},
	{ 2, 3, -1, -1, 0x1},
	{ 0,-1,  2,  3, 0x2},
	{-1,-1, -1, -1, 0x3}
};

typedef struct uart_default_sercom_pads{
	MorphPinNumber tx_pin_num;
	MorphPinNumber rx_pin_num;
} UARTPinConfig;


// All default configs use SERCOM pad 0 for TX and SERCOM pad 2 for RX.
UARTPinConfig uart_default_defs[] =
{
	{ 17, 19}, //SERCOM 0
	{ 35, 37}, //SERCOM 1
	{ 29, 31}, //SERCOM 2
	{ 43, 45}, //SERCOM 3
	{ 25, 27}, //SERCOM 4
	{ 39, 41}, //SERCOM 5
};


UARTPinConfig uart_current_defs[] =
{
	{ -1, -1}, //SERCOM 0
	{ -1, -1}, //SERCOM 1
	{ -1, -1}, //SERCOM 2
	{ -1, -1}, //SERCOM 3
	{ -1, -1}, //SERCOM 4
	{ -1, -1}, //SERCOM 5
};

#define MAX_SERIAL_BUFFER 250

void initClockNVIC( int8_t sercom_channel )
{
	uint8_t clockId = 0;
	IRQn_Type IdNvic=PendSV_IRQn ; // Dummy init to intercept potential error later

	Sercom * sercom = get_sercom_channel_ptr(sercom_channel);

	if(sercom == SERCOM0)
	{
		clockId = 0x14U;
		IdNvic = SERCOM0_IRQn;
	}
	else if(sercom == SERCOM1)
	{
		clockId = 0x15U;
		IdNvic = SERCOM1_IRQn;
	}
	else if(sercom == SERCOM2)
	{
		clockId = 0x16U;
		IdNvic = SERCOM2_IRQn;
	}
	else if(sercom == SERCOM3)
	{
		clockId = 0x17U;
		IdNvic = SERCOM3_IRQn;
	}
	#if defined(SERCOM4)
	else if(sercom == SERCOM4)
	{
		clockId = 0x18U;
		IdNvic = SERCOM4_IRQn;
	}
	#endif // SERCOM4
	#if defined(SERCOM5)
	else if(sercom == SERCOM5)
	{
		clockId = 0x19U;
		IdNvic = SERCOM5_IRQn;
	}
	#endif // SERCOM5

	if ( IdNvic == PendSV_IRQn )
	{
		// We got a problem here
		return ;
	}

	// Setting NVIC
	NVIC_EnableIRQ(IdNvic);
	NVIC_SetPriority (IdNvic, ((1<<__NVIC_PRIO_BITS) - 1));  /* set Priority */

	//Setting clock
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID( clockId ) | // Generic Clock 0 (SERCOMx)
	GCLK_CLKCTRL_GEN_GCLK0 | // Generic Clock Generator 0 is source
	GCLK_CLKCTRL_CLKEN ;

	while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY )
	{
		/* Wait for synchronization */
	}
}

#define UART_BUFF_SIZE 500

uint16_t uart_buffer[6][UART_BUFF_SIZE];

int16_t current_buffer_size[6] = {0};

int16_t current_buffer_front[6] = {0};

int16_t current_buffer_rear[6] = {0};

bool is_sercom_buff_empty(uint8_t channel)
{
	return current_buffer_front[channel] == current_buffer_rear[channel] && current_buffer_size[channel] == 0;
}

bool is_sercom_buff_full(uint8_t channel)
{
	return current_buffer_front[channel] == current_buffer_rear[channel] && current_buffer_size[channel] != 0;
}

uint16_t get_sercom_buff(uint8_t channel)
{
	if(!is_sercom_buff_empty(channel))
	{
		uint16_t data = uart_buffer[channel][current_buffer_front[channel]];
		
		if(current_buffer_front[channel] == UART_BUFF_SIZE - 1)
		current_buffer_front[channel] = 0;
		else
		current_buffer_front[channel] ++;
		
		current_buffer_size[channel] --;
		
		return data;
	}
	else
	{
		// Return null if empty.
		return 0;
	}
}

void add_sercom_buff(uint8_t channel, uint16_t data)
{
	if(!is_sercom_buff_full(channel))
	{
		uart_buffer[channel][current_buffer_rear[channel]] = (MorphUARTByte)data;
		
		if(current_buffer_rear[channel] == UART_BUFF_SIZE - 1)
		current_buffer_rear[channel] = 0;
		else
		current_buffer_rear[channel] ++;
		current_buffer_size[channel]++;
	}
}


void SERCOM0_Handler()
{
	uint8_t channel = 0;
	Sercom * sercom_ptr = get_sercom_channel_ptr(channel);
	
	if(sercom_ptr->USART.INTFLAG.bit.RXC)
	{
		// Put the data into the buffer.
		add_sercom_buff(channel, sercom_ptr->USART.DATA.reg);
		
		// Clear the flag
		sercom_ptr->USART.INTFLAG.bit.RXC = 1;
	}
	
}

void SERCOM1_Handler()
{
	uint8_t channel = 1;
	Sercom * sercom_ptr = get_sercom_channel_ptr(channel);
	
	if(sercom_ptr->USART.INTFLAG.bit.RXC)
	{
		// Put the data into the buffer.
		add_sercom_buff(channel, sercom_ptr->USART.DATA.reg);

		// Clear the flag
		sercom_ptr->USART.INTFLAG.bit.RXC = 1;
	}
	
}

void SERCOM2_Handler()
{
	uint8_t channel = 2;
	Sercom * sercom_ptr = get_sercom_channel_ptr(channel);
	
	if(sercom_ptr->USART.INTFLAG.bit.RXC)
	{
		
		uint16_t new_data = sercom_ptr->USART.DATA.reg;
		
		// Put the data into the buffer.
		add_sercom_buff(channel, new_data);
		
		// Clear the flag
		sercom_ptr->USART.INTFLAG.bit.RXC = 1;
		
	}
	
}

void SERCOM3_Handler()
{
	uint8_t channel = 3;
	Sercom * sercom_ptr = get_sercom_channel_ptr(channel);
	
	if(sercom_ptr->USART.INTFLAG.bit.RXC)
	{
		// Put the data into the buffer.
		add_sercom_buff(channel, sercom_ptr->USART.DATA.reg);
		
		// Clear the flag
		sercom_ptr->USART.INTFLAG.bit.RXC = 1;
		
	}
	
}

void SERCOM4_Handler()
{
	uint8_t channel = 4;
	Sercom * sercom_ptr = get_sercom_channel_ptr(channel);
	
	if(sercom_ptr->USART.INTFLAG.bit.RXC)
	{
		// Put the data into the buffer.
		add_sercom_buff(channel, sercom_ptr->USART.DATA.reg);
		
		// Clear the flag
		sercom_ptr->USART.INTFLAG.bit.RXC = 1;
		
	}
	
}

void SERCOM5_Handler()
{
	uint8_t channel = 5;
	Sercom * sercom_ptr = get_sercom_channel_ptr(channel);
	
	if(sercom_ptr->USART.INTFLAG.bit.RXC)
	{
		// Put the data into the buffer.
		add_sercom_buff(channel, sercom_ptr->USART.DATA.reg);

		// Clear the flag
		sercom_ptr->USART.INTFLAG.bit.RXC = 1;
		
	}
	
}

void morph_config_uart_setup_channel(MorphUARTChannel c, MorphUARTBaudRate br, MorphUARTByteSize bs, enum MorphUARTParity pc, MorphUARTStopBits sb)
{

	if(c < 0 || c > 5)
	return; //Begone!
	
	initClockNVIC(c);
	
	// The "Channel" in this case will refer to a SERCOM channel.
	Sercom * sercom_ptr = get_sercom_channel_ptr(c);
	
	for (uint16_t i; i < UART_BUFF_SIZE; i++)
	{
		// Clear the buffer.
		uart_buffer[c][i] = 0;
	}
	
	// Start the Software Reset
	sercom_ptr->USART.CTRLA.bit.SWRST = 1 ;

	while ( sercom_ptr->USART.CTRLA.bit.SWRST || sercom_ptr->USART.SYNCBUSY.bit.SWRST )
	{
		// Wait for both bits Software Reset from CTRLA and SYNCBUSY coming back to 0
	}
	

	
	// First, setup the muxing on the pins.
	uint8_t def_rx_pin = uart_default_defs[c].rx_pin_num;
	uint8_t def_tx_pin = uart_default_defs[c].tx_pin_num;

	uint8_t cur_rx_pin = uart_current_defs[c].rx_pin_num;
	uint8_t cur_tx_pin = uart_current_defs[c].tx_pin_num;

	if(cur_rx_pin == -1)
	{
		morph_config_uart_set_rx_pin(c, def_rx_pin);
	}
	else
	{
		morph_config_uart_set_rx_pin(c, cur_rx_pin);
	}
	
	if(cur_tx_pin == -1)
	{
		morph_config_uart_set_tx_pin(c, def_tx_pin);
	}
	else
	{
		morph_config_uart_set_tx_pin(c, cur_tx_pin);
	}

	// Pins configured!
	
	// Setting SERCOM mode to UART on internal clock
	sercom_ptr->USART.CTRLA.bit.MODE = SERCOM_USART_CTRLA_MODE_USART_INT_CLK_Val;
	
	// 16x over-sampling using fractional baud rate generation.
	sercom_ptr->USART.CTRLA.bit.SAMPR = 0x1;
	
	//// We are doing 16x oversampling
	uint8_t sample_rate = 16;
	//
	//// Asynchronous fractional mode (Table 24-2 in datasheet)
	////   BAUD = fref / (sampleRateValue * fbaud)
	//// (multiply by 8, to calculate fractional piece)
	uint32_t baudTimes8 = (SystemCoreClock * 8) / (sample_rate * br);

	sercom_ptr->USART.BAUD.FRAC.FP   = (baudTimes8 % 8);
	sercom_ptr->USART.BAUD.FRAC.BAUD = (baudTimes8 / 8);

	// Asynchronous arithmetic mode
	// 65535 * ( 1 - sampleRateValue * baudrate / SystemCoreClock);
	// 65535 - 65535 * (sampleRateValue * baudrate / SystemCoreClock));
	//	sercom_ptr->USART.BAUD.reg = 65536.0f * ( 1.0f - (float)(sample_rate) * (float)(br) / (float)(SystemCoreClock));
	
	// Now for frame stuff.
	
	// Determine if we need parity or not.
	sercom_ptr->USART.CTRLA.bit.FORM = pc == MorphNoParity ? 0 : 1;
	
	if(pc != MorphNoParity)
	{
		// If we have parity, determine if it is even or odd.
		sercom_ptr->USART.CTRLB.bit.PMODE = pc == MorphEvenParity ? 0 : 1;
	}
	
	// Force data order to be LSB first
	sercom_ptr->USART.CTRLA.bit.DORD = 1;
	
	// Setting the character size.
	switch(bs)
	{
		case 9:
		
		sercom_ptr->USART.CTRLB.bit.CHSIZE = 0x1;
		
		break;
		
		case 8:

		sercom_ptr->USART.CTRLB.bit.CHSIZE = 0x0;
		
		break;
		
		case 5:
		case 6:
		case 7:

		sercom_ptr->USART.CTRLB.bit.CHSIZE = bs;
		
		break;

		default:
		sercom_ptr->USART.CTRLB.bit.CHSIZE = 0x0;
		
	}
	
	// Setting stop bits.
	sercom_ptr->USART.CTRLB.bit.SBMODE = sb == 1 ? 0 : 1;
	
	
	// Enable transmitting and receiving!
	sercom_ptr->USART.CTRLB.bit.TXEN = 0x1;
	sercom_ptr->USART.CTRLB.bit.RXEN = 0x1;
	
	////Setting the Interrupt register
	sercom_ptr->USART.INTENSET.reg =	SERCOM_USART_INTENSET_RXC;// | SERCOM_USART_INTENSET_ERROR;
	
	// Enable the SERCOM!
	sercom_ptr->USART.CTRLA.bit.ENABLE = 0x1u;

	//Wait for SYNCBUSY
	while(sercom_ptr->USART.SYNCBUSY.bit.ENABLE);
	
}


void morph_config_uart_send_data(MorphUARTChannel c, MorphUARTData data)
{
	if(c < 0 || c > 5)
		return; //Begone!
		
	Sercom * sercom_ptr = get_sercom_channel_ptr(c);
	
	// Wait for the data register to be empty.
	while(!sercom_ptr->USART.INTFLAG.bit.DRE);
	
	// Now write the data!
	sercom_ptr->USART.DATA.reg = data;
	
}

MorphUARTData morph_config_uart_read_data(MorphUARTChannel c)
{

	Sercom * sercom_ptr = get_sercom_channel_ptr(c);
		
	// The register should be read only when the Receive Complete Interrupt Flag bit in the 
	// Interrupt Flag Status and Clear register (INTFLAG.RXC) is set.
	// (per datasheet section 26.8.10)
	while(!sercom_ptr->USART.INTFLAG.bit.RXC);	
	
	return sercom_ptr->USART.DATA.reg;	
	
}

void morph_config_uart_send_byte(MorphUARTChannel c, MorphUARTByte byte)
{
	if(c < 0 || c > 5)
	return; //Begone!
	
	Sercom * sercom_ptr = get_sercom_channel_ptr(c);
	
	// Wait for the data register to be empty.
	while(!sercom_ptr->USART.INTFLAG.bit.DRE);
	
	// Now write the data!
	sercom_ptr->USART.DATA.reg = byte;	
}

MorphUARTByte morph_config_uart_read_byte(MorphUARTChannel c)
{
	//Sercom * sercom_ptr = get_sercom_channel_ptr(c);
	//
	//// The register should be read only when the Receive Complete Interrupt Flag bit in the
	//// Interrupt Flag Status and Clear register (INTFLAG.RXC) is set.
	//// (per datasheet section 26.8.10)
	//while(!sercom_ptr->USART.INTFLAG.bit.RXC);
	//
	//return sercom_ptr->USART.DATA.reg;
	//
	return (MorphUARTByte)get_sercom_buff(c);
	
}

void morph_config_uart_write_data_buffer(MorphUARTChannel c, MorphUARTData * buffer, size_t length)
{
	
	for(size_t i = 0; i < length && buffer[i] != 0; i ++)
	{
		
		morph_config_uart_send_data(c, (uint16_t)buffer[i]);
		
	}
	
}

enum MorphUARTErrors morph_config_uart_read_data_buffer(MorphUARTChannel c, MorphUARTData * buffer, size_t length, MorphUARTTimeout timeout)
{

	//TODO: timeout.

	for(size_t i = 0; i < length; i ++)
	{
		
		buffer[i] = morph_config_uart_read_data(c);
		
	}	
	
	return MORPH_UART_SUCCESS;

}

void morph_config_uart_write_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer, size_t length)
{
	for(size_t i = 0; i < length && buffer[i] != 0; i ++)
	{
			
		morph_config_uart_send_byte(c, buffer[i]);
			
	}
}

enum MorphUARTErrors morph_config_uart_read_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer, size_t length, MorphUARTTimeout timeout)
{
	for(size_t i = 0; i < length; i ++)
	{
		
		buffer[i] = morph_config_uart_read_byte(c);
		
	}
	
	return MORPH_UART_SUCCESS;
}

bool morph_config_uart_data_ready(MorphUARTChannel c)
{
	
	//Sercom * sercom_ptr = get_sercom_channel_ptr(c);
	//
	//
	//return sercom_ptr->USART.INTFLAG.bit.RXC;

	return !is_sercom_buff_empty(c);

}

void morph_config_uart_set_tx_pin(MorphUARTChannel c, MorphPinNumber p_tx)
{
	// Determine if such a configuration is even possible.

	if(c < 0 || c > 5)
		return; //Begone!

	Sercom * sercom_ptr = get_sercom_channel_ptr(c);

	int8_t pin_group = pin_defs[p_tx - 1].pinGroup;
	int8_t pin_num = pin_defs[p_tx - 1].pinNumInGroup;

	uint8_t txpo_reg_val = 0x0;

	bool do_config = false;
	bool use_config_alt = false;			
	
	if(pin_defs[p_tx].sercomUnit == c)
	{
		uint8_t cur_sercom_pad = pin_defs[p_tx - 1].sercomPad;
	
		// This pin has the correct sercom unit on it!
		// Does this pin line-up with a correct pad?
		for(uint8_t i = 0; i < sizeof(uart_tx_defs) / sizeof(uart_tx_defs[0]); i++)
		{
			
			if(uart_tx_defs[i].tx_pad_num == cur_sercom_pad)
			{
				// This tx configuration works!
				// Configure to use this tx pin.	
				do_config = true;
				use_config_alt = false;
				txpo_reg_val = uart_tx_defs[i].txpo_reg_val;
				break;
			}
			
		}
	}
	else if(pin_defs[p_tx].sercomAltUnit == c)
	{
		uint8_t cur_sercom_pad = pin_defs[p_tx - 1].sercomAltPad;
			
		// This pin has the correct sercom unit on it!
		// Does this pin line-up with a correct pad?
		for(uint8_t i = 0; i < sizeof(uart_tx_defs) / sizeof(uart_tx_defs[0]); i++)
		{
				
			if(uart_tx_defs[i].tx_pad_num == cur_sercom_pad)
			{
				// This tx configuration works!
				// Configure to use this alt-tx pin.
				do_config = true;
				use_config_alt = true;
				txpo_reg_val = uart_tx_defs[i].txpo_reg_val;
				break;
			}
				
		}
	}
	
	if(do_config)
	{
		if(use_config_alt)
			set_mux_group_config(SERCOM_ALT_PMUX, pin_group, pin_num);
		else
			set_mux_group_config(SERCOM_PMUX, pin_group, pin_num);		
	
		// This configures the TX settings for the sercom unit.
		sercom_ptr->USART.CTRLA.bit.TXPO = txpo_reg_val;
	
		// After configuring the mux functions, enable them on the pin.
		PORT->Group[pin_group].PINCFG[pin_num].bit.PMUXEN = 1;
		
		// Save this config
		uart_current_defs[c].tx_pin_num = p_tx;
	}
					

	
}

void morph_config_uart_set_rx_pin(MorphUARTChannel c, MorphPinNumber p_rx)
{
	
	if(c < 0 || c > 5)
		return; //Begone!
		
	Sercom * sercom_ptr = get_sercom_channel_ptr(c);


	int8_t pin_group = pin_defs[p_rx - 1].pinGroup;
	int8_t pin_num = pin_defs[p_rx - 1].pinNumInGroup;
	int8_t sercom_unit  = pin_defs[p_rx - 1].sercomUnit;
	int8_t sercom_alt_unit = pin_defs[p_rx - 1].sercomAltUnit;
	
	if(pin_defs[p_rx - 1].sercomUnit == c)
	{
		
		// Set the direction to input!
		PORT->Group[pin_group].DIRCLR.reg = (1ul << pin_num);
		// Set the input enable to enabled!
		PORT->Group[pin_group].PINCFG[pin_num].bit.INEN = 1;
		
		// This pin has the correct sercom unit on it!
		// The rx pin can be on any pad of the sercom.
		set_mux_group_config(SERCOM_PMUX, pin_group, pin_num);
		
		// After configuring the mux functions, enable them on the pin.
		PORT->Group[pin_group].PINCFG[pin_num].bit.PMUXEN = 1;

		sercom_ptr->USART.CTRLA.bit.RXPO = pin_defs[p_rx - 1].sercomPad;

		// Save this config
		uart_current_defs[c].rx_pin_num = p_rx;

	}
	else if(pin_defs[p_rx - 1].sercomAltUnit == c)
	{
		// This pin has the correct sercom unit on it!
		// The rx pin can be on any pad of the sercom.
		set_mux_group_config(SERCOM_ALT_PMUX, pin_group, pin_num);

		// After configuring the mux functions, enable them on the pin.
		PORT->Group[pin_group].PINCFG[pin_num].bit.PMUXEN = 1;

		sercom_ptr->USART.CTRLA.bit.RXPO = pin_defs[p_rx - 1].sercomAltPad;

		// Set the direction to input!
		PORT->Group[pin_group].DIRCLR.reg = (1ul << pin_num);
		// Set the input enable to enabled!
		PORT->Group[pin_group].PINCFG[pin_num].bit.INEN = 1;


		// Save this config
		uart_current_defs[c].rx_pin_num = p_rx;

	}
}

void morph_config_uart_set_cts_pin(MorphUARTChannel c, MorphPinNumber p_rts)
{
	// TODO: Implement
}

void morph_config_uart_set_rts_pin(MorphUARTChannel c,  MorphPinNumber p_cts)
{
	// TODO: Implement	
}

// --- I2C BEGIN ---

// Initializes the I2C channel as a master.
void morph_config_i2c_init_master(MorphI2CChannel c, MorphI2CBaudRate br)
{
	
	// First, make sure the clock is all set up with SERCOM.
	initClockNVIC(c);

	Sercom * sercom_ptr =  get_sercom_channel_ptr(c);
	
	//Setting the Software bit to 1
	sercom_ptr->I2CM.CTRLA.bit.SWRST = 1;

	//Wait both bits Software Reset from CTRLA and SYNCBUSY are equal to 0
	while(sercom_ptr->I2CM.CTRLA.bit.SWRST || sercom_ptr->I2CM.SYNCBUSY.bit.SWRST);	

	// 0x5 mode sets up master mode.
	sercom_ptr->I2CM.CTRLA.bit.MODE = 0x5;
	
	// Init the baud.
	sercom_ptr->I2CM.BAUD.bit.BAUD = SystemCoreClock / ( 2 * br);	
	
	// Enable the I2C master mode
	sercom_ptr->I2CM.CTRLA.bit.ENABLE = 1 ;

	while ( sercom_ptr->I2CM.SYNCBUSY.bit.ENABLE != 0 );

	// Setting bus idle mode
	sercom_ptr->I2CM.STATUS.bit.BUSSTATE = 1 ;

	while ( sercom_ptr->I2CM.SYNCBUSY.bit.SYSOP != 0 );
	
}

// Initializes the I2C channel as a slave.
void morph_config_i2c_init_slave(MorphI2CChannel c)
{
	
}

// This function is used for starting a transmission from the master.
void morph_config_i2c_start_transmission(MorphI2CChannel c, MorphI2CAddress a, enum MorphI2CReadWrite rw)
{
	uint8_t rw_flag = rw == MorphI2CWrite ? 0 : 1;

	Sercom * sercom_ptr =  get_sercom_channel_ptr(c);

	// This happens while the bus is not IDLE AND the bus owner is not us.
	// If the bus becomes idle, or we become the owner we will continue.
	while(sercom_ptr->I2CM.STATUS.bit.BUSSTATE != 0x1 && sercom_ptr->I2CM.STATUS.bit.BUSSTATE != 0x3);

	uint8_t address = a << 1 | rw_flag;

	// Set the address, also set the RW flag.
	sercom_ptr->I2CM.ADDR.bit.ADDR = address;

	// Address Transmitted
	if ( rw == MorphI2CWrite) // Write mode
	{
		while( !sercom_ptr->I2CM.INTFLAG.bit.MB )
		{
			// Wait transmission complete
		}
	}
	else  // Read mode
	{
		while( !sercom_ptr->I2CM.INTFLAG.bit.SB )
		{
			// If the slave NACKS the address, the MB bit will be set.
			// In that case, send a stop condition and return false.
			if (sercom_ptr->I2CM.INTFLAG.bit.MB) {
				sercom_ptr->I2CM.CTRLB.bit.CMD = 3; // Stop condition
				return false;
			}
			// Wait transmission complete
		}

		// Clean the 'Slave on Bus' flag, for further usage.
		//sercom->I2CM.INTFLAG.bit.SB = 0x1ul;
	}


	////ACK received (0: ACK, 1: NACK)
	//if(sercom_ptr->I2CM.STATUS.bit.RXNACK)
	//{
		//return false;
	//}
	//else
	//{
		//return true;
	//}

}

// This function commits the entire buffer into the bus and general cleanup. This might not be necessary.
void morph_config_i2c_end_transmission(MorphI2CChannel c)
{
	
	Sercom * sercom_ptr =  get_sercom_channel_ptr(c);
	
	// Tell the operation to stop.
	sercom_ptr->I2CM.CTRLB.bit.CMD = 0x3;

	while(sercom_ptr->I2CM.SYNCBUSY.bit.SYSOP)
	{
		// Waiting for synchronization
	}
}

MorphI2CByte morph_config_i2c_read(MorphI2CChannel c)
{
	
}

void morph_config_i2c_write(MorphI2CChannel c, MorphI2CByte b)
{
	Sercom * sercom_ptr =  get_sercom_channel_ptr(c);

	//Send data
	sercom_ptr->I2CM.DATA.reg = b;

	//Wait transmission successful
	while(!sercom_ptr->I2CM.INTFLAG.bit.MB) {

		// If a bus error occurs, the MB bit may never be set.
		// Check the bus error bit and bail if it's set.
		if (sercom_ptr->I2CM.STATUS.bit.BUSERR) {
			return;
		}
	}

	////Problems on line? nack received?
	//if(sercom_ptr->I2CM.STATUS.bit.RXNACK)
	//return false;
	//else
	//return true;
}

void morph_config_i2c_set_scl_pin(MorphI2CChannel c, MorphPinNumber pn)
{
	
	Sercom * sercom_ptr = get_sercom_channel_ptr(c);

	int8_t pin_group = pin_defs[pn - 1].pinGroup;
	int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;
	int8_t sercom_unit  = pin_defs[pn - 1].sercomUnit;
	int8_t sercom_alt_unit = pin_defs[pn - 1].sercomAltUnit;
	
	if(pin_defs[pn - 1].sercomUnit == c && pin_defs[pn - 1].sercomPad == 1)
	{
		
		// Set the direction to input!
		PORT->Group[pin_group].DIRCLR.reg = (1ul << pin_num);
		// Set the input enable to enabled!
		PORT->Group[pin_group].PINCFG[pin_num].bit.INEN = 1;
		
		// This pin has the correct sercom unit on it!
		// The rx pin can be on any pad of the sercom.
		set_mux_group_config(SERCOM_PMUX, pin_group, pin_num);
		
		// After configuring the mux functions, enable them on the pin.
		PORT->Group[pin_group].PINCFG[pin_num].bit.PMUXEN = 1;

	}
	else if(pin_defs[pn - 1].sercomAltUnit == c && pin_defs[pn - 1].sercomAltPad == 1)
	{
		// This pin has the correct sercom unit on it!
		// The rx pin can be on any pad of the sercom.
		set_mux_group_config(SERCOM_ALT_PMUX, pin_group, pin_num);

		// After configuring the mux functions, enable them on the pin.
		PORT->Group[pin_group].PINCFG[pin_num].bit.PMUXEN = 1;

		sercom_ptr->USART.CTRLA.bit.RXPO = pin_defs[pn - 1].sercomAltPad;

		// Set the direction to input!
		PORT->Group[pin_group].DIRCLR.reg = (1ul << pin_num);
		
	}
}

void morph_config_i2c_set_sda_pin(MorphI2CChannel c, MorphPinNumber pn)
{
	
	Sercom * sercom_ptr = get_sercom_channel_ptr(c);

	int8_t pin_group = pin_defs[pn - 1].pinGroup;
	int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;
	int8_t sercom_unit  = pin_defs[pn - 1].sercomUnit;
	int8_t sercom_alt_unit = pin_defs[pn - 1].sercomAltUnit;
	
	if(pin_defs[pn - 1].sercomUnit == c && pin_defs[pn - 1].sercomPad == 0)
	{
		
		// Set the direction to input!
		PORT->Group[pin_group].DIRCLR.reg = (1ul << pin_num);
		// Set the input enable to enabled!
		PORT->Group[pin_group].PINCFG[pin_num].bit.INEN = 1;
		
		// This pin has the correct sercom unit on it!
		// The rx pin can be on any pad of the sercom.
		set_mux_group_config(SERCOM_PMUX, pin_group, pin_num);
		
		// After configuring the mux functions, enable them on the pin.
		PORT->Group[pin_group].PINCFG[pin_num].bit.PMUXEN = 1;

	}
	else if(pin_defs[pn - 1].sercomAltUnit == c && pin_defs[pn - 1].sercomAltPad == 0)
	{
		// This pin has the correct sercom unit on it!
		// The rx pin can be on any pad of the sercom.
		set_mux_group_config(SERCOM_ALT_PMUX, pin_group, pin_num);

		// After configuring the mux functions, enable them on the pin.
		PORT->Group[pin_group].PINCFG[pin_num].bit.PMUXEN = 1;

	}
}
// --- I2C END ---


// This array maps adc channels to MorphPinNumbers.
MorphPinNumber adc_channel_defs [] =
{
	
	 3, // AIN0
	 4, // AIN1
	-1,	// AIN2
	-1,	// AIN3
	 5,	// AIN4
	 6,	// AIN5
     7, // AIN6
	 8, // AIN7
	-1, // AIN8
	-1, // AIN9
	-1, // AIN10
	-1, // AIN11
	-1, // AIN12
	-1, // AIN13
	-1, // AIN14
	10, // AIN15
	11, // AIN16
	12, // AIN17
	13, // AIN18
	14, // AIN19

};


MorphADCValue morph_config_adc_get_adc_value(MorphADCChannel c, MorphADCResolution res)
{
	
	// Get the pin number, convert to the group and pin numbers, multiplex, then sample.
	MorphPinNumber pin = adc_channel_defs[c];
	
	int8_t pin_group = pin_defs[pin - 1].pinGroup;
	int8_t pin_num = pin_defs[pin - 1].pinNumInGroup;

	// We have the pin group and pin number, now multiplex.
	set_mux_group_config(ADC_PMUX, pin_group, pin_num);
	
	// Multiplex done, now start a conversion and return result.
	ADC->CTRLA.bit.ENABLE = 0x1;
}

MorphADCValue morph_config_adc_get_adc_pin(MorphPinNumber p, MorphADCResolution res)
{
	
	//Setting clock
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID( 0x1E ) | // Generic Clock 0 (ADC)
	GCLK_CLKCTRL_GEN_GCLK0 | // Generic Clock Generator 0 is source
	GCLK_CLKCTRL_CLKEN ;

	while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY )
	{
		/* Wait for synchronization */
	}
	
	int8_t adc_unit = pin_defs[p-1].adcUnit;

	// First, is there even an ADC on this pin?	
	if(adc_unit < 0)
	{
		return 0; // Get outta here!
	}
	
	// Yeah, there's an ADC here. Let's get the pin group and number. 
	int8_t pin_group = pin_defs[p - 1].pinGroup;
	int8_t pin_num = pin_defs[p - 1].pinNumInGroup;
	
	// Set the mux for the ADC.
	set_mux_group_config(ADC_PMUX, pin_group, pin_num);

	// Set the mux for the AREF
	set_mux_group_config(ADC_PMUX, 0, 3);
	
	// Select the correct channel
	ADC->INPUTCTRL.bit.MUXPOS = adc_unit;
	
	// Use GND for the negative input
	ADC->INPUTCTRL.bit.MUXNEG = 0x18;
	
	// Setting the reference selection to INT1V (1.0V voltage reference)
	ADC->REFCTRL.bit.REFSEL = 0x3;
	
	// 128 bit prescaler.
	ADC->CTRLB.bit.PRESCALER = 0x7;
	
	// 12-bit resolution.
	ADC->CTRLB.bit.RESSEL = 0x3;

	// Just do a single conversion.
	ADC->CTRLB.bit.FREERUN = 0x0;
	
	// Enable!
	ADC->CTRLA.bit.ENABLE = 0x1;
	
	// Start a conversion.
	ADC->SWTRIG.bit.START = 0x1;
	
	// TODO: Make an adc init function that does this first.
	// Wait for the configuration to be ready.
	while(ADC->STATUS.bit.SYNCBUSY);

	// Wait for the result.
	while(!ADC->INTFLAG.bit.RESRDY);

	// Start a conversion.
	ADC->SWTRIG.bit.START = 0x1;

	// Wait for the result.
	while(!ADC->INTFLAG.bit.RESRDY);

	// Return the result of the conversion.
	MorphADCValue retval = ADC->RESULT.reg;

	return retval;

}

void morph_config_adc_init_adc(MorphPinNumber p)
{
		
	//Setting clock
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID( 0x1E ) | // Generic Clock 0 (ADC)
	GCLK_CLKCTRL_GEN_GCLK0 | // Generic Clock Generator 0 is source
	GCLK_CLKCTRL_CLKEN ;

	while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY )
	{
		/* Wait for synchronization */
	}
		
	int8_t adc_unit = pin_defs[p-1].adcUnit;

	// First, is there even an ADC on this pin?
	if(adc_unit < 0)
	{
		return; // Get outta here!
	}
		
	// Yeah, there's an ADC here. Let's get the pin group and number.
	int8_t pin_group = pin_defs[p - 1].pinGroup;
	int8_t pin_num = pin_defs[p - 1].pinNumInGroup;
		
	// Set the mux for the ADC.
	set_mux_group_config(ADC_PMUX, pin_group, pin_num);
		
	// Select the correct channel
	ADC->INPUTCTRL.bit.MUXPOS = adc_unit;
		
	// Use GND for the negative input
	ADC->INPUTCTRL.bit.MUXNEG = 0x18;
		
	// Setting the reference selection to INT1V (1.0V voltage reference)
	ADC->REFCTRL.bit.REFSEL = 0x0;
		
	// 128 bit prescaler.
	ADC->CTRLB.bit.PRESCALER = 0x7;
		
	// 12-bit resolution.
	ADC->CTRLB.bit.RESSEL = 0x3;

	// Just do a single conversion.
	ADC->CTRLB.bit.FREERUN = 0x0;
		
	// Enable!
	ADC->CTRLA.bit.ENABLE = 0x1;
		
	// Start a conversion.
	ADC->SWTRIG.bit.START = 0x1;
		
	// TODO: Make an adc init function that does this first.
	// Wait for the configuration to be ready.
	while(ADC->STATUS.bit.SYNCBUSY);

	// Wait for the result.
	while(!ADC->INTFLAG.bit.RESRDY);

	// Read the conversion.
	volatile MorphADCValue retval = ADC->RESULT.reg;

}

MorphADCValue morph_config_adc_read(MorphPinNumber p)
{
	// We are assuming the ADC on this pin is already initialized. 
	
	int8_t adc_unit = pin_defs[p-1].adcUnit;
	
	// First, is there even an ADC on this pin?
	if(adc_unit < 0)
	{
		return 0; // Get outta here!
	}
	
	// Select the correct channel
	ADC->INPUTCTRL.bit.MUXPOS = adc_unit;

	while(ADC->STATUS.bit.SYNCBUSY);
	
	// Start a conversion.
	ADC->SWTRIG.bit.START = 0x1;
		
	// Wait for the result.
	while(!ADC->INTFLAG.bit.RESRDY);

	// Return the conversion.
	return ADC->RESULT.reg;
		
}

int8_t morph_config_adc_set_resolution(MorphPinNumber p, MorphADCResolution res)
{

	int8_t adc_unit = pin_defs[p-1].adcUnit;
	
	// First, is there even an ADC on this pin?
	if(adc_unit < 0)
	{
		return 0; // Get outta here!
	}
	
	// Select the correct channel
	ADC->INPUTCTRL.bit.MUXPOS = adc_unit;

	while(ADC->STATUS.bit.SYNCBUSY);
	
	int8_t final_res = 0;
	
	if(res <= 8)
	{
		// Doing 8 bit resolution.
		final_res = 8;
		ADC->CTRLB.bit.RESSEL = 0x3;
		
	}	
	else if(res > 8 && res <= 10)
	{
		// Doing 10 bit resolution.
		final_res = 10;
		ADC->CTRLB.bit.RESSEL = 0x2;
	}
	else
	{ 
		// Doing 12 bit resolution.
		final_res = 12;
		ADC->CTRLB.bit.RESSEL = 0x0;
	}
	
	// Wait for the new options to sync.
	while(ADC->STATUS.bit.SYNCBUSY);	
	
	return final_res;
	
}

void morph_config_adc_set_reference(MorphPinNumber p, enum MorphADCReference ref, uint8_t ref_num)
{
	int8_t adc_unit = pin_defs[p-1].adcUnit;
		
	// First, is there even an ADC on this pin?
	if(adc_unit < 0)
	{
		return; // Get outta here!
	}
		
	// Select the correct channel
	ADC->INPUTCTRL.bit.MUXPOS = adc_unit;

	while(ADC->STATUS.bit.SYNCBUSY);

	if(ref == MorphADCExternalRef)
	{
		switch (ref_num)
		{
			case 0: // VREFA
				ADC->REFCTRL.bit.REFSEL = 0x3;
			break;
			
			case 1: // VREFB
				ADC->REFCTRL.bit.REFSEL = 0x4;
			break;
			
			default: // Default reference selection is VREFA
				ADC->REFCTRL.bit.REFSEL = 0x0;
		}		
	}		
	else
	{
		switch (ref_num)
		{
			case 0: // 1.0V voltage reference.
				ADC->REFCTRL.bit.REFSEL = 0x0;
			break;
			
			case 1: // 1/1.48 VDDANA
				ADC->REFCTRL.bit.REFSEL = 0x1;			
			break;
			
			case 2: // 1/2 VDDANA (only for VDDANA > 2.0v)
				ADC->REFCTRL.bit.REFSEL = 0x2;
			break;
			
			default: // Default reference selection is 1.0v
				ADC->REFCTRL.bit.REFSEL = 0x0;
		}
	}

	// Wait for the new options to sync.
	while(ADC->STATUS.bit.SYNCBUSY);

	// Start a conversion. We have to do this after changing the reference.
	ADC->SWTRIG.bit.START = 0x1;
	
	// Wait for the result.
	while(!ADC->INTFLAG.bit.RESRDY);

}

void morph_config_adc_set_prescaler(MorphPinNumber p, uint16_t prescaler)
{
	int8_t adc_unit = pin_defs[p-1].adcUnit;
		
	// First, is there even an ADC on this pin?
	if(adc_unit < 0)
	{
		return; // Get outta here!
	}
		
	// Select the correct channel
	ADC->INPUTCTRL.bit.MUXPOS = adc_unit;

	while(ADC->STATUS.bit.SYNCBUSY);

	if (prescaler <= 4)
	{
		// DIV4
		ADC->CTRLB.bit.PRESCALER = 0x0;
	}
	else if (prescaler <= 8)
	{
		// DIV8
		ADC->CTRLB.bit.PRESCALER = 0x1;
	}	
	else if (prescaler <= 16)
	{
		// DIV16
		ADC->CTRLB.bit.PRESCALER = 0x2;
	}
	else if (prescaler <= 32)
	{
		// DIV32
		ADC->CTRLB.bit.PRESCALER = 0x3;
	}
	else if (prescaler <= 64)
	{
		// DIV64
		ADC->CTRLB.bit.PRESCALER = 0x4;
	}
	else if (prescaler <= 128)
	{
		// DIV128	
		ADC->CTRLB.bit.PRESCALER = 0x5;
	}			
	else if (prescaler <= 256)
	{
		// DIV256
		ADC->CTRLB.bit.PRESCALER = 0x6;
	}
	else 
	{
		// DIV512
		ADC->CTRLB.bit.PRESCALER = 0x7;
	}
	
	while(ADC->STATUS.bit.SYNCBUSY);


}

MorphTimeValue millisecond_tick = 0;

void SysTick_Handler(void)
{
	// Handles the SysTick event to log the current milliseconds.
	millisecond_tick ++;
	
}

void morph_config_time_init(MorphTimerNumber tn, enum MorphTimerResolution res)
{
	// Do nothing.
	return;
	
}

void morph_config_time_init_rtc()
{
	// Setup the RTC
	
	// Configure SysTick to trigger an ISR every millisecond using a 48MHz CPU Clock
	SysTick->CTRL = 0;					// Disable SysTick
	SysTick->LOAD = 47999UL - 800UL;			// Set reload register for 1mS interrupts
	//NVIC_SetPriority(SysTick_IRQn, 3);	// Set interrupt priority to least urgency
	NVIC_SetPriority(SysTick_IRQn, 1);  // Okay, make it a little important
	SysTick->VAL = 0;					// Reset the SysTick counter value
	SysTick->CTRL = 0x00000007;			// Enable SysTick, Enable SysTick Exceptions, Use CPU Clock
	NVIC_EnableIRQ(SysTick_IRQn);		// Enable SysTick Interrupt
	
}

MorphTimeValue morph_config_time_millis()
{
	// Get the current millisecond time and return.
	return millisecond_tick;
	
}
/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK			  (48000000ul)/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK			  (48000000ul)

// Constants for Clock generators
#define GENERIC_CLOCK_GENERATOR_MAIN      (0u)
#define GENERIC_CLOCK_GENERATOR_XOSC32K   (1u)
#define GENERIC_CLOCK_GENERATOR_OSC32K    (1u)
#define GENERIC_CLOCK_GENERATOR_OSCULP32K (2u) /* Initialized at reset for WDT */
#define GENERIC_CLOCK_GENERATOR_OSC8M     (3u)
// Constants for Clock multiplexers
#define GENERIC_CLOCK_MULTIPLEXER_DFLL48M (0u)

#define CRYSTALLESS

void ClocksInit( void )
{
  /* Set 1 Flash Wait State for 48MHz, cf tables 20.9 and 35.27 in SAMD21 Datasheet */
  NVMCTRL->CTRLB.bit.RWS = NVMCTRL_CTRLB_RWS_HALF_Val ;

  /* Turn on the digital interface clock */
  PM->APBAMASK.reg |= PM_APBAMASK_GCLK ;


#if defined(CRYSTALLESS)

  /* ----------------------------------------------------------------------------------------------
   * 1) Enable OSC32K clock (Internal 32.768Hz oscillator)
   */

  uint32_t calib = (*((uint32_t *) FUSES_OSC32K_CAL_ADDR) & FUSES_OSC32K_CAL_Msk) >> FUSES_OSC32K_CAL_Pos;

  SYSCTRL->OSC32K.reg = SYSCTRL_OSC32K_CALIB(calib) |
                        SYSCTRL_OSC32K_STARTUP( 0x6u ) | // cf table 15.10 of product datasheet in chapter 15.8.6
                        SYSCTRL_OSC32K_EN32K |
                        SYSCTRL_OSC32K_ENABLE;

  while ( (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_OSC32KRDY) == 0 ); // Wait for oscillator stabilization

#else // has crystal

  /* ----------------------------------------------------------------------------------------------
   * 1) Enable XOSC32K clock (External on-board 32.768Hz oscillator)
   */
  SYSCTRL->XOSC32K.reg = SYSCTRL_XOSC32K_STARTUP( 0x6u ) | /* cf table 15.10 of product datasheet in chapter 15.8.6 */
                         SYSCTRL_XOSC32K_XTALEN | SYSCTRL_XOSC32K_EN32K ;
  SYSCTRL->XOSC32K.bit.ENABLE = 1 ; /* separate call, as described in chapter 15.6.3 */

  while ( (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_XOSC32KRDY) == 0 )
  {
    /* Wait for oscillator stabilization */
  }

#endif

  /* Software reset the module to ensure it is re-initialized correctly */
  /* Note: Due to synchronization, there is a delay from writing CTRL.SWRST until the reset is complete.
   * CTRL.SWRST and STATUS.SYNCBUSY will both be cleared when the reset is complete, as described in chapter 13.8.1
   */
  GCLK->CTRL.reg = GCLK_CTRL_SWRST ;

  while ( (GCLK->CTRL.reg & GCLK_CTRL_SWRST) && (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY) )
  {
    /* Wait for reset to complete */
  }

  /* ----------------------------------------------------------------------------------------------
   * 2) Put XOSC32K as source of Generic Clock Generator 1
   */
  GCLK->GENDIV.reg = GCLK_GENDIV_ID( GENERIC_CLOCK_GENERATOR_XOSC32K ) ; // Generic Clock Generator 1

  while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY )
  {
    /* Wait for synchronization */
  }

  /* Write Generic Clock Generator 1 configuration */
  GCLK->GENCTRL.reg = GCLK_GENCTRL_ID( GENERIC_CLOCK_GENERATOR_OSC32K ) | // Generic Clock Generator 1
#if defined(CRYSTALLESS)
                      GCLK_GENCTRL_SRC_OSC32K | // Selected source is Internal 32KHz Oscillator
#else
                      GCLK_GENCTRL_SRC_XOSC32K | // Selected source is External 32KHz Oscillator
#endif
//                      GCLK_GENCTRL_OE | // Output clock to a pin for tests
                      GCLK_GENCTRL_GENEN ;

  while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY )
  {
    /* Wait for synchronization */
  }

  /* ----------------------------------------------------------------------------------------------
   * 3) Put Generic Clock Generator 1 as source for Generic Clock Multiplexer 0 (DFLL48M reference)
   */
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID( GENERIC_CLOCK_MULTIPLEXER_DFLL48M ) | // Generic Clock Multiplexer 0
                      GCLK_CLKCTRL_GEN_GCLK1 | // Generic Clock Generator 1 is source
                      GCLK_CLKCTRL_CLKEN ;

  while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY )
  {
    /* Wait for synchronization */
  }

  /* ----------------------------------------------------------------------------------------------
   * 4) Enable DFLL48M clock
   */

  /* DFLL Configuration in Closed Loop mode, cf product datasheet chapter 15.6.7.1 - Closed-Loop Operation */

  /* Remove the OnDemand mode, Bug http://avr32.icgroup.norway.atmel.com/bugzilla/show_bug.cgi?id=9905 */
  SYSCTRL->DFLLCTRL.reg = SYSCTRL_DFLLCTRL_ENABLE;

  while ( (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY) == 0 )
  {
    /* Wait for synchronization */
  }

  SYSCTRL->DFLLMUL.reg = SYSCTRL_DFLLMUL_CSTEP( 31 ) | // Coarse step is 31, half of the max value
                         SYSCTRL_DFLLMUL_FSTEP( 511 ) | // Fine step is 511, half of the max value
                         SYSCTRL_DFLLMUL_MUL( (VARIANT_MCK + VARIANT_MAINOSC/2) / VARIANT_MAINOSC ) ; // External 32KHz is the reference

  while ( (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY) == 0 )
  {
    /* Wait for synchronization */
  }

#if defined(CRYSTALLESS)

  #define NVM_SW_CALIB_DFLL48M_COARSE_VAL 58

  // Turn on DFLL
  uint32_t coarse =( *((uint32_t *)(NVMCTRL_OTP4) + (NVM_SW_CALIB_DFLL48M_COARSE_VAL / 32)) >> (NVM_SW_CALIB_DFLL48M_COARSE_VAL % 32) )
                   & ((1 << 6) - 1);
  if (coarse == 0x3f) {
    coarse = 0x1f;
  }
  // TODO(tannewt): Load this value from memory we've written previously. There
  // isn't a value from the Atmel factory.
  uint32_t fine = 0x1ff;

  SYSCTRL->DFLLVAL.bit.COARSE = coarse;
  SYSCTRL->DFLLVAL.bit.FINE = fine;
  /* Write full configuration to DFLL control register */
  SYSCTRL->DFLLMUL.reg = SYSCTRL_DFLLMUL_CSTEP( 0x1f / 4 ) | // Coarse step is 31, half of the max value
                         SYSCTRL_DFLLMUL_FSTEP( 10 ) |
                         SYSCTRL_DFLLMUL_MUL( (48000) ) ;

  SYSCTRL->DFLLCTRL.reg = 0;

  while ( (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY) == 0 )
  {
    /* Wait for synchronization */
  }

  SYSCTRL->DFLLCTRL.reg =  SYSCTRL_DFLLCTRL_MODE |
                           SYSCTRL_DFLLCTRL_CCDIS |
                           SYSCTRL_DFLLCTRL_USBCRM | /* USB correction */
                           SYSCTRL_DFLLCTRL_BPLCKC;

  while ( (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY) == 0 )
  {
    /* Wait for synchronization */
  }

  /* Enable the DFLL */
  SYSCTRL->DFLLCTRL.reg |= SYSCTRL_DFLLCTRL_ENABLE ;

#else   // has crystal

  /* Write full configuration to DFLL control register */
  SYSCTRL->DFLLCTRL.reg |= SYSCTRL_DFLLCTRL_MODE | /* Enable the closed loop mode */
                           SYSCTRL_DFLLCTRL_WAITLOCK |
                           SYSCTRL_DFLLCTRL_QLDIS ; /* Disable Quick lock */

  while ( (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY) == 0 )
  {
    /* Wait for synchronization */
  }

  /* Enable the DFLL */
  SYSCTRL->DFLLCTRL.reg |= SYSCTRL_DFLLCTRL_ENABLE ;

  while ( (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLLCKC) == 0 ||
          (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLLCKF) == 0 )
  {
    /* Wait for locks flags */
  }

#endif

  while ( (SYSCTRL->PCLKSR.reg & SYSCTRL_PCLKSR_DFLLRDY) == 0 )
  {
    /* Wait for synchronization */
  }

  /* ----------------------------------------------------------------------------------------------
   * 5) Switch Generic Clock Generator 0 to DFLL48M. CPU will run at 48MHz.
   */
  GCLK->GENDIV.reg = GCLK_GENDIV_ID( GENERIC_CLOCK_GENERATOR_MAIN ) ; // Generic Clock Generator 0

  while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY )
  {
    /* Wait for synchronization */
  }

  /* Write Generic Clock Generator 0 configuration */
  GCLK->GENCTRL.reg = GCLK_GENCTRL_ID( GENERIC_CLOCK_GENERATOR_MAIN ) | // Generic Clock Generator 0
                      GCLK_GENCTRL_SRC_DFLL48M | // Selected source is DFLL 48MHz
//                      GCLK_GENCTRL_OE | // Output clock to a pin for tests
                      GCLK_GENCTRL_IDC | // Set 50/50 duty cycle
                      GCLK_GENCTRL_GENEN ;

  while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY )
  {
    /* Wait for synchronization */
  }

  /* ----------------------------------------------------------------------------------------------
   * 6) Modify PRESCaler value of OSC8M to have 8MHz
   */
  SYSCTRL->OSC8M.bit.PRESC = SYSCTRL_OSC8M_PRESC_0_Val ;  //CMSIS 4.5 changed the prescaler defines
  SYSCTRL->OSC8M.bit.ONDEMAND = 0 ;

  /* ----------------------------------------------------------------------------------------------
   * 7) Put OSC8M as source for Generic Clock Generator 3
   */
  GCLK->GENDIV.reg = GCLK_GENDIV_ID( GENERIC_CLOCK_GENERATOR_OSC8M ) ; // Generic Clock Generator 3

  /* Write Generic Clock Generator 3 configuration */
  GCLK->GENCTRL.reg = GCLK_GENCTRL_ID( GENERIC_CLOCK_GENERATOR_OSC8M ) | // Generic Clock Generator 3
                      GCLK_GENCTRL_SRC_OSC8M | // Selected source is RC OSC 8MHz (already enabled at reset)
//                      GCLK_GENCTRL_OE | // Output clock to a pin for tests
                      GCLK_GENCTRL_GENEN ;

  while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY )
  {
    /* Wait for synchronization */
  }

  /*
   * Now that all system clocks are configured, we can set CPU and APBx BUS clocks.
   * There values are normally the one present after Reset.
   */
  PM->CPUSEL.reg  = PM_CPUSEL_CPUDIV_DIV1 ;
  PM->APBASEL.reg = PM_APBASEL_APBADIV_DIV1_Val ;
  PM->APBBSEL.reg = PM_APBBSEL_APBBDIV_DIV1_Val ;
  PM->APBCSEL.reg = PM_APBCSEL_APBCDIV_DIV1_Val ;

  SystemCoreClock=VARIANT_MCK ;

  /* ----------------------------------------------------------------------------------------------
   * 8) Load ADC factory calibration values
   */

  // ADC Bias Calibration
  uint32_t bias = (*((uint32_t *) ADC_FUSES_BIASCAL_ADDR) & ADC_FUSES_BIASCAL_Msk) >> ADC_FUSES_BIASCAL_Pos;

  // ADC Linearity bits 4:0
  uint32_t linearity = (*((uint32_t *) ADC_FUSES_LINEARITY_0_ADDR) & ADC_FUSES_LINEARITY_0_Msk) >> ADC_FUSES_LINEARITY_0_Pos;

  // ADC Linearity bits 7:5
  linearity |= ((*((uint32_t *) ADC_FUSES_LINEARITY_1_ADDR) & ADC_FUSES_LINEARITY_1_Msk) >> ADC_FUSES_LINEARITY_1_Pos) << 5;

  ADC->CALIB.reg = ADC_CALIB_BIAS_CAL(bias) | ADC_CALIB_LINEARITY_CAL(linearity);

  /*
   * 9) Disable automatic NVM write operations
   */
  NVMCTRL->CTRLB.bit.MANW = 1;
}

void morph_config_init()
{

	ClocksInit();

	NVIC_SetPriority (SysTick_IRQn,  (1 << __NVIC_PRIO_BITS) - 2);  /* set Priority for Systick Interrupt (2nd lowest) */


	// Clock PORT for Digital I/O
	//  PM->APBBMASK.reg |= PM_APBBMASK_PORT ;
	//
	//  // Clock EIC for I/O interrupts
	//  PM->APBAMASK.reg |= PM_APBAMASK_EIC ;

	// Clock SERCOM for Serial
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0 | PM_APBCMASK_SERCOM1 | PM_APBCMASK_SERCOM2 | PM_APBCMASK_SERCOM3 | PM_APBCMASK_SERCOM4 | PM_APBCMASK_SERCOM5 ;
}


void morph_implementation_test()
{
	
	uint8_t i = 0;
	
	i ++;
	
	i ++; 
	
	i ++;
	
}

#endif