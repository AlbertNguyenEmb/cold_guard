idf_component_register(
    SRCS "main.c" "ds18b20_driver.c" "espnow_sender.c"
    INCLUDE_DIRS "." "../../common"
    PRIV_REQUIRES
        freertos log esp_common esp_driver_gpio esp_driver_rmt
        esp_wifi esp_event esp_netif nvs_flash
)
