#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
// #include "protocol_examples_common.h"

#include "esp_log.h"
#include "esp_tls.h"
#include "esp_ota_ops.h"
#include <sys/param.h>

#include "mqttclient.h"
#include "project.h"

// #define CONFIG_MQTT_PROTOCOL_311

#define CONFIG_BROKER_BIN_SIZE_TO_SEND 20000
#define BROKER_URI "mqtts://yoga.fritz.box:8883"

//
// Note: this function is for testing purposes only publishing part of the active partition
//       (to be checked against the original binary)
//
static void send_binary(esp_mqtt_client_handle_t client)
{
    spi_flash_mmap_handle_t out_handle;
    const void *binary_address;
    const esp_partition_t *partition = esp_ota_get_running_partition();
    esp_partition_mmap(partition, 0, partition->size, SPI_FLASH_MMAP_DATA, &binary_address, &out_handle);
    // sending only the configured portion of the partition (if it's less than the partition size)
    int binary_size = MIN(CONFIG_BROKER_BIN_SIZE_TO_SEND,partition->size);
    int msg_id = esp_mqtt_client_publish(client, "/topic/binary", binary_address, binary_size, 0, 0);
    ESP_LOGI(TAG, "binary sent with msg_id=%d", msg_id);
}

/*
 * @brief Event handler registered to receive MQTT events
 *
 *  This function is called by the MQTT client event loop.
 *
 * @param handler_args user data registered to the event.
 * @param base Event base for the handler(always MQTT Base in this example).
 * @param event_id The id for the received event.
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        msg_id = esp_mqtt_client_subscribe(client, "/topic/qos0", 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
        ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        // if (strncmp(event->data, "send binary please", event->data_len) == 0) {
        //     ESP_LOGI(TAG, "Sending the binary");
        //     send_binary(client);
        // }
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            ESP_LOGI(TAG, "Last error code reported from esp-tls: 0x%x", event->error_handle->esp_tls_last_esp_err);
            ESP_LOGI(TAG, "Last tls stack error number: 0x%x", event->error_handle->esp_tls_stack_err);
            ESP_LOGI(TAG, "Last captured errno : %d (%s)",  event->error_handle->esp_transport_sock_errno,
                     strerror(event->error_handle->esp_transport_sock_errno));
        } else if (event->error_handle->error_type == MQTT_ERROR_TYPE_CONNECTION_REFUSED) {
            ESP_LOGI(TAG, "Connection refused error: 0x%x", event->error_handle->connect_return_code);
        } else {
            ESP_LOGW(TAG, "Unknown error type: 0x%x", event->error_handle->error_type);
        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

// void mqtt_pub(esp_mqtt_client_handle_t client){
//  const char* testdata = "MQTT Testdata 12345";
//  esp_mqtt_client_publish(client, "/topic/qos0", testdata, 0, 0, 1);
// }

void mqtt_rsa_app_start(void)
{
//     const esp_mqtt_client_config_t mqtt_cfg = {
//     mqtt_event_callback_t event_handle;     /*!< handle for MQTT events as a callback in legacy mode */
//     esp_event_loop_handle_t event_loop_handle; /*!< handle for MQTT event loop library */
//     const char *host;                       /*!< MQTT server domain (ipv4 as string) */
//     const char *uri;                        /*!< Complete MQTT broker URI */
//     uint32_t port;                          /*!< MQTT server port */
//     const char *client_id;                  /*!< default client id is ``ESP32_%CHIPID%`` where %CHIPID% are last 3 bytes of MAC address in hex format */
//     const char *username;                   /*!< MQTT username */
//     const char *password;                   /*!< MQTT password */
//     const char *lwt_topic;                  /*!< LWT (Last Will and Testament) message topic (NULL by default) */
//     const char *lwt_msg;                    /*!< LWT message (NULL by default) */
//     int lwt_qos;                            /*!< LWT message qos */
//     int lwt_retain;                         /*!< LWT retained message flag */
//     int lwt_msg_len;                        /*!< LWT message length */
//     int disable_clean_session;              /*!< mqtt clean session, default clean_session is true */
//     int keepalive;                          /*!< mqtt keepalive, default is 120 seconds */
//     bool disable_auto_reconnect;            /*!< this mqtt client will reconnect to server (when errors/disconnect). Set disable_auto_reconnect=true to disable */
//     void *user_context;                     /*!< pass user context to this option, then can receive that context in ``event->user_context`` */
//     int task_prio;                          /*!< MQTT task priority, default is 5, can be changed in ``make menuconfig`` */
//     int task_stack;                         /*!< MQTT task stack size, default is 6144 bytes, can be changed in ``make menuconfig`` */
//     int buffer_size;                        /*!< size of MQTT send/receive buffer, default is 1024 (only receive buffer size if ``out_buffer_size`` defined) */
//     const char *cert_pem;                   /*!< Pointer to certificate data in PEM or DER format for server verify (with SSL), default is NULL, not required to verify the server. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in cert_len. */
//     size_t cert_len;                        /*!< Length of the buffer pointed to by cert_pem. May be 0 for null-terminated pem */
//     const char *client_cert_pem;            /*!< Pointer to certificate data in PEM or DER format for SSL mutual authentication, default is NULL, not required if mutual authentication is not needed. If it is not NULL, also `client_key_pem` has to be provided. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in client_cert_len. */
//     size_t client_cert_len;                 /*!< Length of the buffer pointed to by client_cert_pem. May be 0 for null-terminated pem */
//     const char *client_key_pem;             /*!< Pointer to private key data in PEM or DER format for SSL mutual authentication, default is NULL, not required if mutual authentication is not needed. If it is not NULL, also `client_cert_pem` has to be provided. PEM-format must have a terminating NULL-character. DER-format requires the length to be passed in client_key_len */
//     size_t client_key_len;                  /*!< Length of the buffer pointed to by client_key_pem. May be 0 for null-terminated pem */
//     esp_mqtt_transport_t transport;         /*!< overrides URI transport */
//     int refresh_connection_after_ms;        /*!< Refresh connection after this value (in milliseconds) */
//     const struct psk_key_hint* psk_hint_key;     /*!< Pointer to PSK struct defined in esp_tls.h to enable PSK authentication (as alternative to certificate verification). If not NULL and server/client certificates are NULL, PSK is enabled */
//     bool          use_global_ca_store;      /*!< Use a global ca_store for all the connections in which this bool is set. */
//     int reconnect_timeout_ms;               /*!< Reconnect to the broker after this value in miliseconds if auto reconnect is not disabled (defaults to 10s) */
//     const char **alpn_protos;               /*!< NULL-terminated list of supported application protocols to be used for ALPN */
//     const char *clientkey_password;         /*!< Client key decryption password string */
//     int clientkey_password_len;             /*!< String length of the password pointed to by clientkey_password */
//     esp_mqtt_protocol_ver_t protocol_ver;   /*!< MQTT protocol version used for connection, defaults to value from menuconfig*/
//     int out_buffer_size;                    /*!< size of MQTT output buffer. If not defined, both output and input buffers have the same size defined as ``buffer_size`` */
//     bool skip_cert_common_name_check;       /*!< Skip any validation of server certificate CN field, this reduces the security of TLS and makes the mqtt client susceptible to MITM attacks  */
//     bool use_secure_element;                /*!< enable secure element for enabling SSL connection */
//     void *ds_data;                          /*!< carrier of handle for digital signature parameters */
//     int network_timeout_ms;                 /*!< Abort network operation if it is not completed after this value, in milliseconds (defaults to 10s) */
//     bool disable_keepalive;                 /*!< Set disable_keepalive=true to turn off keep-alive mechanism, false by default (keepalive is active by default). Note: setting the config value `keepalive` to `0` doesn't disable keepalive feature, but uses a default keepalive period */
// } ;


    const esp_mqtt_client_config_t mqtt_cfg = {
        .uri = BROKER_URI,
        // .event_loop_handle = ,
        .cert_pem = (const char *)ca_pem_start,
    };
    ESP_LOGI(TAG, "Free memory: %d bytes", esp_get_free_heap_size());
    
    /* new client */
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    const char* testdata = "MQTT Testdata 12345";
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, 0);
    esp_mqtt_client_start(client);
    // esp_mqtt_client_publish(client, "/topic/qos0", testdata, 0, 0, 1);
}

