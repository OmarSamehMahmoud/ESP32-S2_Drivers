/******************************************************************************************************************************
File Name      : MCAL_ESP32_S2_SOLO_2_N4R2_UART.C
Description    : UART Driver for ESP32-S2 with Frame Handling
Author         : Omar Sameh
Device(s)      : ESP32_S2_SOLO_2_N4R2
Creation Date  : 17/08/2024
*********************************************************************************************************************************/
 
#include "MCAL_ESP32_S2_SOLO_2_N4R2_UART.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

uint8_t buffer[UART_BUF_SIZE];
size_t received_length = 0;

/**
* @brief Initializes the UART peripheral with the specified configuration.
*/
void UART_Init(t_uart_port port, t_baudrate baud_rate, t_data_bits data_bits,
               t_uart_parity parity, t_stop_bits stop_bits,
               t_uart_hw_flowcontrol flow_ctrl) {
    // Configure UART
    uart_config_t uart_config = {
        .baud_rate = baud_rate,
        .data_bits = data_bits,
        .parity    = parity,
        .stop_bits = stop_bits,
        .flow_ctrl = flow_ctrl
    };

    // Install UART
    uart_driver_install(port, UART_BUF_SIZE, UART_BUF_SIZE, 0, NULL, 0);
    uart_param_config(port, &uart_config);

    uart_set_pin(port, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}
 

void UART_Send_String(const tsbyte* data, t_uart_port port) {
    uart_write_bytes(port, data, strlen(data));
}

void UART_Send_Byte(const tbyte* data, t_uart_port port) {
    uart_write_bytes(port, (const tsbyte*)data, 1);
}

int UART_Receive_String(t_uart_port port) {
    tsword length = uart_read_bytes(ESP_UART_NUM_0, buffer + received_length, UART_BUF_SIZE - received_length, 5 / portTICK_PERIOD_MS);
    return length;
}

void UART_Receive_Byte(tbyte* buffer, t_uart_port port) {
    uart_read_bytes(port, buffer, 1, portMAX_DELAY);
}

uint8_t calculate_fcc(uint8_t *data, size_t length) {
    uint16_t sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += data[i];
    }
    return (uint8_t)(~sum + 1);
}







