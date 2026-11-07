#include "app_config.h"
#include "ds18b20_driver.h"
#include "espnow_sender.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    ESP_ERROR_CHECK(ds18b20_driver_init());
    ESP_ERROR_CHECK(espnow_sender_init());
    ESP_LOGI("node", "Cold Guard node scaffold ready; DS18B20/ESP-NOW are TODOs");

    uint32_t sequence = 0;
    while (1) {
        float temperature_c = 0.0f;
        if (ds18b20_driver_read(&temperature_c) == ESP_OK) {
            /* TODO: Validate range/finiteness before converting the reading. */
            espnow_sensor_packet_t packet = {
                .version = ESPNOW_PROTOCOL_VERSION,
                .message_type = ESPNOW_MESSAGE_SENSOR,
                .node_id = NODE_ID,
                .sequence = sequence++,
                .temperature_millicelsius = (int32_t)(temperature_c * 1000.0f),
                .flags = ESPNOW_FLAG_TEMPERATURE_VALID,
            };
            esp_err_t result = espnow_sender_send(&packet);
            if (result != ESP_OK) {
                ESP_LOGW("node", "Send skipped: %s", esp_err_to_name(result));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(NODE_SAMPLE_PERIOD_MS));
    }
}
