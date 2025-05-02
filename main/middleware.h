#ifndef MIDDLEWARE_H
#define MIDDLEWARE_H

// Include FreeRTOS header for TaskFunction_t type used in task prototypes
#include "freertos/task.h"

/**
 * @brief Task to blink a specified GPIO pin every 500 milliseconds.
 *
 * This task initializes a GPIO as output and then repeatedly toggles
 * its value with a 500ms delay.
 *
 * @param arg The GPIO pin number (tpin) to blink, passed as a void pointer.
 */
void blink_gpio_task(void *arg);

/**
 * @brief Task to simulate blinking by sending messages via UART.
 *
 * This task sends "Blink ON" and "Blink OFF" messages over a specific
 * UART port (ESP_UART_NUM_0) with 500ms delays.
 *
 * @param pvParameters Task parameters (not used, expected to be NULL).
 */
void blink_task(void *pvParameters);

#endif // MIDDLEWARE_H
