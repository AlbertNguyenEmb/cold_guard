#include "sensor_task.h"
#include "alarm_fsm.h"
#include "app_config.h"
#include "app_state.h"
#include "door_sensor.h"
#include "modbus_sensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static void sensor_task(void *argument)
{
    (void)argument;
    while (true) {
        float temperature_c = 0.0f;
        float humidity_percent = 0.0f;
        bool door_open = false;
        esp_err_t sensor_result = modbus_sensor_read(&temperature_c, &humidity_percent);
        esp_err_t door_result = door_sensor_read(&door_open);
        app_state_set_local_sensor(temperature_c, humidity_percent, sensor_result == ESP_OK);
        app_state_set_door(door_open, door_result == ESP_OK);

        app_state_t snapshot;
        app_state_get(&snapshot);
        alarm_fsm_process(&snapshot);
        /* TODO: Consume ESP-NOW readings from a queue and update per-node state. */
        vTaskDelay(pdMS_TO_TICKS(APP_SENSOR_PERIOD_MS));
    }
}

esp_err_t sensor_task_start(void)
{
    return xTaskCreate(sensor_task, "sensor_task", APP_TASK_STACK_SIZE, NULL,
                       APP_SENSOR_TASK_PRIORITY, NULL) == pdPASS
               ? ESP_OK : ESP_ERR_NO_MEM;
}
