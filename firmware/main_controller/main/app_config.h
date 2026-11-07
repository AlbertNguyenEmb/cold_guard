#pragma once

/* TODO: Select GPIOs from your board schematic before enabling drivers.
 * -1 means unassigned; drivers must reject it before configuring hardware. */
#define APP_MODBUS_UART_PORT        1
#define APP_MODBUS_TX_GPIO          (-1)
#define APP_MODBUS_RX_GPIO          (-1)
#define APP_MODBUS_DE_GPIO          (-1)
#define APP_MODBUS_BAUD_RATE        9600
#define APP_MODBUS_SLAVE_ADDRESS    1
#define APP_DOOR_GPIO               (-1)
#define APP_ALARM_GPIO              (-1)

#define APP_WIFI_SSID               ""
#define APP_WIFI_PASSWORD           ""
#define APP_ESPNOW_CHANNEL          1
#define APP_MQTT_BROKER_URI         ""
#define APP_MQTT_TELEMETRY_TOPIC    "cold_guard/telemetry"
#define APP_MQTT_COMMAND_TOPIC      "cold_guard/commands"

#define APP_SENSOR_PERIOD_MS        1000
#define APP_TELEMETRY_PERIOD_MS     5000
#define APP_TASK_STACK_SIZE         4096
#define APP_SENSOR_TASK_PRIORITY    5
#define APP_TELEMETRY_TASK_PRIORITY 4
