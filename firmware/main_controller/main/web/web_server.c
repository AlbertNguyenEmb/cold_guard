#include "web_server.h"
#include "esp_log.h"

esp_err_t web_server_start(void)
{
    /* TODO: Start esp_http_server after network is ready; register status/config
     * handlers, obtain snapshots through app_state_get(). */
    ESP_LOGW("web_server", "TODO: HTTP server");
    return ESP_OK;
}
