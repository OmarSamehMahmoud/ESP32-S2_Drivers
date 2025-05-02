/******************************************************************************************************************************
 File Name      : MCAL_ESP32_S2_SOLO_2_N4R2_GPIO.H
 Description    : This file as Header for (GPIO)
 Author         : Omar Sameh
 Tester         : 
 Device(s)      : ESP32_S2_SOLO_2_N4R2
 Creation Date  : 16/08/2024
 Testing Date   : 
 @COPYRIGHT 2016 El-ARABY Research and development center.
 all rights reserved
*********************************************************************************************************************************/
#ifndef MCAL_ESP32S2_S2_SOLO_2_N4R2_GPIO_H_
#define MCAL_ESP32S2_S2_SOLO_2_N4R2_GPIO_H_

#include "../ESP32_S2_SOLO_2_N4R2_Main.h"

/**
 * @brief Enumeration for GPIO pins.
 *
 * This enum represents the GPIO pin numbers for the ESP32-S2.
 */
typedef enum {
    Pin_0,
    Pin_1,
    Pin_2,
    Pin_3,
    Pin_4,
    Pin_5,
    Pin_6,
    Pin_7,
    Pin_8,
    Pin_9,
    Pin_10,
    Pin_11,
    Pin_12,
    Pin_13,
    Pin_14,
    Pin_15,
    Pin_16,
    Pin_17,
    Pin_18,
    Pin_19,
    Pin_20,
    Pin_21, 
    Pin_26=26,
    Pin_27,
    Pin_28,   
    Pin_29,
    Pin_30,
    Pin_31,
    Pin_32,
    Pin_33,
    Pin_34,
    Pin_35,
    Pin_36,
    Pin_37,
    Pin_38,
    Pin_39,
    Pin_40,
    Pin_41,
    Pin_42,
    Pin_43,
    Pin_44,
    Pin_45,
    Pin_46, //Input only
} tpin;

/**
 * @brief Enumeration for GPIO direction.
 *
 * This enum defines the direction for the GPIO pin as either input or output.
 */
typedef enum {
    output = GPIO_MODE_OUTPUT,
    input = GPIO_MODE_INPUT
} t_direction;

/** Function Prototypes ===================================================================================================================*/

/**
 * @brief Initializes a GPIO pin as an output.
 *
 * This function configures a GPIO pin as an output and sets its initial value.
 *
 * @param pin The GPIO pin to initialize.
 * @param value The initial value to set for the pin.
 */
void GPIO_Output_Init(tpin pin, tlong value);

/**
 * @brief Initializes a GPIO pin as an input.
 *
 * This function configures a GPIO pin as an input.
 *
 * @param pin The GPIO pin to initialize.
 */
void GPIO_Input_Init(tpin pin);

/**
 * @brief Gets the direction of a GPIO pin.
 *
 * This function retrieves the current direction of a specified GPIO pin.
 *
 * @param pin The GPIO pin whose direction is to be retrieved.
 * @return t_direction The direction of the GPIO pin.
 */
t_direction GPIO_Direction_get(tpin pin);

/**
 * @brief Sets the value of a GPIO pin.
 *
 * This function sets the value of a specified GPIO pin.
 *
 * @param pin The GPIO pin to set.
 * @param value The value to set for the pin.
 */
void GPIO_Value_Set(tpin pin, tlong value);

/**
 * @brief Gets the value of a GPIO pin.
 *
 * This function retrieves the current value of a specified GPIO pin.
 *
 * @param pin The GPIO pin to read.
 * @return tlong The current value of the GPIO pin.
 */
tbyte GPIO_Value_Get(tpin pin);

/**
 * @brief Toggles the value of a GPIO pin.
 *
 * This function toggles the value of a specified GPIO pin.
 *
 * @param pin The GPIO pin to toggle.
 */
void GPIO_Value_Tog(tpin pin);

#endif /* MCAL_ESP32S2_GPIO_H_ */
