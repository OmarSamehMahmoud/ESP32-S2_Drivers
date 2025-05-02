/******************************************************************************************************************************
File Name      : MCAL_ESP32_S2_SOLO_2_N4R2_UART.C
Description    : This file as Header for (UART)
Author         : Omar Sameh
Tester         :
Device(s)      : ESP32_S2_SOLO_2_N4R2
Creation Date  : 17/08/2024
Testing Date   :
@COPYRIGHT 2016 El-ARABY Research and development center.
all rights reserved
*********************************************************************************************************************************/
#ifndef MCAL_ESP32_S2_SOLO_2_N4R2_UART_H_
#define MCAL_ESP32_S2_SOLO_2_N4R2_UART_H_
 
#include "../ESP32_S2_SOLO_2_N4R2_Main.h"
#include "driver/uart.h"
 
/**
* @brief Enumeration for UART used with the ESP32-S2.
*
* This enum defines UART used with the ESP32-S2.
*/
typedef enum {
    ESP_baudrate_9600 = 9600, //A standard baud rate used in many serial communication applications.
	ESP_baudrate_19200 = 19200,
	ESP_baudrate_38400 = 38400,
	ESP_baudrate_57600 = 57600,
	ESP_baudrate_115200 = 115200, //Commonly used for debugging and communication with development tools.
	ESP_baudrate_230400 = 230400,
	ESP_baudrate_460800 = 460800,
	ESP_baudrate_921600 = 921600, //Used for high-speed communication.
	ESP_baudrate_1Mbps = 1000000,
	ESP_baudrate_2Mbps = 2000000,
	ESP_baudrate_4Mbps = 4000000//The ESP32-S2 supports this maximum baud rate for UART.
} t_baudrate;
 
typedef enum {
    ESP_UART_DATA_5_BITS = 0x0,     // 5 data bits
    ESP_UART_DATA_6_BITS = 0x1,     // 6 data bits
    ESP_UART_DATA_7_BITS = 0x2,     // 7 data bits
    ESP_UART_DATA_8_BITS = 0x3      // 8 data bits (most commonly used)
} t_data_bits;
 
typedef enum {
    ESP_UART_STOP_BITS_1 = 0x1,     // 1 stop bit
    ESP_UART_STOP_BITS_1_5 = 0x2,   // 1.5 stop bits (may not be available on all devices)
    ESP_UART_STOP_BITS_2 = 0x3      // 2 stop bits
} t_stop_bits;
 
typedef enum {
    ESP_UART_PARITY_DISABLE = 0x0,  // No parity
    ESP_UART_PARITY_EVEN =  0x2,     // Even parity
    ESP_UART_PARITY_ODD = 0x3       // Odd parity
} t_uart_parity;
 
typedef enum {
    ESP_UART_HW_FLOWCTRL_DISABLE = 0x0,  // Disable hardware flow control (default)
    ESP_UART_HW_FLOWCTRL_RTS = 0x1,      // Enable RTS (Ready to Send) flow control
    ESP_UART_HW_FLOWCTRL_CTS = 0x2,      // Enable CTS (Clear to Send) flow control
    ESP_UART_HW_FLOWCTRL_CTS_RTS = 0x3   // Enable both CTS and RTS flow control
} t_uart_hw_flowcontrol;
 
typedef enum {
    ESP_UART_NUM_0 = 0,  // UART0 (default)
    ESP_UART_NUM_1 = 1,  // UART1
    ESP_UART_NUM_MAX     // Number of UART ports (used for validation or array sizing)
} t_uart_port;
 
typedef enum {
    ESP_UART0_TX_PIN_NONE = -1,  // No TX pin configured for UART0
    ESP_UART0_TX_PIN_1 = 1,      // GPIO1 as TX pin for UART0
    ESP_UART0_TX_PIN_43 = 43,    // GPIO43 as TX pin for UART0 (often used as default)
    ESP_UART0_TX_PIN_17 = 17,    // GPIO17 as TX pin for UART0
    ESP_UART0_TX_PIN_37 = 37,    // GPIO37 as TX pin for UART0
    ESP_UART1_TX_PIN_NONE = -1,  // No TX pin configured for UART1
    ESP_UART1_TX_PIN_4 = 4,    // GPIO4 as TX pin for UART1
    ESP_UART1_TX_PIN_10 = 10,    // GPIO10 as TX pin for UART1
    ESP_UART1_TX_PIN_17 = 17,    // GPIO17 as TX pin for UART1
    ESP_UART1_TX_PIN_21 = 21    // GPIO21 as TX pin for UART1
} t_uart_tx_pin;
 
typedef enum {
    ESP_UART0_RX_PIN_NONE = -1,  // No RX pin configured for UART0
    ESP_UART0_RX_PIN_3 = 3,      // GPIO3 as RX pin for UART0
    ESP_UART0_RX_PIN_44 = 44,    // GPIO44 as RX pin for UART0 (often used as default)
    ESP_UART0_RX_PIN_18 = 18,    // GPIO18 as RX pin for UART0
    ESP_UART0_RX_PIN_36 = 36,    // GPIO36 as RX pin for UART0
    ESP_UART1_RX_PIN_NONE = -1,  // No RX pin configured for UART1
    ESP_UART1_RX_PIN_9 = 9,      // GPIO9 as RX pin for UART1
    ESP_UART1_RX_PIN_18 = 18,    // GPIO18 as RX pin for UART1
    ESP_UART1_RX_PIN_20 = 20     // GPIO20 as RX pin for UART1
} t_uart_rx_pin;
 
 
// UART configuration parameters
#define MAX_RETRIES 3   // Maximum number of retransmissions
#define ACK 0x06        // Acknowledgment code
#define NAK 0x15        // Negative acknowledgment code
#define SHD 0xA5        // Service Header (example)
#define UART_BUF_SIZE 1024 // UART buffer size
#define T1_DELAY_MS  10   // Delay after sending frame (T1)
#define T2_DELAY_MS  10   // Delay before retrying (T2)
#define T3_TIMEOUT_MS 200 // Max wait time for response (T3)
 
/**
* @brief Initializes the UART peripheral with the specified configuration.
*
* This function configures the UART with the specified parameters including
* baud rate, data bits, parity, stop bits, flow control, TX/RX pins, and UART port number.
* It installs the UART driver to handle communication.
*
* @param port       The UART port number (use values from t_uart_port).
* @param baud_rate  The baud rate for UART communication (use values from t_baudrate).
* @param data_bits  The number of data bits (use values from t_data_bits).
* @param parity     The parity setting (use values from t_uart_parity).
* @param stop_bits  The number of stop bits (use values from t_stop_bits).
* @param flow_ctrl  The flow control setting (use values from t_uart_hw_flowcontrol).
* @param tx_pin     The TX pin for UART (use values from t_uart_tx_pin).
* @param rx_pin     The RX pin for UART (use values from t_uart_rx_pin).
*/
void UART_Init(t_uart_port port, t_baudrate baud_rate, t_data_bits data_bits,
               t_uart_parity parity, t_stop_bits stop_bits,
               t_uart_hw_flowcontrol flow_ctrl);
 
/**
* @brief Sends a null-terminated string over UART.
*
* This function transmits a string over UART. It blocks until the entire string
* has been sent. The string should be null-terminated.
*
* @param[in] data Pointer to the null-terminated string to be sent.
*/
void UART_Send_String(const tsbyte* data, t_uart_port port);
 
/**
* @brief Receives a string over UART.
*
* This function receives a string from the UART interface. It reads data until
* a newline character (`\n`) is encountered or the buffer is full. The received
* string is null-terminated.
*
* @param[out] buffer Pointer to the buffer where the received string will be stored.
*/
int UART_Receive_String(t_uart_port port) ;
 
/**
* @brief Sends a buffer of byte over UART.
*
* This function transmits a specified number of byte from a buffer over the UART.
*
* @param[in] data Pointer to the buffer containing the byte to be sent.
*/
void UART_Send_Byte(const tbyte* data, t_uart_port port);
 
/**
* @brief Receives a buffer of bytes over UART.
*
* This function receives a specified byte from the UART and stores them
* in the provided buffer.
*
* @param[out] buffer Pointer to the buffer where the received byte will be stored.
*/
void UART_Receive_Byte(tbyte* buffer, t_uart_port port);

uint8_t calculate_fcc(uint8_t *data, size_t length);
 
#endif /* MCAL_ESP32_S2_SOLO_2_N4R2_UART_H_ */