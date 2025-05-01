/******************************************************************************************************************************
 File Name      : MCAL_ESP32_S2_SOLO_2_N4R2_WIFI.C
 Description    : This file as Header for (WIFI)
 Author         : Omar Sameh
 Tester         : 
 Device(s)      : ESP32_S2_SOLO_2_N4R2
 Creation Date  : 17/08/2024
 Testing Date   : 
*********************************************************************************************************************************/
#ifndef MCAL_ESP32_S2_SOLO_2_N4R2_WIFI_H_
#define MCAL_ESP32_S2_SOLO_2_N4R2_WIFI_H_

#include "../ESP32_S2_SOLO_2_N4R2_Main.h"
#include "esp_wifi.h"
#include "esp_wps.h"
#include "esp_ping.h"
#include "lwip/inet.h"
#include "lwip/ip4_addr.h"
#include "freertos/event_groups.h"
#include "nvs_flash.h"

/**
 * @brief Enumeration for WiFi TX modes.
 *
 * This enum defines the various TX modes that can be configured for WiFi.
 */
typedef enum {
    TX_MODE_11B_1MBPS_19_5DBM,   ///< 802.11b, 20 MHz, 1 Mbps, @19.5 dBm
    TX_MODE_11G_54MBPS_18DBM,    ///< 802.11g, 20 MHz, 54 Mbps, @18 dBm
    TX_MODE_11N_150MBPS_17_5DBM, ///< 802.11n, 40 MHz, 150 Mbps, @17.5 dBm
    TX_MODE_11N_40MHZ_16DBM      ///< 802.11n, 40 MHz, 72 Mbps, @16 dBm
} t_tx_mode;

// Function prototypes

/**
 * @brief Initializes the WiFi subsystem.
 *
 * This function sets up the WiFi driver and initializes necessary components
 * for WiFi communication. It includes creating the event loop and registering
 * event handlers for WiFi events.
 */
void WiFi_Init(void);

/**
 * @brief Connects to the specified WiFi network.
 *
 * This function configures the WiFi connection settings (SSID and password)
 * and attempts to connect to the WiFi network. It starts the WiFi driver
 * and initiates the connection process.
 */
void WiFi_Connect(const tsbyte *ssid, const tsbyte *password);

/**
 * @brief Enables the WiFi subsystem.
 *
 * This function starts the WiFi driver, enabling the WiFi subsystem for
 * communication. It allows the device to connect to a network and send/receive
 * data over WiFi.
 */
void WiFi_Enable(void);

/**
 * @brief Disables the WiFi subsystem.
 *
 * This function stops the WiFi driver, effectively disconnecting from any
 * connected network and halting WiFi communication.
 */
void WiFi_Disable(void);
/**
 * @brief Configures the TX mode for WiFi.
 *
 * This function allows you to configure the TX mode based on specific RF modes
 * like 802.11b with different power and bandwidth settings.
 *
 * t_tx_mode:
 * - TX_MODE_11B_1MBPS_19_5DBM: 802.11b, 20 MHz, 1 Mbps, @19.5 dBm
 *   - Advantages:
 *     1. High transmission power (19.5 dBm) ensures a strong signal.
 *   - Disadvantages:
 *     1. Highest power consumption (310 mA), leading to reduced battery life.
 *   - Indoor Range: 35 to 50 meters
 *   - Outdoor Range: 100 to 150 meters
 *
 * - TX_MODE_11G_54MBPS_18DBM: 802.11g, 20 MHz, 54 Mbps, @18 dBm
 *   - Advantages:
 *     1. Balanced power consumption with moderate range.
 *   - Disadvantages:
 *     1. Slightly lower power than 802.11b, which may reduce range slightly.
 *   - Indoor Range: 30 to 45 meters
 *   - Outdoor Range: 90 to 120 meters
 *
 * - TX_MODE_11N_150MBPS_17_5DBM: 802.11n, 40 MHz, 150 Mbps, @17.5 dBm
 *   - Advantages:
 *     1. Higher data rates suitable for modern applications.
 *   - Disadvantages:
 *     1. Slightly higher power consumption compared to 802.11g.
 *   - Indoor Range: 25 to 40 meters
 *   - Outdoor Range: 80 to 100 meters
 *
 * - TX_MODE_11N_40MHZ_16DBM: 802.11n, 40 MHz, 72 Mbps, @16 dBm
 *   - Advantages:
 *     1. Efficient power consumption with good range.
 *   - Disadvantages:
 *     1. Lower data rate compared to the other 802.11n mode.
 *   - Indoor Range: 20 to 35 meters
 *   - Outdoor Range: 70 to 90 meters
 *
 * @param mode The desired WiFi TX mode configuration.
 */
void WiFi_SetTxMode(t_tx_mode mode);
/**
 * @brief Checks the current WiFi connection status.
 *
 * This function determines whether the device is connected to a WiFi network.
 * If connected, it returns 1; otherwise, it returns 0.
 *
 * @return tsword 1 if connected to WiFi, 0 if not connected.
 */
tsword WiFi_Check_Connection(void);

void WiFi_WPS_Enable(void);

int WiFi_Check_Internet(void);

#endif /* MCAL_ESP32_S2_SOLO_2_N4R2_WIFI_H_ */
