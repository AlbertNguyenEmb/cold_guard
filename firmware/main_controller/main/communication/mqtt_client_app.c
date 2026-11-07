#include "mqtt_client_app.h"
#include "app_config.h"
#include "esp_log.h"

esp_err_t mqtt_client_app_init(void)
{
    /* TODO: Initialize ESP-MQTT, wait for Wi-Fi, subscribe to commands.
     * See README for the ESP-IDF 6.x managed component dependency. */
    ESP_LOGW("mqtt_client_app", "TODO: MQTT client");
    return ESP_OK;
}

esp_err_t mqtt_client_app_publish(const char *payload, size_t length)
{
    if (payload == NULL || length == 0) {
        return ESP_ERR_INVALID_ARG;
    }
    /* TODO: Publish only after MQTT connects; handle queue/backpressure. */
    return ESP_ERR_NOT_SUPPORTED;
}
