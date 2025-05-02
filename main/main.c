#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "middleware.h"

// Include MCAL header for specific pin definitions like Pin_2 and type tpin
// Assumes this header exists and defines these symbols.
#include "MCAL/MCU_Config.h"

// Note: The commented example in the snippet suggested UART_Init.
// This function is NOT provided in the snippets, so it is NOT included here.
// The system relies on the UART being initialized elsewhere if necessary.

void app_main(void)
{
    // Choose a pin to blink, for example Pin_2
    // Assumes Pin_2 and tpin are defined via MCAL/MCU_Config.h
    tpin led_pin = Pin_2;

    // Create the GPIO blinking task
    // Pass the pin number (casted to void*) as the argument to the task
    // Adjust stack size and priority as needed for your application
    // Uses standard FreeRTOS macros configMINIMAL_STACK_SIZE and tskIDLE_PRIORITY
    xTaskCreate(blink_gpio_task, "gpio_blink_task", configMINIMAL_STACK_SIZE * 2, (void *)(uint32_t)led_pin, tskIDLE_PRIORITY + 1, NULL);

    // Create the UART blinking task
    // Pass NULL as the argument as per the snippet's implementation
    // Adjust stack size and priority as needed
    xTaskCreate(blink_task, "uart_blink_task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // The FreeRTOS scheduler will start tasks once app_main completes.
    // In typical ESP-IDF, the scheduler is started automatically after app_main.
}
