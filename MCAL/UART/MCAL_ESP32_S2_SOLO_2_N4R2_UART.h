/* ********************************************************************************************************************
 * File Name      : MCAL_ESP32_S2_SOLO_2_N4R2_UART.h
 * Description    : UART Driver Header for ESP32-S2
 * Author         : Omar Sameh
 * Company        : El-ARABY Research and Development Center
 * Device(s)      : ESP32_S2_SOLO_2_N4R2
 * Creation Date  : 17 August 2024
 * @COPYRIGHT 2025 El-ARABY R&D Center. All rights reserved.
 *********************************************************************************************************************/

#ifndef MCAL_ESP32_S2_SOLO_2_N4R2_UART_H_
#define MCAL_ESP32_S2_SOLO_2_N4R2_UART_H_

#include "../ESP32_S2_SOLO_2_N4R2_Main.h"

/** @brief Baud rate options for UART */
typedef enum {
    ESP_BAUD_9600   = 9600,
    ESP_BAUD_19200  = 19200,
    ESP_BAUD_38400  = 38400,
    ESP_BAUD_57600  = 57600,
    ESP_BAUD_115200 = 115200,
    ESP_BAUD_230400 = 230400,
    ESP_BAUD_460800 = 460800,
    ESP_BAUD_921600 = 921600,
    ESP_BAUD_1M     = 1000000,
    ESP_BAUD_2M     = 2000000,
    ESP_BAUD_4M     = 4000000
} t_baudrate;

/** @brief Data bits configuration */
typedef enum {
    ESP_DATA_5_BITS = UART_DATA_5_BITS,
    ESP_DATA_6_BITS = UART_DATA_6_BITS,
    ESP_DATA_7_BITS = UART_DATA_7_BITS,
    ESP_DATA_8_BITS = UART_DATA_8_BITS
} t_data_bits;

/** @brief Stop bits configuration */
typedef enum {
    ESP_STOP_BITS_1   = UART_STOP_BITS_1,
    ESP_STOP_BITS_1_5 = UART_STOP_BITS_1_5,
    ESP_STOP_BITS_2   = UART_STOP_BITS_2
} t_stop_bits;

/** @brief Parity configuration */
typedef enum {
    ESP_PARITY_DISABLE = UART_PARITY_DISABLE,
    ESP_PARITY_EVEN    = UART_PARITY_EVEN,
    ESP_PARITY_ODD     = UART_PARITY_ODD
} t_uart_parity;

/** @brief Hardware flow control options */
typedef enum {
    ESP_HW_FLOW_DISABLE = UART_HW_FLOWCTRL_DISABLE,
    ESP_HW_FLOW_RTS     = UART_HW_FLOWCTRL_RTS,
    ESP_HW_FLOW_CTS     = UART_HW_FLOWCTRL_CTS,
    ESP_HW_FLOW_CTS_RTS = UART_HW_FLOWCTRL_CTS_RTS
} t_uart_hw_flowcontrol;

/** @brief UART port selections */
typedef enum {
    ESP_UART_NUM_0 = UART_NUM_0,
    ESP_UART_NUM_1 = UART_NUM_1
} t_uart_port;

/** @brief GPIO pin selections for TX */
typedef enum {
    ESP_PIN_TX_NONE = -1,
    ESP_PIN_TX_1    = 1,
    ESP_PIN_TX_4    = 4,
    ESP_PIN_TX_10   = 10,
    ESP_PIN_TX_17   = 17,
    ESP_PIN_TX_21   = 21,
    ESP_PIN_TX_37   = 37,
    ESP_PIN_TX_43   = 43
} t_uart_tx_pin;

/** @brief GPIO pin selections for RX */
typedef enum {
    ESP_PIN_RX_NONE = -1,
    ESP_PIN_RX_3    = 3,
    ESP_PIN_RX_9    = 9,
    ESP_PIN_RX_18   = 18,
    ESP_PIN_RX_20   = 20,
    ESP_PIN_RX_36   = 36,
    ESP_PIN_RX_44   = 44
} t_uart_rx_pin;

// Configuration macros
#define MAX_RETRIES     3
#define UART_BUF_SIZE   1024
#define ACK             0x06
#define NAK             0x15
#define SHD             0xA5
#define T1_DELAY_MS     10
#define T2_DELAY_MS     10
#define T3_TIMEOUT_MS   200

#ifdef __cplusplus
extern "C" {
#endif

void UART_Init(t_uart_port port,
               t_baudrate baud_rate,
               t_data_bits data_bits,
               t_uart_parity parity,
               t_stop_bits stop_bits,
               t_uart_hw_flowcontrol flow_ctrl,
               t_uart_tx_pin tx_pin,
               t_uart_rx_pin rx_pin);

void UART_Send_String(const char *data, t_uart_port port);
int  UART_Receive_String(t_uart_port port);
void UART_Send_Byte(uint8_t byte, t_uart_port port);
void UART_Receive_Byte(uint8_t *byte, t_uart_port port);
uint8_t calculate_fcc(const uint8_t *data, size_t length);

#ifdef __cplusplus
}
#endif

#endif /* MCAL_ESP32_S2_SOLO_2_N4R2_UART_H_ */