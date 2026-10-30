#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "dht.h"

// Hardware Pin Defintions
#define DHT11_GPIO_PIN 18
#define ALERT_LED_PIN   2   // Onboard Blue LED

// Thermostat Setpoint Configuration
#define TEMP_THRESHOLD_F 74.0  // Trigger point in Fahrenheit

static const char *TAG = "THERMOSTAT_APP";

void app_main(void)
{
    ESP_LOGI(TAG, "Initializing Thermostat Application...");

    /* Configure the Alert LED Pin as Output */
    gpio_reset_pin(ALERT_LED_PIN);
    gpio_set_direction(ALERT_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(ALERT_LED_PIN, 0); // Start with LED turned off

    int16_t temperature = 0;
    int16_t humidity = 0;

    while (1) {
        // Read raw data from the DHT11 sensor
        esp_err_t res = dht_read_data(DHT_TYPE_DHT11, DHT11_GPIO_PIN, &humidity, &temperature);

        if (res == ESP_OK) {
            // Unscale and convert values
            float temp_c = temperature / 10.0;
            float temp_f = (temp_c * 9.0 / 5.0) + 32.0;
            float hum = humidity / 10.0;

            // Log current stats to terminal
            ESP_LOGI(TAG, "Temp: %.1f°F | Hum: %.1f%%", temp_f, hum);

            /* Thermostat Core Logic Trigger */
            if (temp_f > TEMP_THRESHOLD_F) {
                gpio_set_level(ALERT_LED_PIN, 1); // Turn ON Blue LED
                ESP_LOGW(TAG, "!!! ALERT !!! Temperature (%.1f°F) exceeds threshold (%.1f°F) -> LED ON", temp_f, TEMP_THRESHOLD_F);
            } else {
                gpio_set_level(ALERT_LED_PIN, 0); // Turn OFF Blue LED
                ESP_LOGI(TAG, "Temperature stable -> LED OFF");
            }

        } else {
            ESP_LOGE(TAG, "Could not read data from sensor (Error: %s)", esp_err_to_name(res));
        }

        // Wait 2 seconds before the next reading cycle
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
