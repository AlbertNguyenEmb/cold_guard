#pragma once
#include <stdbool.h>

typedef struct {
    float temperature_c;
    float humidity_percent;
    bool sensor_valid;
    bool door_open;
    bool door_valid;
    /* TODO: Add per-node readings, timestamps, validity and alarm state. */
} app_state_t;

void app_state_init(void);
void app_state_get(app_state_t *snapshot);
void app_state_set_local_sensor(float temperature_c, float humidity_percent,
                                bool valid);
void app_state_set_door(bool is_open, bool valid);
