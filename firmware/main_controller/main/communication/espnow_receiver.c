#include "espnow_receiver.h"
#include "esp_log.h"

esp_err_t espnow_receiver_init(void)
{
    /* TODO: After Wi-Fi starts, initialize ESP-NOW and register RX callback.
     * Validate length/version/node ID; queue decoded packets for a task. */
    ESP_LOGW("espnow_receiver", "TODO: ESP-NOW receiver");
    return ESP_OK;
}
