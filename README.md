# ESP32 DHT11 Smart Thermostat Monitor

A lightweight **ESP-IDF** (FreeRTOS) application for the ESP32 that reads temperature and humidity data from a DHT11 sensor. It functions as a smart thermostat, automatically triggering an onboard blue alert LED whenever the ambient temperature exceeds a user-configured Fahrenheit threshold.

## 🚀 Features

* **Real-time Monitoring:** Reads and logs ambient temperature (°F) and relative humidity (%) every 2 seconds.
* **Smart Alert Threshold:** Automatically triggers a GPIO alert when the environment gets too warm.
* **Robust Logging:** Uses native `esp_log` macros to report steady-state metrics (`ESP_LOGI`) and high-temperature warnings (`ESP_LOGW`).
* **Non-blocking Execution:** Built on FreeRTOS tasks to keep your microcontroller responsive.

## 🛠️ Hardware Requirements

* **ESP32** Development Board (e.g., ESP32-WROOM-32)
* **DHT11** Temperature and Humidity Sensor
* **Resistor:** 4.7kΩ or 10kΩ pull-up resistor (if using a bare DHT11 sensor instead of a pre-assembled module)
* **Jumper Wires & Breadboard**

## 📌 Pin Configuration

| Component | ESP32 GPIO | Description |
|---|---|---|
| **DHT11 Data Pin** | `GPIO 18` | Bidirectional data line for sensor communication |
| **Onboard Blue LED** | `GPIO 2` | Output indicator for high-temperature alerts |

*Note: Ensure your DHT11 VCC is tied to 3.3V and GND is tied to a common ground pin on the ESP32.*

## ⚙️ Configuration

You can easily adjust the project properties directly inside the source code:

* **Threshold Trigger:** Change `#define TEMP_THRESHOLD_F 74.0` to your desired warning temperature limit.
* **Sensor Pin:** Modify `#define DHT11_GPIO_PIN 18` if you decide to change your physical wiring layout.

## 🛠️ Build and Flash Instructions

This project assumes you have the **ESP-IDF framework** installed and configured in your environment.

1. **Clone or integrate this project** into your active ESP-IDF workspace.
2. **Include the DHT component dependency** (such as the standard `esp-idf-lib` DHT driver) into your `main/CMakeLists.txt`.
3. **Set the target chip:**
   ```bash
   idf.py set-target esp32
   ```
4. **Build the application:**
   ```bash
   idf.py build
   ```
5. **Flash and Monitor:** Replace `PORT` with your specific serial port layout (e.g., `/dev/ttyUSB0` or `COM3`).
   ```bash
   idf.py -p PORT flash monitor
   ```

## 📊 Sample Serial Output

```text
I (314) THERMOSTAT_APP: Initializing Thermostat Application...
I (2324) THERMOSTAT_APP: Temp: 71.6°F | Hum: 45.0%
I (2324) THERMOSTAT_APP: Temperature stable -> LED OFF
I (4324) THERMOSTAT_APP: Temp: 73.4°F | Hum: 44.8%
I (4324) THERMOSTAT_APP: Temperature stable -> LED OFF
W (6324) THERMOSTAT_APP: !!! ALERT !!! Temperature (75.2°F) exceeds threshold (74.0°F) -> LED ON
```

## 📄 License
This project is open-source and available under the MIT License.
