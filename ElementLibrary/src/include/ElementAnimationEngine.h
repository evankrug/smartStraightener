
#ifndef ELEMENTANIMATIONENGINE_H_
#define ELEMENTANIMATIONENGINE_H_

#include "ElementConfig.h"

// This will update every animation buffer that has been registered, then flip buffers.
enum ElementAnimationEngineStatus ElementAnimationEngine_update();

// This function processes only one step. 
// TODO: Define "step".
enum ElementAnimationEngineStatus ElementAnimationEngine_do_step();

// Does a buffer swap between the read and write buffers.
enum ElementAnimationEngineStatus ElementAnimationEngine_swap_buffers(ElementAnimationBufferConfigStruct * buffer);
 
// Adds a buffer to be managed.
enum ElementAnimationEngineStatus ElementAnimationEngine_add_buffer(ElementAnimationBufferConfigStruct * buffer);

// Tells the animation engine to load a specific animation to a specific buffer.
enum ElementAnimationEngineStatus ElementAnimationEngine_load_to_buffer(ElementAnimationInstance * animation, ElementAnimationBufferConfigStruct * buffer);

// This adds another animation to the top of the stack.
enum ElementAnimationEngineStatus ElementAnimationEngine_push_animation(ElementAnimationBufferConfigStruct * buffer, ElementAnimationInstance * animation);

// Pops the top animation on this stack.
enum ElementAnimationEngineStatus ElementAnimationEngine_pop_animation(ElementAnimationBufferConfigStruct * buffer);

// Removes a specific animation from the stack.
enum ElementAnimationEngineStatus ElementAnimationEngine_remove_animation(ElementAnimationBufferConfigStruct * buffer, uint8_t animation_id);

// Removes every animation from the stack.
enum ElementAnimationEngineStatus ElementAnimationEngine_remove_all_animations(ElementAnimationBufferConfigStruct * buffer);

enum ElementAnimationEngineStatus ElementAnimationEngine_pack_bits(uint8_t * buffer);

// This returns the value at the requested pixel in an 8-bit package.
// For example, if requested on an animation with a bit-depth of 1, only the first bit will be significant.
// Will attempt to stuff more than 8 bits into 8 if requested. (Hint: it won't work).
// Any bit requested out of bounds will return 0.
uint8_t ElementAnimationEngine_get_pixel_8bit(ElementAnimationBufferConfigStruct * buffer, uint16_t x, uint16_t y);

#endif