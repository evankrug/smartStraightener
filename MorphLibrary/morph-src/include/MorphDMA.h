/*
 * MorphDMA.h
 *
 * Created: 11/13/2018 3:19:36 PM
 *  Author: 243400
 */


#ifndef MORPHDMA_H_
#define MORPHDMA_H_

#include "MorphUtils.h"
#include "MorphOptions.h"
#include "MorphTypes.h"


#ifndef MORPH_IMPLICIT

// MORPH_IMPLICIT means the functions will not be implemented with function pointers.
// Instead, it will call the (possibly) implemented functions directly.
// This is more dangerous, however, it might see performance gains through compiler optimization.

void MorphDMA_register_init_function(void (*function)(*MorphDMAConfig));
void MorphDMA_register_enable_channel_function(void (*function)(uint8_t unit, uint8_t channel));
void MorphDMA_register_stop_channel_function(void (*function)(uint8_t unit, uint8_t channel));
void MorphDMA_register_enable_complete_callback_function(void (*function)(uint8_t unit, uint8_t channel, bool enabled));
void MorphDMA_register_set_transfer_complete_callback_function(void (*function)(uint8_t unit, uint8_t channel, void (*callback)()));
void MorphDMA_register_enable_error_callback_function(void (*function)(uint8_t unit, uint8_t channel, bool enabled));
void MorphDMA_register_set_transfer_error_callback_function(void (*function)(uint8_t unit, uint8_t channel, void (*callback)()));

#endif

// FUNCTIONS! //

void MorphDMA_init_struct(MorphDMAConfig * dma_config);

void MorphDMA_init(MorphDMAConfig * dma_config);

void MorphDMA_enable_channel(uint8_t unit, uint8_t channel);

void MorphDMA_stop_channel(uint8_t unit, uint8_t channel);

void MorphDMA_enable_complete_callback(uint8_t unit, uint8_t channel, bool enabled);

void MorphDMA_set_transfer_complete_callback(uint8_t unit, uint8_t channel, void (*callback)());

void MorphDMA_enable_error_callback(uint8_t unit, uint8_t channel, bool enabled);

void MorphDMA_set_transfer_error_callback(uint8_t unit, uint8_t channel, void (*callback)());

#endif /* MORPHDMA_H_ */
