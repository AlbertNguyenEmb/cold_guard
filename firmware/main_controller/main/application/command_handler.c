#include "command_handler.h"
#include "esp_log.h"

esp_err_t command_handler_init(void)
{
    ESP_LOGW("command_handler", "TODO: Command validation and dispatch");
    return ESP_OK;
}

esp_err_t command_handler_process(const char *payload, size_t length)
{
    if (payload == NULL || length == 0) {
        return ESP_ERR_INVALID_ARG;
    }
    /* TODO: Parse using explicit length; validate commands before changing state. */
    return ESP_ERR_NOT_SUPPORTED;
}
