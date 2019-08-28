
#ifndef ELEMENT7SEG_H_
#define ELEMENT7SEG_H_

#include "ElementConfig.h"



// This header assumes the layout of buffers fed to it.
// First, the buffer only has a width of 1 byte 
// and a height of n bytes where n is the number of displays.
// It also assumes a bit order of a, b, c, d, e, f, g, period.
// This makes the bits accessible by drivers passing through this file.
// For custom 7 segment displays, there is a set_digit function.
// This allows users to set specific bits for anything out of 
// spec. Such as colons, and other indicators. 

void Element7Seg_set_bit(ElementAnimationBufferConfigStruct * buffer, uint16_t digit, uint8_t bit);

void Element7Seg_clear_bit(ElementAnimationBufferConfigStruct * buffer, uint16_t digit, uint8_t bit);

// This function takes a character and applies it to the specified digit.
void Element7Seg_write_character(ElementAnimationBufferConfigStruct * buffer, uint16_t digit, uint8_t character);

// This function takes a string of characters and an offset. The string will be written into the buffer at the specified offset.
// The offset is in characters. A positive offset will push the characters off the left of the screen.
void Element7Seg_write_string(ElementAnimationBufferConfigStruct * buffer, uint8_t * string, uint8_t string_length, int8_t offset);

uint8_t Element7Seg_get_a_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit);
uint8_t Element7Seg_get_b_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit);
uint8_t Element7Seg_get_c_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit);
uint8_t Element7Seg_get_d_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit);
uint8_t Element7Seg_get_e_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit);
uint8_t Element7Seg_get_f_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit);
uint8_t Element7Seg_get_g_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit);
uint8_t Element7Seg_get_period_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit);

uint8_t Element7Seg_get_bit(ElementAnimationBufferConfigStruct * buffer, uint16_t digit, uint8_t bit);

// This function gets a full byte with the bit order a, b, c, d, e, f, g, period.
uint8_t Element7Seg_get_byte(ElementAnimationBufferConfigStruct * buffer, uint16_t digit);

uint8_t Element7Seg_char_to_7seg(uint8_t value);

#endif