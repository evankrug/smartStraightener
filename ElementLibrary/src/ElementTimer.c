#include "ElementTimer.h"

#include <MorphTime.h>

// Adds a timer to be managed.
void ElementTimer_push(ElementTimer * timer)
{

	if(master_timer_config.current_timer_count < TIMERS_MAX_COUNT)
	{
		master_timer_config.timer_array[master_timer_config.current_timer_count++] = timer;
	}

}

// Removes the last added timer.
ElementTimer * ElementTimer_pop()
{

	if(master_timer_config.current_timer_count > 0)
	{
		master_timer_config.current_timer_count--;
	}
	
}

// Processes all of the timers.
void ElementTimer_update()
{
	for(uint8_t i = 0; i < master_timer_config.current_timer_count; i++)
	{
		
		ElementTimer * timer = master_timer_config.timer_array[i];
		
		// Check for any trigger conditions.
		if(timer->is_paused && !timer->paused_callback_triggered && timer->paused_callback_reg)
		{
			// Trigger the paused callback
			timer->paused_callback();
			timer->paused_callback_triggered = true;
		}
		
		if(timer->is_canceled)
		{
			timer->is_running = false;
			timer->is_done = true;
			if(!timer->canceled_callback_triggered && timer->canceled_callback_reg)
			{
				// Trigger the canceled callback
				timer->canceled_callback();
				timer->canceled_callback_triggered = true;
			}
		}
	
		if(!timer->is_done && !timer->is_canceled)
		{
			// Are we done yet?
			if(ElementTimer_get_remaining_time(timer) <= 0)
			{
				// Now we are done.
				timer->is_done = true;

				// Make sure the timer is no longer running.
				// Doing this here lets the callback restart the timer.
				timer->is_running = false;
				
				if(timer->done_callback_reg)
				{
					timer->done_callback_triggered = true;
					timer->done_callback();
				}	
				

				
			}	
		}
		
	}
}

// Registers a function to be a callback for a certain event on the supplied timer.
void ElementTimer_register_callback(ElementTimer * timer, void (*callback)(void), enum ElementTimerEvent event)
{
	
	switch(event)
	{
		
		case ElementTimerDone:
		
			timer->done_callback = callback;
			timer->done_callback_reg = true;
		
		break;
		
		case ElementTimerPaused:

			timer->paused_callback = callback;
			timer->paused_callback_reg = true;
		
		break; 
		
		case ElementTimerCanceled:
	
			timer->canceled_callback = callback;
			timer->canceled_callback_reg = true;
		
		break;
		
	}
	
}

// Removes a function.
void ElementTimer_deregister_callback(ElementTimer * timer, enum ElementTimerEvent event)
{

	switch(event)
	{
		
		case ElementTimerDone:
	
		timer->done_callback_reg = false;
		
		break;
		
		case ElementTimerPaused:

		timer->paused_callback_reg = false;
		
		break;
		
		case ElementTimerCanceled:

		timer->canceled_callback_reg = false;
		
		break;
		
	}
	
}

// All timer specific functions //

void ElementTimer_start(ElementTimer * timer)
{
	
	if(!timer->is_paused)
	{
		// We need to move the total duration to the remaining duration.
		timer->remaining_duration = timer->total_duration;
	}

		
	// We just have to set the start_time to now.
	timer->start_time = MorphTime_millis();
		
	// Clean-up all the flags.
	timer->is_running = true; // The timer will be running now.
	timer->is_done = false; // The timer is not done.
	timer->is_canceled = false; // The timer is not canceled.
	timer->is_paused = false; // The timer is not paused.
	
	timer->done_callback_triggered = false;
	timer->canceled_callback_triggered = false;
	timer->paused_callback_triggered = false;
	
}

void ElementTimer_pause(ElementTimer * timer)
{
	// You can only pause if the timer isn't paused yet.
	if(!timer->is_paused)
	{
		
		// We have to store the current time away somewhere.
		MorphTimeValue remaining_time = timer->remaining_duration - (MorphTime_millis() - timer->start_time);
	
		// The timer is now paused.
		timer->is_paused = true;
		
		// The timer is not running.
		timer->is_running = true;
	
	}
	
}

void ElementTimer_cancel(ElementTimer * timer)
{
	timer->is_canceled = true;
}

MorphTimeValue ElementTimer_get_remaining_time(ElementTimer * timer)
{
	
	// We might not have caught the end yet!
	MorphTimeValue current_time = MorphTime_millis();
			
	MorphTimeValue delta_time = current_time - timer->start_time;
			
	MorphTimeValue remaining_time = timer->remaining_duration - delta_time;
			
	if(timer->is_running && remaining_time >= 0)
	{
		return remaining_time;
	}
	else if(timer->is_running && remaining_time < 0)
	{
		// The timer is probably actually done, it just hasn't updated yet.
		return 0;
	}
	else if(timer->is_done)
	{
		return 0;
	}
	else
	{
		return timer->remaining_duration;
	}
	
}

void ElementTimer_set_duration(ElementTimer* timer, MorphTimeValue duration)
{
	if(timer->is_running && timer->total_duration != timer->remaining_duration)
	{
		// This is a special case where the timer has already been through a pause. 
		// We need to find how much has already been done, then apply only the remaining.
		
		MorphTimeValue passed_time = timer->total_duration - timer->remaining_duration;
		
		timer->total_duration = duration;
		timer->remaining_duration = duration - passed_time;
		
	}	
	else
	{
		timer->total_duration = duration;
		timer->remaining_duration = duration;		
	}

	
}

void ElementTimer_add_time(ElementTimer * timer, MorphTimeValue delta)
{
	timer->remaining_duration += delta;
}