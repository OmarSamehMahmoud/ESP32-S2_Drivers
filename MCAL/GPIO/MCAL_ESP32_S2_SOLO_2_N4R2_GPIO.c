/******************************************************************************************************************************
 File Name      : MCAL_ESP32_S2_SOLO_2_N4R2_GPIO.C
 Description    : This file as Header for (GPIO)
 Author         : Omar Sameh
 Tester         : 
 Device(s)      : ESP32_S2_SOLO_2_N4R2
 Creation Date  : 16/08/2024
 Testing Date   : 
*********************************************************************************************************************************/
#include "MCAL_ESP32_S2_SOLO_2_N4R2_GPIO.h"

// Static array to store the direction of each GPIO pin
static t_direction pin_directions[49]; // 49 pins available on ESP32-S2

/**
 * @brief Initializes a GPIO pin as an output and sets its initial value.
 *
 * This function configures a GPIO pin as an output. It disables interrupts for the pin,
 * and sets the initial output value based on the provided value. The direction of the pin 
 * is also tracked in the pin_directions array.
 *
 * @param pin The GPIO pin to initialize as output.
 * @param value The initial value to set for the pin (0 or 1).
 */
void GPIO_Output_Init(tpin pin, tlong value) {
    gpio_config_t io_conf;
    
    io_conf.intr_type = GPIO_INTR_DISABLE;        // Disable interrupts for this pin
    io_conf.mode = GPIO_MODE_OUTPUT;              // Set the pin as an output
    io_conf.pin_bit_mask = (1ULL << pin);         // Specify the pin using a bitmask
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // Disable pull-down resistor
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;     // Disable pull-up resistor

    gpio_config(&io_conf);                        // Apply the configuration
    GPIO_Value_Set(pin, value);                   // Set the initial value of the pin
    pin_directions[pin] = output;                 // Store the direction in the array
}

/**
 * @brief Initializes a GPIO pin as an input.
 *
 * This function configures a GPIO pin as an input. It disables interrupts for the pin,
 * enables the internal pull-up resistor, and tracks the direction of the pin.
 *
 * @param pin The GPIO pin to initialize as input.
 */
void GPIO_Input_Init(tpin pin) {
    gpio_config_t io_conf;
    
    io_conf.intr_type = GPIO_INTR_DISABLE;        // Disable interrupts for this pin
    io_conf.mode = GPIO_MODE_INPUT;               // Set the pin as an input
    io_conf.pin_bit_mask = (1ULL << pin);         // Specify the pin using a bitmask
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // Disable pull-down resistor
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;      // Enable pull-up resistor
    
    gpio_config(&io_conf);                        // Apply the configuration
    pin_directions[pin] = input;                  // Store the direction in the array
}

/**
 * @brief Retrieves the direction of a specified GPIO pin.
 *
 * This function returns the current direction (input or output) of a GPIO pin 
 * based on the stored direction in the pin_directions array.
 *
 * @param pin The GPIO pin whose direction is to be retrieved.
 * @return t_direction The direction of the specified GPIO pin.
 */
t_direction GPIO_Direction_get(tpin pin) {
    return pin_directions[pin]; // Return the stored direction
}

/**
 * @brief Sets the value of a GPIO pin.
 *
 * This function sets the output level of a specified GPIO pin.
 *
 * @param pin The GPIO pin to set the value for.
 * @param value The value to set for the pin (0 or 1).
 */
void GPIO_Value_Set(tpin pin, tlong value) {
    gpio_set_level(pin, value); // Set the pin to the specified value
}

/**
 * @brief Retrieves the current value of a GPIO pin.
 *
 * This function reads the current input level of a specified GPIO pin.
 *
 * @param pin The GPIO pin to read the value from.
 * @return tlong The current value of the GPIO pin (0 or 1).
 */
tbyte GPIO_Value_Get(tpin pin) {
    return gpio_get_level(pin); // Return the current value of the pin
}

/**
 * @brief Toggles the value of a GPIO pin.
 *
 * This function toggles the output level of a specified GPIO pin. If the current level is 0,
 * it will set it to 1, and if it is 1, it will set it to 0.
 *
 * @param pin The GPIO pin to toggle.
 */
void GPIO_Value_Tog(tpin pin) {
    tlong current_level = gpio_get_level(pin); // Get the current level of the pin
    gpio_set_level(pin, !current_level);       // Set the pin to the opposite level
}
