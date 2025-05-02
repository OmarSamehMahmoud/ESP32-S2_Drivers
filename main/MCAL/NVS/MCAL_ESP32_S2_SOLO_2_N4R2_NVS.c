/******************************************************************************************************************************
 File Name      : MCAL_ESP32_S2_SOLO_2_N4R2_NVS.H
 Description    : This file as Header for (NVS)
 Author         : Omar Sameh
 Tester         :
 Device(s)      : ESP32_S2_SOLO_2_N4R2
 Creation Date  : 17/08/2024
 Testing Date   : 
 @COPYRIGHT 2016 El-ARABY Research and development center.
 all rights reserved
*********************************************************************************************************************************/
#include "MCAL_ESP32_S2_SOLO_2_N4R2_NVS.h"
// Initialize NVS
void NVS_Init(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

// Write an integer to NVS
void NVS_Write_Int(const tsbyte *key, tsword value) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err == ESP_OK) {
        err = nvs_set_i32(nvs_handle, key, value);
        if (err == ESP_OK) {
            nvs_commit(nvs_handle);
        }
        nvs_close(nvs_handle);
    }
    ESP_ERROR_CHECK(err);
}

// Read an integer from NVS
void NVS_Read_Int(const tsbyte *key, tsword *out_value) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs_handle);
    if (err == ESP_OK) {
        err = nvs_get_i32(nvs_handle, key, out_value);
        if (err == ESP_ERR_NVS_NOT_FOUND) {
            *out_value = 0; // Default value
        }
        nvs_close(nvs_handle);
    } else {
        *out_value = 0; // Default value
    }
}


// Write an array to NVS
void NVS_Write_Array(const tsbyte *key, tsword *data, size_t length) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err == ESP_OK) {
        err = nvs_set_blob(nvs_handle, key, data, length * sizeof(tsword));
        if (err == ESP_OK) {
            nvs_commit(nvs_handle);
        }
        nvs_close(nvs_handle);
    }
    ESP_ERROR_CHECK(err);
}

// Read an array from NVS
void NVS_Read_Array(const tsbyte *key, tsword *data, size_t length) {
    nvs_handle_t nvs_handle;
    size_t required_size = length * sizeof(tsword);
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs_handle);
    if (err == ESP_OK) {
        err = nvs_get_blob(nvs_handle, key, data, &required_size);
        if (err == ESP_ERR_NVS_NOT_FOUND) {
            memset(data, 0, required_size); // Default to zero if not found
        }
        nvs_close(nvs_handle);
    } else {
        memset(data, 0, required_size); // Default to zero if error
    }
}


// Write a string to NVS
void NVS_Write_String(const tsbyte *key, const tsbyte *value) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err == ESP_OK) {
        err = nvs_set_str(nvs_handle, key, value);
        if (err == ESP_OK) {
            nvs_commit(nvs_handle);
        }
        nvs_close(nvs_handle);
    }
    ESP_ERROR_CHECK(err);
}

// Read a string from NVS
void NVS_Read_String(const tsbyte *key, tsbyte *out_value, size_t max_length) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs_handle);
    if (err == ESP_OK) {
        err = nvs_get_str(nvs_handle, key, out_value, &max_length);
        if (err == ESP_ERR_NVS_NOT_FOUND) {
            strcpy(out_value, ""); // Default to empty string if not found
        }
        nvs_close(nvs_handle);
    } else {
        strcpy(out_value, ""); // Default to empty string if error
    }
}

void NVS_Erase_Key(const tsbyte *key) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err == ESP_OK) {
        err = nvs_erase_key(nvs_handle, key);
        if (err == ESP_OK) {
            nvs_commit(nvs_handle);
        }
        nvs_close(nvs_handle);
    }
    ESP_ERROR_CHECK(err);
}

