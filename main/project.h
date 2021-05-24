#ifndef MAIN_H
#define MAIN_H

// extern const char* TAG = "MyModule";
#define TAG "MyModule"

extern const uint8_t ca_pem_start[]   asm("_binary_ca_pem_start");
extern const uint8_t ca_pem_end[]   asm("_binary_ca_pem_end");

#endif