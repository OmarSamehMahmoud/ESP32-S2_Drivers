/******************************************************************************************************************************
 File Name      : MCAL_General_Config.h
 Description    : This file as Header for (Device_Main)
 Author         : Sherif Elgiar
 Tester         :
 Device(s)      : ESP32_S2_SOLO_2_N4R2
 Creation Date  : 31/07/2024
 Testing Date   :
 @COPYRIGHT 2016 El-ARABY Research and development center.
 all rights reserved
*********************************************************************************************************************************/
#ifndef MCAL_ESP32_S2_SOLO_2_N4R2_MAIN_H_
#define MCAL_ESP32_S2_SOLO_2_N4R2_MAIN_H_
/*==============================================================================================================================*/
/* Includes */
#pragma once
/*==================================*/
/* Core */

#include <errno.h>
#include <float.h>

#include <iso646.h>
#include <limits.h>
#include <math.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>  // Include for strchr and other string functions
#include <stdlib.h>  // Include for malloc, realloc, free
#include <stdio.h>   // Include for snprintf
#include <stddef.h>
#include <ctype.h>
#include "cJSON.h"
#include <pthread.h>
#include "esp_timer.h"

#include "driver/gpio.h"
#include "soc/io_mux_reg.h"
#include "driver/adc.h"
#include "driver/periph_ctrl.h"
#include "soc/sens_reg.h"

/*==============================================================================================================================*/
/* Data Types */

#define tbyte uint8_t
#define tword uint16_t
#define tlong uint32_t
#define tsbyte char
#define tsword int
#define tslong int32_t

/*==============================================================================================================================*/
/* Definitions */


/*==============================================================================================================================*/
/* BIT Math  */
#define SET_BIT(reg, bit)   ((reg) |= (1 << (bit)))  // Set a specific bit in a register
#define CLR_BIT(reg, bit)   ((reg) &= ~(1 << (bit))) // Clear a specific bit in a register
#define GET_BIT(reg, bit)   (((reg) >> (bit)) & 0x01) // Get the value of a specific bit in a register
#define TOG_BIT(reg, bit)   ((reg) ^= (1 << (bit)))  // Toggle a specific bit in a register

/*==============================================================================================================================*/
/* Safe_Guards  */
#define GPIO_SAFEGUARD_Init() do { \
    for (int i = 0; i < SOC_GPIO_PIN_COUNT; ++i) { \
        gpio_set_direction(i, GPIO_MODE_INPUT); \
    } \
} while(0)

#define Registers_SAFEGUARD_Init() do { \
    REG_WRITE(SYSTEM_PERIP_CLK_EN0_REG, 0x0); \
    REG_WRITE(SYSTEM_PERIP_CLK_EN1_REG, 0x0); \
} while(0)


/*==============================================================================================================================*/
/*END*/
#endif