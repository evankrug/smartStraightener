/*
 * MorphTypes.h
 *
 * Created: 11/30/2018 9:20:26 AM
 *  Author: 243400
 */ 


#ifndef MORPHTYPES_H_
#define MORPHTYPES_H_

//#define MORPH_IMPLICIT

#include "stdint.h"
#include "stdbool.h"

// GPIO Types

enum MorphPinDirection {Input = 0, Output = 1};

enum MorphPinValue {Low = 0, High = 1};

enum MorphPinPullState {PullNone = 0, PullHigh = 1, PullLow = 2};

enum MorphExternalInterruptType {NoInterrupt = 0, RisingEdgeInterrupt = 1, FallingEdgeInterrupt = 2, DualEdgeInterrupt = 3, HighLevelInterrupt = 4, LowLevelInterrupt = 5};

typedef signed char MorphPinNumber;

// UART Types

typedef unsigned char MorphUARTChannel;

typedef unsigned long MorphUARTBaudRate;

typedef unsigned char MorphUARTByteSize;

typedef unsigned char MorphUARTStopBits;

typedef unsigned short MorphUARTData;

typedef unsigned char MorphUARTByte;

typedef signed long MorphUARTTimeout;

enum MorphUARTErrors {MORPH_UART_SUCCESS, MORPH_UART_TIMEOUT, MORPH_UART_UNKNOWN};

enum MorphUARTParity {MorphEvenParity = 0, MorphOddParity = 1, MorphNoParity = 2};

// Time types

typedef unsigned char MorphTimerNumber;

typedef signed long long MorphTimeValue;

// Timer types

// The timer of a certain resolution, if timers cannot change resolutions.
// If timers can change resolutions, then this is the global timer number.
typedef unsigned char MorphTimerNumber;

// The resolution. 
// Keeping this as a number allows configurations to define their own categories.
typedef unsigned char MorphTimerResolution;

// 

// The rate of interrupts in microseconds.
typedef unsigned long long MorphTimerRate;

// PWM Types

typedef unsigned char MorphPWMNumber;

typedef unsigned long MorphPWMDuty;

// The maximum value our duty cycle type can take.
#define MORPH_PWM_DUTY_MAX 0xFFFFFFFF

// ADC Types

typedef unsigned char MorphADCChannel;

typedef signed long MorphADCValue;

typedef unsigned char MorphADCResolution;

enum MorphADCReference {MorphADCInternalRef=0, MorphADCExternalRef=1};

// I2C Types

typedef unsigned char MorphI2CChannel;

typedef unsigned char MorphI2CByte;

typedef unsigned char MorphI2CAddress;

enum MorphI2CReadWrite {MorphI2CWrite=0, MorphI2CRead=1};

typedef unsigned long MorphI2CBaudRate;

// SPI Types

typedef unsigned char MorphSPIChannel;

typedef unsigned long MorphSPIBaudRate;

typedef unsigned char MorphSPIByte;

enum MorphSPIClockPolarity {MorphSPIClockLowIdle = 0, MorphSPIClockHighIdle = 1};

enum MorphSPIClockPhase {MorphSPIClockPolarityStartIdle = 0, MorphSPIClockPolarityStartAsserted = 1};

// DMA Types

enum DMATransferTrigger {NO_TRIGGER_DMA, SPI_RX_TRIGGER_DMA, SPI_TX_TRIGGER_DMA, I2C_RX_TRIGGER_DMA, I2C_TX_TRIGGER_DMA, UART_RX_TRIGGER_DMA, UART_TX_TRIGGER_DMA};

enum DMAPriority {DMALowPriority, DMAMediumPriority, DMAHighPriority, DMAVeryHighPriority};

typedef struct morph_dma_config{
uint8_t dma_unit; // Which dma unit will we be using?
uint8_t dma_channel; // Which channel is this?
enum DMAPriority dma_priority; // Which priority is this?
uint32_t dma_src_address;
uint32_t dma_dest_address;
uint16_t transfer_count;
uint8_t  data_size; // size of the data to be transfered in bits.
bool use_dma_complete_callback;
void (*transfer_complete_callback)();
bool use_dma_error_callback;
void (*transfer_error_callback)();
enum DMATransferTrigger trigger;
uint8_t trigger_group_id; // Used to identify sub-groups of triggers. For example, We want to start when SPI channel 0 receives a byte. This would be 0.
bool periph_transfer; // Is a peripheral involved at all? If this is false, the library can optimize for memory to memory transfers.
bool is_periph_read; // Is this reading from a peripheral?
bool step_source;   // Should the source be stepped
bool step_source_up; // Should the source be stepped up? (If false, will step down)
uint8_t source_step_size;
bool step_destination;
bool step_destination_up; // Should the increments be up or down?
uint8_t destination_step_size;
} MorphDMAConfig;


#endif /* MORPHTYPES_H_ */
