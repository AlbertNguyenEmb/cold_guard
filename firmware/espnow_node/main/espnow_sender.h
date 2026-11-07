#pragma once
#include "esp_err.h"
#include "espnow_protocol.h"

esp_err_t espnow_sender_init(void);
esp_err_t espnow_sender_send(const espnow_sensor_packet_t *packet);
