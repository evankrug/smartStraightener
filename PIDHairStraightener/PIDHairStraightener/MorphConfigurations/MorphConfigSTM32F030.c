/*
 * MorphConfigATmega328.c
 * 
 * This is an example configuration file for the ATmega328 chip from Atmel.
 *
 * Created: 11/15/2018 6:20:52 PM
 *  Author: 243400
 */

#ifdef ENABLE_STM32F030_CONFIG

#include "stm32f0xx.h"

#include <MorphGPIO.h>

#include <MorphConfig.h>

#include <MorphDMA.h>

#include <inttypes.h>

#include <stdbool.h>

#define PIN_COUNT 64

#define EVENTOUT           (uint8_t)0
#define MCO                (uint8_t)1
#define IR_OUT             (uint8_t)2
#define SWDIO              (uint8_t)3
#define SWCLK              (uint8_t)4
#define SCL                (uint8_t)5
#define SDA                (uint8_t)6
#define USART1_RX          (uint8_t)7
#define USART1_TX          (uint8_t)8
#define USART1_RTS         (uint8_t)9
#define USART1_CTS         (uint8_t)10
#define USART1_CK          (uint8_t)11
#define USART2_RX          (uint8_t)12
#define USART2_TX          (uint8_t)13
#define USART2_RTS         (uint8_t)14
#define USART2_CTS         (uint8_t)15
#define USART2_CK          (uint8_t)16
#define USART3_RX          (uint8_t)17
#define USART3_TX          (uint8_t)18
#define USART3_RTS         (uint8_t)19
#define USART3_CTS         (uint8_t)20
#define USART3_CK          (uint8_t)21
#define USART4_RX          (uint8_t)22
#define USART4_TX          (uint8_t)23
#define USART4_RTS         (uint8_t)24
#define USART4_CTS         (uint8_t)25
#define USART4_CK          (uint8_t)26
#define USART5_RX          (uint8_t)27
#define USART5_TX          (uint8_t)28
#define USART5_RTS         (uint8_t)29
#define USART5_CTS         (uint8_t)30
#define USART5_CK          (uint8_t)31
#define USART5_CK_RTS      (uint8_t)32
#define USART6_RX          (uint8_t)33
#define USART6_TX          (uint8_t)34
#define USART6_RTS         (uint8_t)35
#define USART6_CTS         (uint8_t)36
#define USART6_CK          (uint8_t)37
#define USART7_RX          (uint8_t)38
#define USART7_TX          (uint8_t)39
#define USART7_RTS         (uint8_t)40
#define USART7_CTS         (uint8_t)41
#define USART7_CK          (uint8_t)42
#define USART8_RX          (uint8_t)43
#define USART8_TX          (uint8_t)44
#define USART8_RTS         (uint8_t)45
#define USART8_CTS         (uint8_t)46
#define USART8_CK          (uint8_t)47
#define SPI1_MISO          (uint8_t)48
#define SPI1_MOSI          (uint8_t)49
#define SPI1_SCK           (uint8_t)50
#define SPI1_NSS           (uint8_t)51
#define SPI2_MISO          (uint8_t)52
#define SPI2_MOSI          (uint8_t)53
#define SPI2_SCK           (uint8_t)54
#define SPI2_NSS           (uint8_t)55
#define I2C1_SCL           (uint8_t)56
#define I2C1_SDA           (uint8_t)57
#define I2C1_SMBA          (uint8_t)58
#define I2C2_SCL           (uint8_t)59
#define I2C2_SDA           (uint8_t)60
#define TIM1_ETR           (uint8_t)61
#define TIM1_CH1           (uint8_t)62
#define TIM1_CH1N          (uint8_t)63
#define TIM1_CH2           (uint8_t)64
#define TIM1_CH2N          (uint8_t)65
#define TIM1_CH3           (uint8_t)66
#define TIM1_CH3N          (uint8_t)67
#define TIM1_CH4           (uint8_t)68
#define TIM1_BKIN          (uint8_t)69
#define TIM3_ETR           (uint8_t)70
#define TIM3_CH1           (uint8_t)71
#define TIM3_CH1N          (uint8_t)72
#define TIM3_CH2           (uint8_t)73
#define TIM3_CH2N          (uint8_t)74
#define TIM3_CH3           (uint8_t)75
#define TIM3_CH3N          (uint8_t)76
#define TIM3_CH4           (uint8_t)77
#define TIM3_BKIN          (uint8_t)78
#define TIM6_ETR           (uint8_t)79
#define TIM6_CH1           (uint8_t)80
#define TIM6_CH1N          (uint8_t)81
#define TIM6_CH2           (uint8_t)82
#define TIM6_CH2N          (uint8_t)83
#define TIM6_CH3           (uint8_t)84
#define TIM6_CH3N          (uint8_t)85
#define TIM6_CH4           (uint8_t)86
#define TIM6_BKIN          (uint8_t)87
#define TIM7_ETR           (uint8_t)88
#define TIM7_CH1           (uint8_t)89
#define TIM7_CH1N          (uint8_t)90
#define TIM7_CH2           (uint8_t)91
#define TIM7_CH2N          (uint8_t)92
#define TIM7_CH3           (uint8_t)93
#define TIM7_CH3N          (uint8_t)94
#define TIM7_CH4           (uint8_t)95
#define TIM7_BKIN          (uint8_t)96
#define TIM14_ETR          (uint8_t)97
#define TIM14_CH1          (uint8_t)98
#define TIM14_CH1N         (uint8_t)99
#define TIM14_CH2          (uint8_t)100
#define TIM14_CH2N         (uint8_t)101
#define TIM14_CH3          (uint8_t)102
#define TIM14_CH3N         (uint8_t)103
#define TIM14_CH4          (uint8_t)104
#define TIM14_BKIN         (uint8_t)105
//#define TIM15              (uint8_t)106
#define TIM15_ETR          (uint8_t)107
#define TIM15_CH1          (uint8_t)108
#define TIM15_CH1N         (uint8_t)109
#define TIM15_CH2          (uint8_t)110
#define TIM15_CH2N         (uint8_t)111
#define TIM15_CH3          (uint8_t)112
#define TIM15_CH3N         (uint8_t)113
#define TIM15_CH4          (uint8_t)114
#define TIM15_BKIN         (uint8_t)115
#define TIM16_ETR          (uint8_t)116
#define TIM16_CH1          (uint8_t)117
#define TIM16_CH1N         (uint8_t)118
#define TIM16_CH2          (uint8_t)119
#define TIM16_CH2N         (uint8_t)120
#define TIM16_CH3          (uint8_t)121
#define TIM16_CH3N         (uint8_t)122
#define TIM16_CH4          (uint8_t)123
#define TIM16_BKIN         (uint8_t)124
#define TIM17_ETR          (uint8_t)125
#define TIM17_CH1          (uint8_t)126
#define TIM17_CH1N         (uint8_t)127
#define TIM17_CH2          (uint8_t)128
#define TIM17_CH2N         (uint8_t)129
#define TIM17_CH3          (uint8_t)130
#define TIM17_CH3N         (uint8_t)131
#define TIM17_CH4          (uint8_t)132
#define TIM17_BKIN         (uint8_t)133

typedef struct morph_alt_mapping {

	uint8_t alt_function_num;
	uint8_t alt_type_num;

} MorphAltMapping;

typedef struct morph_pin_alt_mappings {
	uint8_t num_mappings;
	MorphAltMapping alt_mappings[];
} MorphAltPinMappings;

typedef struct morph_config_pin_def {
	int8_t pinGroup;
	int8_t pinNumInGroup;
	MorphAltPinMappings * alt_functions;

//	int8_t extIntUnit;
//	int8_t sercomUnit;
//	int8_t sercomPad;
//	int8_t sercomAltUnit;
//	int8_t sercomAltPad;
//	int8_t adcUnit;
} MorphConfigPinDefinition;

typedef struct uart_default_sercom_pads {
	MorphPinNumber tx_pin_num;
	MorphPinNumber rx_pin_num;
} UARTPinConfig;

typedef struct spi_default_sercom_pads {
	MorphPinNumber tx_pin_num;
	MorphPinNumber rx_pin_num;
	MorphPinNumber sck_pin_num;
} SPIPinConfig;

#if defined(STM32F030CCTx)

#pragma message "Using STM32F030CCTx Config"

MorphAltPinMappings PA0_mapping =  {.num_mappings = 2, .alt_mappings = { { 1, USART2_CTS },   { 4, USART4_TX },   }  };
MorphAltPinMappings PA1_mapping =  {.num_mappings = 4, .alt_mappings = {{ 0, EVENTOUT }, { 1, USART2_RTS },   { 4, USART4_RX }, { 5, TIM15_CH1N },  }  };
MorphAltPinMappings PA2_mapping =  {.num_mappings = 2, .alt_mappings = {{ 0, TIM15_CH1 }, { 1, USART2_TX },      }  };
MorphAltPinMappings PA3_mapping =  {.num_mappings = 2, .alt_mappings = {{ 0, TIM15_CH2 }, { 1, USART2_RX },      }  };
MorphAltPinMappings PA4_mapping =  {.num_mappings = 4, .alt_mappings = {{ 0, SPI1_NSS }, { 1, USART2_CK },   { 4, TIM14_CH1 }, { 5, USART6_TX },  }  };
MorphAltPinMappings PA5_mapping =  {.num_mappings = 2, .alt_mappings = {{ 0, SPI1_SCK },     { 5, USART6_RX },  }  };
MorphAltPinMappings PA6_mapping =  {.num_mappings = 6, .alt_mappings = {{ 0, SPI1_MISO }, { 1, TIM3_CH1 }, { 2, TIM1_BKIN },  { 4, USART3_CTS }, { 5, TIM16_CH1 }, { 6, EVENTOUT } }  };
MorphAltPinMappings PA7_mapping =  {.num_mappings = 6, .alt_mappings = {{ 0, SPI1_MOSI }, { 1, TIM3_CH2 }, { 2, TIM1_CH1N },  { 4, TIM14_CH1 }, { 5, TIM17_CH1 }, { 6, EVENTOUT } }  };
MorphAltPinMappings PA8_mapping =  {.num_mappings = 4, .alt_mappings = {{ 0, MCO }, { 1, USART1_CK }, { 2, TIM1_CH1N }, { 3, EVENTOUT },    }  };
MorphAltPinMappings PA9_mapping =  {.num_mappings = 5, .alt_mappings = {{ 0, TIM15_BKIN }, { 1, USART1_TX }, { 2, TIM1_CH2 },  { 4, I2C1_SCL }, { 5, MCO },  }  };
MorphAltPinMappings PA10_mapping = {.num_mappings = 4, .alt_mappings = {{ 0, TIM17_BKIN }, { 1, USART1_RX }, { 2, TIM1_CH3 },  { 4, I2C1_SDA },   }  };
MorphAltPinMappings PA11_mapping = {.num_mappings = 4, .alt_mappings = {{ 0, EVENTOUT }, { 1, USART1_CTS }, { 2, TIM1_CH4 },   { 5, SCL },  }  };
MorphAltPinMappings PA12_mapping = {.num_mappings = 4, .alt_mappings = {{ 0, EVENTOUT }, { 1, USART1_RTS }, { 2, TIM1_ETR },   { 5, SDA },  }  };
MorphAltPinMappings PA13_mapping = {.num_mappings = 2, .alt_mappings = {{ 0, SWDIO }, { 1, IR_OUT },      }  };
MorphAltPinMappings PA14_mapping = {.num_mappings = 2, .alt_mappings = {{ 0, SWCLK }, { 1, USART2_TX },      }  };
MorphAltPinMappings PA15_mapping = {.num_mappings = 4, .alt_mappings = {{ 0, SPI1_NSS }, { 1, USART2_RX },  { 3, EVENTOUT }, { 4, USART4_RTS },   }  };
MorphAltPinMappings PB0_mapping =  {.num_mappings = 4, .alt_mappings = {{ 0, EVENTOUT }, { 1, TIM3_CH3 }, { 2, TIM1_CH2N },  { 4, USART3_CK },   }  };
MorphAltPinMappings PB1_mapping =  {.num_mappings = 4, .alt_mappings = {{ 0, TIM14_CH1 }, { 1, TIM3_CH4 }, { 2, TIM1_CH3N },  { 4, USART3_RTS },   }  };
MorphAltPinMappings PB3_mapping =  {.num_mappings = 3, .alt_mappings = {{ 0, SPI1_SCK }, { 1, EVENTOUT },   { 4, USART5_TX },   }  };
MorphAltPinMappings PB4_mapping =  {.num_mappings = 5, .alt_mappings = {{ 0, SPI1_MISO }, { 1, TIM3_CH1 }, { 2, EVENTOUT },  { 4, USART5_RX }, { 5, TIM17_BKIN },  }  };
MorphAltPinMappings PB5_mapping =  {.num_mappings = 5, .alt_mappings = {{ 0, SPI1_MOSI }, { 1, TIM3_CH2 }, { 2, TIM16_BKIN }, { 3, I2C1_SMBA }, { 4, USART5_CK_RTS },   }  };
MorphAltPinMappings PB6_mapping =  {.num_mappings = 3, .alt_mappings = {{ 0, USART1_TX }, { 1, I2C1_SCL }, { 2, TIM16_CH1N },     }  };
MorphAltPinMappings PB7_mapping =  {.num_mappings = 4, .alt_mappings = {{ 0, USART1_RX }, { 1, I2C1_SDA }, { 2, TIM17_CH1N },  { 4, USART4_CTS },   }  };
MorphAltPinMappings PB8_mapping =  {.num_mappings = 2, .alt_mappings = { { 1, I2C1_SCL }, { 2, TIM16_CH1N },     }  };
MorphAltPinMappings PB9_mapping =  {.num_mappings = 5, .alt_mappings = {{ 0, IR_OUT }, { 1, I2C1_SDA }, { 2, TIM17_CH1N }, { 3, EVENTOUT },  { 5, SPI2_NSS },  }  };
MorphAltPinMappings PB10_mapping = {.num_mappings = 3, .alt_mappings = { { 1, I2C2_SCL },   { 4, USART3_TX }, { 5, SPI2_SCK },  }  };
MorphAltPinMappings PB11_mapping = {.num_mappings = 3, .alt_mappings = {{ 0, EVENTOUT }, { 1, I2C2_SDA },   { 4, USART3_RX },   }  };
MorphAltPinMappings PB12_mapping = {.num_mappings = 5, .alt_mappings = {{ 0, SPI2_NSS }, { 1, EVENTOUT }, { 2, TIM1_BKIN },  { 4, USART3_RTS }, { 5, TIM15 },  }  };
MorphAltPinMappings PB13_mapping = {.num_mappings = 4, .alt_mappings = {{ 0, SPI2_SCK },  { 2, TIM1_CH1N },  { 4, USART3_CTS }, { 5, I2C2_SCL },  }  };
MorphAltPinMappings PB14_mapping = {.num_mappings = 5, .alt_mappings = {{ 0, SPI1_MISO }, { 1, TIM15_CH1 }, { 2, TIM1_CH2N },  { 4, USART3_RTS }, { 5, I2C2_SDA },  }  };
MorphAltPinMappings PB15_mapping = {.num_mappings = 4, .alt_mappings = {{ 0, SPI2_MOSI }, { 1, TIM15_CH2 }, { 2, TIM1_CH3N }, { 3, TIM15_CH1N },    }  };
MorphAltPinMappings PC0_mapping =  {.num_mappings = 2, .alt_mappings = {{ 0, EVENTOUT },  { 2, USART6_TX },     }  };
MorphAltPinMappings PC1_mapping =  {.num_mappings = 2, .alt_mappings = {{ 0, EVENTOUT },  { 2, USART6_RX },     }  };
MorphAltPinMappings PC2_mapping =  {.num_mappings = 2, .alt_mappings = {{ 0, EVENTOUT }, { 1, SPI2_MISO },      }  };
MorphAltPinMappings PC3_mapping =  {.num_mappings = 2, .alt_mappings = {{ 0, EVENTOUT }, { 1, SPI2_MOSI },      }  };
MorphAltPinMappings PC4_mapping =  {.num_mappings = 2, .alt_mappings = {{ 0, EVENTOUT }, { 1, USART3_TX },      }  };
MorphAltPinMappings PC5_mapping =  {.num_mappings = 1, .alt_mappings = { { 1, USART3_RX },      }  };
MorphAltPinMappings PC6_mapping =  {.num_mappings = 1, .alt_mappings = {{ 0, TIM3_CH1 },       }  };
MorphAltPinMappings PC7_mapping =  {.num_mappings = 1, .alt_mappings = {{ 0, TIM3_CH2 },       }  };
MorphAltPinMappings PC8_mapping =  {.num_mappings = 1, .alt_mappings = {{ 0, TIM3_CH3 },       }  };
MorphAltPinMappings PC9_mapping =  {.num_mappings = 1, .alt_mappings = {{ 0, TIM3_CH4 },       }  };
MorphAltPinMappings PC10_mapping = {.num_mappings = 2, .alt_mappings = {{ 0, USART4_TX }, { 1, USART3_TX },      }  };
MorphAltPinMappings PC11_mapping = {.num_mappings = 2, .alt_mappings = {{ 0, USART4_RX }, { 1, USART3_RX },      }  };
MorphAltPinMappings PC12_mapping = {.num_mappings = 3, .alt_mappings = {{ 0, USART4_CK }, { 1, USART3_CK }, { 2, USART5_TX },     }  };
MorphAltPinMappings PD2_mapping =  {.num_mappings = 3, .alt_mappings = {{ 0, TIM3_ETR }, { 1, USART3_RTS }, { 2, USART5_RX },     }  };
MorphAltPinMappings PF0_mapping =  {.num_mappings = 1, .alt_mappings = { { 1, I2C1_SDA },      }  };
MorphAltPinMappings PF1_mapping =  {.num_mappings = 1, .alt_mappings = { { 1, I2C1_SCL },      }  };
MorphAltPinMappings PF4_mapping =  {.num_mappings = 1, .alt_mappings = {{ 0, EVENTOUT },       }  };
MorphAltPinMappings PF5_mapping =  {.num_mappings = 1, .alt_mappings = {{ 0, EVENTOUT },       }  };




MorphConfigPinDefinition pin_defs[] = {
		//Pin Group, Pin Number, sercomUnit, sercomPad, sercomAltUnit, sercomAltPad

		{ -1, -1, NULL },
		{ 2, 13, NULL },
		{ 2, 14, NULL },
		{ 2, 15, NULL },
		{ 5, 0, &PF0_mapping },
		{ 5, 1, &PF1_mapping },
		{ -1, -1, NULL },
		{ -1, -1, NULL },
		{ -1, -1, NULL },
		{ 0, 0, &PA0_mapping },
		{ 0, 1, &PA1_mapping },
		{ 0, 2, &PA2_mapping },
		{ 0, 3, &PA3_mapping },
		{ 0, 4, &PA4_mapping },
		{ 0, 5, &PA5_mapping },
		{ 0, 6, &PA6_mapping },
		{ 0, 7, &PA7_mapping },
		{ 1, 0, &PB0_mapping },
		{ 1, 1, &PB1_mapping },
		{ 1, 2, NULL },
		{ 1, 10, &PB10_mapping },
		{ 1, 11, &PB11_mapping },
		{ -1, -1, NULL},
		{ -1, -1, NULL},
		{ 1, 12, &PB12_mapping },
		{ 1, 13, &PB13_mapping },
		{ 1, 14, &PB14_mapping },
		{ 1, 15, &PB15_mapping },
		{ 0, 8, &PA8_mapping },
		{ 0, 9, &PA9_mapping },
		{ 0, 10, &PA10_mapping },
		{ 0, 11, &PA11_mapping },
		{ 0, 12, &PA12_mapping },
		{ 0, 13, &PA13_mapping },
		{ -1, -1, NULL},
		{ -1, -1, NULL},
		{ 0, 14, &PA14_mapping },
		{ 0, 15, &PA15_mapping },
		{ 1, 3, &PB3_mapping },
		{ 1, 4, &PB4_mapping },
		{ 1, 5, &PB5_mapping },
		{ 1, 6, &PB6_mapping },
		{ 1, 7, &PB7_mapping },
		{ -1, -1, NULL},
		{ 1, 8, &PB8_mapping },
		{ 1, 9, &PB9_mapping },
		{ -1, -1, NULL},
		{ -1, -1, NULL},

};

// All default configs use SERCOM pad 0 for TX and SERCOM pad 2 for RX.
UARTPinConfig uart_default_defs[] = { { 17, 19 }, //SERCOM 0
		{ 35, 37 }, //SERCOM 1
		{ 29, 31 }, //SERCOM 2
		{ 43, 45 }, //SERCOM 3
		{ 25, 27 }, //SERCOM 4
		{ 39, 41 }, //SERCOM 5
		};

// All default configs use SERCOM pad 0 for TX and SERCOM pad 3 for RX.
SPIPinConfig spi_default_defs[] = { { 17, 20 }, //SERCOM 0
		{ 35, 38 }, //SERCOM 1
		{ 29, 32 }, //SERCOM 2
		{ 43, 46 }, //SERCOM 3
		{ 25, 28 }, //SERCOM 4
		{ 39, 42 }, //SERCOM 5
		};

// This array maps adc channels to MorphPinNumbers.
MorphPinNumber adc_channel_defs[] = {

		3,  // AIN0
		4,  // AIN1
		11,	// AIN2
		12,	// AIN3
		13,	// AIN4
		14,	// AIN5
		15, // AIN6
		16, // AIN7
		61, // AIN8
		62, // AIN9
		63, // AIN10
		64, // AIN11
		5, // AIN12
		6, // AIN13
		9, // AIN14
		10, // AIN15
		17, // AIN16
		18, // AIN17
		19, // AIN18
		20, // AIN19

		};

#endif

enum PMUXTypes {
	EIC_PMUX = 0,
	ADC_PMUX = 1,
	SERCOM_PMUX = 2,
	SERCOM_ALT_PMUX = 3,
	TC_PMUX = 4,
	TCC_PMUX = 5,
	COM_PMUX = 6,
	GCLK_PMUX = 7
};

static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

uint32_t get_sysclk_frequency()
{
	uint32_t tmp = 0, pllmull = 0, pllsource = 0, prediv1factor = 0, pllclk = 0;

	/* Get SYSCLK source -------------------------------------------------------*/

	uint32_t output_frequency = HSI_VALUE;

	switch (RCC->CFGR & RCC_CFGR_SWS)
	{
	case 0x00:  /* HSI used as system clock */
	  output_frequency = HSI_VALUE;
	  break;
	case 0x04:  /* HSE used as system clock */
	  output_frequency = HSE_VALUE;
	  break;
	case 0x08:  /* PLL used as system clock */
	  /* Get PLL clock source and multiplication factor ----------------------*/
	  pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
	  pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
	  pllmull = ( pllmull >> 18) + 2;

	  if (pllsource == 0x00)
	  {
		/* HSI oscillator clock divided by 2 selected as PLL clock entry */
		pllclk = (HSI_VALUE >> 1) * pllmull;
	  }
	  else
	  {
		prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1;
		/* HSE oscillator clock selected as PREDIV1 clock entry */
		pllclk = (HSE_VALUE / prediv1factor) * pllmull;
	  }
	  output_frequency = pllclk;
	  break;
	case 0x0C:  /* HSI48 used as system clock */
		output_frequency = HSI48_VALUE;
	  break;
	default: /* HSI used as system clock */
		output_frequency = HSI_VALUE;
	  break;
	}

	return output_frequency;

}





uint32_t get_hclk_frequency()
{
	uint32_t presc = 0, tmp = 0;

	/* Get HCLK prescaler */
	tmp = RCC->CFGR & RCC_CFGR_HPRE;
	tmp = tmp >> 4;
	presc = APBAHBPrescTable[tmp];
	/* HCLK clock frequency */
	return get_sysclk_frequency() >> presc;

}

uint32_t get_pclk_frequency()
{
	uint32_t presc = 0, tmp = 0;

	/* Get PCLK prescaler */
	tmp = RCC->CFGR & RCC_CFGR_PPRE;
	tmp = tmp >> 8;
	presc = APBAHBPrescTable[tmp];
	/* PCLK clock frequency */
	return get_hclk_frequency() >> presc;
}


int8_t get_alt_funct_type(uint8_t pin_num, uint8_t alt_func_type)
{

	int8_t alt_fun_type = -1;

	if(pin_defs[pin_num - 1].alt_functions != NULL)
	{

		MorphConfigPinDefinition * pin_def = &pin_defs[pin_num - 1];

		MorphAltPinMappings * mappings = pin_def->alt_functions;

		uint8_t num_mappings = mappings->num_mappings;

		for(uint8_t i = 0; i < num_mappings; i++)
		{
			if(mappings->alt_mappings[i].alt_type_num == alt_func_type)
			{
				alt_fun_type = mappings->alt_mappings[i].alt_function_num;
			}
		}

	}

	return alt_fun_type;

}

GPIO_TypeDef * get_gpio_typedef(uint8_t pingroup_id) {

	switch (pingroup_id) {

#ifdef GPIOA

	case 0:

		return GPIOA;

		break;

#endif
#ifdef GPIOB
	case 1:

		return GPIOB;

		break;

#endif
#ifdef GPIOC
	case 2:

		return GPIOC;

		break;

#endif
#ifdef GPIOD
	case 3:

		return GPIOD;

		break;

#endif
#ifdef GPIOE
	case 4:

		return GPIOE;

		break;

#endif
#ifdef GPIOF
	case 5:

		return GPIOF;

		break;

#endif

	default:

		return GPIOA;

	}

}

void morph_config_gpio_set_pin_value(MorphPinNumber pn, enum MorphPinValue pv) {

	uint8_t value = (pv == High ? 1 : 0);

	if (pn >= 1 && pn <= PIN_COUNT && pin_defs[pn - 1].pinGroup >= 0) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[pn - 1].pinGroup);

		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;

		if (pin_num >= 0 && pin_num <= 15) {
			if (value == 1) {
				gpio_struct->BSRR |= (1ul << pin_num);
			} else {
				gpio_struct->BRR |= (1ul << pin_num);
			}
		}

	}

}

enum MorphPinValue morph_config_gpio_get_pin_value(MorphPinNumber pn) {

	enum MorphPinValue return_val = Low;

	if (pn >= 1 && pn <= PIN_COUNT && pin_defs[pn - 1].pinGroup >= 0) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[pn - 1].pinGroup);
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;

		if (pin_defs[pn - 1].pinGroup >= 0 && pin_num <= 15) {

			uint8_t pin_val = gpio_struct->IDR >> pin_num & 0x1;

			if (pin_val == 1)
				return_val = High;
			else
				return_val = Low;

		}

	}

	return return_val;

}

void morph_config_gpio_set_pin_direction(MorphPinNumber pn, enum MorphPinDirection pd) {

	if (pn >= 1 && pn <= PIN_COUNT && pin_defs[pn - 1].pinGroup >= 0) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[pn - 1].pinGroup);

		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;

		if (pin_num >= 0 && pin_num <= 15) {

			if (pd == Output) {
				// Make sure open-drain type is used on this pin.
				gpio_struct->OTYPER = (gpio_struct->OTYPER & ~(1ul << pin_num));

				uint32_t moder_reg = (gpio_struct->MODER & ~(0b11 << pin_num * 2))
								| (0b01 << pin_num * 2);

				// Set the pin mode to General purpose output mode.
				gpio_struct->MODER = moder_reg;

			} else {
				// This is an input!

				// Set the pin mode to input mode.
				gpio_struct->MODER = (gpio_struct->MODER & ~(0b11 << pin_num * 2));

			}

		}

	}

}

enum MorphPinDirection morph_config_gpio_get_pin_direction(MorphPinNumber pn) {

	enum MorphPinDirection return_pin_direction = Input;

	if (pn >= 1 && pn <= PIN_COUNT) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[pn - 1].pinGroup);
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;

		if (pin_defs[pn - 1].pinGroup >= 0 && pin_num >= 0 && pin_num <= 15) {

			uint8_t moder_val = (gpio_struct->MODER >> pin_num * 2) & 0b11;

			if (moder_val == 0b00 || moder_val == 0b10)
				return_pin_direction = Input;
			else if (moder_val == 0b01 || 0b11)
				return_pin_direction = Output;
			else
				return_pin_direction = Input;

		}

	}

	return return_pin_direction;

}

void morph_config_gpio_set_pin_pull_state(MorphPinNumber pn, enum MorphPinPullState ps) {

	if (pn >= 1 && pn <= PIN_COUNT) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[pn - 1].pinGroup);
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;

		if (pin_defs[pn - 1].pinGroup >= 0) {

			// These all need the input set
			// This will set the port for input.

			switch (ps) {

			case PullHigh:

				// Ensure the pullups are enabled.

				gpio_struct->PUPDR = (gpio_struct->PUPDR & ~(0b11 << pin_num * 2))
						| (0b01 << pin_num * 2);

				break;

			case PullLow:

				// Ensure the pulldowns are enabled.

				gpio_struct->PUPDR = (gpio_struct->PUPDR & ~(0b11 << pin_num * 2))
						| (0b10 << pin_num * 2);

				break;

			case PullNone:
			default:

				// Ensure pulling is disabled.

				gpio_struct->PUPDR = (gpio_struct->PUPDR & ~(0b11 << pin_num * 2));

			}

		}

	}

}

enum MorphPinPullState morph_config_gpio_get_pin_pull_state(MorphPinNumber pn) {

	enum MorphPinPullState pin_pull_val = PullNone;

	if (pn >= 1 && pn <= PIN_COUNT) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[pn - 1].pinGroup);
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;

		if (pin_defs[pn - 1].pinGroup >= 0) {

			uint8_t pupdr_val = (gpio_struct->PUPDR >> pin_num * 2) & 0b11;

			if (pupdr_val == 0b00)
				pin_pull_val = PullNone;
			if (pupdr_val == 0b01)
				pin_pull_val = PullHigh;
			if (pupdr_val == 0b10)
				pin_pull_val = PullLow;
			else
				pin_pull_val = PullNone;

		}

	}

	return pin_pull_val;

}

#define EXT_INT_COUNT 16

void (*pin_interrupt_functions[EXT_INT_COUNT])(void) = {&MorphUtils_empty_callback };

void EIC_Handler(void) {

//	// One of the interrupts did something.
//	// Figure out which one and call the function for it.
//	for(uint8_t i = 0; i < EXT_INT_COUNT; i++)
//	{
//		if(EIC->INTFLAG.reg & (0x1 << i) != 0)
//		{
//			pin_interrupt_functions[i]();
//			// Clear the flag by writing a 1 to it.
//			EIC->INTFLAG.reg = 0x1 << i;
//		}
//	}

}

void init_EIC() {

}

void morph_config_gpio_set_pin_interrupt(void (*function)(void), MorphPinNumber pn,
		enum MorphExternalInterruptType it) {

}


uint32_t get_uart_channel_frequency(MorphUARTChannel c)
{

	uint32_t cfgr3_mask = RCC_CFGR3_USART1SW;

	uint32_t cfgr3_mask_0 = RCC_CFGR3_USART1SW_0;
	uint32_t cfgr3_mask_1 = RCC_CFGR3_USART1SW_1;

	uint32_t uart_frequency = 0;

	/* USART1CLK clock frequency */
	if((RCC->CFGR3 & cfgr3_mask) == 0x0)
	{
		/* USART1 Clock is PCLK */
		uart_frequency = get_pclk_frequency();
	}
	else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == cfgr3_mask_0)
	{
		/* USART1 Clock is System Clock */
		uart_frequency = get_sysclk_frequency();
	}
	else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == cfgr3_mask_1)
	{
		/* USART1 Clock is LSE Osc. */
		uart_frequency = LSE_VALUE;
	}
	else if((RCC->CFGR3 & RCC_CFGR3_USART1SW) == cfgr3_mask)
	{
		/* USART1 Clock is HSI Osc. */
		uart_frequency = HSI_VALUE;
	}

	return uart_frequency;

}

USART_TypeDef * get_usart_typedef(uint8_t usart_id)
{

	USART_TypeDef * res_pointer = USART1;

	switch(usart_id)
	{
	case 1:

		res_pointer = USART1;

		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

		break;
	case 2:
		res_pointer = USART2;

		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

		break;
	case 3:
		res_pointer = USART3;

		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

		break;
	case 4:
		res_pointer = USART4;

		RCC->APB1ENR |= RCC_APB1ENR_USART4EN;

		break;
	case 5:
		res_pointer = USART5;

		RCC->APB1ENR |= RCC_APB1ENR_USART5EN;

		break;
	case 6:
		res_pointer = USART6;

		RCC->APB2ENR |= RCC_APB2ENR_USART6EN;

		break;
	case 7:
		res_pointer = USART7;
		break;
	case 8:
		res_pointer = USART8;
		break;

	}

	return res_pointer;

}

void morph_config_uart_setup_channel(MorphUARTChannel c, MorphUARTBaudRate br, MorphUARTByteSize bs,
		enum MorphUARTParity pc, MorphUARTStopBits sb) {

	USART_TypeDef * usart = get_usart_typedef(c);

	usart->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UE);

	uint32_t divider = 0, apbclock = 0, tmpreg = 0;

	/* Disable USART */
	usart->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UE);

	/*---------------------------- USART CR2 Configuration -----------------------*/
	tmpreg = usart->CR2;
	/* Clear STOP[13:12] bits */
	tmpreg &= (uint32_t)~((uint32_t)USART_CR2_STOP);

	/* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
	/* Set STOP[13:12] bits according to USART_StopBits value */
	if(sb == 2)
		tmpreg |= (uint32_t)USART_StopBits_2;
	else
		tmpreg |= (uint32_t)USART_StopBits_1;


	/* Write to USART CR2 */
	usart->CR2 = tmpreg;

	/*---------------------------- USART CR1 Configuration -----------------------*/
	tmpreg = usart->CR1;
	/* Clear M, PCE, PS, TE and RE bits */
	tmpreg &= (uint32_t)~((uint32_t)(USART_CR1_M | USART_CR1_PCE | \
            						USART_CR1_PS | USART_CR1_TE | \
									USART_CR1_RE));

	/* Configure the USART Word Length, Parity and mode ----------------------- */
	/* Set the M bits according to USART_WordLength value */
	/* Set PCE and PS bits according to USART_Parity value */
	/* Set TE and RE bits according to USART_Mode value */

	uint32_t word_length_mask = USART_WordLength_8b;

	if(bs == 8)
	{
		word_length_mask = USART_WordLength_8b;
	}
	else if(bs == 7)
	{
		word_length_mask = USART_WordLength_7b;
	}
	else if(bs == 9)
	{
		word_length_mask = USART_WordLength_9b;
	}
	else
	{
		// Assume 8 bits
		word_length_mask = USART_WordLength_8b;
	}

	uint32_t parity_mask = USART_Parity_No;

	if(pc == MorphNoParity)
	{
		parity_mask = USART_Parity_No;
	}
	else if(pc == MorphEvenParity)
	{
		parity_mask = USART_Parity_Even;
	}
	else if(pc == MorphOddParity)
	{
		parity_mask = USART_Parity_Odd;
	}

	// Combining options into register. Note: the mode is always RX and TX.
	tmpreg |= (uint32_t)word_length_mask | parity_mask | (USART_Mode_Rx | USART_Mode_Tx);

	/* Write to USART CR1 */
	usart->CR1 = tmpreg;

	/*---------------------------- USART CR3 Configuration -----------------------*/
	tmpreg = usart->CR3;
	/* Clear CTSE and RTSE bits */
	tmpreg &= (uint32_t)~((uint32_t)(USART_CR3_RTSE|USART_CR3_CTSE));

	/* Configure the USART HFC -------------------------------------------------*/
	/* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
	tmpreg |= (USART_HardwareFlowControl_None);

	/* Write to USART CR3 */
	usart->CR3 = tmpreg;

	/*---------------------------- USART BRR Configuration -----------------------*/
	/* Configure the USART Baud Rate -------------------------------------------*/

	if (usart == USART1)
	{
	apbclock = get_uart_channel_frequency(1);
	}
	else if (usart == USART2)
	{
	apbclock = get_uart_channel_frequency(2);
	}
	else if (usart == USART3)
	{
	apbclock = get_uart_channel_frequency(3);
	}
	else
	{
	apbclock = get_pclk_frequency();
	}

	/* Determine the integer part */
	if ((usart->CR1 & USART_CR1_OVER8) != 0)
	{
	/* (divider * 10) computing in case Oversampling mode is 8 Samples */
	divider = (uint32_t)((2 * apbclock) / (br));
	tmpreg  = (uint32_t)((2 * apbclock) % (br));
	}
	else /* if ((usart->CR1 & CR1_OVER8_Set) == 0) */
	{
	/* (divider * 10) computing in case Oversampling mode is 16 Samples */
	divider = (uint32_t)((apbclock) / (br));
	tmpreg  = (uint32_t)((apbclock) % (br));
	}

	/* round the divider : if fractional part i greater than 0.5 increment divider */
	if (tmpreg >=  (br) / 2)
	{
	divider++;
	}

	/* Implement the divider in case Oversampling mode is 8 Samples */
	if ((usart->CR1 & USART_CR1_OVER8) != 0)
	{
	/* get the LSB of divider and shift it to the right by 1 bit */
	tmpreg = (divider & (uint16_t)0x000F) >> 1;

	/* update the divider value */
	divider = (divider & (uint16_t)0xFFF0) | tmpreg;
	}

	/* Write to USART BRR */
	usart->BRR = (uint16_t)divider;

	/* Enable the USART interface */
	usart->CR1 |= (uint32_t)USART_CR1_UE;


}

// Disables the UART channel and returns it to its normal state (as GPIO pins or whatever default is).
void morph_config_uart_disable_channel(MorphUARTChannel c) {

}

// Will send the first n bytes of data depending on serial config.
void morph_config_uart_send_data(MorphUARTChannel c, MorphUARTData data) {

	USART_TypeDef * usart = get_usart_typedef(c);

	usart->TDR = (data & (uint16_t)0x01FF);

}

// Receives one frame of data. May be up to 9 bits. Bit manipulation is on the user.
MorphUARTData morph_config_uart_read_data(MorphUARTChannel c) {

	USART_TypeDef * usart = get_usart_typedef(c);

	/* Receive Data */
	return (uint16_t)(usart->RDR & (uint16_t)0x01FF);

}

// Will send the first n bytes of data depending on serial config.
// Does not support 9 bit frames.
void morph_config_uart_send_byte(MorphUARTChannel c, MorphUARTByte byte) {

	USART_TypeDef * usart = get_usart_typedef(c);

	usart->TDR = (byte & (uint16_t)0x01FF);

}

// Receives one frame of data.
// Only receives up to 8 bits.
MorphUARTByte morph_config_uart_read_byte(MorphUARTChannel c) {

	USART_TypeDef * usart = get_usart_typedef(c);

	/* Receive Data */
	return (uint8_t)(usart->RDR & (uint16_t)0x00FF);

}

// Writes a buffer to the UART channel. Will only use frames the size of the byte size configuration.
void morph_config_uart_write_data_buffer(MorphUARTChannel c, MorphUARTData * buffer, size_t length) {

}

// Writes a buffer to the UART channel. Will limit frame size to 8 bits.
void morph_config_uart_write_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer, size_t length) {

}

enum MorphUARTErrors morph_config_uart_read_data_buffer(MorphUARTChannel c, MorphUARTData * buffer,
		size_t length, MorphUARTTimeout timeout) {

}

enum MorphUARTErrors morph_config_uart_read_byte_buffer(MorphUARTChannel c, MorphUARTByte * buffer,
		size_t length, MorphUARTTimeout timeout) {

}

bool morph_config_uart_data_ready(MorphUARTChannel c) {

	USART_TypeDef * usart = get_usart_typedef(c);

	return (usart->ISR & USART_ISR_RXNE) != 0;

}

// Purges the input buffer
void morph_config_uart_purge_input(MorphUARTChannel c) {

}

void morph_config_uart_set_tx_pin(MorphUARTChannel c, MorphPinNumber p_tx) {

	int8_t alt_pin_function = -1;

	if (p_tx >= 1 && p_tx <= PIN_COUNT) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[p_tx - 1].pinGroup);
		int8_t pin_num = pin_defs[p_tx - 1].pinNumInGroup;

		switch(c)
		{

			case 1:

				alt_pin_function = get_alt_funct_type(p_tx, USART1_TX);

				break;

			case 2:

				alt_pin_function = get_alt_funct_type(p_tx, USART2_TX);

				break;

			case 3:

				alt_pin_function= get_alt_funct_type(p_tx, USART3_TX);

				break;

			case 4:

				alt_pin_function = get_alt_funct_type(p_tx, USART4_TX);

				break;

			case 5:

				alt_pin_function = get_alt_funct_type(p_tx, USART5_TX);

				break;

			case 6:

				alt_pin_function = get_alt_funct_type(p_tx, USART6_TX);

				break;

			case 7:

				alt_pin_function = get_alt_funct_type(p_tx, USART7_TX);

				break;

			case 8:

				alt_pin_function = get_alt_funct_type(p_tx, USART8_TX);


		}

		if(alt_pin_function != -1)
		{
			// We have a valid pin function. Switch to it.

			uint8_t low_high_reg = pin_num / 8;

			// This isolates the bits to be changed, clears them, and ORs the new value in.
			gpio_struct->AFR[low_high_reg] = (gpio_struct->AFR[low_high_reg] & ~(0xFFFF << ((pin_num % 8) * 4))) | (((uint8_t)alt_pin_function) & 0xF) << ((pin_num % 8) * 4);

			uint8_t pin_num_in_group = pin_defs[p_tx - 1].pinNumInGroup;

			// Change the pin's mode to the alternate function mode.
			gpio_struct->MODER = (gpio_struct->MODER & ~(0b11 << (pin_num_in_group * 2))) | (0b10 << pin_num_in_group * 2);

		}

	}

}

void morph_config_uart_set_rx_pin(MorphUARTChannel c, MorphPinNumber p_rx) {

	int8_t alt_pin_function = -1;

	if (p_rx >= 1 && p_rx <= PIN_COUNT) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[p_rx - 1].pinGroup);
		int8_t pin_num = pin_defs[p_rx - 1].pinNumInGroup;

		switch(c)
		{

			case 1:

				alt_pin_function = get_alt_funct_type(p_rx, USART1_RX);

				break;

			case 2:

				alt_pin_function = get_alt_funct_type(p_rx, USART2_RX);

				break;

			case 3:

				alt_pin_function= get_alt_funct_type(p_rx, USART3_RX);

				break;

			case 4:

				alt_pin_function = get_alt_funct_type(p_rx, USART4_RX);

				break;

			case 5:

				alt_pin_function = get_alt_funct_type(p_rx, USART5_RX);

				break;

			case 6:

				alt_pin_function = get_alt_funct_type(p_rx, USART6_RX);

				break;

			case 7:

				alt_pin_function = get_alt_funct_type(p_rx, USART7_RX);

				break;

			case 8:

				alt_pin_function = get_alt_funct_type(p_rx, USART8_RX);


		}

		if(alt_pin_function != -1)
		{
			// We have a valid pin function. Switch to it.

			uint8_t low_high_reg = pin_num / 8;

			// This isolates the bits to be changed, clears them, and ORs the new value in.
			gpio_struct->AFR[low_high_reg] = (gpio_struct->AFR[low_high_reg] & ~(0xFFFF << ((pin_num % 8) * 4))) | (((uint8_t)alt_pin_function) & 0xF) << ((pin_num % 8) * 4);

			uint8_t pin_num_in_group = pin_defs[p_rx - 1].pinNumInGroup;

			// Change the pin's mode to the alternate function mode.
			gpio_struct->MODER = (gpio_struct->MODER & ~(0b11 << (pin_num_in_group * 2))) | (0b10 << pin_num_in_group * 2);

		}

	}

}

void morph_config_uart_set_rts_pin(MorphUARTChannel c, MorphPinNumber p_rts) {
	int8_t alt_pin_function = -1;

	if (p_rts >= 1 && p_rts <= PIN_COUNT) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[p_rts - 1].pinGroup);
		int8_t pin_num = pin_defs[p_rts - 1].pinNumInGroup;

		switch(c)
		{

			case 1:

				alt_pin_function = get_alt_funct_type(p_rts, USART1_RTS);

				break;

			case 2:

				alt_pin_function = get_alt_funct_type(p_rts, USART2_RTS);

				break;

			case 3:

				alt_pin_function= get_alt_funct_type(p_rts, USART3_RTS);

				break;

			case 4:

				alt_pin_function = get_alt_funct_type(p_rts, USART4_RTS);

				break;

			case 5:

				alt_pin_function = get_alt_funct_type(p_rts, USART5_RTS);

				break;

			case 6:

				alt_pin_function = get_alt_funct_type(p_rts, USART6_RTS);

				break;

			case 7:

				alt_pin_function = get_alt_funct_type(p_rts, USART7_RTS);

				break;

			case 8:

				alt_pin_function = get_alt_funct_type(p_rts, USART8_RTS);


		}

		if(alt_pin_function != -1)
		{
			// We have a valid pin function. Switch to it.

			uint8_t low_high_reg = pin_num / 8;

			// This isolates the bits to be changed, clears them, and ORs the new value in.
			gpio_struct->AFR[low_high_reg] = (gpio_struct->AFR[low_high_reg] & ~(0xFFFF << ((pin_num % 8) * 4))) | (((uint8_t)alt_pin_function) & 0xF) << ((pin_num % 8) * 4);

			uint8_t pin_num_in_group = pin_defs[p_rts - 1].pinNumInGroup;

			// Change the pin's mode to the alternate function mode.
			gpio_struct->MODER = (gpio_struct->MODER & ~(0b11 << (pin_num_in_group * 2))) | (0b10 << pin_num_in_group * 2);

		}

	}
}

void morph_config_uart_set_cts_pin(MorphUARTChannel c, MorphPinNumber p_cts) {
	int8_t alt_pin_function = -1;

	if (p_cts >= 1 && p_cts <= PIN_COUNT) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[p_cts - 1].pinGroup);
		int8_t pin_num = pin_defs[p_cts - 1].pinNumInGroup;

		switch(c)
		{

			case 1:

				alt_pin_function = get_alt_funct_type(p_cts, USART1_CTS);

				break;

			case 2:

				alt_pin_function = get_alt_funct_type(p_cts, USART2_CTS);

				break;

			case 3:

				alt_pin_function= get_alt_funct_type(p_cts, USART3_CTS);

				break;

			case 4:

				alt_pin_function = get_alt_funct_type(p_cts, USART4_CTS);

				break;

			case 5:

				alt_pin_function = get_alt_funct_type(p_cts, USART5_CTS);

				break;

			case 6:

				alt_pin_function = get_alt_funct_type(p_cts, USART6_CTS);

				break;

			case 7:

				alt_pin_function = get_alt_funct_type(p_cts, USART7_CTS);

				break;

			case 8:

				alt_pin_function = get_alt_funct_type(p_cts, USART8_CTS);


		}

		if(alt_pin_function != -1)
		{
			// We have a valid pin function. Switch to it.

			uint8_t low_high_reg = pin_num / 8;

			// This isolates the bits to be changed, clears them, and ORs the new value in.
			gpio_struct->AFR[low_high_reg] = (gpio_struct->AFR[low_high_reg] & ~(0xFFFF << ((pin_num % 8) * 4))) | (((uint8_t)alt_pin_function) & 0xF) << ((pin_num % 8) * 4);

			uint8_t pin_num_in_group = pin_defs[p_cts - 1].pinNumInGroup;

			// Change the pin's mode to the alternate function mode.
			gpio_struct->MODER = (gpio_struct->MODER & ~(0b11 << (pin_num_in_group * 2))) | (0b10 << pin_num_in_group * 2);

		}

	}
}


SPI_TypeDef * get_spi_typedef(uint8_t usart_id)
{

	SPI_TypeDef * res_pointer = SPI1;

	switch(usart_id)
	{
	case 1:

		res_pointer = SPI1;

		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

		break;
	case 2:
		res_pointer = SPI2;

		RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

		break;

	}

	return res_pointer;

}

#define CR1_CLEAR_MASK       ((uint16_t)0x3040)
#define CR1_CLEAR_MASK2      ((uint16_t)0xFFFB)
#define CR2_LDMA_MASK        ((uint16_t)0x9FFF)

int16_t spi_baud_prescalers[] = {2, 4, 8, 16, 32, 64, 128, 256};

void morph_config_spi_init_master(MorphI2CChannel c, MorphSPIBaudRate br, enum MorphSPIClockPhase cpha, enum MorphSPIClockPolarity cpol)
{

	SPI_TypeDef * spi = get_spi_typedef(c);

	uint32_t tmpreg;

	/*-------------------------Data Size Configuration -----------------------*/
	/* Get the SPIx CR2 value */
	tmpreg = spi->CR2;
	/* Clear DS[3:0] bits */
	tmpreg &=(uint16_t)~SPI_CR2_DS;
	/* Configure SPIx: Data Size */
	tmpreg |= (uint16_t)((8 - 1) << 8); // We are doing 8 bits for the data size.
	/* Write to SPIx CR2 */
	spi->CR2 = tmpreg;

	/*---------------------------- SPIx CR1 Configuration ------------------------*/
	/* Get the SPIx CR1 value */
	tmpreg = spi->CR1;
	/* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, CPOL and CPHA bits */
	tmpreg &= CR1_CLEAR_MASK;
	/* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
	master/slave mode, CPOL and CPHA */
	/* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
	/* Set SSM, SSI bit according to SPI_NSS values */
	/* Set LSBFirst bit according to SPI_FirstBit value */
	/* Set BR bits according to SPI_BaudRatePrescaler value */
	/* Set CPOL bit according to SPI_CPOL value */
	/* Set CPHA bit according to SPI_CPHA value */

	if(cpol == MorphSPIClockLowIdle)
		tmpreg |= 0x0;
	else
		tmpreg |= SPI_CR1_CPOL;

	if(cpha == MorphSPIClockPolarityStartIdle)
		tmpreg |= 0x0;
	else
		tmpreg |= SPI_CR1_CPHA;


	int32_t baud_error = get_pclk_frequency();

	uint8_t baud_id = 0;

	/* Choose the closest baud rate that we can achieve */
	for(uint8_t i = 0; i < sizeof(spi_baud_prescalers); i++)
	{
		int32_t temp_error = br - (get_pclk_frequency() / spi_baud_prescalers[i]);

		if(temp_error < 0)
			temp_error *= -1;

		if(temp_error < baud_error)
		{
			baud_id = i;
			baud_error = temp_error;
		}
	}

	// We have found the prescaler that is closest to what we want.
	tmpreg |= baud_id << 3;

	// Software Slave Management.
	tmpreg |= SPI_CR1_SSM;

	tmpreg |= SPI_CR1_SSI;

	tmpreg |= SPI_CR1_MSTR;

	tmpreg |= SPI_CR1_SPE;

	/* Write to SPIx CR1 */
	spi->CR1 = tmpreg;




}

void morph_config_spi_init_slave(MorphI2CChannel c, enum MorphSPIClockPhase cpha, enum MorphSPIClockPolarity cpol)
{

}

MorphSPIByte morph_config_spi_read(MorphI2CChannel c)
{

	SPI_TypeDef * spi = get_spi_typedef(c);

	// Doing this lets us write to only the bottom 8 bits of the data register.
	// This will make the processor ignore the 8 MSB in the register.
	uint32_t spixbase = (uint32_t)spi;
	spixbase += 0x0C;

	return *(__IO uint8_t *) spixbase;

}

void morph_config_spi_write(MorphSPIChannel c, MorphSPIByte b)
{

	SPI_TypeDef * spi = get_spi_typedef(c);

	// Doing this lets us write to only the bottom 8 bits of the data register.
	// This will make the processor ignore the 8 MSB in the register.
	uint32_t spixbase = (uint32_t)spi;
	spixbase += 0x0C;

	 *(__IO uint8_t *) spixbase = b;

}

void morph_config_spi_set_data_out_pin(MorphSPIChannel c, MorphPinNumber pn)
{
	int8_t alt_pin_function = -1;

	if (pn >= 1 && pn <= PIN_COUNT) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[pn - 1].pinGroup);
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;

		switch(c)
		{

			case 1:

				alt_pin_function = get_alt_funct_type(pn, SPI1_MOSI);

				break;

			case 2:

				alt_pin_function = get_alt_funct_type(pn, SPI2_MOSI);

				break;

		}

		if(alt_pin_function != -1)
		{
			// We have a valid pin function. Switch to it.

			uint8_t low_high_reg = pin_num / 8;

			// This isolates the bits to be changed, clears them, and ORs the new value in.
			gpio_struct->AFR[low_high_reg] = (gpio_struct->AFR[low_high_reg] & ~(0xFFFF << ((pin_num % 8) * 4))) | (((uint8_t)alt_pin_function) & 0xF) << ((pin_num % 8) * 4);

			uint8_t pin_num_in_group = pin_defs[pn - 1].pinNumInGroup;

			// Change the pin's mode to the alternate function mode.
			gpio_struct->MODER = (gpio_struct->MODER & ~(0b11 << (pin_num_in_group * 2))) | (0b10 << pin_num_in_group * 2);

		}

	}
}

void morph_config_spi_set_data_in_pin(MorphSPIChannel c, MorphPinNumber pn)
{
	int8_t alt_pin_function = -1;

	if (pn >= 1 && pn <= PIN_COUNT) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[pn - 1].pinGroup);
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;

		switch(c)
		{

			case 1:

				alt_pin_function = get_alt_funct_type(pn, SPI1_MISO);

				break;

			case 2:

				alt_pin_function = get_alt_funct_type(pn, SPI2_MISO);

				break;

		}

		if(alt_pin_function != -1)
		{
			// We have a valid pin function. Switch to it.

			uint8_t low_high_reg = pin_num / 8;

			// This isolates the bits to be changed, clears them, and ORs the new value in.
			gpio_struct->AFR[low_high_reg] = (gpio_struct->AFR[low_high_reg] & ~(0xFFFF << ((pin_num % 8) * 4))) | (((uint8_t)alt_pin_function) & 0xF) << ((pin_num % 8) * 4);

			uint8_t pin_num_in_group = pin_defs[pn - 1].pinNumInGroup;

			// Change the pin's mode to the alternate function mode.
			gpio_struct->MODER = (gpio_struct->MODER & ~(0b11 << (pin_num_in_group * 2))) | (0b10 << pin_num_in_group * 2);

		}

	}
}

void morph_config_spi_set_sck_pin(MorphSPIChannel c, MorphPinNumber pn)
{
	int8_t alt_pin_function = -1;

	if (pn >= 1 && pn <= PIN_COUNT) {

		GPIO_TypeDef * gpio_struct = get_gpio_typedef(pin_defs[pn - 1].pinGroup);
		int8_t pin_num = pin_defs[pn - 1].pinNumInGroup;

		switch(c)
		{

			case 1:

				alt_pin_function = get_alt_funct_type(pn, SPI1_SCK);

				break;

			case 2:

				alt_pin_function = get_alt_funct_type(pn, SPI2_SCK);

				break;

		}

		if(alt_pin_function != -1)
		{
			// We have a valid pin function. Switch to it.

			uint8_t low_high_reg = pin_num / 8;

			// This isolates the bits to be changed, clears them, and ORs the new value in.
			gpio_struct->AFR[low_high_reg] = (gpio_struct->AFR[low_high_reg] & ~(0xFFFF << ((pin_num % 8) * 4))) | (((uint8_t)alt_pin_function) & 0xF) << ((pin_num % 8) * 4);

			uint8_t pin_num_in_group = pin_defs[pn - 1].pinNumInGroup;

			// Change the pin's mode to the alternate function mode.
			gpio_struct->MODER = (gpio_struct->MODER & ~(0b11 << (pin_num_in_group * 2))) | (0b10 << pin_num_in_group * 2);

		}

	}

}

// ---- DMA CONFIG BEGIN ----

DMA_TypeDef * get_morph_dma_unit(uint8_t unit)
{

	switch(unit)
	{
	case 0:
		return DMA1;

	case 1:
		return DMA2;

	default:
		return DMA1;

	}

}

DMA_Channel_TypeDef * get_morph_dma_channel(uint8_t unit, uint8_t channel)
{

	if(unit == 0)
	{
		switch(channel)
		{
		case 0:
			return DMA1_Channel1;

		case 1:
			return DMA1_Channel2;

		case 2:
			return DMA1_Channel3;

		case 3:
			return DMA1_Channel4;

		case 4:
			return DMA1_Channel5;

		case 5:
			return DMA1_Channel6;

		case 6:
			return DMA1_Channel7;

		default:
			return DMA1_Channel1;

		}

	}
	else
	{
		switch(channel)
		{
		case 0:
			return DMA2_Channel1;

		case 1:
			return DMA2_Channel2;

		case 2:
			return DMA2_Channel3;

		case 3:
			return DMA2_Channel4;

		case 4:
			return DMA2_Channel5;

		default:
			return DMA2_Channel1;

		}

	}
}

uint8_t get_morph_dma_selection(uint8_t channel, enum DMATransferTrigger trigger, uint8_t trigger_group)
{

	switch(channel)
	{
	case 1:
	case 2:
	case 3:
	case 4:

	case 5:
		break;
	}

}

void morph_config_dma_init(MorphDMAConfig * dma_config)
{
	RCC->AHBENR |= (RCC_AHBENR_DMAEN);

	DMA_TypeDef * dma_unit = get_morph_dma_unit(dma_config->dma_unit);

	DMA_Channel_TypeDef * dma_channel = get_morph_dma_channel(dma_config->dma_unit, dma_config->dma_channel);

	// Clear the channel
	dma_channel->CCR = 0x00;

	uint32_t tmpreg = 0;

	if(!dma_config->periph_transfer)
	{
		// This dma transfer type doesn't depend on triggers. This is memory to memory mode in STM32.
		tmpreg |= DMA_M2M_Enable;
	}

	switch(dma_config->dma_priority)
	{

	case DMAVeryHighPriority:

		tmpreg |= DMA_Priority_VeryHigh;

		break;

	case DMAHighPriority:

		tmpreg |= DMA_Priority_High;

		break;

	case DMAMediumPriority:

		tmpreg |= DMA_Priority_Medium;

		break;

	case DMALowPriority:
	default:

		tmpreg |= DMA_Priority_Low;

	}

	if(dma_config->data_size <= 8)
	{
		tmpreg |= DMA_MemoryDataSize_Byte;
		tmpreg |= DMA_PeripheralDataSize_Byte;
	}
	else if(dma_config->data_size <= 16)
	{
		tmpreg |= DMA_MemoryDataSize_HalfWord;
		tmpreg |= DMA_PeripheralDataSize_Byte;
	}
	else if(dma_config->data_size <= 32)
	{
		tmpreg |= DMA_MemoryDataSize_Word;
		tmpreg |= DMA_PeripheralDataSize_Byte;
	}

	// We are assuming the direction is going to the peripheral.
	// Setup dma to move from CMAR to CPAR.
	tmpreg |= DMA_DIR_PeripheralDST;

	dma_channel->CCR |= tmpreg;

	dma_channel->CNDTR = dma_config->transfer_count > 0xFFFF ? 0xFFFF : dma_config->transfer_count;

	if(dma_config->trigger == UART_RX_TRIGGER_DMA)
	{
		get_usart_typedef(dma_config->trigger_group_id)->CR3 |= USART_CR3_DMAR;
	}
	else if(dma_config->trigger == UART_TX_TRIGGER_DMA)
	{
		get_usart_typedef(dma_config->trigger_group_id)->CR3 |= USART_CR3_DMAT;
	}

	// We'll just assume STM32 DMA doesn't care about where it's reading from/writing to for now.
	dma_channel->CMAR = dma_config->dma_src_address;

	dma_channel->CPAR = dma_config->dma_dest_address;


//	if(dma_config->periph_transfer)
//	{
//		// We are transferring to/from a peripheral.
//		if(dma_config->is_periph_read)
//		{
//
//		}
//		else
//		{
//
//		}
//
//	}
//
//	if(dma_config->)
//	{
//
//	}
}

void morph_config_dma_enable_channel(uint8_t unit, uint8_t channel)
{

	DMA_Channel_TypeDef * dma_channel = get_morph_dma_channel(unit, channel);

	// Enable
	dma_channel->CCR |= DMA_CCR_EN;

}

void morph_config_dma_force_trigger(uint8_t channel)
{

}

// ---- DMA CONFIG END ----


void morph_config_init() {


	// Enable all of the GPIO peripherals.
	RCC->AHBENR |= (RCC_AHBENR_GPIOAEN);
	RCC->AHBENR |= (RCC_AHBENR_GPIOBEN);
	RCC->AHBENR |= (RCC_AHBENR_GPIOCEN);
	RCC->AHBENR |= (RCC_AHBENR_GPIODEN);
	RCC->AHBENR |= (RCC_AHBENR_GPIOEEN);
	RCC->AHBENR |= (RCC_AHBENR_GPIOFEN);




//	SYSCTRL->OSC8M.bit.PRESC = 0;	

//	SystemCoreClock = 8000000;

	NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 2); /* set Priority for Systick Interrupt (2nd lowest) */

	// Clock PORT for Digital I/O
	//  PM->APBBMASK.reg |= PM_APBBMASK_PORT ;
	//
	//  // Clock EIC for I/O interrupts
	//  PM->APBAMASK.reg |= PM_APBAMASK_EIC ;

	// Clock SERCOM for Serial
//	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0 | PM_APBCMASK_SERCOM1 | PM_APBCMASK_SERCOM2 | PM_APBCMASK_SERCOM3 | PM_APBCMASK_SERCOM4 | PM_APBCMASK_SERCOM5 ;
//
//	PM->APBAMASK.reg |= PM_APBAMASK_EIC;
//
}

void morph_implementation_test() {

	uint8_t i = 0;

	i++;

	i++;

	i++;

}

#endif
