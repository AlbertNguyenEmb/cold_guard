#pragma once
#include <stdbool.h>
#include "esp_err.h"

esp_err_t door_sensor_init(void);
esp_err_t door_sensor_read(bool *is_open);
