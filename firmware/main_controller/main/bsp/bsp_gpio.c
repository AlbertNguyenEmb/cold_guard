#include "bsp_gpio.h"
#include "app_config.h"
#include "esp_log.h"

esp_err_t bsp_gpio_init(void)
{
    /* TODO: Validate app_config.h pins, configure GPIOs and safe output levels. */
    ESP_LOGW("bsp_gpio", "TODO: GPIO configuration");
    return ESP_OK;
}
