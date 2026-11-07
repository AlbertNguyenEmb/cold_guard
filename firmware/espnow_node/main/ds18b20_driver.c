#include "ds18b20_driver.h"
#include "app_config.h"
#include "esp_log.h"

esp_err_t ds18b20_driver_init(void)
{
    /* TODO: Initialize 1-Wire bus, discover DS18B20 and configure resolution. */
    ESP_LOGW("ds18b20_driver", "TODO: DS18B20 driver");
    return ESP_OK;
}

esp_err_t ds18b20_driver_read(float *temperature_c)
{
    if (temperature_c == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    /* TODO: Start conversion, wait for completion, check CRC, return degrees C. */
    return ESP_ERR_NOT_SUPPORTED;
}
