#include "ElementConfig.h"

#ifndef ELEMENTDIRECTBUTTON_H_
#define ELEMENTDIRECTBUTTON_H_

void ElementDirectButton_init();

void ElementDirectButton_update();

void ElementDirectButton_register_button(uint8_t button_id, MorphPinNumber button_pin, enum MorphPinValue depressed_value, enum MorphPinPullState pull_state);

void ElementDirectButton_deregister_button(uint8_t button_id);

uint8_t ElementDirectButton_get_count();

uint8_t ElementDirectButton_get_max_count();

void ElementDirectButton_register_button_combo();

void ElementDirectButton_register_callback(void (*button_callback)(void), int8_t button_number, enum ElementButtonEvent event);

void ElementDirectButton_deregister_callback(int8_t button_number, enum ElementButtonEvent event);

void ElementDirectButton_deregister_all_callbacks();

uint8_t ElementDirectButton_get_combo_count();

uint8_t ElementDirectButton_get_max_combo_count();

void ElementDirectButton_register_combo(int8_t combo_id);

void ElementDirectButton_deregister_combo(int8_t combo_id);

void ElementDirectButton_set_combo_callback_time(int8_t combo_id, MorphTimeValue timeout);

void ElementDirectButton_register_combo_callback(int8_t combo_id, void (*combo_callback)(void));

void ElementDirectButton_deregister_combo_callback(int8_t combo_id);

void ElementDirectButton_add_button_to_combo(int8_t combo_id, int8_t button_id);

void ElementDirectButton_remove_button_from_combo(int8_t combo_id, int8_t button_id);



#endif 