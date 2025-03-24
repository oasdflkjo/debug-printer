#include "esp_bt.h"
#include "esp_bt_device.h"
#include "esp_bt_main.h"
#include "esp_log.h"
#include "esp_spp_api.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include <stdio.h>
#include <string.h>

static const char *TAG = "HARDPANEL";
static uint32_t spp_handle = 0;

// Bluetooth SPP callback
static void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
    switch (event) {
    case ESP_SPP_INIT_EVT:
        ESP_LOGI(TAG, "SPP initialized");
        esp_spp_start_srv(ESP_SPP_SEC_AUTHENTICATE, ESP_SPP_ROLE_SLAVE, 0,
                          "HardPanel");
        break;

    case ESP_SPP_DISCOVERY_COMP_EVT:
        ESP_LOGI(TAG, "SPP discovery complete");
        break;

    case ESP_SPP_OPEN_EVT:
        ESP_LOGI(TAG, "SPP connection opened, handle: %d", param->open.handle);
        spp_handle = param->open.handle;
        break;

    case ESP_SPP_CLOSE_EVT:
        ESP_LOGI(TAG, "SPP connection closed, handle: %d", param->close.handle);
        if (spp_handle == param->close.handle) {
            spp_handle = 0;
        }
        break;

    case ESP_SPP_START_EVT:
        ESP_LOGI(TAG, "SPP server started");
        // Set device name
        esp_bt_dev_set_device_name("HardPanel");
        break;

    case ESP_SPP_CL_INIT_EVT:
        ESP_LOGI(TAG, "SPP client initialized");
        break;

    case ESP_SPP_DATA_IND_EVT:
        ESP_LOGI(TAG, "SPP data received, len=%d", param->data_ind.len);
        // Echo data back
        esp_spp_write(param->data_ind.handle, param->data_ind.len,
                      param->data_ind.data);
        break;

    default:
        break;
    }
}

// Task to send periodic messages
static void send_periodic_messages(void *arg) {
    const char *msg = "BT OK\r\n";
    int len = strlen(msg);

    while (1) {
        if (spp_handle) {
            ESP_LOGI(TAG, "Sending: %s", msg);
            esp_err_t err = esp_spp_write(spp_handle, len, (uint8_t *)msg);
            if (err != ESP_OK) {
                ESP_LOGE(TAG, "Failed to send data: %d", err);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void) {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "Initializing Bluetooth...");

    // Initialize Bluetooth
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_BLE));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if (esp_bt_controller_init(&bt_cfg) != ESP_OK) {
        ESP_LOGE(TAG, "Bluetooth controller init failed");
        return;
    }

    if (esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT) != ESP_OK) {
        ESP_LOGE(TAG, "Bluetooth controller enable failed");
        return;
    }

    if (esp_bluedroid_init() != ESP_OK) {
        ESP_LOGE(TAG, "Bluedroid init failed");
        return;
    }

    if (esp_bluedroid_enable() != ESP_OK) {
        ESP_LOGE(TAG, "Bluedroid enable failed");
        return;
    }

    // Set discoverable and connectable mode
    if (esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE,
                                 ESP_BT_GENERAL_DISCOVERABLE) != ESP_OK) {
        ESP_LOGE(TAG, "Set scan mode failed");
        return;
    }

    // Initialize SPP
    if (esp_spp_register_callback(esp_spp_cb) != ESP_OK) {
        ESP_LOGE(TAG, "SPP register callback failed");
        return;
    }

    if (esp_spp_init(ESP_SPP_MODE_CB) != ESP_OK) {
        ESP_LOGE(TAG, "SPP init failed");
        return;
    }

    // Print device address
    const uint8_t *addr = esp_bt_dev_get_address();
    ESP_LOGI(TAG, "Device address: %02x:%02x:%02x:%02x:%02x:%02x", addr[0],
             addr[1], addr[2], addr[3], addr[4], addr[5]);

    // Create task to send periodic messages
    xTaskCreate(send_periodic_messages, "send_msgs", 4096, NULL, 5, NULL);

    ESP_LOGI(TAG, "HardPanel initialized successfully");
}