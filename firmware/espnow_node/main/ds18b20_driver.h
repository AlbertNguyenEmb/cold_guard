#pragma once
#include "esp_err.h"

esp_err_t ds18b20_driver_init(void);
esp_err_t ds18b20_driver_read(float *temperature_c);
