#include "dmxHandler.h"

void updateFixtureDMX(String id, String preset) {
    artnetControlActive = false;
    Serial.println("Setting fixture " + id + " to " + preset);
    for (int i = 0; i < numFixtures; i++) {
        if (id == dmx_fixtures[i].id) {
            int numPresets = sizeof(dmx_fixtures[i].presets) / sizeof(dmx_fixtures[i].presets[0]);
            for (int j = 0; j < numPresets; j++) {
                if (preset == dmx_fixtures[i].presets[j].name) {
                    // Update current preset
                    dmx_fixtures[i].currentPreset = preset.c_str();

                    // Send this preset's values to DMX
                    int startChannel = dmx_fixtures[i].channel;
                    for (int k = 0; k < dmx_fixtures[i].channel_mode; k++) {
                        dmxMaster.write(startChannel + k, dmx_fixtures[i].presets[j].values[k]);
                    }

                    togglePower(i, preset);

                    return;
                }
            }
        }
    }
    Serial.println("Invalid fixture or preset");
} 


void updateScene(String sceneName, String command) {

    if (command != "on" && command != "off") {
      Serial.println("Invalid command: " + command);
      return;
    }

    // Check for the "Manual" scene first as it has special handling
    if (sceneName == "Manual") {
      if (command == "on") {
          artnetControlActive = true;
          Serial.println("Toggled artnet manual mode on");
      } else if (command == "off") {
          artnetControlActive = false;
          Serial.println("Toggled artnet manual mode off");
      }

    // Handle any other scene
    } else {
      bool foundScene = false;
      for (int i = 0; i < numScenes; i++) {
          if (sceneName == dmx_scenes[i].id) {
              foundScene = true;
              int numSceneFixtures = sizeof(dmx_scenes[i].presets) / sizeof(dmx_scenes[i].presets[0]);
              for (int j = 0; j < numSceneFixtures; j++) {
                // The "off" command turns each fixture within the scene off
                if (command == "off") {
                  updateFixtureDMX(dmx_scenes[i].presets[j].fixtureId, "off");
                } else {
                  // Otherwise, we run the specified preset
                  // Note that we do not run error checking since we assume scenes are configured & tested correctly
                  updateFixtureDMX(dmx_scenes[i].presets[j].fixtureId, dmx_scenes[i].presets[j].presetName);
                }
              }
              break; // Stop looping when scene is processed
          }
      }

      if (foundScene) {
        currentScene = sceneName;
      } else {
          Serial.println("Invalid scene name");
          return;      
      }
    }
    
}


bool isValidFixturePreset(String id, String preset) {
    for (int i = 0; i < numFixtures; i++) {
        if (id == dmx_fixtures[i].id) {
            int numPresets = sizeof(dmx_fixtures[i].presets) / sizeof(dmx_fixtures[i].presets[0]);
            for (int j = 0; j < numPresets; j++) {
                if (preset == dmx_fixtures[i].presets[j].name) {
                    return true; // Found valid fixture and preset
                }
            }
        }
    }
    return false; // If we reach here, it's not valid
}

bool isValidScene(String id) {
    for (int i = 0; i < numScenes; i++) {
        if (id == dmx_scenes[i].id) {
          return true; // Found valid fixture and preset
        }
    }
    return false; // If we reach here, it's not valid
}