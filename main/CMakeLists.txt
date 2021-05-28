idf_component_register(SRCS "app_main.c" 
"project.h"
# "ecc/ecc_task.c"
# "ecc/ecc_task.h"
# "ecc/uECC.c"
# "ecc/uECC.h"
"wifi/wifi.h"
"wifi/wifi.c"
# "wifi/espping.c"
"wifi/repl.c"
"wifi/wifisecrets.h"
"mqtt/app_mqtt.c"
"mqtt/app_mqtt.h"
                    INCLUDE_DIRS "."
                                "./ecc"
                                "./wifi"
                                "./mqtt")
#  FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/*.*)
# idf_component_register(SRCS ${app_sources})