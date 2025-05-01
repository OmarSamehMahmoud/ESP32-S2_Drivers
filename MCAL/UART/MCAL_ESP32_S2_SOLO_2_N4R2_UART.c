/* ********************************************************************************************************************
 * File Name      : MCAL_ESP32_S2_SOLO_2_N4R2_UART.c
 * Description    : UART Driver with Frame Handling for ESP32-S2
 * Author         : Omar Sameh
 * Company        : El-ARABY Research and Development Center
 * Device(s)      : ESP32_S2_SOLO_2_N4R2
 * Creation Date  : 17 August 2024
 *********************************************************************************************************************/

#include "MCAL_ESP32_S2_SOLO_2_N4R2_UART.h"

// Logger Tag
static const char *TAG = "MCAL_UART";

// UART buffer and state
static uint8_t uart_buffer[UART_BUF_SIZE];
static size_t  received_length = 0;

/**
 * @brief Initialize UART peripheral with specified settings.
 *
 * Configures and installs UART driver, sets pins, and applies parameters.
 *
 * @param port       UART port (t_uart_port)
 * @param baud_rate  Baud rate (t_baudrate)
 * @param data_bits  Data bits (t_data_bits)
 * @param parity     Parity configuration (t_uart_parity)
 * @param stop_bits  Stop bits (t_stop_bits)
 * @param flow_ctrl  Hardware flow control (t_uart_hw_flowcontrol)
 */
void UART_Init(t_uart_port port,
               t_baudrate       baud_rate,
               t_data_bits      data_bits,
               t_uart_parity    parity,
               t_stop_bits      stop_bits,
               t_uart_hw_flowcontrol flow_ctrl)
{
    uart_config_t config = {
        .baud_rate    = baud_rate,
        .data_bits    = data_bits,
        .parity       = parity,
        .stop_bits    = stop_bits,
        .flow_ctrl    = flow_ctrl
    };

    // Install and configure UART driver
    ESP_LOGI(TAG, "Installing UART driver on port %d", port);
    uart_driver_install(port, UART_BUF_SIZE, UART_BUF_SIZE, 0, NULL, 0);
    uart_param_config(port, &config);

    // Set TX/RX pins
    uart_set_pin(port,
                 (int)tx_pin != -1 ? (int)tx_pin : UART_PIN_NO_CHANGE,
                 (int)rx_pin != -1 ? (int)rx_pin : UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE);

    ESP_LOGI(TAG, "UART%u configured: %u bps, data bits %u, parity %u, stop bits %u",
             port, baud_rate, data_bits, parity, stop_bits);
}

/**
 * @brief Send a null-terminated string over UART.
 *
 * Blocks until entire string transmitted.
 *
 * @param data  Pointer to string data
 * @param port  UART port
 */
void UART_Send_String(const char *data,
                      t_uart_port  port)
{
    uart_write_bytes(port, data, strlen(data));
}

/**
 * @brief Send a single byte over UART.
 *
 * @param byte  Byte to send
 * @param port  UART port
 */
void UART_Send_Byte(uint8_t byte,
                    t_uart_port port)
{
    uart_write_bytes(port, (const char *)&byte, 1);
}

/**
 * @brief Receive bytes into internal buffer.
 *
 * Reads available bytes up to buffer size or timeout.
 *
 * @param port  UART port
 * @return Number of bytes read
 */
int UART_Receive_String(t_uart_port port)
{
    int len = uart_read_bytes(port,
                              uart_buffer + received_length,
                              UART_BUF_SIZE - received_length,
                              pdMS_TO_TICKS(T3_TIMEOUT_MS));
    if (len > 0) {
        received_length += len;
    }
    return len;
}

/**
 * @brief Receive a single byte (blocking).
 *
 * @param[out] byte  Pointer to store received byte
 * @param port       UART port
 */
void UART_Receive_Byte(uint8_t *byte,
                       t_uart_port  port)
{
    uart_read_bytes(port, byte, 1, portMAX_DELAY);
}

/**
 * @brief Calculate Frame Check Character (FCC) for a data frame.
 *
 * Sum all bytes, take two's complement.
 *
 * @param data   Pointer to data array
 * @param length Number of bytes
 * @return FCC byte
 */
uint8_t calculate_fcc(const uint8_t *data,
                      size_t length)
{
    uint16_t sum = 0;
    for (size_t i = 0; i < length; ++i) {
        sum += data[i];
    }
    return (uint8_t)(~sum + 1);
}
