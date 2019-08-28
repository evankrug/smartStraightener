/*
 * MorphSPI.h
 *
 * Created: 11/13/2018 3:20:46 PM
 *  Author: 243400
 */ 


#ifndef MORPHSPI_H_
#define MORPHSPI_H_

#include "MorphTypes.h"

#ifndef MORPH_IMPLICIT

// MORPH_IMPLICIT means the functions will not be implemented with function pointers.
// Instead, it will call the (possibly) implemented functions directly.
// This is more dangerous, however it might see performance gains through compiler optimization.


void MorphSPI_register_init_master(void (*function)(MorphSPIChannel, MorphSPIBaudRate, enum MorphSPIClockPhase, enum MorphSPIClockPolarity));

void MorphSPI_register_init_slave(void (*function)(MorphSPIChannel, enum MorphSPIClockPhase, enum MorphSPIClockPolarity));

// This function reads from the bus. Can be used for either slave or master.
void MorphSPI_register_read(MorphSPIByte (*function)(MorphSPIChannel));

// Writes a byte to the bus. May be used for either slave or master.
void MorphSPI_register_write(void (*function)(MorphSPIChannel, MorphSPIByte));

void MorphSPI_register_set_data_out_pin(void (*function)(MorphSPIChannel, MorphPinNumber));

void MorphSPI_register_set_data_in_pin(void (*function)(MorphSPIChannel, MorphPinNumber));

void MorphSPI_register_set_sck_pin(void (*function)(MorphSPIChannel, MorphPinNumber));

#endif

// FUNCTIONS! //

// Initializes the SPI channel as a master.
void MorphSPI_init_master(MorphSPIChannel c, MorphSPIBaudRate br, enum MorphSPIClockPhase cpha, enum MorphSPIClockPolarity cpol);

// Initializes the SPI channel as a slave.
void MorphSPI_init_slave(MorphSPIChannel c, enum MorphSPIClockPhase cpha, enum MorphSPIClockPolarity cpol);

// This function reads from the bus. Can be used for either slave or master.
MorphSPIByte MorphSPI_read(MorphSPIChannel c);

// Writes a byte to the bus. May be used for either slave or master.
void MorphSPI_write(MorphSPIChannel c, MorphSPIByte b);

void MorphSPI_set_data_out_pin(MorphSPIChannel c, MorphPinNumber pn);  

void MorphSPI_set_data_in_pin(MorphSPIChannel c, MorphPinNumber pn);

void MorphSPI_set_sck_pin(MorphSPIChannel c, MorphPinNumber pn);  

#endif /* MORPHSPI_H_ */