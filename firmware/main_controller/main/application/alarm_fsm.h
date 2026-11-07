#pragma once
#include "app_state.h"
#include "esp_err.h"

esp_err_t alarm_fsm_init(void);
void alarm_fsm_process(const app_state_t *state);
