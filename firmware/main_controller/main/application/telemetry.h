#pragma once
#include <stddef.h>
#include "app_state.h"
#include "esp_err.h"

esp_err_t telemetry_encode(const app_state_t *state, char *buffer,
                           size_t capacity, size_t *length);
