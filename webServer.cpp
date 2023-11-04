#include <Arduino.h>
#include "webServer.h"

void setupWebServer(AsyncWebServer &server) {
    // API Endpoints
    server.on("/updateFixture", HTTP_POST, [](AsyncWebServerRequest *request) {
        String id = request->arg("id");
        String preset = request->arg("preset");
        String command;

        // When the off command is sent, it overrides any preset that is provided with the "off" preset
        if(request->arg("command")=="off"){
          preset = "off";
        } else {
          command = "on"; // default command to "on" if none is provided
        }
        
        if(isValidFixturePreset(id, preset)) {
            updateFixtureDMX(id, preset);
            request->send(200, "text/plain", "Fixture updated");
        } else {
            request->send(400, "text/plain", "Invalid fixture ID (" + id + ") or preset (" + preset + ")");
        }
    });

    server.on("/updateScene", HTTP_POST, [](AsyncWebServerRequest *request) {
        String scene = request->arg("id");
        String command = request->hasArg("command") ? request->arg("command") : "on"; // default on

        Serial.println("Received scene: " + scene);
        Serial.println("Received command: " + command);
        
        if ( (scene == "Manual" || isValidScene(scene)) && (command == "on" || command == "off") ) {
            updateScene(scene, command);
            request->send(200, "text/plain", "Scene updated");
        } else {
            request->send(400, "text/plain", "Invalid scene name or command");
        }
    });


    server.on("/getScene", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", currentScene);
    });

    server.on("/getFixturePreset", HTTP_GET, [](AsyncWebServerRequest *request){
        String id = request->arg("id");
        for (int i = 0; i < numFixtures; i++) {
            if (id == dmx_fixtures[i].id) {
                request->send(200, "text/plain", dmx_fixtures[i].currentPreset);
                return;
            }
        }
        request->send(400, "text/plain", "Invalid fixture ID");
    });


  // Route to serve the CSS file
  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
      // Serve the CSS file
      request->send(SPIFFS, "/styles.css", "text/css");
  });


  // Route for the root web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    File file = SPIFFS.open("/index.html", "r");
    if (!file) {
      Serial.println("Failed to open file for reading");
      request->send(404, "text/plain", "File not found");
      return;
    }

    String fileContent = "";
    while (file.available()) {
      fileContent += (char)file.read();
    }
    file.close();

    request->send(200, "text/html", fileContent);
  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    Serial.printf("Received %s request for: %s\n", request->methodToString(), request->url().c_str());

    // Respond with a 404 Not Found since this is a catch-all handler
    request->send(404, "text/plain", "Not Found");
  });


    server.begin();
}
