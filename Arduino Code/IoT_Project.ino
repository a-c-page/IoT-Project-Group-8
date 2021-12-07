#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
#define USED_PIN A0
const int THRESHOLD = 200;
boolean auto_mode = false;

void setup()
{
  Serial.begin(115200);
  pinMode(D1, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Toby", "55Password");
}

void loop()
{
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    WiFiClient client;
    HTTPClient http;

    // BEGIN HTTP GET ON MODE API
    if (http.begin(client, "http://iotprojecttam.herokuapp.com/mode/"))
    {
      int httpCode = http.GET();

      if (httpCode > 0)
      {
        // DETERMINE LIGHT STATE
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
          String payload = http.getString();
          int len = payload.length();
          String modeie = payload.substring(len-4, len-3);
          
          if (modeie == "t")
          {
            auto_mode = true;
            float light = analogRead(USED_PIN);
            Serial.println(light);
            if (light < THRESHOLD)  { digitalWrite(D1, HIGH); }
            else { digitalWrite(D1, LOW); }
          }
          else { auto_mode = false; }
        }

      }
      // ERROR HANDLING
      else { Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str()); }
      http.end();
    }
    // ERROR HANDLING
    else { Serial.printf("[HTTP} Unable to connect\n"); }
    
    // BEGIN HTTP GET ON STATE API
    if (http.begin(client, "http://iotprojecttam.herokuapp.com/state/"))
    {
      int httpCode = http.GET();

      if (httpCode > 0)
      {
        // DETERMINE LIGHT STATE
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
          if (auto_mode == false)
          {
            String payload = http.getString();
            int len = payload.length();
            String state = payload.substring(len-4, len-3);
  
            if (state == "O") { digitalWrite(D1, HIGH); }
            else { digitalWrite(D1, LOW); }
          }
        }
      }
      // ERROR HANDLING
      else { Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str()); }
      http.end();
    }
    // ERROR HANDLING
    else { Serial.printf("[HTTP} Unable to connect\n"); }
  }
  delay(1000);
}
