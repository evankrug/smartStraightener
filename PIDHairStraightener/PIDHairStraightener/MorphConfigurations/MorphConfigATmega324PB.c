/*
 * MorphConfigATmega324PB.c
 *
 * Created: 3/8/2019 10:08:25 AM
 *  Author: 243400
 */ 

#ifdef ENABLE_ATMEGA324PB_CONFIG
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <float.h>
#include <math.h>

#include <MorphTypes.h>
#include <MorphUtils.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#define NO_ADDRESS 0x0

#define PORTA_ADDRESS (uint8_t*)0x22
#define PORTB_ADDRESS (uint8_t*)0x25
#define PORTC_ADDRESS (uint8_t*)0x28
#define PORTD_ADDRESS (uint8_t*)0x2B
#define PORTE_ADDRESS (uint8_t*)0x2E

#define PINA_ADDRESS (uint8_t*)0X20
#define PINB_ADDRESS (uint8_t*)0X23
#define PINC_ADDRESS (uint8_t*)0X26
#define PIND_ADDRESS (uint8_t*)0X29
#define PINE_ADDRESS (uint8_t*)0x2C

#define DDRA_ADDRESS (uint8_t*)0X21
#define DDRB_ADDRESS (uint8_t*)0X24
#define DDRC_ADDRESS (uint8_t*)0X27
#define DDRD_ADDRESS (uint8_t*)0X2A
#define DDRE_ADDRESS (uint8_t*)0x2D


#define PORTA_GROUP      PORTA_ADDRESS, PINA_ADDRESS, DDRA_ADDRESS
#define PORTB_GROUP      PORTB_ADDRESS, PINB_ADDRESS, DDRB_ADDRESS
#define PORTC_GROUP      PORTC_ADDRESS, PINC_ADDRESS, DDRC_ADDRESS
#define PORTD_GROUP      PORTD_ADDRESS, PIND_ADDRESS, DDRD_ADDRESS
#define PORTE_GROUP      PORTE_ADDRESS, PINE_ADDRESS, DDRE_ADDRESS
#define NO_ADDRESS_GROUP NO_ADDRESS,    NO_ADDRESS,   NO_ADDRESS

#define NUM_PINS 44

#define CLOCK_SPEED 8000000

#define MAXIMUM_TIMERS_PER_PIN 2

typedef struct morph_timer_pin_group {
	uint8_t pin_number;
	int8_t timer_output;
	int8_t timer_output_channel;
} MorphTimerPinGroup;

typedef struct morph_pin_def_struct {
	bool is_io;
	volatile uint8_t * port_address;
	volatile uint8_t * pin_address;
	volatile uint8_t * direction_address;
	uint8_t port_bit;
	int8_t adc_mux_value;
} MorphConfigPinDefinition;

MorphConfigPinDefinition pin_defs[] = {
	//I/O?  Port Group      , Port Bit, ADC MUX
	{true,  PORTB_GROUP     ,        5,      -1}, // 1
	{true,  PORTB_GROUP     ,        6,      -1}, // 2
	{true,  PORTB_GROUP     ,        7,      -1}, // 3
	{true,  NO_ADDRESS_GROUP,        0,      -1}, // 4
	{true,  NO_ADDRESS_GROUP,        0,      -1}, // 5
	{true,  NO_ADDRESS_GROUP,        0,      -1}, // 6
	{true,  PORTE_GROUP     ,        0,      -1}, // 7
	{true,  PORTE_GROUP     ,        1,      -1}, // 8
	{true,  PORTD_GROUP     ,        0,      -1}, // 9
	{true,  PORTD_GROUP     ,        1,      -1}, // 10
	{true,  PORTD_GROUP     ,        2,      -1}, // 11
	{true,  PORTD_GROUP     ,        3,      -1}, // 12
	{true,  PORTD_GROUP     ,        4,      -1}, // 13
	{true,  PORTD_GROUP     ,        5,      -1}, // 14
	{true,  PORTD_GROUP     ,        6,      -1}, // 15
	{true,  PORTD_GROUP     ,        7,      -1}, // 16
	{true,  PORTE_GROUP     ,        2,      -1}, // 17
	{true,  PORTE_GROUP     ,        3,      -1}, // 18
	{true,  PORTC_GROUP     ,        0,      -1}, // 19
	{true,  PORTC_GROUP     ,        1,      -1}, // 20
	{true,  PORTC_GROUP     ,        2,      -1}, // 21
	{true,  PORTC_GROUP     ,        3,      -1}, // 22
	{true,  PORTC_GROUP     ,        4,      -1}, // 23
	{true,  PORTC_GROUP     ,        5,      -1}, // 24
	{true,  PORTC_GROUP     ,        6,      -1}, // 25
	{true,  PORTC_GROUP     ,        7,      -1}, // 26
	{true,  NO_ADDRESS_GROUP,        0,      -1}, // 27
	{true,  NO_ADDRESS_GROUP,        0,      -1}, // 28
	{true,  PORTE_GROUP     ,        4,      -1}, // 29
	{true,  PORTA_GROUP     ,        7,       7}, // 30
	{true,  PORTA_GROUP     ,        6,       6}, // 31
	{true,  PORTA_GROUP     ,        5,       5}, // 32
	{true,  PORTA_GROUP     ,        4,       4}, // 33
	{true,  PORTA_GROUP     ,        3,       3}, // 34
	{true,  PORTA_GROUP     ,        2,       2}, // 35
	{true,  PORTA_GROUP     ,        1,       1}, // 36
	{true,  PORTA_GROUP     ,        0,       0}, // 37
	{true,  PORTE_GROUP     ,        5,      -1}, // 38
	{true,  PORTE_GROUP     ,        6,      -1}, // 39
	{true,  PORTB_GROUP     ,        0,      -1}, // 40
	{true,  PORTB_GROUP     ,        1,      -1}, // 41
	{true,  PORTB_GROUP     ,        2,      -1}, // 42
	{true,  PORTB_GROUP     ,        3,      -1}, // 43
	{true,  PORTB_GROUP     ,        4,      -1}, // 44
};

#define NUM_TIMER_OUTPUTS 10

MorphTimerPinGroup timer_groups[NUM_TIMER_OUTPUTS] = 
{
	{43, 0, 0},
	{44, 0, 1},
	{14, 1, 0},		
	{13, 1, 1},
	{16, 2, 0},
	{15, 2, 1},
	{02, 3, 0},
	{03, 3, 1},
	{23, 4, 0},
	{03, 4, 1},
};

typedef struct morph_timer_8_bit_def_struct {
	bool is_in_use;
	bool is_in_use_by_morph_pwm;
	bool a_counter_in_use;
	bool b_counter_in_use;
	uint8_t * control_reg_a;
	uint8_t * control_reg_b;
	uint8_t * interrupt_mask_reg;
	uint8_t * output_compare_a;
	uint8_t * output_compare_b;
	void (*callback_a)(void);
	void (*callback_b)(void);
} MorphConfig8BitTimerDefinition;

typedef struct morph_timer_16_bit_def_struct {
	bool is_in_use;
	bool is_in_use_by_morph_pwm;
	bool a_counter_in_use;
	bool b_counter_in_use;
	volatile uint8_t * control_reg_a;
	volatile uint8_t * control_reg_b;
	volatile uint8_t * control_reg_c;
	volatile uint8_t * interrupt_mask_reg;
	volatile uint8_t * output_compare_a_low;
	volatile uint8_t * output_compare_a_high;
	volatile uint8_t * output_compare_b_low;
	volatile uint8_t * output_compare_b_high;
	void (*callback_a)(void);
	void (*callback_b)(void);
} MorphConfig16BitTimerDefinition;

MorphConfig8BitTimerDefinition timer_configs_8_bit[] = {
	{false, false, false, false, 0x44 /*TCCR0A*/, 0x45 /*TCCR0B*/, 0x6E /*TIMSK0*/, 0x47 /*OCR0A*/, 0x48 /*OCR0B*/, &MorphUtils_empty_callback, &MorphUtils_empty_callback},	//Timer/Counter0
	{false, false, false, false, 0xB0 /*TCCR2A*/, 0xB1 /*TCCR2B*/, 0x70 /*TIMSK2*/, 0xB3 /*OCR2A*/, 0xB4 /*OCR2B*/, &MorphUtils_empty_callback, &MorphUtils_empty_callback}	//Timer/Counter2
};

MorphConfig16BitTimerDefinition timer_configs_16_bit[] = {
	{false, false, false, false, 0x80 /*TCCR1A*/, 0x81 /*TCCR1B*/, 0x82 /*TCCR1C*/, 0x6F/*TIMSK1*/, 0x88 /*OCR1AL*/, 0x89 /*OCR1AH*/, 0x8A /*OCR1BL*/, 0x8B /*OCR1BH*/, &MorphUtils_empty_callback, &MorphUtils_empty_callback},
	{false, false, false, false, 0x90 /*TCCR3A*/, 0x91 /*TCCR3B*/, 0x92 /*TCCR3C*/, 0x71/*TIMSK3*/, 0x98 /*OCR3AL*/, 0x99 /*OCR3AH*/, 0x9A /*OCR3BL*/, 0x9B /*OCR3BH*/, &MorphUtils_empty_callback, &MorphUtils_empty_callback},
	{false, false, false, false, 0xA0 /*TCCR4A*/, 0xA1 /*TCCR4B*/, 0xA2 /*TCCR4C*/, 0x72/*TIMSK4*/, 0xA8 /*OCR4AL*/, 0xA9 /*OCR4AH*/, 0xAA /*OCR4BL*/, 0xAB /*OCR4BH*/, &MorphUtils_empty_callback, &MorphUtils_empty_callback}		
};

#define NUM_TIMER_PRESCALERS 5

uint16_t timer_prescaler_values[NUM_TIMER_PRESCALERS] = {
	1,
	8,
	64,
	256,
	1024
};



ISR(TIMER0_COMPA_vect) {
	timer_configs_8_bit[0].callback_a();
}

ISR(TIMER0_COMPB_vect) {
	timer_configs_8_bit[0].callback_b();
}

ISR(TIMER1_COMPA_vect) {
	timer_configs_16_bit[0].callback_a();
}

ISR(TIMER1_COMPB_vect) {
	timer_configs_16_bit[0].callback_b();
}

ISR(TIMER2_COMPA_vect) {
	timer_configs_8_bit[1].callback_a();
}

ISR(TIMER2_COMPB_vect) {
	timer_configs_8_bit[1].callback_b();
}

ISR(TIMER3_COMPA_vect) {
	timer_configs_16_bit[1].callback_a();
}

ISR(TIMER3_COMPB_vect) {
	timer_configs_16_bit[1].callback_b();
}

ISR(TIMER4_COMPA_vect) {
	timer_configs_16_bit[2].callback_a();
}

ISR(TIMER4_COMPB_vect) {
	timer_configs_16_bit[2].callback_b();
}


uint8_t find_timer_config(MorphPinNumber pn, MorphTimerPinGroup * ret_timer_groups, uint8_t size)
{

	uint8_t ret_timer_num = 0;

	for(uint8_t i = 0; i < NUM_TIMER_OUTPUTS; i ++)
	{
		
		if(timer_groups[i].pin_number == pn)
		{
			// Add it to the list.
			ret_timer_groups[ret_timer_num].pin_number				= timer_groups[i].pin_number;
			ret_timer_groups[ret_timer_num].timer_output			= timer_groups[i].timer_output;
			ret_timer_groups[ret_timer_num].timer_output_channel	= timer_groups[i].timer_output_channel;
		
			ret_timer_num += 1;
		
 			if(ret_timer_num >= size)
			{
				break;
			}
			
		}
		
	}
	
	return ret_timer_num;
	
}

void morph_config_gpio_set_pin_value(MorphPinNumber pn, enum MorphPinValue pv)
{
	if(pn < 1 || pn > NUM_PINS)
	return;
	
	MorphConfigPinDefinition cur_pin = pin_defs[pn - 1];
	
	uint8_t value = pv == High ? 1 : 0;
	
	uint8_t reg_val = (*cur_pin.port_address);
	
	(*cur_pin.port_address) = (reg_val & ~(0x1 << cur_pin.port_bit)) | (value << cur_pin.port_bit);
	
}

enum MorphPinValue morph_config_gpio_get_pin_value(MorphPinNumber pn)
{
	if(pn < 1 || pn > NUM_PINS)
	return Low;

	MorphConfigPinDefinition cur_pin = pin_defs[pn - 1];
	
	uint8_t bit_val = ((*cur_pin.pin_address) >> cur_pin.port_bit) & 0x1;
	
	return bit_val == 1 ? High : Low;

}

void morph_config_gpio_set_pin_direction(MorphPinNumber pn, enum MorphPinDirection pd)
{
	if(pn < 1 || pn > NUM_PINS)
	return;
	
	MorphConfigPinDefinition cur_pin = pin_defs[pn - 1];
	
	uint8_t value = pd == Output ? 1 : 0;
	
	uint8_t reg_val = (*cur_pin.direction_address);
	
	(*cur_pin.direction_address) = (reg_val & ~(0x1 << cur_pin.port_bit)) | (value << cur_pin.port_bit);
}

enum MorphPinDirection morph_config_gpio_get_pin_direction(MorphPinNumber pn)
{
	if(pn < 1 || pn > NUM_PINS)
	return;

	MorphConfigPinDefinition cur_pin = pin_defs[pn - 1];
	
	uint8_t bit_val = ((*cur_pin.direction_address) >> cur_pin.port_bit) & 0x1;
	
	return bit_val == 1 ? Output : Input;
}

void morph_config_gpio_set_pin_pull_state(MorphPinNumber pn, enum MorphPinPullState ps)
{
	if(pn < 1 || pn > NUM_PINS)
	return;
	
	MorphConfigPinDefinition cur_pin = pin_defs[pn - 1];
	
	// The ATmega328 can only pull up. It can also only pull up when it is configured as an input.
	uint8_t dir_bit = ((*cur_pin.direction_address) >> cur_pin.port_bit) & 0x1;
	
	if(dir_bit == 0 && (ps == PullHigh || ps == PullNone))
	{
		uint8_t value = ps == PullHigh ? 1 : 0;
		
		uint8_t reg_val = (*cur_pin.port_address);
		
		(*cur_pin.port_address) = (reg_val & ~(0x1 << cur_pin.port_bit)) | (value << cur_pin.port_bit);
	}
	
}

enum MorphPinPullState morph_config_gpio_get_pin_pull_state(MorphPinNumber pn)
{
}

void morph_config_gpio_set_pin_interrupt(void (*function)(void), MorphPinNumber pn, enum MorphExternalInterruptType pv)
{
}

void morph_config_gpio_unset_pin_interrupt(MorphPinNumber pn, enum MorphPinValue pv)
{
}

// ---- UART BEGIN ----

void morph_config_uart_setup_channel(MorphUARTChannel c, MorphUARTBaudRate br, MorphUARTByteSize bs, enum MorphUARTParity pc, MorphUARTStopBits sb)
{
	
	uint16_t brr_val = CLOCK_SPEED/16/br - 1;
	//
	///*Set baud rate */
	UBRR0H = (unsigned char)(brr_val>>8);
	UBRR0L = (unsigned char)brr_val;

	//UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	///* Set frame format: 8data, 2stop bit */
	UCSR0B = (1<<RXEN)|(3<<TXEN);
	
}

// Disables the UART channel and returns it to its normal state (as GPIO pins or whatever default is).
void morph_config_uart_disable_channel(MorphUARTChannel c)
{
}

// Will send the first n bytes of data depending on serial config.
void morph_config_uart_send_data(MorphUARTChannel c, MorphUARTData data)
{
}

// Receives one frame of data. May be up to 9 bits. Bit manipulation is on the user.
MorphUARTData morph_config_uart_read_data(MorphUARTChannel c)
{
}

// Will send the first n bytes of data depending on serial config.
// Does not support 9 bit frames.
void morph_config_uart_send_byte(MorphUARTChannel c, MorphUARTByte byte)
{
	
	 /* Wait for empty transmit buffer */
	 while ( !( UCSR0A & (1<<UDRE)) )
	 ;
	 /* Put data into buffer, sends the data */
	 UDR0 = byte;
}

// Receives one frame of data.
// Only receives up to 8 bits.
MorphUARTByte morph_config_uart_read_byte(MorphUARTChannel c)
{
}

// Writes a buffer to the UART channel. Will only use frames the size of the byte size configuration.
void morph_config_uart_write_data_buffer(MorphUARTChannel c, MorphUARTData * buffer, size_t length)
{
}

// Writes a buffer to the UART channel. Will limit frame size to 8 bits.
void morph_config_uart_write_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer, size_t length)
{
}

enum MorphUARTErrors morph_config_uart_read_data_buffer(MorphUARTChannel c, MorphUARTData * buffer, size_t length, MorphUARTTimeout timeout)
{
}

enum MorphUARTErrors morph_config_uart_read_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer, size_t length, MorphUARTTimeout timeout)
{
}

bool morph_config_uart_data_ready(MorphUARTChannel c)
{
}

// Purges the input buffer
void morph_config_uart_purge_input(MorphUARTChannel c)
{
}

void morph_config_uart_set_tx_pin(MorphUARTChannel c, MorphPinNumber p_tx)
{
}

void morph_config_uart_set_rx_pin(MorphUARTChannel c, MorphPinNumber p_rx)
{
}

void morph_config_uart_set_rts_pin(MorphUARTChannel c, MorphPinNumber p_rts)
{
}

void morph_config_uart_set_cts_pin(MorphUARTChannel c, MorphPinNumber p_cts)
{
}

// ---- UART END ----

// --- I2C BEGIN ---

// Initializes the I2C channel as a master.
void morph_config_i2c_init_master(MorphI2CChannel c, MorphI2CBaudRate br)
{
}

// Initializes the I2C channel as a slave.
void morph_config_i2c_init_slave(MorphI2CChannel c)
{
}

// This function is used for starting a transmission from the master.
void morph_config_i2c_start_transmission(MorphI2CChannel c, MorphI2CAddress a, enum MorphI2CReadWrite rw)
{
}

// This function commits the entire buffer into the bus and general cleanup. This might not be necessary.
void morph_config_i2c_end_transmission(MorphI2CChannel c)
{
}

MorphI2CByte morph_config_i2c_read(MorphI2CChannel c)
{
}

void morph_config_i2c_write(MorphI2CChannel c, MorphI2CByte b)
{
}

void morph_config_i2c_set_scl_pin(MorphI2CChannel c, MorphPinNumber pn)
{
}

void morph_config_i2c_set_sda_pin(MorphI2CChannel c, MorphPinNumber pn)
{
}

// --- I2C END ---

// ---- TIME BEGIN ----

MorphTimeValue millis_ticks;

void timer_update_millis()
{
	millis_ticks ++;
}

void morph_config_time_init(MorphTimerNumber tn, MorphTimerResolution res)
{
	// Acquire the second 8 bit timer.
	morph_config_timer_acquire_timer(tn, res);
	
	morph_config_timer_set_rate(tn, res, (MorphTimerRate)1000);
	
	morph_config_timer_set_timer_callback(tn, res, &timer_update_millis);
}

void morph_config_time_init_rtc()
{
}

MorphTimeValue morph_config_time_millis()
{
	return millis_ticks;
}

// ---- TIME END ----

// ---- TIMER BEGIN ----



void set_rate_8_bit(MorphTimerNumber tn, MorphTimerRate rate)
{
	
	if(tn > 1)
	return;
	
	// WARNING: Not thread safe!
	timer_configs_8_bit[tn].is_in_use = true;
	
	uint64_t prescaler_count_settings[NUM_TIMER_PRESCALERS] = {0};
	float prescaler_count_errors[NUM_TIMER_PRESCALERS] = {FLT_MAX};
	
	// Hold onto your pants, we're gonna do some float math really quick.
	
	for(uint8_t i = 0; i < NUM_TIMER_PRESCALERS; i++)
	{
		prescaler_count_settings[i] = ((float)CLOCK_SPEED / (1.0f * (float)timer_prescaler_values[i] * (float)rate)) * 8.0f - 1.0f;
		
		float true_frequency = (float)CLOCK_SPEED / (1.0f * (float)timer_prescaler_values[i] * (1.0f + (float)prescaler_count_settings[i])) * 8;
		
		float error = true_frequency - (float)rate;
		
		if(error < 0)
		error *= -1.0f;
		
		prescaler_count_errors[i] = error;
		
	}

	// We've calculated all of the required counts to get close to the desired frequency.
	// Now, figure out which one is closest and the count fits into 8 bits.
	
	// This makes the default prescaler the highest.
	uint8_t used_prescaler = NUM_TIMER_PRESCALERS - 1;
	float lowest_error = prescaler_count_errors[used_prescaler];
	
	for(uint8_t i = 0; i < NUM_TIMER_PRESCALERS; i ++)
	{
		if(prescaler_count_settings[i] < 0xFF && prescaler_count_errors[i] <= lowest_error)
		{
			// Hey, this one fits in 8 bits AND it has the lowest error.
			lowest_error = prescaler_count_errors[i];
			used_prescaler = i;
		}
	}

	// Everything has been calculated out and we've found the best clock settings. Yay!
	// Now, it's time to apply them.

	// First, put the clock into Clear Timer on Compare Match (CTC) mode. WGM is 011.
	
	// Clear WGM02
	*(timer_configs_8_bit[tn].control_reg_b) &= ~(0x1 << WGM02);

	uint8_t reg_a = *(timer_configs_8_bit[tn].control_reg_a);

	// Set WGM 01 and clear WGM 00
	*(timer_configs_8_bit[tn].control_reg_a) = (reg_a | (0x1 << WGM01)) & ~(0x1 << WGM00);

	// Set the count value to the chosen value.
	*(timer_configs_8_bit[tn].output_compare_a) = prescaler_count_settings[used_prescaler];

	uint8_t prescale_bits_val = 0x0;

	// Now, time to set up the prescaler. Once this is set, the timer will start.
	switch(timer_prescaler_values[used_prescaler])
	{
		case 1:
		prescale_bits_val = 0b001;
		break;
		
		case 8:
		prescale_bits_val = 0b010;
		break;
		
		case 64:
		prescale_bits_val = 0b011;
		break;
		
		case 256:
		prescale_bits_val = 0b100;
		break;
		
		case 1024:
		prescale_bits_val = 0b101;
		break;
	}
	
	uint8_t reg_b = *(timer_configs_8_bit[tn].control_reg_b);
	
	// Start the timer.
	*(timer_configs_8_bit[tn].control_reg_b) = (reg_b & (0xFF << 3)) | prescale_bits_val;
	
	// All done!
	
}

void set_rate_16_bit(MorphTimerNumber tn, MorphTimerRate rate)
{
	
	if(tn > 1)
	return;
	
	// WARNING: Not thread safe!
	timer_configs_16_bit[tn].is_in_use = true;
	
	uint64_t prescaler_count_settings[NUM_TIMER_PRESCALERS] = {0};
	float prescaler_count_errors[NUM_TIMER_PRESCALERS] = {FLT_MAX};
	
	// Hold onto your pants, we're gonna do some float math really quick.
	
	for(uint8_t i = 0; i < NUM_TIMER_PRESCALERS; i++)
	{
		prescaler_count_settings[i] = ((float)CLOCK_SPEED / (1.0f * (float)timer_prescaler_values[i] * (float)rate)) - 1.0f;
		
		float true_frequency = (float)CLOCK_SPEED / (1.0f * (float)timer_prescaler_values[i] * (1.0f + (float)prescaler_count_settings[i]));
		
		float error = true_frequency - (float)rate;
		
		if(error < 0)
		error *= -1.0f;
		
		prescaler_count_errors[i] = error;
		
	}

	// We've calculated all of the required counts to get close to the desired frequency.
	// Now, figure out which one is closest and the count fits into 8 bits.
	
	// This makes the default prescaler the highest.
	uint8_t used_prescaler = NUM_TIMER_PRESCALERS - 1;
	float lowest_error = prescaler_count_errors[used_prescaler];
	
	for(uint8_t i = 0; i < NUM_TIMER_PRESCALERS; i ++)
	{
		if(prescaler_count_settings[i] < 0xFFFF && prescaler_count_errors[i] <= lowest_error)
		{
			// Hey, this one fits in 8 bits AND it has the lowest error.
			lowest_error = prescaler_count_errors[i];
			used_prescaler = i;
		}
	}

	// Everything has been calculated out and we've found the best clock settings. Yay!
	// Now, it's time to apply them.

	// TODO: CHANGE ALL OF THIS!!

	// First, put the clock into Clear Timer on Compare Match (CTC) mode. WGM is 011.
	
	// Clear WGM13, Set WGM12
	*(timer_configs_16_bit[tn].control_reg_b) = (*(timer_configs_16_bit[tn].control_reg_b) & ~(0x1 << WGM13)) | (0x1 << WGM12);

	// Clear WGM11 and WGM10
	*(timer_configs_16_bit[tn].control_reg_a) = (*(timer_configs_16_bit[tn].control_reg_a) & ~(0x1 << WGM11)) & ~(0x1 << WGM10);

	// Set the count value to the chosen value.
	*(timer_configs_16_bit[tn].output_compare_a_high) = ((prescaler_count_settings[used_prescaler] >> 8) & 0xFF);
	*(timer_configs_16_bit[tn].output_compare_a_low)  = (prescaler_count_settings[used_prescaler] & 0xFF);


	uint8_t prescale_bits_val = 0x0;

	// Now, time to set up the prescaler. Once this is set, the timer will start.
	switch(timer_prescaler_values[used_prescaler])
	{
		case 1:
		prescale_bits_val = 0b001;
		break;
		
		case 8:
		prescale_bits_val = 0b010;
		break;
		
		case 64:
		prescale_bits_val = 0b011;
		break;
		
		case 256:
		prescale_bits_val = 0b100;
		break;
		
		case 1024:
		prescale_bits_val = 0b101;
		break;
	}
	
	uint8_t reg_b = *(timer_configs_16_bit[tn].control_reg_b);
	
	// Start the timer.
	*(timer_configs_16_bit[tn].control_reg_b) = (reg_b & (0xFF << 3)) | prescale_bits_val;
	
	// All done!
	
}

void acquire_16_bit(MorphTimerNumber tn, MorphTimerRate rate)
{
	
}

void morph_config_timer_acquire_timer(MorphTimerNumber tn, MorphTimerResolution res)
{
	//TODO: Fix this.
	if(res <= 8)
	{
		timer_configs_8_bit[tn].is_in_use = true;
	}
	else if(res <= 16)
	{
		timer_configs_16_bit[tn].is_in_use = true;
	}

}

void morph_config_timer_release_timer(MorphTimerNumber tn, MorphTimerResolution res)
{
	
}

void morph_config_timer_set_rate(MorphTimerNumber tn, MorphTimerResolution res, MorphTimerRate rate)
{
	if(res <= 8)
	{
		set_rate_8_bit(tn, rate);
	}
	else if(res <= 16)
	{

		set_rate_16_bit(tn, rate);
		//
	}
}

void morph_config_timer_set_timer_callback(MorphTimerNumber tn, MorphTimerResolution res, void (*callback)(void))
{
	if(res <= 8)
	{
		timer_configs_8_bit[tn].callback_a = callback;
		
		// Make sure the interrupt is enabled.
		*(timer_configs_8_bit[tn].interrupt_mask_reg) |= (0x1 << OCIE0A);
		
		// Make sure those dang interrupts are on.
		sei();
	}
	else if(res <= 16)
	{
		timer_configs_16_bit[tn].callback_a = callback;

		*(timer_configs_16_bit[tn].interrupt_mask_reg) |= (0x1 << OCIE1A);

		// Make sure those dang interrupts are on.
		sei();

	}
}

void morph_config_timer_unset_timer_callback(MorphTimerNumber tn, MorphTimerResolution res, void (*callback)(void))
{
	
}

bool morph_config_timer_is_in_use(MorphTimerNumber tn, MorphTimerResolution res)
{
	
}

// ---- TIMER END ----

// ---- PWM BEGIN ----

void set_pwm_raw_8_bit(uint8_t timer_num, uint8_t timer_channel, uint8_t count_val)
{
	uint8_t type_index = 0;
	
	//These are both 8 bit timers.
	if(timer_num == 0)
	{
		type_index = 0;
	}
	else if(timer_num == 2)
	{
		type_index = 1;
	}
	else
	{
		return;
	}
	
	if(timer_channel == 0)
	*(timer_configs_8_bit[type_index].output_compare_a) = count_val;
	else if(timer_channel == 1)
	*(timer_configs_8_bit[type_index].output_compare_b) = count_val;
}

void morph_config_pwm_start_pwm(MorphPinNumber pn)
{
	// First, we've got to figure out if this pin is supported
	if(pn > NUM_PINS)
	return;
	
	MorphTimerPinGroup groups[MAXIMUM_TIMERS_PER_PIN];
	
	uint8_t num_timers = find_timer_config(pn, groups, MAXIMUM_TIMERS_PER_PIN);
	
	if(num_timers <= 0)
	{
		return; // No timers here.
	}
	
	int8_t timer_num     = groups[0].timer_output;
	int8_t timer_channel = groups[0].timer_output_channel;
	
	if(timer_num != -1 && timer_channel != -1)
	{
		// This is the right pin! Yay!
		
		uint8_t resolution = 0;
		bool is_taken = false;
		uint8_t type_index = 0;
		
		if(timer_num == 0 || timer_num == 2)
		{
			//These are both 8 bit timers.
			resolution = 8;
			
			if(timer_num == 0)
			{
				type_index = 0;
			}
			else if(timer_num == 2)
			{
				type_index = 1;
			}

			if(timer_configs_8_bit[type_index].is_in_use_by_morph_pwm)
			{
				// The PWM driver is using this timer. Check if we can hop on.
				if(!timer_configs_8_bit[type_index].a_counter_in_use || !timer_configs_8_bit[type_index].b_counter_in_use)
				{
					// Nice! We can use one of them.
					is_taken = false;
					
				}
				
			}
			else
			{
				is_taken = timer_configs_8_bit[type_index].is_in_use;
			}

			
		}
		else if(timer_num == 1)
		{
			// This is a 16 bit timer.
			resolution = 16;
			
			type_index = 0;

			is_taken = timer_configs_16_bit[type_index].is_in_use;
			
		}
		else
		{
			return; // go away.
		}
		
		if(!is_taken)
		{
			// Go through the proper channel to acquire the timer.
			morph_config_timer_acquire_timer(timer_num, resolution);
			
			if(resolution == 8)
			{
				if(!timer_configs_8_bit[type_index].is_in_use_by_morph_pwm)
				{
					// This timer isn't being used for PWM yet.
					// Set this to true and continue.
					timer_configs_8_bit[type_index].is_in_use_by_morph_pwm = true;
					
					// Time to initialize the timer for PWM use.
					
					// Will be using Phase Correct PWM Mode
					// WGM01:0 = 1

					// Clear WGM02
					*(timer_configs_8_bit[type_index].control_reg_b) &= ~(0x1 << WGM02);

					uint8_t reg_a = *(timer_configs_8_bit[type_index].control_reg_a);

					// clear WGM 01 and set WGM 00
					*(timer_configs_8_bit[type_index].control_reg_a) = (reg_a | (0x1 << WGM00)) & ~(0x1 << WGM01);

					uint8_t reg_b = timer_configs_8_bit[type_index].control_reg_b;
					
					// These two lines makes sure the starting output will be 0V.
					*(timer_configs_8_bit[type_index].output_compare_a) = 0x00;
					*(timer_configs_8_bit[type_index].output_compare_b) = 0x00;
					
					// Start the timer with no prescaling.
					*(timer_configs_8_bit[type_index].control_reg_b) = (reg_b & (0xFF << 3)) | 0b001;
					
				}
				
				if(timer_channel == 0)
				{
					uint8_t reg_a = *(timer_configs_8_bit[type_index].control_reg_a);

					// Verify PWM output is enabled for this channel
					// This sets non-inverting mode on COMnA
					*(timer_configs_8_bit[type_index].control_reg_a) = (reg_a & (0xFF >> (8 - COM0A0))) | 0b10 << COM0A0;
				}
				else if(timer_channel == 1)
				{
					uint8_t reg_a = *(timer_configs_8_bit[type_index].control_reg_a);
					// Verify PWM output is enable for this channel
					// This sets non-inverting mode on COMnB
					*(timer_configs_8_bit[type_index].control_reg_a) = (reg_a & (0xFF >> (8 - COM0B0))) | 0b10 << COM0B0;
				}
				
				morph_config_gpio_set_pin_direction(pn, Output);
				
			}
			else if(resolution == 16)
			{
				timer_configs_16_bit[type_index].is_in_use_by_morph_pwm = true;
			}
			
		}
		
	}
	
}

void morph_config_pwm_stop_pwm(MorphPinNumber pn)
{
	
	

	
}

void morph_config_pwm_set_pwm_duty_float(MorphPinNumber pn, float duty)
{

	MorphTimerPinGroup groups[MAXIMUM_TIMERS_PER_PIN];
	
	uint8_t num_timers = find_timer_config(pn, &groups, MAXIMUM_TIMERS_PER_PIN);
	
	if(num_timers <= 0)
	{
		return; // No timers here.
	}
	
	int8_t timer_num     = groups[0].timer_output;
	int8_t timer_channel = groups[0].timer_output_channel;

	uint8_t type_index = 0;
	
	// This locks the duty between 0.0 and 1.0;
	duty = fmax(fmin(1.0f, duty), 0.0f);
	
	if(timer_num == 0 || timer_num == 2)
	{
		//These are both 8 bit timers.
		set_pwm_raw_8_bit(timer_num, timer_channel, duty * 0xFF);
		
	}
	else if(timer_num == 1)
	{
		// This is a 16 bit timer.
		type_index = 0;
		
	}
}

void morph_config_pwm_set_pwm_duty_64bit(MorphPinNumber pn, uint64_t duty)
{
	
}

void morph_config_pwm_set_pwm_duty_32bit(MorphPinNumber pn, uint32_t duty)
{
	
}

void morph_config_pwm_set_pwm_duty_16bit(MorphPinNumber pn, uint16_t duty)
{
	
}

void morph_config_pwm_set_pwm_duty_8bit (MorphPinNumber pn, uint8_t duty)
{
	
}


// ---- PWM END ----

// ---- ADC BEGIN ----

typedef struct running_adc_config {
	uint8_t adc_prescaler_value;
	uint8_t refs_val;
} RunningConfigADC;

RunningConfigADC adc_configs[8] =
{
	{
		0, 0b11
	},
	{
		0, 0b11
	},
	{
		0, 0b11
	},
	{
		0, 0b11
	},
	{
		0, 0b11
	},
	{
		0, 0b11
	},
	{
		0, 0b11
	},
	{
		0, 0b11
	}
};

int8_t last_read_mux = -1;

MorphADCValue morph_config_adc_get_adc_value(MorphADCChannel c, MorphADCResolution res)
{
	
	
	
}

MorphADCValue morph_config_adc_get_adc_pin(MorphPinNumber c, MorphADCResolution res)
{
}

void morph_config_adc_init_adc(MorphPinNumber p)
{

	// Enable the ADC
	ADCSRA |= 0x1 << ADEN;

}

MorphADCValue morph_config_adc_read(MorphPinNumber p)
{
	
	// First, fetch the mux value
	int8_t adc_mux = pin_defs[p-1].adc_mux_value;
	
	if(adc_mux == -1)
	{
		// Okay, bye!
		return;
	}

	// Set the prescaler value.
	ADCSRA = (ADCSRA & 0xF8) | adc_configs[adc_mux].adc_prescaler_value;
	
	if(last_read_mux != adc_mux)
	{
		// We have to do some setup before we get to read from the ADC.
		
		// First, clear ADEN to safely switch ADMUX (datasheet section 24.5)
		ADCSRA &= ~(0x1 << ADEN);
		
		// Now, we can change the mux and refs.

		// This will build the mux and refs value and put it into the ADMUX.
		ADMUX = adc_configs[adc_mux].refs_val << REFS0 | (uint8_t)adc_mux << MUX0;
		
		// Now, let's start a conversion then throw away the value.
		// (This needs to be done as the first value after switching refs might not be accurate).

		// Re-enable ADC
		ADCSRA |= 0x1 << ADEN;

		// Start ADC conversion
		ADCSRA |= 0x1 << 6;

		// Wait for ADC conversion to complete
		while(ADCSRA >> ADSC & 0x1 == 1);
		
		// The registers have to be read in this order.
		volatile uint8_t low  = ADCL;
		volatile uint8_t high = ADCH;
		
		// Okay, setup complete!
		last_read_mux = adc_mux;
		
	}
	
	// Do a convert!
	// Start ADC conversion
	ADCSRA |= 0x1 << 6;

	// Wait for ADC conversion to complete
	while(ADCSRA >> ADSC & 0x1 == 1);
	
	// The registers have to be read in this order.
	uint8_t low  = ADCL;
	uint8_t high = ADCH;

	// combine the two bytes
	uint64_t raw_adc_value = (high << 8) | low;
	
	return (MorphADCValue)raw_adc_value;
	
}

int8_t morph_config_adc_set_resolution(MorphPinNumber p, MorphADCResolution res)
{
	
	// You can't really set the resolution on the ATmega328.
	// At least, we aren't supporting it.
	return 10;
	
}

void morph_config_adc_set_reference(MorphPinNumber p, enum MorphADCReference ref, uint8_t ref_num)
{
	// First, fetch the mux value
	int8_t adc_mux = pin_defs[p-1].adc_mux_value;
	
	if(adc_mux == -1)
	{
		// Okay, bye!
		return;
	}
	
	if(ref == MorphADCExternalRef)
	{
		if(ref_num == 0)
		{
			adc_configs[adc_mux].refs_val = 0b00;
		}
		else // This takes care of out of range values as well as ref_num == 1.
		{
			adc_configs[adc_mux].refs_val = 0b01;
		}
	}
	else
	{
		// There is only one internal reference on the 328.
		adc_configs[adc_mux].refs_val = 0b11;
	}
	
}

void morph_config_adc_set_prescaler(MorphPinNumber p, uint16_t prescaler)
{
	// Setting the prescaler happens on a global basis.
	// This function will simply store the desired prescaler value and apply it before a conversion.
	
	// First, fetch the mux value
	int8_t adc_mux = pin_defs[p-1].adc_mux_value;
	
	if(adc_mux == -1)
	{
		// Okay, bye!
		return;
	}

	if(prescaler <= 2)
	{
		// Setting prescaler to 2
		adc_configs[adc_mux].adc_prescaler_value = 0b001;
	}
	else if(prescaler <= 4)
	{
		// Setting prescaler to 4
		adc_configs[adc_mux].adc_prescaler_value = 0b010;
	}
	else if(prescaler <= 8)
	{
		// Setting prescaler to 8
		adc_configs[adc_mux].adc_prescaler_value = 0b011;
	}
	else if(prescaler <= 16)
	{
		// Setting prescaler to 16
		adc_configs[adc_mux].adc_prescaler_value = 0b100;
	}
	else if(prescaler <= 32)
	{
		// Setting prescaler to 32
		adc_configs[adc_mux].adc_prescaler_value = 0b101;
	}
	else if(prescaler <= 64)
	{
		// Setting prescaler to 64
		adc_configs[adc_mux].adc_prescaler_value = 0b110;
	}
	else
	{
		// Setting prescaler to 128
		adc_configs[adc_mux].adc_prescaler_value = 0b111;
	}

}

MorphADCValue morph_config_adc_get_maximum_value(MorphPinNumber p)
{
	// Return 10 bits maximum.
	return (MorphADCValue)1023;
}

// ---- ADC END ----

void morph_config_init()
{
}

void morph_implementation_test()
{
}


#endif //ENABLE_ATMEGA324PB_CONFIG