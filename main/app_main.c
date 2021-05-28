#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_ping.h"
#include "ping/ping_sock.h"
#include "sdkconfig.h"
#include "esp_console.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "argtable3/argtable3.h"
#include "protocol_examples_common.h"

#include "lwip/inet.h"
#include "lwip/netdb.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/sockets.h"

#include "project.h"
#include "wifi/wifi.c" // TODO include h, declare all functions
#include "wifi/repl.c"

#include "mqtt/app_mqtt.h"


// #include "ecc/ecc_task.h"

// #define TAG "MAIN"

/** TODO
 * 
void ecc_test() {
    // ESP_LOGI(TAG,"free DRAM %u IRAM %u",esp_get_free_heap_size(),xPortGetFreeHeapSizeTagged(MALLOC_CAP_32BIT));
    ESP_LOGI(TAG,"free DRAM %u IRAM %u",esp_get_free_heap_size(),xPortGetFreeHeapSize());
    xTaskCreate(ecc_task, "gpio_task", 12288, NULL, 5, NULL);

}
*/

/**
* init REPL for testing and fun
* */
void run_with_repl(void) {
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    esp_console_dev_uart_config_t uart_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    // init console REPL environmentecho
    ESP_ERROR_CHECK(esp_console_new_repl_uart(&uart_config, &repl_config, &s_repl));
    /* register command `ping` */
    register_ping();
    /* register command `quit` */
    register_quit();
    // start console REPL
    ESP_ERROR_CHECK(esp_console_start_repl(s_repl));
}



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
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    /* wait for active network connection */
    ESP_ERROR_CHECK(example_connect());

    // ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    //wifi_init_sta();

    // ESP_LOGI(TAG, "HELLO_WORLD");

    // // ecc_test();
    // // ESP_LOGI(TAG, "Done ECC test.");    // esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();

    mqtt_rsa_app_start();
    ESP_LOGI(TAG, "MQTT check done.");
}
