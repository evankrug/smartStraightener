#include "ElementConfig.h"

#ifndef ELEMENTTIMER_H_
#define ELEMENTTIMER_H_

// Adds a timer to be managed.
void ElementTimer_push(ElementTimer * timer);

// Removes the last added timer.
ElementTimer * ElementTimer_pop();

// Processes all of the timers.
void ElementTimer_update();

// Registers a function to be a callback for a certain event on the supplied timer.
void ElementTimer_register_callback(ElementTimer * timer, void (*callback)(void), enum ElementTimerEvent event);

// Removes a function.
void ElementTimer_deregister_callback(ElementTimer * timer, enum ElementTimerEvent event);

// All timer specific functions //

void ElementTimer_start(ElementTimer * timer);

void ElementTimer_pause(ElementTimer * timer);

void ElementTimer_cancel(ElementTimer * timer);

MorphTimeValue ElementTimer_get_remaining_time(ElementTimer * timer);

void ElementTimer_set_duration(ElementTimer* timer, MorphTimeValue duration);

void ElementTimer_add_time(ElementTimer * timer, MorphTimeValue delta);


#endif