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

#include "esp_sleep.h"

// #include "ecc/ecc_task.h"

// #define TAG "MAIN"

#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP_IN_SECONDS 30

/** TODO
 * 
void ecc_test() {
    // ESP_LOGI(TAG,"free DRAM %u IRAM %u",esp_get_free_heap_size(),xPortGetFreeHeapSizeTagged(MALLOC_CAP_32BIT));
    ESP_LOGI(TAG,"free DRAM %u IRAM %u",esp_get_free_heap_size(),xPortGetFreeHeapSize());
    xTaskCreate(ecc_task, "gpio_task", 12288, NULL, 5, NULL);

}
*/


void app_main(void)
{
    //Initialize NVS (Non Volatile Storage)
    // TODO use NVS Encryption
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    // ESP_ERROR_CHECK(ret);
    // ESP_ERROR_CHECK(nvs_flash_init());
    // ESP_ERROR_CHECK(esp_netif_init());
    // ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();

    ESP_LOGI(TAG, "HELLO_WORLD");

    // ecc_test();
    // ESP_LOGI(TAG, "Done ECC test.");
    
    mqtt_rsa_app_start();
    ESP_LOGI(TAG, "Done MQTT.");

    ESP_LOGI(TAG, "Entering Sleep Mode");
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP_IN_SECONDS*uS_TO_S_FACTOR);
    esp_deep_sleep_start();
}
