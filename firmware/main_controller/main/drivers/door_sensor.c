#include "door_sensor.h"
#include "app_config.h"
#include "esp_log.h"

esp_err_t door_sensor_init(void)
{
    /* TODO: Configure input pull-up/pull-down and debounce. */
    ESP_LOGW("door_sensor", "TODO: Door sensor driver");
    return ESP_OK;
}

esp_err_t door_sensor_read(bool *is_open)
{
    if (is_open == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    /* TODO: Read debounced input. Write output only on ESP_OK. */
    return ESP_ERR_NOT_SUPPORTED;
}
