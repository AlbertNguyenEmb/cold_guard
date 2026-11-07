#include "alarm_fsm.h"
#include "esp_log.h"

esp_err_t alarm_fsm_init(void)
{
    ESP_LOGW("alarm_fsm", "TODO: Alarm states, thresholds and timing");
    return ESP_OK;
}

void alarm_fsm_process(const app_state_t *state)
{
    (void)state;
    /* TODO: Check validity, thresholds, hysteresis, door timeout and sensor loss.
     * Drive alarms through BSP functions, using monotonic timestamps. */
}
