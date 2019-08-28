/*
 * MorphUART.c
 *
 * Created: 11/27/2018 3:49:01 PM
 *  Author: 243400
 */ 

#include "include/MorphUART.h"
#include "include/MorphUtils.h"
#include "include/MorphOptions.h"


#ifndef MORPH_IMPLICIT

void (*morph_setup_channel_function)(MorphUARTChannel, MorphUARTBaudRate, MorphUARTByteSize, enum MorphUARTParity, MorphUARTStopBits) = &MorphUtils_empty_callback;

void (*morph_disable_channel_function)(MorphUARTChannel) = &MorphUtils_empty_callback;

void (*morph_send_data_function)(MorphUARTChannel, MorphUARTData) = &MorphUtils_empty_callback;

MorphUARTData (*morph_read_data_function)(MorphUARTChannel) = &MorphUtils_empty_callback;

void (*morph_send_byte_function)(MorphUARTChannel, MorphUARTByte) = &MorphUtils_empty_callback;

MorphUARTByte (*morph_read_byte_function)(MorphUARTChannel) = &MorphUtils_empty_callback;

void (*morph_write_data_buffer_function)(MorphUARTChannel, MorphUARTData*, size_t) = &MorphUtils_empty_callback;

void (*morph_write_byte_buffer_function)(MorphUARTChannel, MorphUARTByte*, size_t) = &MorphUtils_empty_callback;

enum MorphUARTErrors (*morph_read_data_buffer_function)(MorphUARTChannel, MorphUARTData*, size_t, MorphUARTTimeout) = &MorphUtils_empty_callback;

enum MorphUARTErrors (*morph_read_byte_buffer_function)(MorphUARTChannel, MorphUARTByte*, size_t, MorphUARTTimeout) = &MorphUtils_empty_callback;

bool (*morph_data_ready_function)(MorphUARTChannel);

void (*morph_purge_input_function)(MorphUARTChannel) = &MorphUtils_empty_callback;

void (*morph_set_tx_pin_function)(MorphUARTChannel, MorphPinNumber) = &MorphUtils_empty_callback;

void (*morph_set_rx_pin_function)(MorphUARTChannel, MorphPinNumber) = &MorphUtils_empty_callback;

void (*morph_set_rts_pin_function)(MorphUARTChannel, MorphPinNumber) = &MorphUtils_empty_callback;

void (*morph_set_cts_pin_function)(MorphUARTChannel, MorphPinNumber) = &MorphUtils_empty_callback;

void MorphUART_register_setup_channel_function(void (*function)(MorphUARTChannel, MorphUARTBaudRate, MorphUARTByteSize, enum MorphUARTParity, MorphUARTStopBits))
{
	morph_setup_channel_function = function;
}

void MorphUART_register_disable_channel_function(void (*function)(MorphUARTChannel))
{
	morph_disable_channel_function = function;
}

void MorphUART_register_send_data_function(void (*function)(MorphUARTChannel, MorphUARTData))
{
	morph_send_data_function = function;
}

void MorphUART_register_read_data_function(MorphUARTData (*function)(MorphUARTChannel))
{
	morph_read_data_function = function;
}

void MorphUART_register_send_byte_function(void (*function)(MorphUARTChannel, MorphUARTByte))
{
	morph_send_byte_function = function;
}

void MorphUART_register_read_byte_function(MorphUARTByte (*function)(MorphUARTChannel))
{
	morph_read_byte_function = function;
}

void MorphUART_register_write_data_buffer_function(void (*function)(MorphUARTChannel, MorphUARTData*, size_t))
{
	morph_write_data_buffer_function = function;
}

void MorphUART_register_write_byte_buffer_function(void (*function)(MorphUARTChannel, MorphUARTByte*, size_t))
{
	morph_write_byte_buffer_function = function;
}

void MorphUART_register_read_data_buffer_function(enum MorphUARTErrors (*function)(MorphUARTChannel, MorphUARTData *, size_t, MorphUARTTimeout))
{
	morph_read_data_buffer_function = function;
}

void MorphUART_register_read_byte_buffer_function(enum MorphUARTErrors (*function)(MorphUARTChannel, MorphUARTByte *, size_t, MorphUARTTimeout))
{
	morph_read_byte_buffer_function = function;
}

void MorphUART_register_data_ready_function(bool (* function)(MorphUARTChannel))
{
	morph_data_ready_function = function;
}

void MorphUART_register_purge_input_function(void (*function)(MorphUARTChannel))
{
	morph_purge_input_function = function;
}

void MorphUART_register_set_tx_pin_function(void (*function)(MorphUARTChannel, MorphPinNumber))
{
	morph_set_tx_pin_function = function;
}

void MorphUART_register_set_rx_pin_function(void (*function)(MorphUARTChannel, MorphPinNumber))
{
	morph_set_rx_pin_function = function;
}

void MorphUART_register_set_rts_pin_function(void (*function)(MorphUARTChannel, MorphPinNumber))
{
	morph_set_rts_pin_function = function;
}

void MorphUART_register_set_cts_pin_function(void (*function)(MorphUARTChannel, MorphPinNumber))
{
	morph_set_cts_pin_function = function;
}

#endif

// FUNCTIONS! //

void MorphUART_setup_channel(MorphUARTChannel c, MorphUARTBaudRate br, MorphUARTByteSize bs, enum MorphUARTParity pc, MorphUARTStopBits sb)
{
	#ifdef MORPH_IMPLICIT
		morph_config_uart_setup_channel(c, br, bs, pc, sb);
	#else
		morph_setup_channel_function(c, br, bs, pc, sb);
	#endif
}

// Disables the UART channel and returns it to its normal state (as GPIO pins or whatever default is).
void MorphUART_disable_channel(MorphUARTChannel c)
{
	#ifdef MORPH_IMPLICIT		
		morph_config_uart_disable_channel(c);
	#else
		morph_disable_channel_function(c);
	#endif
}

// Will send the first n bytes of data depending on serial config.
void MorphUART_send_data(MorphUARTChannel c, MorphUARTData data)
{
	#ifdef MORPH_IMPLICIT	
		morph_config_uart_send_data(c, data);
	#else
		morph_send_data_function(c, data);
	#endif		
}

// Receives one frame of data. May be up to 9 bits. Bit manipulation is on the user.
MorphUARTData MorphUART_read_data(MorphUARTChannel c)
{
	#ifdef MORPH_IMPLICIT
		return morph_config_uart_read_data(c);
	#else
		return morph_read_data_function(c);
	#endif
}

// Will send the first n bytes of data depending on serial config.
// Does not support 9 bit frames.
void MorphUART_send_byte(MorphUARTChannel c, MorphUARTByte byte)
{
	#ifdef MORPH_IMPLICIT
		morph_config_uart_send_byte(c, byte);
	#else
		morph_send_byte_function(c, byte);
	#endif
}

// Receives one frame of data.
// Only receives up to 8 bits.
MorphUARTByte MorphUART_read_byte(MorphUARTChannel c)
{
	#ifdef MORPH_IMPLICIT
		return morph_config_uart_read_byte(c);
	#else
		return morph_read_byte_function(c);
	#endif
}

// Writes a buffer to the UART channel. Will only use frames the size of the byte size configuration.
void MorphUART_write_data_buffer(MorphUARTChannel c, MorphUARTData * buffer, size_t length)
{
	#ifdef MORPH_IMPLICIT
		morph_config_uart_write_data_buffer(c, buffer, length);
	#else
		morph_write_data_buffer_function(c, buffer, length);
	#endif
}

// Writes a buffer to the UART channel. Will limit frame size to 8 bits.
void MorphUART_write_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer, size_t length)
{
	#ifdef MORPH_IMPLICIT	
		morph_config_uart_write_byte_buffer(c, buffer, length);
	#else
		morph_write_byte_buffer_function(c, buffer, length);
	#endif
}

enum MorphUARTErrors MorphUART_read_data_buffer(MorphUARTChannel c, MorphUARTData * buffer, size_t length, MorphUARTTimeout timeout)
{
	#ifdef MORPH_IMPLICIT	
		return morph_config_uart_read_data_buffer(c, buffer, length, timeout);
	#else
		return morph_read_data_buffer_function(c, buffer, length, timeout);
	#endif
}

enum MorphUARTErrors MorphUART_read_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer, size_t length, MorphUARTTimeout timeout)
{
	#ifdef MORPH_IMPLICIT	
		return morph_config_uart_read_byte_buffer(c, buffer, length, timeout);
	#else
		return morph_read_byte_buffer_function(c, buffer, length, timeout);
	#endif
}

bool MorphUART_data_ready(MorphUARTChannel c)
{
	#ifdef MORPH_IMPLICIT
		return morph_config_uart_data_ready(c);
	#else
		return morph_data_ready_function(c);
	#endif	
}

// Purges the input buffer
void MorphUART_purge_input(MorphUARTChannel c)
{
	#ifdef MORPH_IMPLICIT
		morph_config_uart_purge_input(c);
	#else
		morph_purge_input_function(c);
	#endif		
}

void MorphUART_set_tx_pin(MorphUARTChannel c, MorphPinNumber p_tx)
{
	#ifdef MORPH_IMPLICIT
		morph_config_uart_set_tx_pin(c, p_tx);
	#else
		morph_set_tx_pin_function(c, p_tx);
	#endif
}

void MorphUART_set_rx_pin(MorphUARTChannel c, MorphPinNumber p_rx)
{
	#ifdef MORPH_IMPLICIT
	morph_config_uart_set_rx_pin(c, p_rx);
	#else
	morph_set_rx_pin_function(c, p_rx);
	#endif
}

void MorphUART_set_rts_pin(MorphUARTChannel c, MorphPinNumber p_rts)
{
	#ifdef MORPH_IMPLICIT
	morph_config_uart_set_rts_pin(c, p_rts);
	#else
	morph_set_rts_pin_function(c, p_rts);
	#endif
}

void MorphUART_set_cts_pin(MorphUARTChannel c, MorphPinNumber p_cts)
{
	#ifdef MORPH_IMPLICIT
	morph_config_uart_set_cts_pin(c, p_cts);
	#else
	morph_set_cts_pin_function(c, p_cts);
	#endif
}
