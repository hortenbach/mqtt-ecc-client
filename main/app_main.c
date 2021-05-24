#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "project.h"
#include "wifi/wifi.c"
#include "mqtt/mqttclient.h"


void app_main(void)
{
    //Initialize NVS (Non Volatile Storage)
    // TODO use NVS Encryption
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    // ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());


    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();

    ESP_LOGI(TAG, "HELLO_WORLD");

    // mqtt_app_main();
    // mqtt_rsa_app_start();
    ESP_LOGI(TAG, "HELLO MQTT");
}
