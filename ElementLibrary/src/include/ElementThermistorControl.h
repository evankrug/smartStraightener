#include "ElementConfig.h"

#ifndef ELEMENTTHERMISTORCONTROL_H_
#define ELEMENTTHERMISTORCONTROL_H_

#define ELEMENT_THERMISTOR_K_TO_C 273.15f

void ElementThermistorControl_update();

void ElementThermistorControl_push_thermistor(ElementThermistor * thermistor);

ElementThermistor * ElementThermistorControl_pop_thermistor();

void ElementThermistorControl_remove_all_thermistors();

void ElementThermistorControl_push_controller(ElementThermistorController * controller);

ElementThermistorOnOffController * ElementThermistorControl_pop_controller();

void ElementThermistorControl_remove_all_controllers();

void ElementThermistorControl_register_callback(ElementThermistorController * thermistor, void (*callback)(), enum ElementThermistorEvent event);

void ElementThermistorControl_deregister_callback(ElementThermistorController * thermistor, void (*callback)(), enum ElementThermistorEvent event);

void ElementThermistorControl_activate_controller(ElementThermistorController * controller);

void ElementThermistorControl_deactivate_controller(ElementThermistorController * controller);

#endif