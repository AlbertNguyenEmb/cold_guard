#include "app_state.h"
#include "freertos/FreeRTOS.h"

static app_state_t s_state;
static portMUX_TYPE s_state_lock = portMUX_INITIALIZER_UNLOCKED;

void app_state_init(void)
{
    portENTER_CRITICAL(&s_state_lock);
    s_state = (app_state_t){0};
    portEXIT_CRITICAL(&s_state_lock);
}

void app_state_get(app_state_t *snapshot)
{
    if (snapshot == NULL) {
        return;
    }
    portENTER_CRITICAL(&s_state_lock);
    *snapshot = s_state;
    portEXIT_CRITICAL(&s_state_lock);
}

void app_state_set_local_sensor(float temperature_c, float humidity_percent,
                                bool valid)
{
    portENTER_CRITICAL(&s_state_lock);
    s_state.sensor_valid = valid;
    if (valid) {
        s_state.temperature_c = temperature_c;
        s_state.humidity_percent = humidity_percent;
    }
    portEXIT_CRITICAL(&s_state_lock);
}

void app_state_set_door(bool is_open, bool valid)
{
    portENTER_CRITICAL(&s_state_lock);
    s_state.door_valid = valid;
    if (valid) {
        s_state.door_open = is_open;
    }
    portEXIT_CRITICAL(&s_state_lock);
}
