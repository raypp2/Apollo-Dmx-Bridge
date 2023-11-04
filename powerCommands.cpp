#include "powerCommands.h"

void devicePower(const String& url) {
    HTTPClient http;
    
    http.begin(url);  // Unlike ESP8266, for ESP32 you can directly use the URL

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.println("Error on HTTP request");
    }
    
    http.end();
}

void handleDelayedPowerOff(int i) {
  if (dmx_fixtures[i].isWaitingOff) {
    if (millis() - dmx_fixtures[i].lastActionTime >= dmx_fixtures[i].offDelay * 1000) {
      devicePower(dmx_fixtures[i].offUrl);
      dmx_fixtures[i].isWaitingOff = false;
    }
  }
}

void togglePower(int i, String preset){
  //Toggle device power if a URL exists
  if (preset == "off" && dmx_fixtures[i].offUrl && *dmx_fixtures[i].offUrl) {

      if (dmx_fixtures[i].offDelay != 0) {
        // Turn off after preset delay. Allows fixture to cool.
        // Delay is executed by the loop function
        dmx_fixtures[i].lastActionTime = millis();
        dmx_fixtures[i].isWaitingOff = true;
      } else {
        devicePower(dmx_fixtures[i].offUrl); 
      }

  } else if (dmx_fixtures[i].onUrl && *dmx_fixtures[i].onUrl) {
      dmx_fixtures[i].isWaitingOff = false; // Cancel any pending power off command
      devicePower(dmx_fixtures[i].onUrl); 
  }
}