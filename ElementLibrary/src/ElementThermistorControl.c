#include "ElementThermistorControl.h"

#include <math.h>
#include <MorphADC.h>
#include <MorphTime.h>

//#define FAKE_THERMISTOR_ADC 950L

void _process_thermistor_controller(ElementThermistorController * controller);

void _process_pid_thermistor_controller(ElementThermistorPIDController * controller);

void _process_on_off_thermistor_controller(ElementThermistorOnOffController * controller);

void _calculate_controller_thermistor_temp(ElementThermistorController * controller);

void _add_temp_to_history(ElementThermistor * thermistor, float temp)
{
	
	uint8_t back = thermistor->filter_array_loc;
	
	thermistor->history[back] = temp;
	
	if(back == THERMISTOR_TEMP_HISTORY - 1)
	{
		// Time to loop back.
		thermistor->filter_array_loc = 0;
	}
	else
	{
		thermistor->filter_array_loc ++;
	}

	if(thermistor->filter_array_size < THERMISTOR_TEMP_HISTORY)
	{
		thermistor->filter_array_size ++;
	}
	
}

float _get_filtered_temperature(ElementThermistor * thermistor)
{
	
	float sum = 0.0f;
	
	for(uint8_t i = 0; i < thermistor->filter_array_size; i ++)
	{
		sum	+= thermistor->history[i];
	}
	
	return  sum / thermistor->filter_array_size;
	
}

void ElementThermistorControl_update()
{
	
	for(uint8_t i = 0; i < master_thermistor_system_config.thermistor_count; i++)
	{
		ElementThermistor * therm = master_thermistor_system_config.thermistors[i];
		
		// WARNING: This calculation only works if AREF = Vin for the thermostat circuit.
		// This is a simplified function that does not require conversion to actual voltage.
		// The equivalent unsimplified code is this:
		// double voltage = raw_adc_value/(float)maximum_value * (float)input_voltage;
		// double resistance = - (47690 * voltage) / (voltage - 5.0f);

		double resistance = 0;
		
		MorphPinNumber therm_pin = therm->pin;
		
		MorphADCValue current_adc_val = MorphADC_read(therm_pin);
		
#ifdef FAKE_THERMISTOR_ADC
	
		current_adc_val = FAKE_THERMISTOR_ADC;
	
#endif
		
		MorphADCValue max_adc_val = MorphADC_get_maximum_value(therm_pin);
		
		resistance = therm->series_resistor_value * (-1.0f + ((float)max_adc_val/(float)current_adc_val));
		
		double steinhart = (1.0 / (therm->nominal_temp + ELEMENT_THERMISTOR_K_TO_C)) + ((log(resistance / therm->nominal_resistance)) / therm->beta);
		
		double temp = (1.0f / steinhart) - ELEMENT_THERMISTOR_K_TO_C;
		
		if(temp > therm->valid_low && temp < therm->valid_high)
		{
			// Only update the temperature if it is in a valid range.
			_add_temp_to_history(therm, temp);
		
			therm->current_temp = _get_filtered_temperature(therm);
		}
		
	}
	
	for(uint8_t i = 0; i < master_thermistor_system_config.controller_count; i++)
	{
		
		_process_thermistor_controller(master_thermistor_system_config.thermistor_controllers[i]);
		
	}
	
}

void _process_thermistor_controller(ElementThermistorController * controller)
{

	_calculate_controller_thermistor_temp(controller);

	// First, we have to figure out what type of controller we are working with.
	if(controller->type == ElementThermistorOnOffControl)
	{
		_process_on_off_thermistor_controller(controller);
	}
	else if(controller->type == ElementThermistorPIDControl)
	{
		_process_pid_thermistor_controller(controller);
	}

}

void _calculate_controller_thermistor_temp(ElementThermistorController * controller)
{
	ElementThermistor * therm = controller->thermistor;

	// WARNING: This calculation only works if AREF = Vin for the thermostat circuit.
	// This is a simplified function that does not require conversion to actual voltage.
	// The equivalent unsimplified code is this:
	// double voltage = raw_adc_value/(float)maximum_value * (float)input_voltage;
	// double resistance = - (47690 * voltage) / (voltage - 5.0f);

	double resistance = 0;

	MorphPinNumber therm_pin = therm->pin;

	MorphADCValue current_adc_val = MorphADC_read(therm_pin);

#ifdef FAKE_THERMISTOR_ADC
	
		current_adc_val = FAKE_THERMISTOR_ADC;
	
#endif

	MorphADCValue max_adc_val = MorphADC_get_maximum_value(therm_pin);

	resistance = therm->series_resistor_value * (-1.0f + ((float)max_adc_val/(float)current_adc_val));

	double steinhart = (1.0 / (therm->nominal_temp + ELEMENT_THERMISTOR_K_TO_C)) + ((log(resistance / therm->nominal_resistance)) / therm->beta);

	double temp = (1.0f / steinhart) - ELEMENT_THERMISTOR_K_TO_C;

	if(temp > therm->valid_low && temp < therm->valid_high)
	{
		// Only update the temperature if it is in a valid range.
		_add_temp_to_history(therm, temp);
		
		therm->current_temp = _get_filtered_temperature(therm);
	}	
}

void _process_pid_thermistor_controller(ElementThermistorPIDController * controller)
{
	
	if(controller->super.active && controller->rate > 0.0f)
	{
		// We are active and the rate makes sense.

		MorphTimeValue control_delay = 1.0f / controller->rate * 1000UL;
		
		MorphTimeValue cur_time = MorphTime_millis();
		
		if(cur_time - controller->last_update >= control_delay)
		{
			// It's time to update the controller.
			
			// The equation is as follows: 
			// operations pertaining to KC, Ti, and Td are precomputed and put into P_coef, I_coef, and D_coef.
			// Note: the derivative term is subtracted, this is because the derivative is being taken on PV, not e(t).
			// CO = CObias + Kc * e(t) + KC/Ti Integral(e(t)) dt - Kc * Td(dPV/dt)
			
			// Let's get the error first.
			float error = controller->super.setpoint - controller->super.thermistor->current_temp;

			// We want the derivative on the PV, not the Error.			
			controller->cur_derivative = (controller->super.thermistor->current_temp - controller->previous_process_variable) /  ((MorphTime_millis() - controller->last_update)/1000.0f);
			
			// Add to the integral for the current time-slice.
			controller->cur_integral += error * ((MorphTime_millis() - controller->last_update)/1000.0f);
			
			if(controller->cap_integral && fabs(controller->cur_integral) > controller->max_integral)
			{
				controller->cur_integral = fabs(controller->cur_integral)/controller->cur_integral * controller->max_integral;
			}
				
			
			// Put everything together for the new output.
			controller->control_output = controller->control_output_bias + controller->P_coef * error + controller->I_coef * controller->cur_integral - controller->D_coef * controller->cur_derivative;
			
			if(controller->control_callback_reg)
				controller->control_callback(controller);
			
			
		}
		
	}
	
	
}

void _process_on_off_thermistor_controller(ElementThermistorOnOffController * controller)
{	

	ElementThermistor * therm = controller->super.thermistor;

	// The temperature has been read for this controller.
	// Now, call any callbacks necessary

	if(controller->super.active)
	{
	
		// Hey, the controller is active!
	
		if(controller->forward_hyst)
		{
			// Do forward hysteresis control.
			if( therm->current_temp > controller->super.setpoint + controller->hysteresis_range )
			{
				// We are above setpoint + hysteresis amount. Time to go down! (only called for one-shot mode)
				if(controller->temp_high_callback_reg && !controller->temp_high_callback_triggered && controller->one_shot)
				{
					controller->temp_high_callback();
					controller->temp_high_callback_triggered = true;
					controller->temp_low_callback_triggered = false;
				}
				controller->control_direction_up = false;
			}
			else if(therm->current_temp < controller->super.setpoint)
			{
				// We are below setpoint. Time to go up! (only called for one-shot mode)
				if(controller->temp_low_callback_reg && !controller->temp_low_callback_triggered && controller->one_shot)
				{
					controller->temp_low_callback();
					controller->temp_low_callback_triggered = true;
					controller->temp_high_callback_triggered = false;
				}
				controller->control_direction_up = true;
			}
		
		}
		else
		{
			// Do reverse hysteresis control.
			if(therm->current_temp > controller->super.setpoint)
			{
				// We are above setpoint. Time to go down! (only called for one-shot mode)
				if(controller->temp_high_callback_reg && !controller->temp_high_callback_triggered && !controller->one_shot)
				{
					controller->temp_high_callback();
					controller->temp_high_callback_triggered = true;
					controller->temp_low_callback_triggered = false;
				}
				controller->control_direction_up = false;
			}
			else if(therm->current_temp < controller->super.setpoint - controller->hysteresis_range)
			{
				// We are below setpoint + hysteresis amount. Time to go up! (only called for one-shot mode)
				if(controller->temp_low_callback_reg && !controller->temp_low_callback_triggered && !controller->one_shot)
				{
					controller->temp_low_callback();
					controller->temp_low_callback_triggered = true;
					controller->temp_high_callback_triggered = false;
				}
				controller->control_direction_up = true;
			}
		}
	
	
		// If one-shot mode is off, constantly call the callbacks.
		if(!controller->control_direction_up && !controller->one_shot && controller->temp_high_callback_reg)
		{
			controller->temp_high_callback();
		}
		else if(controller->control_direction_up && !controller->one_shot && controller->temp_low_callback_reg)
		{
			controller->temp_low_callback();
		}
	
	}
}

void ElementThermistorControl_push_thermistor(ElementThermistor * thermistor)
{
	
	// Check if we have any space left in the stack
	if(master_thermistor_system_config.thermistor_count < THERMISTORS_MAX_COUNT)
	{
		// Okay, we can push it!

		// First, make sure the ADC is initialized.
		MorphADC_init_adc(thermistor->pin);

		MorphADC_set_reference(thermistor->pin, thermistor->ref, thermistor->ref_id);
	
		MorphADC_set_resolution(thermistor->pin, thermistor->res);

		MorphADC_set_prescaler(thermistor->pin, thermistor->prescaler_value);
	
		// Add the pointer to the array.
		master_thermistor_system_config.thermistors[master_thermistor_system_config.thermistor_count++] = thermistor;
		
	}
	
	
}

ElementThermistor * ElementThermistorControl_pop_thermistor()
{
	// Check if we have something in the stack
	if(master_thermistor_system_config.thermistor_count > 0)
	{
		// There is something here, simply subtract one from the count.
		master_thermistor_system_config.thermistor_count--;
	}
	
}

void ElementThermistorControl_remove_all_thermistors()
{
	// ez
	master_thermistor_system_config.thermistor_count = 0;
}

void ElementThermistorControl_push_controller(ElementThermistorController * controller)
{
	// Check if we have any space left in the stack
	if(master_thermistor_system_config.controller_count < THERMISTORS_MAX_COUNT)
	{
		// Okay, we can push it!

		// First, make sure the ADC is initialized.
		MorphADC_init_adc(controller->thermistor->pin);

		MorphADC_set_reference(controller->thermistor->pin, controller->thermistor->ref, controller->thermistor->ref_id);
		
		MorphADC_set_resolution(controller->thermistor->pin, controller->thermistor->res);
		
		MorphADC_set_prescaler(controller->thermistor->pin, controller->thermistor->prescaler_value);		
		
		// Add the pointer to the array.
		master_thermistor_system_config.thermistor_controllers[master_thermistor_system_config.controller_count++] = controller;
		
	}	
}

ElementThermistorOnOffController * ElementThermistorControl_pop_controller()
{
	// Check if we have something in the stack
	if(master_thermistor_system_config.controller_count > 0)
	{
		// There is something here, simply subtract one from the count.
		master_thermistor_system_config.controller_count--;
	}
		
}

void ElementThermistorControl_remove_all_controllers()
{
	master_thermistor_system_config.controller_count = 0;	
}

void ElementThermistorControl_register_callback(ElementThermistorController * controller, void (*callback)(), enum ElementThermistorEvent event)
{
	switch(event)
	{
		case ElementThermistorHigh:
			
			if(controller->type == ElementThermistorOnOffControl)
			{
				((ElementThermistorOnOffController*)controller)->temp_high_callback = callback;
				((ElementThermistorOnOffController*)controller)->temp_high_callback_reg = true;				
			}

		break;
		case ElementThermistorLow:
			
			if(controller->type == ElementThermistorOnOffControl)
			{
				((ElementThermistorOnOffController*)controller)->temp_low_callback = callback;
				((ElementThermistorOnOffController*)controller)->temp_low_callback_reg = true;
			}
			
		case ElementThermistorDirectCallback:

			if(controller->type == ElementThermistorPIDControl)
			{
				((ElementThermistorPIDController*)controller)->control_callback = callback;
				((ElementThermistorPIDController*)controller)->control_callback_reg = true;
			}
			
		break;
	}
}

void ElementThermistorControl_deregister_callback(ElementThermistorController * controller, void (*callback)(), enum ElementThermistorEvent event)
{
	switch(event)
	{
		case ElementThermistorHigh:
			if(controller->type == ElementThermistorOnOffControl)
				((ElementThermistorOnOffController*)controller)->temp_high_callback_reg = false;		
		break;
		case ElementThermistorLow:
			if(controller->type == ElementThermistorOnOffControl)
				((ElementThermistorOnOffController*)controller)->temp_low_callback_reg = false;		

		case ElementThermistorDirectCallback:

		if(controller->type == ElementThermistorPIDControl)
		{
			((ElementThermistorPIDController*)controller)->control_callback_reg = false;
		}
			
		break;
	}	
}

void ElementThermistorControl_activate_controller(ElementThermistorController * controller)
{
	
	controller->active = false;
	
	if(controller->type = ElementThermistorPIDControl)
	{
		// For PID controllers, we have to make sure to set it up to bumplessly transfer.
		
		// Set PV = SP. We need to make sure the controller is up to date for this.
		_calculate_controller_thermistor_temp(controller);
		
		((ElementThermistorPIDController*)controller)->previous_process_variable = controller->thermistor->current_temp;
		
		((ElementThermistorPIDController*)controller)->cur_derivative = 0;
		((ElementThermistorPIDController*)controller)->cur_integral = 0;
		
		((ElementThermistorPIDController*)controller)->control_output_bias = ((ElementThermistorPIDController*)controller)->control_output;
		
		((ElementThermistorPIDController*)controller)->last_update = MorphTime_millis();
		
		// Bumpless transfer stuff. Probably don't want?
		//controller->setpoint = controller->thermistor->current_temp;
//
		//// We need to run the loop once to get a current control output.
		//// Let's disable the callback for this.
				//
		//((ElementThermistorPIDController*)controller).cal
		//
		//
		//_process_pid_thermistor_controller(controller);
		//
		//
		//((ElementThermistorPIDController*)controller).control_output_bias
		//
	}
	
	controller->active = true;
	
}

void ElementThermistorControl_deactivate_controller(ElementThermistorController * controller)
{
	controller->active = false;
}