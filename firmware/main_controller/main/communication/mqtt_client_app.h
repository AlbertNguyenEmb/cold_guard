#pragma once
#include <stddef.h>
#include "esp_err.h"

esp_err_t mqtt_client_app_init(void);
esp_err_t mqtt_client_app_publish(const char *payload, size_t length);
