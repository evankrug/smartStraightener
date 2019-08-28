
#include "include/Element7Seg.h"

// Note, these bytes do not include the period bit. 
// For some operations, a left shift by 1 might be required. 
uint8_t seven_seg_char_ascii_map[127] = {
    0x00,        //NUL
    0x00,        //SOH
    0x00,        //STX
    0x00,        //ETX
    0x00,        //EOT
    0x00,        //ENQ
    0x00,        //ACK
    0x00,        //BEL
    0x00,        //BS
    0x00,        //TAB
    0x00,        //LF
    0x00,        //VT
    0x00,        //FF
    0x00,        //CR
    0x00,        //SO
    0x00,        //SI
    0x00,        //DLE
    0x00,        //DC1
    0x00,        //DC2
    0x00,        //DC3
    0x00,        //DC4
    0x00,        //NAK
    0x00,        //SYN
    0x00,        //ETB
    0x00,        //CAN
    0x00,        //EM
    0x00,        //SUB
    0x00,        //ESC
    0x00,        //FS
    0x00,        //GS
    0x00,        //RS
    0x00,        //US
    0x00,        //(space)
    0x00,        //!
    0x00,        //"
    0x00,        //#
    0x00,        //$
    0x00,        //%
    0x00,        //&
    0x00,        //'
    0x4E,        //(
    0x78,        //)
    0x00,        //*
    0x00,        //+
    0x00,        //,
    0x01,        //-
    0x00,        //.
    0x00,        ///
    0x7E,        //0
    0x30,        //1
    0x6D,        //2
    0x79,        //3
    0x33,        //4
    0x5B,        //5
    0x5F,        //6
    0x70,        //7
    0x7F,        //8
    0x7B,        //9
    0x00,        //:
    0x00,        //;
    0x00,        //<
    0x00,        //=
    0x00,        //>
    0x00,        //?
    0x00,        //@
    0x77,        //A
    0x7F,        //B
    0x4E,        //C
    0x7E,        //D
    0x4F,        //E
    0x47,        //F
    0x5E,        //G
    0x37,        //H
    0x30,        //I
    0x3C,        //J
    0x37,        //K
    0x0E,        //L
    0x55,        //M
    0x15,        //N
    0x7E,        //O
    0x67,        //P
    0x73,        //Q
    0x77,        //R
    0x5B,        //S
    0x46,        //T
    0x3E,        //U
    0x27,        //V
    0x37,        //W
    0x25,        //X
    0x3B,        //Y
    0x6D,        //Z
    0x01,        //[
    0x02,        // (SLASH)
    0x03,        //]
    0x04,        //^
    0x05,        //_
    0x06,        //`
    0x7D,        //a
    0x1F,        //b
    0x0D,        //c
    0x3D,        //d
    0x6f,        //e
    0x47,        //f
    0x7B,        //g
    0x17,        //h
    0x10,        //i
    0x38,        //j
    0x17,        //k
    0x06,        //l
    0x55,        //m
    0x15,        //n
    0x1D,        //o
    0x67,        //p
    0x73,        //q
    0x05,        //r
    0x5B,        //s
    0x0F,        //t
    0x1C,        //u
    0x23,        //v
    0x2B,        //w
    0x25,        //x
    0x33,        //y
    0x6D,        //z
    0x00,        //{
    0x00,        //|
    0x00,        //}
    0x00        //~
};

void Element7Seg_set_bit(ElementAnimationBufferConfigStruct * buffer, uint16_t digit, uint8_t bit)
{
	uint8_t value = buffer->write_buffer[digit];
	
	value = (value & ~(0x1 << bit)) | 0x1 << bit;
	
	buffer->write_buffer[digit] = value;
	
}

void Element7Seg_clear_bit(ElementAnimationBufferConfigStruct * buffer, uint16_t digit, uint8_t bit)
{
	
}

// This function takes a character and applies it to the specified digit.
void Element7Seg_write_character(ElementAnimationBufferConfigStruct * buffer, uint16_t digit, uint8_t character)
{

	// Enforce size requirements.
	if(buffer->data_dimensions[1] > digit && character < 127)
	{
		// The Y-axis is the number of digits. We are in range.
		buffer->write_buffer[digit] |= seven_seg_char_ascii_map[character] << 1;			
	}
	
}

// This function takes a string of characters and an offset. The string will be written into the buffer at the specified offset.
// The offset is in characters. A positive offset will push the characters off the left of the screen.
void Element7Seg_write_string(ElementAnimationBufferConfigStruct * buffer, uint8_t * string, uint8_t string_length, int8_t offset)
{

	for(int8_t j = 0; j < buffer->data_dimensions[1]; j++)
	{
		buffer->write_buffer[j] |= 0;
	}
	
	for(int8_t i = offset, j = 0; i < string_length && j < buffer->data_dimensions[1]; i++, j++)
	{
		buffer->write_buffer[j] |= seven_seg_char_ascii_map[string[i]] << 1;
	}
}

uint8_t Element7Seg_get_a_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit)
{
	return Element7Seg_get_bit(buffer, digit, 7);	
}
uint8_t Element7Seg_get_b_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit)
{
	return Element7Seg_get_bit(buffer, digit, 6);	
}
uint8_t Element7Seg_get_c_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit)
{
	return Element7Seg_get_bit(buffer, digit, 5);	
}
uint8_t Element7Seg_get_d_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit)
{
	return Element7Seg_get_bit(buffer, digit, 4);	
}
uint8_t Element7Seg_get_e_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit)
{
	return Element7Seg_get_bit(buffer, digit, 3);	
}
uint8_t Element7Seg_get_f_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit)
{
	return Element7Seg_get_bit(buffer, digit, 2);	
}
uint8_t Element7Seg_get_g_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit)
{
	return Element7Seg_get_bit(buffer, digit, 1);	
}
uint8_t Element7Seg_get_period_value(ElementAnimationBufferConfigStruct * buffer, uint16_t digit)
{
	return Element7Seg_get_bit(buffer, digit, 0);
}

uint8_t Element7Seg_get_bit(ElementAnimationBufferConfigStruct * buffer, uint16_t digit, uint8_t bit)
{
	uint8_t value = 0;
	if(bit <= 7 && digit < buffer->data_dimensions[1])
	{
		value = (buffer->read_buffer[digit] >> (7 - bit)) & 0x1;
	}	

	return value; 
	
}

// This function gets a full byte with the bit order a, b, c, d, e, f, g, period.
uint8_t Element7Seg_get_byte(ElementAnimationBufferConfigStruct * buffer, uint16_t digit)
{
	uint8_t value = 0;
	if(digit < buffer->data_dimensions[1])
	{
		value = buffer->read_buffer[digit];
	}

	return value;
}


uint8_t Element7Seg_char_to_7seg(uint8_t value)
{
	
	return seven_seg_char_ascii_map[value];
	
}