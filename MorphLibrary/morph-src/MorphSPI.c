/*
 * MorphSPI.c
 *
 * Created: 11/27/2018 3:49:01 PM
 *  Author: 243400
 */ 

#include "include/MorphSPI.h"
#include "include/MorphUtils.h"
#include "include/MorphOptions.h"


#ifndef MORPH_IMPLICIT

void (*morph_spi_init_master_function)(MorphSPIChannel, MorphSPIBaudRate, enum MorphSPIClockPhase, enum MorphSPIClockPolarity) = &MorphUtils_empty_callback;

void (*morph_spi_init_slave_function)(MorphSPIChannel, enum MorphSPIClockPhase, enum MorphSPIClockPolarity) = &MorphUtils_empty_callback;

MorphSPIByte (*morph_spi_read_function)(MorphSPIChannel) = &MorphUtils_empty_callback;

void (*morph_spi_write_function)(MorphSPIChannel, MorphSPIByte) = &MorphUtils_empty_callback;

void (*morph_spi_set_data_out_pin_function)(MorphSPIChannel, MorphPinNumber) = &MorphUtils_empty_callback;

void (*morph_spi_set_data_in_pin_function)(MorphSPIChannel, MorphPinNumber) = &MorphUtils_empty_callback;

void (*morph_spi_set_sck_pin_function)(MorphSPIChannel, MorphPinNumber) = &MorphUtils_empty_callback;


void MorphSPI_register_init_master(void (*function)(MorphSPIChannel, MorphSPIBaudRate, enum MorphSPIClockPhase, enum MorphSPIClockPolarity))
{
	morph_spi_init_master_function = function;
}

void MorphSPI_register_init_slave(void (*function)(MorphSPIChannel, enum MorphSPIClockPhase, enum MorphSPIClockPolarity))
{
	morph_spi_init_slave_function = function;
}

// This function reads from the bus. Can be used for either slave or master.
void MorphSPI_register_read(MorphSPIByte (*function)(MorphSPIChannel))
{
	morph_spi_read_function = function;
}

// Writes a byte to the bus. May be used for either slave or master.
void MorphSPI_register_write(void (*function)(MorphSPIChannel, MorphSPIByte))
{
	morph_spi_write_function = function;
}

void MorphSPI_register_set_data_out_pin(void (*function)(MorphSPIChannel, MorphPinNumber))
{
	morph_spi_set_data_out_pin_function = function;
}

void MorphSPI_register_set_data_in_pin(void (*function)(MorphSPIChannel, MorphPinNumber))
{
	morph_spi_set_data_in_pin_function = function;
}

void MorphSPI_register_set_sck_pin(void (*function)(MorphSPIChannel, MorphPinNumber))
{
	morph_spi_set_sck_pin_function = function;
}

#endif

// FUNCTIONS! //

// Initializes the SPI channel as a master.
void MorphSPI_init_master(MorphSPIChannel c, MorphSPIBaudRate br, enum MorphSPIClockPhase cpha, enum MorphSPIClockPolarity cpol)
{
	#ifdef MORPH_IMPLICIT
		morph_config_spi_init_master(c, br, cpha, cpol);
	#else
		morph_spi_init_master_function(c, br, cpha, cpol);
	#endif
}

// Initializes the SPI channel as a slave.
void MorphSPI_init_slave(MorphSPIChannel c, enum MorphSPIClockPhase cpha, enum MorphSPIClockPolarity cpol)
{
	#ifdef MORPH_IMPLICIT
		morph_config_spi_init_slave(c, cpha, cpol);
	#else
		morph_spi_init_slave_function(c, cpha, cpol);
	#endif
}

// This function reads from the bus. Can be used for either slave or master.
MorphSPIByte MorphSPI_read(MorphSPIChannel c)
{
	#ifdef MORPH_IMPLICIT
		return morph_config_spi_read(c);
	#else
		return morph_spi_read_function(c);
	#endif
}

// Writes a byte to the bus. May be used for either slave or master.
void MorphSPI_write(MorphSPIChannel c, MorphSPIByte b)
{
	
	#ifdef MORPH_IMPLICIT
		return morph_config_spi_write(c, b);
	#else
		return morph_spi_write_function(c, b);
	#endif	

}

void MorphSPI_set_data_out_pin(MorphSPIChannel c, MorphPinNumber pn)
{
	#ifdef MORPH_IMPLICIT
		morph_config_spi_set_data_out_pin(c, pn);
	#else
		morph_spi_set_data_out_pin_function(c, pn);
	#endif	
}

void MorphSPI_set_data_in_pin(MorphSPIChannel c, MorphPinNumber pn)
{
	#ifdef MORPH_IMPLICIT
		morph_config_spi_set_data_in_pin(c, pn);
	#else
		morph_spi_set_data_in_pin_function(c, pn);
	#endif	
}

void MorphSPI_set_sck_pin(MorphSPIChannel c, MorphPinNumber pn)
{
	#ifdef MORPH_IMPLICIT
		morph_config_spi_set_sck_pin(c, pn);
	#else
		morph_spi_set_sck_pin_function(c, pn);
	#endif
}