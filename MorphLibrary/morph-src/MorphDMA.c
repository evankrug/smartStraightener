/*
 * MorphDMA.c
 *
 * Created: 11/15/2018 5:46:43 PM
 *  Author: 243400
 */

#include "include/MorphDMA.h"
#include "include/MorphConfig.h"
#include "include/MorphUtils.h"


#ifndef MORPH_IMPLICIT

void (*morph_dma_init_function)(*MorphDMAConfig) = &MorphUtils_empty_callback;
void (*morph_dma_enable_channel_function)(uint8_t unit, uint8_t channel) = &MorphUtils_empty_callback;
void (*morph_dma_stop_channel_function)(uint8_t unit, uint8_t channel) = &MorphUtils_empty_callback;
void (*morph_dma_enable_complete_callback_function)(uint8_t unit, uint8_t channel, bool enabled) = &MorphUtils_empty_callback;
void (*morph_dma_set_transfer_complete_callback_function)(uint8_t unit, uint8_t channel, void (*callback)()) = &MorphUtils_empty_callback;
void (*morph_dma_enable_error_callback_function)(uint8_t unit, uint8_t channel, bool enabled) = &MorphUtils_empty_callback;
void (*morph_dma_set_transfer_error_callback_function)(uint8_t unit, uint8_t channel, void (*callback)()) = &MorphUtils_empty_callback;


void MorphDMA_register_init_function(void (*function)(*MorphDMAConfig))
{
	morph_dma_init_function = function;
}

void MorphDMA_register_enable_channel_function(void (*function)(uint8_t unit, uint8_t channel))
{
	morph_dma_enable_channel_function = function;
}

void MorphDMA_register_stop_channel_function(void (*function)(uint8_t unit, uint8_t channel))
{
	morph_dma_stop_channel_function = function;
}

void MorphDMA_register_enable_complete_callback_function(void (*function)(uint8_t unit, uint8_t channel, bool enabled))
{
	morph_dma_enable_complete_callback_function = function;
}

void MorphDMA_register_set_transfer_complete_callback_function(void (*function)(uint8_t unit, uint8_t channel, void (*callback)()))
{
	morph_dma_set_transfer_complete_callback_function = function;
}

void MorphDMA_register_enable_error_callback_function(void (*function)(uint8_t unit, uint8_t channel, bool enabled))
{
	morph_dma_enable_error_callback_function = function;
}

void MorphDMA_register_set_transfer_error_callback_function(void (*function)(uint8_t unit, uint8_t channel, void (*callback)()))
{
	morph_dma_set_transfer_error_callback_function = function;
}

#endif

// FUNCTIONS! //


void MorphDMA_init_struct(MorphDMAConfig * dma_config)
{

	dma_config->dma_unit = 0;
	dma_config->dma_channel = 0;
	dma_config->dma_priority = DMAHighPriority;
	dma_config->dma_src_address = 0x0;
	dma_config->dma_dest_address = 0x0;
	dma_config->transfer_count = 0x0;

	dma_config->data_size = 8; // size of the data to be transfered in bits.
	dma_config->use_dma_complete_callback = false;
	dma_config->transfer_complete_callback = &MorphUtils_empty_callback;
	dma_config->use_dma_error_callback = false;
	dma_config->transfer_error_callback = &MorphUtils_empty_callback;
	dma_config->trigger = NO_TRIGGER_DMA;
	dma_config->trigger_group_id = 0; // Used to identify sub-groups of triggers. For example, We want to start when SPI channel 0 receives a byte. This would be 0.
	dma_config->step_source = false;   // Should the source be stepped
	dma_config->step_source_up = false; // Should the source be stepped up? (If false, will step down)
	dma_config->source_step_size = 0;
	dma_config->step_destination = false;
	dma_config->step_destination_up = false; // Should the increments be up or down?
	dma_config->destination_step_size = 0;

}

void MorphDMA_init(MorphDMAConfig * dma_config)
{
#ifdef MORPH_IMPLICIT
	morph_config_dma_init(dma_config);
#else
	morph_dma_init_function(dma_config);
#endif
}

void MorphDMA_enable_channel(uint8_t unit, uint8_t channel)
{
#ifdef MORPH_IMPLICIT
	morph_config_dma_enable_channel(unit, channel);
#else
	morph_dma_enable_channel_function(unit, channel);
#endif
}

void MorphDMA_stop_channel(uint8_t unit, uint8_t channel)
{
#ifdef MORPH_IMPLICIT
	morph_config_dma_stop_channel(unit, channel);
#else
	morph_dma_stop_channel_function(unit, channel);
#endif
}

void MorphDMA_enable_complete_callback(uint8_t unit, uint8_t channel, bool enabled)
{
#ifdef MORPH_IMPLICIT
	morph_config_dma_enable_complete_callback(unit, channel, enabled);
#else
	morph_dma_enable_complete_callback_function(unit, channel, enabled);
#endif
}

void MorphDMA_set_transfer_complete_callback(uint8_t unit, uint8_t channel, void (*callback)())
{
#ifdef MORPH_IMPLICIT
	morph_config_dma_set_transfer_complete_callback(unit, channel, callback);
#else
	morph_dma_set_transfer_complete_callback_function(unit, channel, callback);
#endif
}

void MorphDMA_enable_error_callback(uint8_t unit, uint8_t channel, bool enabled)
{
#ifdef MORPH_IMPLICIT
	morph_config_dma_enable_transfer_callback(unit, channel, enabled);
#else
	morph_dma_enable_error_callback_function(unit, channel, enabled);
#endif
}

void MorphDMA_set_transfer_error_callback(uint8_t unit, uint8_t channel, void (*callback)())
{
#ifdef MORPH_IMPLICIT
	morph_config_dma_enable_transfer_error_callback(unit, channel, callback);
#else
	morph_dma_set_transfer_error_callback_function(unit, channel, callback);
#endif
}
