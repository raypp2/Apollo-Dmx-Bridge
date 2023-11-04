#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include "fixtureConfig.h"
#include "dmxHandler.h"

extern String currentScene;

void setupWebServer(AsyncWebServer &server);

#endif