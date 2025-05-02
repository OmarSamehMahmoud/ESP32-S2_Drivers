# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

idf_component_register(
    SRCS "GPIO/MCAL_ESP32_S2_SOLO_2_N4R2_GPIO.c" "WIFI/MCAL_ESP32_S2_SOLO_2_N4R2_WIFI.c" "NVS/MCAL_ESP32_S2_SOLO_2_N4R2_NVS.c" "UART/MCAL_ESP32_S2_SOLO_2_N4R2_UART.c"
    INCLUDE_DIRS "." 
    REQUIRES driver esp_wifi nvs_flash esp_wdt  esp_netif esp_ping
    
)

