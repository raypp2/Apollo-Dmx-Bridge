#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SparkFunDMX.h>
#include <WiFiUdp.h>
#include <ArtnetWifi.h>
#include <ESPmDNS.h>
#include "SPIFFS.h" // Include SPIFFS library

// Artnet
WiFiUDP UdpSend;
ArtnetWifi artnet;

// Web server
AsyncWebServer server(80);

// DMX
SparkFunDMX dmxMaster;


String currentScene = "None";  // Default to "None" if no scene has been set.
bool artnetControlActive = false; // default to ArtNet control off


#include "credentials.h"
#include "fixtureConfig.h"
#include "artnetManual.h"
#include "dmxHandler.h"
#include "webServer.h"


void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Set up mDNS
    if (MDNS.begin("dmx")) { 
      Serial.println("Web interface available via mDNS at http://dmx.local");
    } else {
      Serial.println("Error setting up MDNS responder. Access web interface directly via IP address.");
    }
  
    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }    

    // Initialize Artnet
    setupArtnet();

    // Initialize DMX for output
    dmxMaster.initWrite(TOTAL_CHANNELS);

    // Initialize the Web Server
    setupWebServer(server);  // Set up HTML Server & API endpoints

}




void loop() {
    if (artnetControlActive) {
        readArtnet();
        
    } else {
      // Normal mode where we are sending the values we've establisehd from presets.
      //for (int channel = 1; channel <= TOTAL_CHANNELS; channel++){
      //  dmxMaster.write(channel,active[channel-1]);   
      //}
      dmxMaster.update();
      delay(100);
    }

    // Run any delayed power off commands
    for (int i = 0; i < numFixtures; i++) {
        handleDelayedPowerOff(i);
    }
}
