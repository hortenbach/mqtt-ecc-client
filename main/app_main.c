#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_netif.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "esp_ping.h"
#include "ping/ping_sock.h"
#include "sdkconfig.h"
#include "esp_console.h"
#include "argtable3/argtable3.h"
#include "lwip/inet.h"

// #include "project.h"
// #include "wifi/wifi.c" // TODO include h, declare all functions
// #include "wifi/repl.c"

// #include "mqtt/app_mqtt.h"
#include "esp_tls.h"
#include "esp_crt_bundle.h"

//openssl req -newkey rsa:2048 -new -nodes -x509 -days 3650 -keyout key.pem -subj "/C=DE/ST=b/L=B/CN=192.168.178.25" -out cert.pem
/* Constants that aren't configurable in menuconfig */
#define WEB_SERVER "192.168.178.25"
#define WEB_PORT "8080"
#define WEB_URL "https://192.168.178.25:8080"

extern const uint8_t ca_pem_start[]   asm("_binary_cert_pem_start");
extern const uint8_t ca_pem_end[]   asm("_binary_cert_pem_end");

static const char *TAG = "example";

static const char *REQUEST = "GET " WEB_URL " HTTP/1.0\r\n"
    "Host: "WEB_SERVER"\r\n"
    "User-Agent: esp-idf/1.0 esp32\r\n"
    "\r\n";

static void https_get_task(void *pvParameters)
{
    char buf[512];
    int ret, len;

    while(1) {
        esp_tls_cfg_t cfg = { 0 };
        cfg.use_global_ca_store = false;
        cfg.cacert_buf = ca_pem_start;
        cfg.cacert_bytes = ca_pem_end - ca_pem_start;
        cfg.use_secure_element = false;

    //   const char *common_name;                /*!< If non-NULL, server certificate CN must match this name.
                                                //  If NULL, server certificate CN must match hostname. */  

        struct esp_tls *tls = esp_tls_conn_http_new(WEB_URL, &cfg);

        if(tls != NULL) {
            ESP_LOGI(TAG, "Connection established...");
        } else {
            ESP_LOGE(TAG, "Connection failed...");
            goto exit;
        }

        size_t written_bytes = 0;
        do {
            ret = esp_tls_conn_write(tls,
                                     REQUEST + written_bytes,
                                     strlen(REQUEST) - written_bytes);
            if (ret >= 0) {
                ESP_LOGI(TAG, "%d bytes written", ret);
                written_bytes += ret;
            } else if (ret != ESP_TLS_ERR_SSL_WANT_READ  && ret != ESP_TLS_ERR_SSL_WANT_WRITE) {
                ESP_LOGE(TAG, "esp_tls_conn_write  returned 0x%x", ret);
                goto exit;
            }
        } while(written_bytes < strlen(REQUEST));

        ESP_LOGI(TAG, "Reading HTTPS response...");

        do
        {
            len = sizeof(buf) - 1;
            bzero(buf, sizeof(buf));
            ret = esp_tls_conn_read(tls, (char *)buf, len);

            if(ret == ESP_TLS_ERR_SSL_WANT_WRITE  || ret == ESP_TLS_ERR_SSL_WANT_READ)
                continue;

            if(ret < 0)
           {
                ESP_LOGE(TAG, "esp_tls_conn_read  returned -0x%x", -ret);
                break;
            }

            if(ret == 0)
            {
                ESP_LOGI(TAG, "connection closed");
                break;
            }

            len = ret;
            ESP_LOGD(TAG, "%d bytes read", len);
            /* Print response directly to stdout as it is read */
            for(int i = 0; i < len; i++) {
                putchar(buf[i]);
            }
        } while(1);

    exit:
        esp_tls_conn_delete(tls);
        putchar('\n'); // JSON output doesn't have a newline at end

        static int request_count;
        ESP_LOGI(TAG, "Completed %d requests", ++request_count);

        for(int countdown = 10; countdown >= 0; countdown--) {
            ESP_LOGI(TAG, "%d...", countdown);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        ESP_LOGI(TAG, "Starting again!");
    }
}

void app_main(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());

    xTaskCreate(&https_get_task, "https_get_task", 8192, NULL, 5, NULL);
}