/*
 * app.h
 * Everything related to this app.
 * Created: 12/5/2018 5:22:32 PM
 *  Author: 243400
 */ 


#ifndef APP_H_
#define APP_H_

#include <ElementConfig.h>
#include <ElementAnimationEngine.h>
#include <Element7Seg.h>


// This is frame data for animations. 
// To comply with the (possibly  over-complex) animation engine,
// this data should probably be computer generated.
// Generating this data by hand is probably a bad idea.
uint8_t blink_animation_frames[4][1][1] = {
	{{0b10101010}},
	{{0b01010101}}
};

static ElementCalculatedAnimationInstance blink_calc = {
	
	0, // Animation ID.
	0x1, // The alpha is the first bit.
	1, // 1 FPS framerate
	blink_animation_frames, // This is frame data. Probably auto-generated. 
	2, // There are 2 frames.
	1, // Every frame is made of 1 byte.
	{	// This is the dimensions data.
		// 4 X 1 space.
		1, 1
	},
	1, // The bit-depth is 1. It's an LED, only need on/off data.
	false, //is the animation currently running? No!
	0, // The start time is undefined. Just make it 0.
	0, // The current frame is also undefined. 0.
	true // This animation should repeat.
};

static ElementAnimationInstance blink = {
	true,
	&blink_calc,
	NULL
};

// Here, we will define a buffer to accept the blink animation

// First, allocate some space for the buffers.
uint8_t led_buffer_arrays[2][1][1] = {0x0};

static ElementAnimationBufferConfigStruct led_buffer = {	
	{0x0},				// Buffer ID is 0.
	&led_buffer_arrays,	// The pointer to the buffer space.
	NULL,				// This is the write buffer. 
						// Will be initialized when passed to animation engine.
	NULL,				// This is the read buffer.
						// Will be initialized when passed to animation engine.
	2,					// We have 2 buffers.
	1,					// The bit depth of this buffer is 1.
	1,					// Every buffer is made of 1 byte.
	{	// This buffer is for a 4 x 1 display. 
		1, 1
	},
	{
		NULL
	},
	0					// We have 0 animations running on this buffer currently.
};

uint8_t seg_buffer_arrays[2][4][1] = {0x0};

static ElementAnimationBufferConfigStruct seven_seg_buffer = {
	0x1,				// Buffer ID is 1.
	seg_buffer_arrays,	// The pointer to the buffer space.
	NULL,				// This is the write buffer.
	// Will be initialized when passed to animation engine.
	NULL,				// This is the read buffer.
	// Will be initialized when passed to animation engine.
	2,					// We have 2 buffers.
	1,					// The bit depth of this buffer is 1.
	4,					// Every buffer is made of 4 bytes.
	{	// This buffer is for a 8 x 4 display.
		8, 4
	},
	{
		NULL
	},
	0					// We have 0 animations running on this buffer currently.
};

enum ElementAnimationEngineStatus print_time_7_seg(ElementAnimationBufferConfigStruct * buffer)
{
	
	uint8_t hour = ElementClock_get_24_hour();
	
	uint8_t hour_one = hour / 10 + '0';
	uint8_t hour_two = hour % 10 + '0';

	uint8_t minute = ElementClock_get_minute();
	
	uint8_t minute_one = minute / 10 + '0';
	uint8_t minute_two = minute % 10 + '0';

	Element7Seg_write_character(buffer, 0, hour_one);
	Element7Seg_write_character(buffer, 1, hour_two);
	
	Element7Seg_write_character(buffer, 2, minute_one);
	Element7Seg_write_character(buffer, 3, minute_two);	

	return Animation_Engine_Success;
	
}

static ElementFunctionalAnimationInstance print_7_seg_time_anim_func = 
{
	&print_time_7_seg
};

static ElementAnimationInstance print_7_seg_time_anim = 
{
	false,
	NULL,
	&print_7_seg_time_anim_func
};

enum ElementAnimationEngineStatus print_name(ElementAnimationBufferConfigStruct * buffer)
{
	
	int8_t string_len = 11;
	
	Element7Seg_write_string(buffer, "Hello there", string_len, ((MorphTime_millis() / 500) % (string_len + 3)) - 3);

	return Animation_Engine_Success;
	
}

static ElementFunctionalAnimationInstance print_name_anim_func =
{
	&print_name
};

static ElementAnimationInstance print_name_anim =
{
	false,
	NULL,
	&print_name_anim_func
};





#endif /* APP_H_ */