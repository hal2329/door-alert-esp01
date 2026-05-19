# Door Alert ESP-01S (ESP8266)

A lightweight, ultra-low-power IoT door security system built with an ESP-01S (ESP8266). The system monitors the door status (Open/Closed) using a magnetic reed switch, logs battery voltage data to Blynk, sends instant notifications via Telegram, and immediately enters Deep Sleep mode to conserve power.

## Features

- **Instant Notifications:** Sends door status alerts straight to your Telegram channel/chat.
- **Blynk Integration:** Logs and updates battery voltage (`vcc_bat`) over Wi-Fi.
- **Ultra-Low Power:** Utilizes ESP8266 Deep Sleep mode (`ESP.deepSleep(0)`) to ensure long battery life, waking up only when the door status changes.
- **State Persistence:** Uses EEPROM to store and verify the last known state of the door, preventing redundant alerts.
- **Internal Voltage Reading:** Uses `ADC_MODE(ADC_VCC)` to monitor the battery voltage directly from the VCC pin without requiring external voltage dividers.

## Hardware & Circuit Notes

- **Module:** ESP-01S (ESP8266)
- **Sensor:** Magnetic Reed Switch (connected to trigger a reset/wake the ESP from Deep Sleep)
- **Power Supply:** Powered directly by a 3.7V Li-ion battery. 
  > *Note: While the ESP8266 nominal voltage is 3.3V, this project connects the battery directly to the VCC pin. This allows `ESP.getVcc()` to accurately read the remaining battery charge as it drains, eliminating the need for an external analog voltage divider circuit.*

## Libraries Required

To compile this project, you need to install the following libraries through the **Arduino Library Manager** (Sketch > Include Library > Manage Libraries):

- **UniversalTelegramBot** (by Jacinto Silva) – For sending messages to Telegram.
- **ArduinoJson** (by Benoit Blanchon) – Required dependency for the Telegram Bot library (Recommended: version 6.x).
- **Blynk** (by Volodymyr Shymanskyy) – For connecting and sending data to the Blynk IoT platform.

*Note: The `ESP8266WiFi.h`, `WiFiClientSecure.h`, and `EEPROM.h` libraries are standard and included automatically when you install the ESP8266 board package in the Arduino IDE.*

## Configuration

Before flashing the code to your ESP-01S, make sure to update the placeholder credentials with your own:

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

#define BOTtoken "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID "YOUR_TELEGRAM_CHAT_ID"
