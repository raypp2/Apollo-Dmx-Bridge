#ifndef POWER_COMMANDS_H
#define POWER_COMMANDS_H

#include <Arduino.h>
#include <HTTPClient.h> // For powerOn and powerOff commands via URL

#include "fixtureConfig.h"

void devicePower(const String& url);
void handleDelayedPowerOff(int i);
void togglePower(int i, String preset);

#endif