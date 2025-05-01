/******************************************************************************************************************************
 File Name      : MCAL_ESP32_S2_SOLO_2_N4R2_WIFI.C
 Description    : This file as Header for (WIFI)
 Author         : Omar Sameh
 Tester         : 
 Device(s)      : ESP32_S2_SOLO_2_N4R2
 Creation Date  : 17/08/2024
 Testing Date   : 
*********************************************************************************************************************************/
#include "MCAL_ESP32_S2_SOLO_2_N4R2_WIFI.h"

static EventGroupHandle_t wifi_event_group; ///< Event group for WiFi events
const tsword WIFI_CONNECTED_BIT = BIT0;

/**
 * @brief Event handler for WiFi events.
 *
 * This function handles various WiFi events such as connection, disconnection,
 * and IP address acquisition. It updates the event group to reflect the current
 * state of the WiFi connection.
 *
 * @param arg Unused parameter.
 * @param event_base Event base for WiFi events.
 * @param event_id The ID of the event.
 * @param event_data Data associated with the event.
 */
static void wifi_event_handler(void* arg, esp_event_base_t event_base, tlong event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

/**
 * @brief Initializes the WiFi subsystem.
 *
 * This function sets up the WiFi subsystem by initializing the TCP/IP stack,
 * creating a default WiFi station, and setting up the WiFi driver. It also
 * creates an event group and registers event handlers for WiFi events.
 */
void WiFi_Init(void) {
    nvs_flash_init();
    
    // Initialize the TCP/IP stack
    esp_netif_init();

    // Create the default event loop
    esp_event_loop_create_default();

    // Create a default WiFi station (client)
    esp_netif_create_default_wifi_sta();

    // Initialize WiFi configuration
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    // Create an event group for WiFi events
    wifi_event_group = xEventGroupCreate();

    // Register event handlers for WiFi and IP events
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL);
}

/**
 * @brief Connects to the specified WiFi network.
 *
 * This function sets the WiFi mode to station and configures the WiFi settings
 * using the SSID and password defined in the configuration. It connects the WiFi
 * driver and initiates the connection process.
 */

void WiFi_Connect(const tsbyte *ssid, const tsbyte *password) {
    // Configure WiFi connection settings
    wifi_config_t wifi_config = {0}; // Initialize to zero to clear any garbage values
    strncpy((tsbyte *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid) - 1);
    strncpy((tsbyte *)wifi_config.sta.password, password, sizeof(wifi_config.sta.password) - 1);

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    esp_wifi_start();
    esp_wifi_connect();
   
    // Connect the WiFi driver
    esp_wifi_connect();
}



/**
 * @brief Enables the WiFi subsystem.
 *
 * This function starts the WiFi driver, allowing the device to connect to
 * a network and perform communication over WiFi.
 */
void WiFi_Enable(void) {
	// Connect the WiFi driver
    esp_wifi_connect();
    esp_wifi_start(); // Start the WiFi driver
}

/**
 * @brief Disables the WiFi subsystem.
 *
 * This function stops the WiFi driver, disconnecting from any connected network
 * and halting WiFi communication.
 */
void WiFi_Disable(void) {
    esp_wifi_stop(); // Stop the WiFi driver
}

/**
 * @brief Configures the TX mode for WiFi.
 *
 * This function allows you to configure the TX mode based on specific RF modes
 * like 802.11b with different power and bandwidth settings.
 *
 * @param mode The desired WiFi TX mode configuration.
 */
void WiFi_SetTxMode(t_tx_mode mode) {
    switch(mode) {
        case TX_MODE_11B_1MBPS_19_5DBM:
            // Set TX mode to 802.11b, 20 MHz, 1 Mbps, @19.5 dBm
            esp_wifi_set_protocol(ESP_IF_WIFI_STA, WIFI_PROTOCOL_11B);
            esp_wifi_set_bandwidth(ESP_IF_WIFI_STA, WIFI_BW_HT20);
            esp_wifi_set_max_tx_power(78); // Set power in units of 0.25 dBm (19.5 dBm * 4 = 78)
            break;
        
        case TX_MODE_11G_54MBPS_18DBM:
            // Set TX mode to 802.11g, 20 MHz, 54 Mbps, @18 dBm
            esp_wifi_set_protocol(ESP_IF_WIFI_STA, WIFI_PROTOCOL_11G);
            esp_wifi_set_bandwidth(ESP_IF_WIFI_STA, WIFI_BW_HT20);
            esp_wifi_set_max_tx_power(72); // 18 dBm * 4 = 72
            break;

        case TX_MODE_11N_150MBPS_17_5DBM:
            // Set TX mode to 802.11n, 40 MHz, 150 Mbps, @17.5 dBm
            esp_wifi_set_protocol(ESP_IF_WIFI_STA, WIFI_PROTOCOL_11N);
            esp_wifi_set_bandwidth(ESP_IF_WIFI_STA, WIFI_BW_HT40);
            esp_wifi_set_max_tx_power(70); // 17.5 dBm * 4 = 70
            break;

        case TX_MODE_11N_40MHZ_16DBM:
            // Set TX mode to 802.11n, 40 MHz, 72 Mbps, @16 dBm
            esp_wifi_set_protocol(ESP_IF_WIFI_STA, WIFI_PROTOCOL_11N);
            esp_wifi_set_bandwidth(ESP_IF_WIFI_STA, WIFI_BW_HT40);
            esp_wifi_set_max_tx_power(64); // 16 dBm * 4 = 64
            break;

        default:
            // Handle unsupported modes
            break;
    }
}
/**
 * @brief Checks the current WiFi connection status.
 *
 * This function determines whether the device is connected to a WiFi network.
 * If connected, it returns 1; otherwise, it returns 0.
 *
 * @return tsword 1 if connected to WiFi, 0 if not connected.
 */
tsword WiFi_Check_Connection(void) {
    wifi_ap_record_t ap_info; // Stores current access point info

    // Check if connected to a Wi-Fi network
    if (esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK) {
        return 1; // Connected
    } else {
        return 0; // Not connected
    }
}

void WiFi_WPS_Enable(void) {
    esp_wps_config_t wps_config = WPS_CONFIG_INIT_DEFAULT(WPS_TYPE_PBC);
    esp_wifi_wps_enable(&wps_config);
    esp_wifi_wps_start(0);  
}

int WiFi_Check_Internet(void) {
    ip4_addr_t target_ip;
    inet_aton("8.8.8.8", &target_ip); // Convert IP to struct

    // Set the target IP for ping
    if (esp_ping_set_target(PING_TARGET_IP_ADDRESS, &target_ip, sizeof(target_ip)) != ESP_OK) {
        return 0; // Failed to set target
    }

    uint32_t timeout_ms = 1000;
    esp_ping_set_target(PING_TARGET_RCV_TIMEO, &timeout_ms, sizeof(timeout_ms));

    // Set ping count to 1
    uint32_t count = 1;
    esp_ping_set_target(PING_TARGET_IP_ADDRESS_COUNT, &count, sizeof(count));

    vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for ping to execute

    esp_ping_found result;
    memset(&result, 0, sizeof(result));

    // Check ping results
    if (esp_ping_result(PING_RES_OK, result.bytes, result.resp_time) == ESP_OK) {
        return 1; // Internet is working
    }

    return 0; // No internet connection
}
