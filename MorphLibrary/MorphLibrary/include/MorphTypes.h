/*
 * MorphTypes.h
 *
 * Created: 11/30/2018 9:20:26 AM
 *  Author: 243400
 */ 


#ifndef MORPHTYPES_H_
#define MORPHTYPES_H_

//#define MORPH_IMPLICIT

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

enum MorphSPIClockPhase {MorphSPIClockLowIdle = 0, MorphSPIClockHighIdle = 1};

enum MorphSPIClockPolarity {MorphSPIClockPolarityStartIdle = 0, MorphSPIClockPolarityStartAsserted = 1};



#endif /* MORPHTYPES_H_ */