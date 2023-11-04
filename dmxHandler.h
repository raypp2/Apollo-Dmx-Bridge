#ifndef DMX_HANDLER_H
#define DMX_HANDLER_H

#include <Arduino.h>
#include <SparkFunDMX.h>

#include "fixtureConfig.h"
#include "powerCommands.h"

extern SparkFunDMX dmxMaster;
extern bool artnetControlActive;
extern String currentScene;

void updateFixtureDMX(String id, String preset);
void updateScene(String sceneName, String command);
bool isValidFixturePreset(String id, String preset);
bool isValidScene(String id);

#endif