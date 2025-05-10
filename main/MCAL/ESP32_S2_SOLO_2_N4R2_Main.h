/******************************************************************************************************************************
 File Name      : MCAL_General_Config.h
 Description    : This file as Header for (Device_Main)
 Author         : Omar Sameh
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
#include <stdbool.h>
#include <stdio.h>
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

#define GPIO_SAFEGUARD_Init() \
    do { \
        /* Set GPIO direction to input for all available pins on ESP32-S2 */ \
        gpio_config_t io_conf; \
        io_conf.intr_type = GPIO_INTR_DISABLE; \
        io_conf.mode = GPIO_MODE_INPUT; \
        io_conf.pin_bit_mask = ( \
            (1ULL << GPIO_NUM_0) | \
            (1ULL << GPIO_NUM_1) | \
            (1ULL << GPIO_NUM_2) | \
            (1ULL << GPIO_NUM_3) | \
            (1ULL << GPIO_NUM_4) | \
            (1ULL << GPIO_NUM_5) | \
            (1ULL << GPIO_NUM_6) | \
            (1ULL << GPIO_NUM_7) | \
            (1ULL << GPIO_NUM_8) | \
            (1ULL << GPIO_NUM_9) | \
            (1ULL << GPIO_NUM_10) | \
            (1ULL << GPIO_NUM_11) | \
            (1ULL << GPIO_NUM_12) | \
            (1ULL << GPIO_NUM_13) | \
            (1ULL << GPIO_NUM_14) | \
            (1ULL << GPIO_NUM_15) | \
            (1ULL << GPIO_NUM_16) | \
            (1ULL << GPIO_NUM_17) | \
            (1ULL << GPIO_NUM_18) | \
            (1ULL << GPIO_NUM_19) | \
            (1ULL << GPIO_NUM_20) | \
            (1ULL << GPIO_NUM_21) | \
            (1ULL << GPIO_NUM_26) | \
            (1ULL << GPIO_NUM_27) | \
            (1ULL << GPIO_NUM_28) | \
            (1ULL << GPIO_NUM_29) | \
            (1ULL << GPIO_NUM_30) | \
            (1ULL << GPIO_NUM_31) | \
            (1ULL << GPIO_NUM_32) | \
            (1ULL << GPIO_NUM_33) | \
            (1ULL << GPIO_NUM_34) | \
            (1ULL << GPIO_NUM_35) | \
            (1ULL << GPIO_NUM_36) | \
            (1ULL << GPIO_NUM_37) | \
            (1ULL << GPIO_NUM_38) | \
            (1ULL << GPIO_NUM_39) | \
            (1ULL << GPIO_NUM_40) | \
            (1ULL << GPIO_NUM_41) | \
            (1ULL << GPIO_NUM_42) | \
            (1ULL << GPIO_NUM_43) | \
            (1ULL << GPIO_NUM_44) | \
            (1ULL << GPIO_NUM_45) | \
            (1ULL << GPIO_NUM_46) \
        ); \
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; \
        io_conf.pull_up_en = GPIO_PULLUP_DISABLE; \
        gpio_config(&io_conf); \
    } while(0)

#define Registers_SAFEGUARD_Init() \
    do { \
        /* Disable ADC option */ \
        REG_WRITE(SENS_SAR_MEAS1_MUX_REG, 0); \
        REG_WRITE(SENS_SAR_MEAS2_MUX_REG, 0); \
        /* Disable clock for I2C, ADC, D/A (if applicable) */ \
        periph_module_disable(PERIPH_I2C0_MODULE); \
        periph_module_disable(PERIPH_I2C1_MODULE); \
        periph_module_disable(PERIPH_RMT_MODULE); \
    } while(0)


/*==============================================================================================================================*/
/*END*/
#endif
