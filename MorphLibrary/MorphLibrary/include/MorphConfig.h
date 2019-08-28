/*
 * MorphConfig.h
 *
 * Created: 11/16/2018 4:15:53 PM
 *  Author: 243400
 */ 


#ifndef MORPHCONFIG_H_
#define MORPHCONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>

#include "MorphTypes.h"
#include "MorphGPIO.h"
#include "MorphTime.h"
#include "MorphTimer.h"
#include "MorphUART.h"
#include "MorphADC.h"



// These are functions that depend on a configuration C file to implement them.


// Comment out this macro to disable functionality.
// The functions will still be callable, they just won't do anything.
// This also allows for configuration files to be partially implemented.


void morph_config_gpio_set_pin_value(MorphPinNumber pn, enum MorphPinValue pv);

enum MorphPinValue morph_config_gpio_get_pin_value(MorphPinNumber pn);

void morph_config_gpio_set_pin_direction(MorphPinNumber pn, enum MorphPinDirection pd);

enum MorphPinDirection morph_config_gpio_get_pin_direction(MorphPinNumber pn);

void morph_config_gpio_set_pin_pull_state(MorphPinNumber pn, enum MorphPinPullState ps);

enum MorphPinPullState morph_config_gpio_get_pin_pull_state(MorphPinNumber pn);

void morph_config_gpio_set_pin_interrupt(void (*function)(void), MorphPinNumber pn, enum MorphExternalInterruptType pv);

void morph_config_gpio_unset_pin_interrupt(MorphPinNumber pn, enum MorphPinValue pv);

// ---- UART BEGIN ----

void morph_config_uart_setup_channel(MorphUARTChannel c, MorphUARTBaudRate br, MorphUARTByteSize bs, enum MorphUARTParity pc, MorphUARTStopBits sb);

// Disables the UART channel and returns it to its normal state (as GPIO pins or whatever default is).
void morph_config_uart_disable_channel(MorphUARTChannel c);

// Will send the first n bytes of data depending on serial config.
void morph_config_uart_send_data(MorphUARTChannel c, MorphUARTData data);

// Receives one frame of data. May be up to 9 bits. Bit manipulation is on the user.
MorphUARTData morph_config_uart_read_data(MorphUARTChannel c);

// Will send the first n bytes of data depending on serial config.
// Does not support 9 bit frames.
void morph_config_uart_send_byte(MorphUARTChannel c, MorphUARTByte byte);

// Receives one frame of data.
// Only receives up to 8 bits.
MorphUARTByte morph_config_uart_read_byte(MorphUARTChannel c);

// Writes a buffer to the UART channel. Will only use frames the size of the byte size configuration.
void morph_config_uart_write_data_buffer(MorphUARTChannel c, MorphUARTData * buffer, size_t length);

// Writes a buffer to the UART channel. Will limit frame size to 8 bits.
void morph_config_uart_write_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer, size_t length);

enum MorphUARTErrors morph_config_uart_read_data_buffer(MorphUARTChannel c, MorphUARTData * buffer, size_t length, MorphUARTTimeout timeout);

enum MorphUARTErrors morph_config_uart_read_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer, size_t length, MorphUARTTimeout timeout);

bool morph_config_uart_data_ready(MorphUARTChannel c);

// Purges the input buffer
void morph_config_uart_purge_input(MorphUARTChannel c);

void morph_config_uart_set_tx_pin(MorphUARTChannel c, MorphPinNumber p_tx);

void morph_config_uart_set_rx_pin(MorphUARTChannel c, MorphPinNumber p_rx);

void morph_config_uart_set_rts_pin(MorphUARTChannel c, MorphPinNumber p_rts);

void morph_config_uart_set_cts_pin(MorphUARTChannel c, MorphPinNumber p_cts);

// ---- UART END ----

// --- I2C BEGIN ---

// Initializes the I2C channel as a master.
void morph_config_i2c_init_master(MorphI2CChannel c, MorphI2CBaudRate br);

// Initializes the I2C channel as a slave.
void morph_config_i2c_init_slave(MorphI2CChannel c);

// This function is used for starting a transmission from the master.
void morph_config_i2c_start_transmission(MorphI2CChannel c, MorphI2CAddress a, enum MorphI2CReadWrite rw);

// This function commits the entire buffer into the bus and general cleanup. This might not be necessary.
void morph_config_i2c_end_transmission(MorphI2CChannel c);

MorphI2CByte morph_config_i2c_read(MorphI2CChannel c);

void morph_config_i2c_write(MorphI2CChannel c, MorphI2CByte b);

void morph_config_i2c_set_scl_pin(MorphI2CChannel c, MorphPinNumber pn);

void morph_config_i2c_set_sda_pin(MorphI2CChannel c, MorphPinNumber pn);

// --- I2C END ---

// --- SPI BEGIN ---

void morph_config_spi_init_master(MorphI2CChannel c, MorphSPIBaudRate br, enum MorphSPIClockPhase cpha, enum MorphSPIClockPolarity cpol);

void morph_config_spi_init_slave(MorphI2CChannel c, enum MorphSPIClockPhase cpha, enum MorphSPIClockPolarity cpol);

MorphSPIByte morph_config_spi_read(MorphI2CChannel c);

void morph_config_spi_write(MorphSPIChannel c, MorphSPIByte b);

void morph_config_spi_set_data_out_pin(MorphSPIChannel c, MorphPinNumber pn);

void morph_config_spi_set_data_in_pin(MorphSPIChannel c, MorphPinNumber pn);

void morph_config_spi_set_sck_pin(MorphSPIChannel c, MorphPinNumber pn);

// --- SPI END ---

// ---- TIME BEGIN ----

void morph_config_time_init(MorphTimerNumber tn, MorphTimerResolution res);

void morph_config_time_init_rtc();

MorphTimeValue morph_config_time_millis();

// ---- TIME END ----

// ---- TIMER BEGIN ----

void morph_config_timer_acquire_timer(MorphTimerNumber tn, MorphTimerResolution res);

void morph_config_timer_release_timer(MorphTimerNumber tn, MorphTimerResolution res);

void morph_config_timer_set_rate(MorphTimerNumber tn, MorphTimerResolution res, MorphTimerRate rate);

void morph_config_timer_set_timer_callback(MorphTimerNumber tn, MorphTimerResolution res, void (*callback)(void));

void morph_config_timer_unset_timer_callback(MorphTimerNumber tn, MorphTimerResolution res, void (*callback)(void));

bool morph_config_timer_is_in_use(MorphTimerNumber tn, MorphTimerResolution res);

// ---- TIMER END ----

// ---- PWM BEGIN ----

void morph_config_pwm_start_pwm(MorphPinNumber pn);

void morph_config_pwm_stop_pwm(MorphPinNumber pn);

void morph_config_pwm_set_pwm_duty_float(MorphPinNumber pn, float duty);

void morph_config_pwm_set_pwm_duty_64bit(MorphPinNumber pn, uint64_t duty);

void morph_config_pwm_set_pwm_duty_32bit(MorphPinNumber pn, uint32_t duty);

void morph_config_pwm_set_pwm_duty_16bit(MorphPinNumber pn, uint16_t duty);

void morph_config_pwm_set_pwm_duty_8bit (MorphPinNumber pn, uint8_t duty);


// ---- PWM END ----

// ---- ADC BEGIN ----

MorphADCValue morph_config_adc_get_adc_value(MorphADCChannel c, MorphADCResolution res);

MorphADCValue morph_config_adc_get_adc_pin(MorphPinNumber c, MorphADCResolution res);

void morph_config_adc_init_adc(MorphPinNumber p);

MorphADCValue morph_config_adc_read(MorphPinNumber p);

int8_t morph_config_adc_set_resolution(MorphPinNumber p, MorphADCResolution res);

void morph_config_adc_set_reference(MorphPinNumber p, enum MorphADCReference ref, uint8_t ref_num);

void morph_config_adc_set_prescaler(MorphPinNumber p, uint16_t prescaler);

MorphADCValue morph_config_adc_get_maximum_value(MorphPinNumber p);

// ---- ADC END ----

void morph_config_init();

void morph_implementation_test();

// Does the configuration during run-time
// Configuration only involves setting function pointer values.
static void MorphConfig_init()
{

	morph_config_init();

#ifndef MORPH_IMPLICIT

	// GPIO Config

	MorphGPIO_register_set_pin_value_function(&morph_config_gpio_set_pin_value);

	MorphGPIO_register_get_pin_value_function(&morph_config_gpio_get_pin_value);
	
	MorphGPIO_register_set_pin_direction_function(&morph_config_gpio_set_pin_direction);
	
	MorphGPIO_register_get_pin_direction_function(&morph_config_gpio_get_pin_direction);

	MorphGPIO_register_set_pin_pull_state_function(&morph_config_gpio_set_pin_pull_state);
	
	MorphGPIO_register_get_pin_pull_state_function(&morph_config_gpio_get_pin_pull_state);	
	
	// UART Config
	
	MorphUART_register_setup_channel_function(&morph_config_uart_setup_channel);
	
	//MorphUART_register_disable_channel_function
	
	MorphUART_register_send_data_function(&morph_config_uart_send_data);

	MorphUART_register_read_data_function(&morph_config_uart_read_data);

	MorphUART_register_send_byte_function(&morph_config_uart_send_byte);
	
	MorphUART_register_read_byte_function(&morph_config_uart_read_byte);

	MorphUART_register_read_byte_buffer_function(&morph_config_uart_read_byte_buffer);
	
	MorphUART_register_write_byte_buffer_function(&morph_config_uart_write_byte_buffer);
	
	MorphUART_register_write_data_buffer_function(&morph_config_uart_write_data_buffer);
	
	MorphUART_register_read_data_buffer_function(&morph_config_uart_read_data_buffer);
	
	MorphUART_register_data_ready_function(&morph_config_uart_data_ready);
	
	MorphUART_register_set_tx_pin_function(&morph_config_uart_set_tx_pin);

	MorphUART_register_set_rx_pin_function(&morph_config_uart_set_rx_pin);

	// I2C Config
	
	//MorphI2C_register_init_master(&morph_config_i2c_init_master);
	//MorphI2C_register_init_slave(&morph_config_i2c_init_slave);
	//MorphI2C_register_start_transmission(&morph_config_i2c_start_transmission);
	//MorphI2C_register_end_transmission(&morph_config_i2c_end_transmission);
	//MorphI2C_register_read(&morph_config_i2c_read);
	//MorphI2C_register_write(&morph_config_i2c_write);
	//MorphI2C_register_set_scl_pin(&morph_config_i2c_set_scl_pin);
	//MorphI2C_register_set_sda_pin(&morph_config_i2c_set_sda_pin);

	// Time functions
	MorphTime_register_init_function(&morph_config_time_init);
	
	MorphTime_register_init_rtc_function(&morph_config_time_init_rtc);
	
	MorphTime_register_millis_function(&morph_config_time_millis);
	
	// Timer functions
	
	//MorphTimer_register_acquire_timer_function(&morph_config_timer_acquire_timer);
//
	//MorphTimer_register_set_rate_function(&morph_config_timer_set_rate);
//
	//MorphTimer_register_release_timer_function(&morph_config_timer_release_timer);
	//
	//MorphTimer_register_set_timer_callback_function(&morph_config_timer_set_timer_callback);
		
	// PWM functions

	//MorphPWM_register_start_pwm(&morph_config_pwm_start_pwm);
//
	//MorphPWM_register_stop_pwm(&morph_config_pwm_stop_pwm);
//
	//MorphPWM_register_set_pwm_duty_float(&morph_config_pwm_set_pwm_duty_float);
//
	//MorphPWM_register_set_pwm_duty_64bit(&morph_config_pwm_set_pwm_duty_64bit);
//
	//MorphPWM_register_set_pwm_duty_32bit(&morph_config_pwm_set_pwm_duty_32bit);
//
	//MorphPWM_register_set_pwm_duty_16bit(&morph_config_pwm_set_pwm_duty_16bit);
//
	//MorphPWM_register_set_pwm_duty_8bit(&morph_config_pwm_set_pwm_duty_8bit);

	// ADC functions
	MorphADC_register_get_adc_value_function(&morph_config_adc_get_adc_value);
	MorphADC_register_get_adc_pin_function(&morph_config_adc_get_adc_pin);
	MorphADC_register_init_adc_function(&morph_config_adc_init_adc);
	MorphADC_register_read_function(&morph_config_adc_read);
	MorphADC_register_set_resolution_function(&morph_config_adc_set_resolution);
	MorphADC_register_set_reference_function(&morph_config_adc_set_reference);
	MorphADC_register_set_prescaler_function(&morph_config_adc_set_prescaler);
	
	MorphADC_register_get_maximum_value(&morph_config_adc_get_maximum_value);

	MorphSPI_register_init_master(&morph_config_spi_init_master);
	MorphSPI_register_init_slave(&morph_config_spi_init_slave);
	MorphSPI_register_read(&morph_config_spi_read);
	MorphSPI_register_write(&morph_config_spi_write);
	MorphSPI_register_set_data_out_pin(&morph_config_spi_set_data_out_pin);
	MorphSPI_register_set_data_in_pin(&morph_config_spi_set_data_in_pin);
	MorphSPI_register_set_sck_pin(&morph_config_spi_set_sck_pin);

#endif

}

#ifdef __cplusplus
}
#endif

#endif /* MORPHCONFIG_H_ */