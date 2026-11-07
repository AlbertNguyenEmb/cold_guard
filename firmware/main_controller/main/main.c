#include "alarm_fsm.h"
#include "app_state.h"
#include "bsp_gpio.h"
#include "command_handler.h"
#include "door_sensor.h"
#include "esp_log.h"
#include "espnow_receiver.h"
#include "modbus_sensor.h"
#include "mqtt_client_app.h"
#include "sensor_task.h"
#include "telemetry_task.h"
#include "web_server.h"
#include "wifi_manager.h"

void app_main(void)
{
    app_state_init();
    ESP_ERROR_CHECK(bsp_gpio_init());
    ESP_ERROR_CHECK(modbus_sensor_init());
    ESP_ERROR_CHECK(door_sensor_init());
    ESP_ERROR_CHECK(wifi_manager_init());
    ESP_ERROR_CHECK(espnow_receiver_init());
    ESP_ERROR_CHECK(mqtt_client_app_init());
    ESP_ERROR_CHECK(alarm_fsm_init());
    ESP_ERROR_CHECK(command_handler_init());
    ESP_ERROR_CHECK(web_server_start());
    ESP_ERROR_CHECK(sensor_task_start());
    ESP_ERROR_CHECK(telemetry_task_start());

    ESP_LOGI("main", "Cold Guard controller scaffold ready; hardware/network modules are TODOs");
}
