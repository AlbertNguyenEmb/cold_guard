idf_component_register(
    SRCS
        "main.c"
        "bsp/bsp_gpio.c"
        "drivers/modbus_sensor.c"
        "drivers/door_sensor.c"
        "communication/espnow_receiver.c"
        "communication/wifi_manager.c"
        "communication/mqtt_client_app.c"
        "application/app_state.c"
        "application/sensor_task.c"
        "application/telemetry_task.c"
        "application/telemetry.c"
        "application/alarm_fsm.c"
        "application/command_handler.c"
        "web/web_server.c"
    INCLUDE_DIRS
        "."
        "bsp"
        "drivers"
        "communication"
        "application"
        "web"
        "../../common"
    PRIV_REQUIRES
        freertos log esp_common esp_timer
        esp_driver_gpio esp_driver_uart
        esp_wifi esp_event esp_netif nvs_flash esp_http_server
)
