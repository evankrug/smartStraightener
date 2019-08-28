/*
 * MorphI2C.c
 *
 * Created: 11/27/2018 3:49:01 PM
 *  Author: 243400
 */ 

#include "include/MorphUART.h"
#include "include/MorphUtils.h"
#include "include/MorphOptions.h"


#ifndef MORPH_IMPLICIT

void (*morph_init_master_function)(MorphI2CChannel, MorphI2CBaudRate) = &MorphUtils_empty_callback;

void (*morph_init_slave_function)(MorphI2CChannel) = &MorphUtils_empty_callback;

void (*morph_start_transmission_function)(MorphI2CChannel, MorphI2CAddress, enum MorphI2CReadWrite) = &MorphUtils_empty_callback;

void (*morph_end_transmission_function)(MorphI2CChannel) = &MorphUtils_empty_callback;

MorphI2CByte (*morph_i2c_read_function)(MorphI2CChannel) = &MorphUtils_empty_callback;

void (*morph_write_function)(MorphI2CChannel, MorphI2CByte) = &MorphUtils_empty_callback;

void (*morph_set_scl_pin_function)(MorphI2CChannel, MorphPinNumber) = &MorphUtils_empty_callback;

void (*morph_set_sda_pin_function)(MorphI2CChannel, MorphPinNumber) = &MorphUtils_empty_callback;

// Initializes the I2C channel as a master.
void MorphI2C_register_init_master(void (*function)(MorphI2CChannel, MorphI2CBaudRate))
{
	morph_init_master_function = function;
}

// Initializes the I2C channel as a slave.
void MorphI2C_register_init_slave(void (*function)(MorphI2CChannel))
{
	morph_init_slave_function = function;
}

// This function is used for starting a transmission from the master.
void MorphI2C_register_start_transmission(void (*function)(MorphI2CChannel, MorphI2CAddress, enum MorphI2CReadWrite))
{
	morph_start_transmission_function = function;
}

// This function commits the entire buffer into the bus and general cleanup. This might not be necessary.
void MorphI2C_register_end_transmission(void (*function)(MorphI2CChannel))
{
	morph_end_transmission_function = function;
}

// This function reads from the bus. Can be used for either slave or master.
void MorphI2C_register_read(MorphI2CByte (*function)(MorphI2CChannel))
{
	morph_i2c_read_function = function;
}

// Writes a byte to the bus. May be used for either slave or master.
void MorphI2C_register_write(void (*function)(MorphI2CChannel, MorphI2CByte))
{
	morph_write_function = function;
}

void MorphI2C_register_set_scl_pin(void (*function)(MorphI2CChannel, MorphPinNumber))
{
	morph_set_scl_pin_function = function;
}

void MorphI2C_register_set_sda_pin(void (*function)(MorphI2CChannel, MorphPinNumber))
{
	morph_set_sda_pin_function = function;
}

#endif

// FUNCTIONS! //

// Initializes the I2C channel as a master.
void MorphI2C_init_master(MorphI2CChannel c, MorphI2CBaudRate br)
{
	#ifdef MORPH_IMPLICIT
		morph_config_i2c_init_master(c, br);
	#else
		morph_init_master_function(c, br);
	#endif
}

// Initializes the I2C channel as a slave.
void MorphI2C_init_slave(MorphI2CChannel c)
{
	#ifdef MORPH_IMPLICIT
		morph_config_i2c_init_slave(c);
	#else
		morph_init_slave_function(c);
	#endif
}

// This function is used for starting a transmission from the master.
void MorphI2C_start_transmission(MorphI2CChannel c, MorphI2CAddress a, enum MorphI2CReadWrite rw)
{
	#ifdef MORPH_IMPLICIT
		morph_config_i2c_start_transmission(c, a, rw);
	#else
		morph_start_transmission_function(c, a, rw);
	#endif
}

// This function commits the entire buffer into the bus and general cleanup. This might not be necessary.
void MorphI2C_end_transmission(MorphI2CChannel c)
{
	#ifdef MORPH_IMPLICIT
		morph_config_i2c_end_transmission(c);
	#else
		morph_end_transmission_function(c);
	#endif
}

// This function reads from the bus. Can be used for either slave or master.
MorphI2CByte MorphI2C_read(MorphI2CChannel c)
{
	#ifdef MORPH_IMPLICIT
		return morph_config_i2c_read(c);
	#else
		return morph_read_function(c);
	#endif
}

// Writes a byte to the bus. May be used for either slave or master.
void MorphI2C_write(MorphI2CChannel c, MorphI2CByte b)
{

	#ifdef MORPH_IMPLICIT
		return morph_config_i2c_write(c, b);
	#else
		return morph_write_function(c, b);
	#endif	

}

void MorphI2C_set_scl_pin(MorphI2CChannel c, MorphPinNumber pn)
{
	#ifdef MORPH_IMPLICIT
	return morph_config_i2c_set_scl_pin(c, pn);
	#else
	return morph_set_scl_pin_function(c, pn);
	#endif	
}

void MorphI2C_set_sda_pin(MorphI2CChannel c, MorphPinNumber pn)
{
	#ifdef MORPH_IMPLICIT
	return morph_config_i2c_set_sda_pin(c, pn);
	#else
	return morph_set_sda_pin_function(c, pn);
	#endif	
}
