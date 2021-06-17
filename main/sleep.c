#include "sleep.h"

void goToSleep(void){
    ESP_LOGI(TAG, "Entering Sleep Mode");
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP_IN_SECONDS*uS_TO_S_FACTOR);
    esp_deep_sleep_start();
}