#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <BlynkSimpleEsp8266.h>

#define DEBUG_MODE false

ADC_MODE(ADC_VCC);

const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

int t = 0;
int lastState; //0 Open - 1 Closed
int lastState_adress = 0;

#define BOTtoken "YOUR_TELEGRAM_BOT_TOKEN"  // your Bot Token (Get from Botfather)
#define CHAT_ID "YOUR_TELEGRAM_CHAT_ID"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  configTime(0, 0, "pool.ntp.org");
  client.setTrustAnchors(&cert);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  
  EEPROM.begin(2);
  lastState = EEPROM.read(lastState_adress);

  EEPROM.put(lastState_adress, 0);
  EEPROM.commit();

  String message = "Door Alert! Status: ";
  switch (lastState) {
    case 0: // Was open
      message += "Closed";
      EEPROM.put(lastState_adress, 1);
      break;
    case 1: // Was closed
      message += "Open";
      EEPROM.put(lastState_adress, 0);
      break;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (t == 60){
      ESP.deepSleep(0);
    }
    else{
      t++;
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");  

  float vcc_bat = (ESP.getVcc() / 1000.0) * 0.927;
  if (vcc_bat < 3.3) {
    message += "\nLOW BATTERY! ";
    message += vcc_bat;
    message += " V";
  }

  Serial.print("Battery Voltage: ");
  Serial.print(vcc_bat);
  Serial.println(" V");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password); 
  
  Blynk.virtualWrite(V1, vcc_bat);
  
  Blynk.run(); 
  Blynk.run();

  EEPROM.commit();
  
  if (!DEBUG_MODE) {
    bot.sendMessage(CHAT_ID, message, "");
    delay(100);
    ESP.deepSleep(0);
  }
}

void loop() {

}
