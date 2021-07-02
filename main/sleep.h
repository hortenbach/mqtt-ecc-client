#ifndef SLEEP_H
#define SLEEP_H

#include "esp_log.h"
#include "esp_sleep.h"

#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP_IN_SECONDS 10

void goToSleep(void);

#endif