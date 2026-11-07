#pragma once
#include <stdint.h>

/* Shared by both firmwares. Increment version when changing the wire format.
 * Integers use little-endian byte order. Serialize explicitly in send/receive
 * implementations; do not assume the layout of an arbitrary C struct. */
#define ESPNOW_PROTOCOL_VERSION       1U
#define ESPNOW_MESSAGE_SENSOR         1U
#define ESPNOW_FLAG_TEMPERATURE_VALID (1U << 0)
#define ESPNOW_SENSOR_PACKET_SIZE     16U

typedef struct {
    uint8_t version;
    uint8_t message_type;
    uint16_t node_id;
    uint32_t sequence;
    int32_t temperature_millicelsius;
    uint32_t flags;
} espnow_sensor_packet_t;

_Static_assert(sizeof(espnow_sensor_packet_t) == ESPNOW_SENSOR_PACKET_SIZE,
               "Unexpected ESP-NOW packet layout");
