/*
 * MorphI2C.h
 *
 * Created: 11/13/2018 3:20:33 PM
 *  Author: 243400
 */ 


#ifndef MORPHI2C_H_
#define MORPHI2C_H_


#include <stddef.h>
#include <stdbool.h>

#include "MorphTypes.h"
#include "MorphUtils.h"
#include "MorphOptions.h"



#ifndef MORPH_IMPLICIT

// MORPH_IMPLICIT means the functions will not be implemented with function pointers.
// Instead, it will call the (possibly) implemented functions directly.
// This is more dangerous, however it might see performance gains through compiler optimization.

// Initializes the I2C channel as a master.
void MorphI2C_register_init_master(void (*function)(MorphI2CChannel, MorphI2CBaudRate));

// Initializes the I2C channel as a slave.
void MorphI2C_register_init_slave(void (*function)(MorphI2CChannel));

// This function is used for starting a transmission from the master.
void MorphI2C_register_start_transmission(void (*function)(MorphI2CChannel, MorphI2CAddress, enum MorphI2CReadWrite));

// This function commits the entire buffer into the bus and general cleanup. This might not be necessary.
void MorphI2C_register_end_transmission(void (*function)(MorphI2CChannel));

// This function reads from the bus. Can be used for either slave or master.
void MorphI2C_register_read(MorphI2CByte (*function)(MorphI2CChannel));

// Writes a byte to the bus. May be used for either slave or master.
void MorphI2C_register_write(void (*function)(MorphI2CChannel, MorphI2CByte));

void MorphI2C_register_set_scl_pin(void (*function)(MorphI2CChannel, MorphPinNumber));

void MorphI2C_register_set_sda_pin(void (*function)(MorphI2CChannel, MorphPinNumber));


#endif

// FUNCTIONS! //

// Initializes the I2C channel as a master.
void MorphI2C_init_master(MorphI2CChannel c, MorphI2CBaudRate br);

// Initializes the I2C channel as a slave.
void MorphI2C_init_slave(MorphI2CChannel c);

// This function is used for starting a transmission from the master.
void MorphI2C_start_transmission(MorphI2CChannel c, MorphI2CAddress a, enum MorphI2CReadWrite rw);

// This function commits the entire buffer into the bus and general cleanup. This might not be necessary.
void MorphI2C_end_transmission(MorphI2CChannel c);

// This function reads from the bus. Can be used for either slave or master.
MorphI2CByte MorphI2C_read(MorphI2CChannel c);

// Writes a byte to the bus. May be used for either slave or master.
void MorphI2C_write(MorphI2CChannel c, MorphI2CByte b);

void MorphI2C_set_scl_pin(MorphI2CChannel c, MorphPinNumber pn);

void MorphI2C_set_sda_pin(MorphI2CChannel c, MorphPinNumber pn);

#endif /* MORPHI2C_H_ */