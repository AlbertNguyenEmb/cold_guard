#include "telemetry_task.h"
#include "app_config.h"
#include "app_state.h"
#include "mqtt_client_app.h"
#include "telemetry.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static void telemetry_task(void *argument)
{
    (void)argument;
    while (true) {
        app_state_t snapshot;
        char payload[512];
        size_t length = 0;
        app_state_get(&snapshot);
        if (telemetry_encode(&snapshot, payload, sizeof(payload), &length) == ESP_OK) {
            esp_err_t result = mqtt_client_app_publish(payload, length);
            if (result != ESP_OK) {
                ESP_LOGW("telemetry_task", "Publish skipped: %s", esp_err_to_name(result));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(APP_TELEMETRY_PERIOD_MS));
    }
}

esp_err_t telemetry_task_start(void)
{
    return xTaskCreate(telemetry_task, "telemetry_task", APP_TASK_STACK_SIZE, NULL,
                       APP_TELEMETRY_TASK_PRIORITY, NULL) == pdPASS
               ? ESP_OK : ESP_ERR_NO_MEM;
}
