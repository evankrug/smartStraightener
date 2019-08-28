/*
 * MorphUART.h
 *
 * Created: 11/27/2018 3:49:57 PM
 *  Author: 243400
 */ 


#ifndef MORPHUART_H_
#define MORPHUART_H_

#include <stddef.h>
#include <stdbool.h>

#include "MorphTypes.h"	
#include "MorphUtils.h"
#include "MorphOptions.h"



#ifndef MORPH_IMPLICIT

// MORPH_IMPLICIT means the functions will not be implemented with function pointers.
// Instead, it will call the (possibly) implemented functions directly.
// This is more dangerous, however it might see performance gains through compiler optimization.

void MorphUART_register_setup_channel_function(void (*)(MorphUARTChannel, MorphUARTBaudRate, MorphUARTByteSize, enum MorphUARTParity, MorphUARTStopBits));

void MorphUART_register_disable_channel_function(void (*)(MorphUARTChannel));

void MorphUART_register_send_data_function(void (*)(MorphUARTChannel, MorphUARTData));

void MorphUART_register_read_data_function(MorphUARTData (*)(MorphUARTChannel));

void MorphUART_register_send_byte_function(void (*)(MorphUARTChannel, MorphUARTByte));

void MorphUART_register_read_byte_function(MorphUARTByte (*)(MorphUARTChannel));

void MorphUART_register_write_data_buffer_function(void (*)(MorphUARTChannel, MorphUARTData*, size_t));

void MorphUART_register_write_byte_buffer_function(void (*)(MorphUARTChannel, MorphUARTByte*, size_t));

void MorphUART_register_read_data_buffer_function(enum MorphUARTErrors (*)(MorphUARTChannel, MorphUARTData *, size_t, MorphUARTTimeout));

void MorphUART_register_read_byte_buffer_function(enum MorphUARTErrors (*)(MorphUARTChannel, MorphUARTByte *, size_t, MorphUARTTimeout));

void MorphUART_register_data_ready_function(bool (*)(MorphUARTChannel));

void MorphUART_register_purge_input_function(void (*)(MorphUARTChannel));

void MorphUART_register_set_tx_pin_function(void (*)(MorphUARTChannel, MorphPinNumber));

void MorphUART_register_set_rx_pin_function(void (*)(MorphUARTChannel, MorphPinNumber));

void MorphUART_register_set_rts_pin_function(void (*)(MorphUARTChannel, MorphPinNumber));

void MorphUART_register_set_cts_pin_function(void (*)(MorphUARTChannel, MorphPinNumber));

#endif

// FUNCTIONS! //

void MorphUART_setup_channel(MorphUARTChannel c, MorphUARTBaudRate br, MorphUARTByteSize bs, enum MorphUARTParity pc, MorphUARTStopBits sb);

// Disables the UART channel and returns it to its normal state (as GPIO pins or whatever default is).
void MorphUART_disable_channel(MorphUARTChannel c);

// Will send the first n bytes of data depending on serial config.
void MorphUART_send_data(MorphUARTChannel c, MorphUARTData data);

// Receives one frame of data. May be up to 9 bits. Bit manipulation is on the user.
MorphUARTData MorphUART_read_data(MorphUARTChannel c);

// Will send the first n bytes of data depending on serial config. 
// Does not support 9 bit frames. 
void MorphUART_send_byte(MorphUARTChannel c, MorphUARTByte byte);

// Receives one frame of data. 
// Only receives up to 8 bits. 
MorphUARTByte MorphUART_read_byte(MorphUARTChannel c);

// Writes a buffer to the UART channel. Will only use frames the size of the byte size configuration.
void MorphUART_write_data_buffer(MorphUARTChannel c, MorphUARTData * buffer, size_t length);

// Writes a buffer to the UART channel. Will limit frame size to 8 bits.
void MorphUART_write_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer, size_t length);

enum MorphUARTErrors MorphUART_read_data_buffer(MorphUARTChannel c, MorphUARTData * buffer, size_t length, MorphUARTTimeout timeout);

enum MorphUARTErrors MorphUART_read_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer, size_t length, MorphUARTTimeout timeout);

bool MorphUART_data_ready(MorphUARTChannel c);

// Purges the input buffer
void MorphUART_purge_input(MorphUARTChannel c);

void MorphUART_set_tx_pin(MorphUARTChannel c, MorphPinNumber p_tx);

void MorphUART_set_rx_pin(MorphUARTChannel c, MorphPinNumber p_rx);

void MorphUART_set_rts_pin(MorphUARTChannel c, MorphPinNumber p_rts);

void MorphUART_set_cts_pin(MorphUARTChannel c, MorphPinNumber p_cts);




#endif /* MORPHUART_H_ */