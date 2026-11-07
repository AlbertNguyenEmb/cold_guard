#include "telemetry.h"

esp_err_t telemetry_encode(const app_state_t *state, char *buffer,
                           size_t capacity, size_t *length)
{
    if (state == NULL || buffer == NULL || capacity == 0 || length == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    buffer[0] = '\0';
    *length = 0;
    /* TODO: Encode JSON, checking validity flags and buffer capacity.
     * Invalid readings must become null/absent, never fabricated zero values. */
    return ESP_ERR_NOT_SUPPORTED;
}
