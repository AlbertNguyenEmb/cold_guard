#pragma once
#include "esp_err.h"

esp_err_t modbus_sensor_init(void);
esp_err_t modbus_sensor_read(float *temperature_c, float *humidity_percent);
