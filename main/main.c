#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "dht.h"

// Define the pin where your DHT11 Data line is connected
#define DHT11_GPIO_PIN 27

static const char *TAG = "DHT11_APP";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting DHT11 Sensor Application...");
    
    // REMOVE ALL gpio_reset_pin, gpio_set_direction, and gpio_pullup_en LINES!
    // The dht library handles this internally on every cycle.

    int16_t temperature = 0;
    int16_t humidity = 0;

    while (1) {
        // Read data using GPIO 27
        esp_err_t res = dht_read_data(DHT_TYPE_DHT11, DHT11_GPIO_PIN, &humidity, &temperature);

        if (res == ESP_OK) {
            float temp_c = temperature / 10.0;
            float temp_f = (temp_c * 9.0 / 5.0) + 32.0;
            float hum = humidity / 10.0;
            ESP_LOGI(TAG, "Read Success -> Temp: %.1f°C (%.1f°F) | Hum: %.1f%%", temp_c, temp_f, hum);
        } else {
            ESP_LOGE(TAG, "Could not read data from sensor (Error: %s)", esp_err_to_name(res));
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
