#include "modbus_sensor.h"
#include "app_config.h"
#include "esp_log.h"

esp_err_t modbus_sensor_init(void)
{
    /* TODO: Configure UART/RS485, slave address and register mapping. */
    ESP_LOGW("modbus_sensor", "TODO: Modbus sensor driver");
    return ESP_OK;
}

esp_err_t modbus_sensor_read(float *temperature_c, float *humidity_percent)
{
    if (temperature_c == NULL || humidity_percent == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    /* TODO: Read and validate registers. Write outputs only on ESP_OK. */
    return ESP_ERR_NOT_SUPPORTED;
}
