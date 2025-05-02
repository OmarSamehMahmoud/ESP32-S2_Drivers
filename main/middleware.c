#include "middleware.h"

// Includes required by Snippet 1
#include "MCAL/MCU_Config.h" // Provides tpin, GPIO_Output_Init, GPIO_Value_Tog
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Includes required by Snippet 2
// Provides tsbyte, t_uart_port, UART_Send_String, ESP_UART_NUM_0
#include "MCAL_ESP32_S2_SOLO_2_N4R2_UART.h"

// Note: Implementations for MCAL functions like GPIO_Output_Init,
// GPIO_Value_Tog, and UART_Send_String are NOT provided in the snippets.
// The code below calls these functions as they are used in the snippets,
// assuming their declarations are available via the included headers
// and their implementations are provided by the MCAL layer elsewhere.

/**
 * @brief Task to blink a specified GPIO pin every 500 milliseconds.
 *
 * @param arg The GPIO pin number (tpin) to blink, passed as a void pointer.
 */
void blink_gpio_task(void *arg)
{
    // Cast the argument to the tpin type
    tpin blink_pin = (tpin)(uint32_t)arg;

    // Initialize the GPIO pin as output with an initial state of low (0)
    // Uses the provided API
    GPIO_Output_Init(blink_pin, 0);

    // Infinite loop for blinking
    for (;;) {
        // Toggle the value of the GPIO pin
        // Uses the provided API
        GPIO_Value_Tog(blink_pin);

        // Delay for 500 milliseconds using the allowed FreeRTOS API
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    // Note: This task loop is infinite and should not be exited.
    // In a real application, if termination is needed, vTaskDelete(NULL)
    // would be called here.
    // vTaskDelete(NULL); // Reached only if the loop breaks, which it doesn't
}

/**
 * @brief Task to simulate blinking by sending messages via UART.
 *
 * This task sends "Blink ON" and "Blink OFF" messages over UART_NUM_0
 * with a 500ms delay between them, effectively creating a "blink"
 * indication on a connected serial console.
 *
 * @param pvParameters Task parameters (not used).
 */
void blink_task(void *pvParameters)
{
    // Messages to send for "ON" and "OFF" states
    // Assuming tsbyte is compatible with char for string literals
    const tsbyte* msg_on = (const tsbyte*)"Blink ON\n";
    const tsbyte* msg_off = (const tsbyte*)"Blink OFF\n";

    while (1) {
        // Send the "ON" message via UART0
        // Uses the provided API UART_Send_String
        // Assumes ESP_UART_NUM_0 is a valid t_uart_port value
        UART_Send_String(msg_on, ESP_UART_NUM_0);

        // Wait for 500 milliseconds
        // Uses the provided FreeRTOS API vTaskDelay
        vTaskDelay(pdMS_TO_TICKS(500));

        // Send the "OFF" message via UART0
        // Uses the provided API UART_Send_String
        UART_Send_String(msg_off, ESP_UART_NUM_0);

        // Wait for another 500 milliseconds before the next cycle
        // Uses the provided FreeRTOS API vTaskDelay
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
