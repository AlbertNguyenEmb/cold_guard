#include "espnow_sender.h"
#include "app_config.h"
#include "esp_log.h"

esp_err_t espnow_sender_init(void)
{
    /* TODO: Initialize NVS/netif/event loop/Wi-Fi STA, select channel, start
     * ESP-NOW, register send callback and add controller peer. */
    ESP_LOGW("espnow_sender", "TODO: ESP-NOW sender");
    return ESP_OK;
}

esp_err_t espnow_sender_send(const espnow_sensor_packet_t *packet)
{
    if (packet == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    /* TODO: Serialize the 16-byte packet, send and handle async completion. */
    return ESP_ERR_NOT_SUPPORTED;
}
