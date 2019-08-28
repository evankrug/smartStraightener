#include <MorphTypes.h>
#include <stddef.h>

#include "include/ElementAnimationEngine.h"

int32_t ElementAnimationEngine_get_current_frame(ElementCalculatedAnimationInstance * animation)
{
	ElementCalculatedAnimationInstance * anim_inst = animation;
		
	MorphTimeValue cur_time = MorphTime_millis();
		
	MorphTimeValue start_time = anim_inst->start_time;
		
	MorphTimeValue elapsed_time = cur_time - start_time;
		
	int32_t current_frame = 0;
		
	// Is the animation paused? If it is, we don't have to calculate the current frame!

	if(anim_inst->is_running)
	{
			
		// It's not paused. Calculate the frame!
			
		// How many milliseconds does the current animation take?
		MorphTimeValue animation_duration_ms = ((float)anim_inst->num_frames / (float)anim_inst->framerate) * 1000;

		MorphTimeValue frame_duration_ms = 1000 / anim_inst->framerate;

		// Is this animation supposed to loop?
		if(!anim_inst->is_repeating && animation_duration_ms < elapsed_time)
		{
			// It's not and we have gone passed the end.
			// Say the current frame is the end.
				
		}
		else
		{
			// Either the animation is supposed to loop, or the animation hasn't reached the end yet.
				
			// Find the current millisecond in the animation, then translate that to a frame.
			current_frame = ((elapsed_time % animation_duration_ms) - anim_inst->offset_time) / frame_duration_ms;
				
		}

	}
	else
	{

		// The animation is paused, simply take the current frame.
		current_frame = anim_inst->current_frame;
			
	}
	
	return current_frame;
	
}

uint8_t isolate_bits(uint8_t val, int8_t start_bit, int8_t length, uint8_t *result)
{
	// Just act like this works.	
	uint8_t mask_size = 0;

	if(start_bit + 1 >= length)
	{
		// This is a fine size. We can be full length!
		mask_size = length;
	}
	else
	{
		// This is small. Can't be full length.
		mask_size = (start_bit + 1);
	}

	// How far over do we have to shift?
	int8_t shift_size = start_bit + 1 - length;
	
	if(shift_size < 0)
		shift_size = 0;
		
		   // create the mask | shift into position | Apply | Shift back
	*result = ((~(~(0x0) << mask_size) << shift_size) & val) >> shift_size;
	
	return mask_size;

}

// The "size" is in bit_depth sized units.
uint8_t ElementAnimationEngine_access_bits(uint8_t * frame, uint8_t bit_depth, uint16_t x_size, uint16_t y_size, uint16_t x_pixel, uint16_t y_pixel)
{
	
	uint64_t result = 0;
	
	// This access type uses a row-major model. Arrays are allocated array[y][x], for example. This allows the memory to formatted in a nice way in memory.
	uint8_t trailing_bits_remainder = x_size % bit_depth;
	
	// First, which bit are we on?
	uint16_t bit_offset = x_pixel * bit_depth + (y_pixel * x_size * bit_depth);
	
	// Okay, which byte is that in?
	uint16_t start_byte = bit_offset / 8;

	// Nice. Which bit in that byte?
	uint8_t in_byte_location = 7 - (bit_offset % 8);
	
	// Hey, lets go ahead, isolate those bits and apply them to the result.
	uint8_t cur_bit_offset = bit_offset + isolate_bits(*(frame + start_byte), in_byte_location, bit_depth, &result);
	
	while(cur_bit_offset - bit_offset < bit_depth)
	{
		uint8_t new_bits;

		// Now which byte are we in?
		start_byte = cur_bit_offset / 8;

		// Nice. Which bit in that byte?
		in_byte_location = 7 - (cur_bit_offset % 8);
		
		uint8_t return_size = isolate_bits(*(frame + start_byte), in_byte_location, bit_depth - (cur_bit_offset - bit_offset), &new_bits);

		// Shift the new bits into the result variable.
		result = result << return_size | new_bits;
		
		cur_bit_offset += return_size;
		
	}
	
	return result;
	
}

// The start bit and length REFER TO THE DESTINATION START BIT AND BIT LENGTH OF THE VALUE.
// THE WHOLE val WILL BE STUFFED INTO THE BYTE AT THAT LOCATION IF POSSIBLE
uint8_t write_bits( uint8_t * destination, int8_t start_bit, int8_t length, uint64_t val)
{
	// Just act like this works.
	int8_t mask_size = 0;
	int8_t shift_size = 0;

	uint8_t val_to_add = val;

	if(start_bit + 1 >= length)
	{
		// This is a fine size. We can be full length!
		mask_size = length;
		shift_size = start_bit + 1 - length;
	}
	else
	{
		// This is small. Can't be full length.
		mask_size = (start_bit + 1);
					 // Get the number of bits that need to be added.
		shift_size = length - mask_size;
		start_bit = mask_size - 1;

		val_to_add = ((~(~(0x0) << mask_size) << shift_size) & val) >> shift_size;
	}
	


	
	// Put that value into the destination at the start bit location.
	*destination = (*destination  & ~(~(~(0x0) << mask_size) << shift_size)) | val_to_add << (start_bit + 1) - mask_size;

	// How many bits did we end up adding?
	return mask_size;
	
}

uint8_t ElementAnimationEngine_write_bits(uint8_t * frame, uint8_t bit_depth, uint16_t x_size, uint16_t y_size, uint16_t x_pixel, uint16_t y_pixel, uint64_t bits)
{

	uint64_t result = 0;
		
	// This access type uses a row-major model. Arrays are allocated array[y][x], for example. This allows the memory to formatted in a nice way in memory.
		
	// First, which bit are we on?
	uint16_t bit_offset = x_pixel * bit_depth + (y_pixel * x_size * bit_depth);
		
	// Okay, which byte is that in?
	uint16_t start_byte = bit_offset / 8;

	// Nice. Which bit in that byte?
	uint8_t in_byte_location = 7 - (bit_offset % 8);
		
	uint8_t cur_bit_offset = bit_offset + write_bits((frame + start_byte), in_byte_location, bit_depth, bits);

	while(cur_bit_offset - bit_offset < bit_depth)
	{



		// Now which byte are we in?
		start_byte = cur_bit_offset / 8;

		// Nice. Which bit in that byte?
		in_byte_location = 7 - (cur_bit_offset % 8);
			
		uint8_t return_size = write_bits((frame + start_byte), in_byte_location, bit_depth - (cur_bit_offset - bit_offset), bits);
			
		cur_bit_offset += return_size;
			
	}
		
	return 0;
	
}


uint64_t ElementAnimationEngine_get_max_bitdepth_value(uint8_t bitdepth)
{
	
	return ~(~(0x0ull) << bitdepth);
	
}

enum ElementAnimationEngineStatus ElementAnimationEngine_load_to_buffer(ElementAnimationInstance * animation, ElementAnimationBufferConfigStruct * buffer)
{
	
	if(!animation->is_calculated)
	{
		// TODO: deal with this later. 
		
		enum ElementAnimationEngineStatus status = animation->fun_anim->function(buffer);
	
		return status;
	
	}
	
	ElementCalculatedAnimationInstance * anim_inst = animation->cal_anim;
	
	int32_t current_frame = ElementAnimationEngine_get_current_frame(anim_inst);
	
	uint64_t maximum_bitdepth_value = ElementAnimationEngine_get_max_bitdepth_value(anim_inst->bit_depth);

	if(current_frame >= 0 && current_frame < anim_inst->num_frames)
	{
		// Actually process this.
	
		// This gets a pointer to the frame we are interested in.
		uint8_t * frame = (anim_inst->frames + anim_inst->frame_size * current_frame);

		for(uint16_t x = 0; x < anim_inst->data_dimensions[0]; x++)		
		{	
			for(uint16_t y = 0; y < anim_inst->data_dimensions[1]; y++)
			{
				
				uint64_t pixel_bits = ElementAnimationEngine_access_bits(frame, anim_inst->bit_depth, anim_inst->data_dimensions[0], anim_inst->data_dimensions[1], x, y);
	
				// Okay, not lets access the bits from the current frame, then push the result back into the frame.

				uint64_t buffer_bits = ElementAnimationEngine_access_bits(buffer->write_buffer, buffer->bit_depth, buffer->data_dimensions[0], buffer->data_dimensions[1], x, y);	
	
				// The following logic only uses additive coloring. TODO: Implement alpha.
	
				uint64_t result_bits = 0;
	
				// Now check, is the addition of both bits going to go over the maximum value?
				if(maximum_bitdepth_value - pixel_bits < buffer_bits)
				{
					// No! There's not enough space left. Simply max it out.
					result_bits = maximum_bitdepth_value;
				}
				else
				{
					result_bits = buffer_bits + pixel_bits;
				}
	
				// Now push the new result into the buffer.
				ElementAnimationEngine_write_bits(buffer->write_buffer, buffer->bit_depth, buffer->data_dimensions[0], buffer->data_dimensions[1], x, y, result_bits);
			
			}
		}
	}
	return Animation_Engine_Success;
}

enum ElementAnimationEngineStatus ElementAnimationEngine_add_buffer(ElementAnimationBufferConfigStruct * buffer)
{

	if(animation_engine_config.current_animation_buffers < animation_engine_config.maximum_animation_buffers)
	{
		animation_engine_config.animation_buffers[animation_engine_config.current_animation_buffers++] = buffer;
		
		// Initialize the buffers in this struct to do swapping.
		buffer->read_buffer = &(buffer->buffers)[buffer->buffer_size * 0];
		buffer->write_buffer = &(buffer->buffers)[buffer->buffer_size * 1];
	}
	
	return Animation_Engine_Success;
	
}

// This adds another animation to the top of the stack.
enum ElementAnimationEngineStatus ElementAnimationEngine_push_animation(ElementAnimationBufferConfigStruct * buffer, ElementAnimationInstance * animation)
{

	if(buffer->current_animation_size < ELEMENT_ANIMATION_ENGINE_CONCURRENT_ANIMATION_MAX)
	{
		// We can add another animation.
		buffer->current_animations[buffer->current_animation_size++] = animation;
	}

	return Animation_Engine_Success;	
	
}

enum ElementAnimationEngineStatus ElementAnimationEngine_pop_animation(ElementAnimationBufferConfigStruct * buffer)
{

	if(buffer->current_animation_size > 0)
	{
		buffer->current_animation_size--;
	}
	
	return Animation_Engine_Success;	

}

// Removes a specific animation from the stack.
enum ElementAnimationEngineStatus ElementAnimationEngine_remove_animation(ElementAnimationBufferConfigStruct * buffer, uint8_t animation_id)
{
	
	for(uint8_t i = 0, j = 0; i < buffer->current_animation_size - 1; i ++, j++)
	{
		
		if(buffer->current_animations[i]->animation_id == animation_id)
		{
			j ++;
		}
		
		buffer->current_animations[i] = buffer->current_animations[j];
				
	}
	
	buffer->current_animation_size --;
	
	return Animation_Engine_Success;
	
}

// Removes every animation from the stack.
enum ElementAnimationEngineStatus ElementAnimationEngine_remove_all_animations(ElementAnimationBufferConfigStruct * buffer)
{
	
	buffer->current_animation_size = 0;
	
	return Animation_Engine_Success;
	
}


// This will update every animation buffer that has been registered, then flip buffers.
enum ElementAnimationEngineStatus ElementAnimationEngine_update()
{

	// Steps:
	// 1. First, grab a buffer from the buffer list.
	// 2. Then, loop through that buffer's animation list.
	// 3. For every animation in the list:
	//		3a. Calculate which frame the animation is on.
	//		3b. Extract the correct bits from the frame
	//		3c. Add the bits to the buffer bits then integrate back into buffer.	
	//		3c. Repeat for next animation. 
	// 4. Repeat with next buffer.
	
	for(uint8_t buf = 0; buf < animation_engine_config.current_animation_buffers; buf++)
	{
		
		ElementAnimationBufferConfigStruct * buffer_ptr = animation_engine_config.animation_buffers[buf];
		
		for(uint8_t cur_anim = 0; cur_anim < buffer_ptr->current_animation_size; cur_anim++)
		{
			enum ElementAnimationEngineStatus status = ElementAnimationEngine_load_to_buffer(buffer_ptr->current_animations[cur_anim], buffer_ptr);
		
			if(status == Animation_Engine_Animation_Complete)
			{
				// We need to pop this one off the stack.
				ElementAnimationEngine_remove_animation(buffer_ptr, buffer_ptr->current_animations[cur_anim]->animation_id);
			}
		}
		
		uint8_t * swap = buffer_ptr->write_buffer;
		
		buffer_ptr->write_buffer = buffer_ptr->read_buffer;
		
		buffer_ptr->read_buffer = swap;
	
		// Clear the write buffer.
		for(uint8_t i = 0; i < buffer_ptr->buffer_size; i++)
		{
			buffer_ptr->write_buffer[i] = 0x0;
		}
			
	
	}
	
}


// This function processes only one step.
// TODO: Define "step".
enum ElementAnimationEngineStatus ElementAnimationEngine_do_step();