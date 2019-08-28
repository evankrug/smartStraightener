
#include <MorphTypes.h>
#include <MorphUtils.h>
#include <MorphTime.h>

#include "include/ElementDirectButton.h"

int8_t find_button_id(uint8_t button_id)
{
	int8_t button_index = -1;
		
	// Find the button
	for(uint8_t i = 0; i < ElementDirectButton_get_count(); i++)
	{
		
		if(element_master_direct_button_group.element_button_config_array[i].button_id == button_id)
		{
			// found it.
			button_index = i;
		
			// Stop the loop.
			break;

		}
		
	}


	return button_index;

}

void clear_button_config(ElementButtonConfigStruct * config_struct)
{
	// This function clears all of the data in a ElementButtonConfigStruct
	// and sets it up in a state that won't break everything if it is accidentally used.
	config_struct->button_pin_number = 0;
	config_struct->button_id = -1;
	config_struct->button_depressed_value = Low;
	config_struct->button_default_pull = PullNone;
	
	config_struct->button_signaled = false;
	config_struct->button_signaled_time = 0;
	config_struct->button_stabilized = false;
	
	config_struct->button_down_callback = &MorphUtils_empty_callback;
	config_struct->button_down_callback_reg = false;
	config_struct->button_down_event_triggered = false;

	config_struct->button_up_callback = &MorphUtils_empty_callback;
	config_struct->button_up_callback_reg = false;
	config_struct->button_up_event_triggered = false;
	
	config_struct->button_press_callback = &MorphUtils_empty_callback;
	config_struct->button_press_callback_reg = false;
	config_struct->button_press_event_triggered = false;
	
	config_struct->button_short_callback = &MorphUtils_empty_callback;
	config_struct->button_short_callback_reg = false;
	config_struct->button_short_event_triggered = false;
	
	config_struct->button_long_callback = &MorphUtils_empty_callback;
	config_struct->button_long_callback_reg = false;
	config_struct->button_long_event_triggered = false;				
	
}

void ElementDirectButton_init()
{
	
	// Setup the GPIOs for buttoning
	for(uint8_t i = 0; i < ElementDirectButton_get_count(); i ++)
	{

		ElementButtonConfigStruct btn_struct = element_master_direct_button_group.element_button_config_array[i];

		// Make sure they are inputs!		
		MorphGPIO_set_pin_direction(btn_struct.button_pin_number, Input);
		
		// Also, set the pull direction.
		MorphGPIO_set_pin_pull_state(btn_struct.button_pin_number, btn_struct.button_default_pull);
		
	}
	
}

void ElementDirectButton_update()
{
	
	for(uint8_t i = 0; i < ElementDirectButton_get_count(); i++)
	{

		ElementButtonConfigStruct * btn_struct = &(element_master_direct_button_group.element_button_config_array[i]);

		MorphPinNumber pin = btn_struct->button_pin_number;

		enum MorphPinValue current_input = MorphGPIO_get_pin_value(pin);
		
		MorphTimeValue cur_time = MorphTime_millis();
		
		MorphTimeValue button_signaled_delta = cur_time - (MorphTimeValue)btn_struct->button_signaled_time;
	
		if(btn_struct->button_signaled)
		{
                        
			// The button has been pressed in the previous update loop.
			if(current_input == btn_struct->button_depressed_value)
			{
				// The button is being held still.
        
                
				if(button_signaled_delta > ELEMENT_DIRECT_BUTTON_DEBOUNCE_TIME_MS)
				{
					// The button is in a stable press!
					btn_struct->button_stabilized = true;
                    
					// Fire the button down callback if it exists
					if(!btn_struct->button_down_event_triggered && btn_struct->button_down_callback_reg)
						btn_struct->button_down_callback();
    
					btn_struct->button_down_event_triggered = true;
                    
				}
				else
				{
					// The button hasn't been pressed long enough to be stable. 
					btn_struct->button_stabilized = false;
				}
                
			}
			else
			{
				// The button was released or bounced. 
				if(button_signaled_delta > ELEMENT_DIRECT_BUTTON_DEBOUNCE_TIME_MS)
				{
					
					// The button was pressed for long enough to be a press.
					// Call the button up callback if it exists.
					if(btn_struct->button_up_callback_reg)
					{
						btn_struct->button_up_callback();
					}
                    
					// If the button was pressed for less than the time of a short hold, then it's a press.
					if(button_signaled_delta < ELEMENT_DIRECT_BUTTON_SHORT_HOLD_TIME_MS)
					{
						// It was shorter than a short hold.
						// Fire the callback for button press if it exists.
						if(btn_struct->button_press_callback_reg)
							btn_struct->button_press_callback();
					}
                    
				}

				// Do clean-up                
				btn_struct->button_signaled = false;
				btn_struct->button_stabilized = false;
                
				// Make sure none of the events are triggered.
				btn_struct->button_down_event_triggered = false;
				btn_struct->button_up_event_triggered = false;
				btn_struct->button_press_event_triggered = false;
				btn_struct->button_short_event_triggered = false;
				btn_struct->button_long_event_triggered = false;
																                
			}
		}    
		else if(current_input == btn_struct->button_depressed_value)
		{
			// This is the first update loop we've seen a press on this button.
			// We have to do a bit of de-bounce before doing any button stuff.
            
			btn_struct->button_signaled = true;
			btn_struct->button_signaled_time = MorphTime_millis();
			
		}
        
        
		if(btn_struct->button_stabilized)
		{
			// If this button is stabilized, we just need to check timings.
            
			// First, if the button has been held for more than the short hold time, 
			// then it is a short hold.
			
			if (!btn_struct->button_short_event_triggered &&
				button_signaled_delta > ELEMENT_DIRECT_BUTTON_SHORT_HOLD_TIME_MS)
			{
				// Fire the button short hold callback.
				if(!btn_struct->button_short_event_triggered && btn_struct->button_short_callback_reg)
					btn_struct->button_short_callback();
            
			
				// Mark it as triggered. This event only happens once per press.
				btn_struct->button_short_event_triggered = true;
                
			}

			// Next, if the button has been held for more than the long hold time,
			// then it is a long hold.            
			if (!btn_struct->button_long_event_triggered &&
			button_signaled_delta > ELEMENT_DIRECT_BUTTON_LONG_HOLD_TIME_MS)
			{
				// Fire the button short hold callback.
				if(!btn_struct->button_long_event_triggered && btn_struct->button_long_callback_reg)
				btn_struct->button_long_callback();
							
							
				// Mark it as triggered. This event only happens once per press.
				btn_struct->button_long_event_triggered = true;
							
			}
            
		}

        
	}
    
}

void ElementDirectButton_register_button(uint8_t button_id, MorphPinNumber button_pin, enum MorphPinValue depressed_value, enum MorphPinPullState pull_state)
{

	uint8_t cur_num_buttons = ElementDirectButton_get_count();

	if(cur_num_buttons < ElementDirectButton_get_max_count())
	{
		
		// We have enough space for more buttons.
		
		ElementButtonConfigStruct * new_button = 
			&element_master_direct_button_group.element_button_config_array[cur_num_buttons];
		
		// Clear the button's attributes before using it.
		clear_button_config(new_button);
			
		new_button->button_id = button_id;
		new_button->button_pin_number = button_pin;
		new_button->button_depressed_value = depressed_value;
		new_button->button_default_pull = pull_state;
		
		// Make sure they are inputs!		
		MorphGPIO_set_pin_direction(new_button->button_pin_number, Input);
		
		// Also, set the pull direction.
		MorphGPIO_set_pin_pull_state(new_button->button_pin_number, new_button->button_default_pull);		
		
		// TODO: Abstract the direct variable away here.
		element_master_direct_button_group.cur_num_buttons++;
		
	}
	
}

void ElementDirectButton_deregister_button(uint8_t button_id)
{

	// Not doing this for now.

	//int8_t button_index = -1;
//
	//// Find the button
	//for(uint8_t i = 0; i < ElementDirectButton_get_count(); i++)
	//{
		//
		//if(element_master_direct_button_group.element_button_config_array[i] == button_id)
		//{
			//// found it. 
			//button_index = i;
			//
			//// Stop the loop.
			//break;
		//}	
		//
	//}
//
	//if(button_index >= 0)
	//{
		//
		//// We have an index. 
		//
	//}

}

uint8_t ElementDirectButton_get_count()
{
	return element_master_direct_button_group.cur_num_buttons;
}

uint8_t ElementDirectButton_get_max_count()
{
	return ELEMENT_MAXIMUM_NUM_BUTTONS;	
}

void ElementDirectButton_register_callback(void (*button_callback)(void), int8_t button_id, enum ElementButtonEvent event)
{
	
	int8_t index = find_button_id(button_id);
	
	if(index < 0)
	{
		return;
	}
	
	
	ElementButtonConfigStruct * cur_button =
	&element_master_direct_button_group.element_button_config_array[index];
	
	switch(event)
	{
		
		case ElementButtonEventDown:
		
			cur_button->button_down_callback = button_callback;
			cur_button->button_down_callback_reg = true;
		
		break;
		
		case ElementButtonEventUp:

			cur_button->button_up_callback = button_callback;
			cur_button->button_up_callback_reg = true;
		
		break;
		
		case ElementButtonEventPress:
		
			cur_button->button_press_callback = button_callback;
			cur_button->button_press_callback_reg = true;
		
		break;
		
		case ElementButtonEventShort:

			cur_button->button_short_callback = button_callback;
			cur_button->button_short_callback_reg = true;

		break;
		
		case ElementButtonEventLong:

			cur_button->button_long_callback = button_callback;
			cur_button->button_long_callback_reg = true;

		break;
		
	}
	
}

void ElementDirectButton_deregister_callback(int8_t button_id, enum ElementButtonEvent event)
{
	
	int8_t index = find_button_id(button_id);
		
	if(index < 0)
	{
		return;
	}
		
		
	ElementButtonConfigStruct * cur_button =
	&element_master_direct_button_group.element_button_config_array[index];
		
	
	switch(event)
	{
		
		case ElementButtonEventDown:
	
			cur_button->button_down_callback = &MorphUtils_empty_callback;
			cur_button->button_down_callback_reg = false;
				
		break;
		
		case ElementButtonEventUp:
		
			cur_button->button_up_callback = &MorphUtils_empty_callback;
			cur_button->button_up_callback_reg = false;
		
		break;
		
		case ElementButtonEventPress:
		
			cur_button->button_press_callback = &MorphUtils_empty_callback;
			cur_button->button_press_callback_reg = false;
		
		break;
		
		case ElementButtonEventShort:

			cur_button->button_short_callback = &MorphUtils_empty_callback;
			cur_button->button_short_callback_reg = false;

		break;
		
		case ElementButtonEventLong:

			cur_button->button_long_callback = &MorphUtils_empty_callback;
			cur_button->button_long_callback_reg = false;
		
		break;
		
	}
	
}

void ElementDirectButton_deregister_all_callbacks()
{
	

	for(uint8_t i = 0; i < ElementDirectButton_get_count(); i++)
	{
			
		element_master_direct_button_group.element_button_config_array[i].button_down_callback_reg  = false;
		element_master_direct_button_group.element_button_config_array[i].button_up_callback_reg    = false;
		element_master_direct_button_group.element_button_config_array[i].button_press_callback_reg = false;
		element_master_direct_button_group.element_button_config_array[i].button_short_callback_reg = false;
		element_master_direct_button_group.element_button_config_array[i].button_long_callback_reg  = false;
			
		element_master_direct_button_group.element_button_config_array[i].button_down_event_triggered  = false;
		element_master_direct_button_group.element_button_config_array[i].button_up_event_triggered    = false;
		element_master_direct_button_group.element_button_config_array[i].button_press_event_triggered = false;
		element_master_direct_button_group.element_button_config_array[i].button_short_event_triggered = false;
		element_master_direct_button_group.element_button_config_array[i].button_long_event_triggered  = false;
			
	}
	
}

uint8_t ElementDirectButton_get_combo_count()
{
	
	return element_master_direct_button_group.cur_num_combos;
	
}

uint8_t ElementDirectButton_get_max_combo_count()
{
	
	return ELEMENT_MAXIMUM_NUM_COMBOS;
	
}

void ElementDirectButton_register_combo(int8_t combo_id)
{
	
	
	
}

void ElementDirectButton_deregister_combo(int8_t combo_id)
{
	
}

void ElementDirectButton_set_combo_callback_time(int8_t combo_id, MorphTimeValue timeout)
{
	
}

void ElementDirectButton_register_combo_callback(int8_t combo_id, void (*combo_callback)(void))
{
	
}

void ElementDirectButton_deregister_combo_callback(int8_t combo_id)
{
	
}

void ElementDirectButton_add_button_to_combo(int8_t combo_id, int8_t button_id)
{
	
}

void ElementDirectButton_remove_button_from_combo(int8_t combo_id, int8_t button_id)
{
	
}

