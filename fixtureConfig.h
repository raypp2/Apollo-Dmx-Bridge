#ifndef FIXTURE_CONFIG_H
#define FIXTURE_CONFIG_H

#define MAX_PRESETS_PER_FIXTURE 5
#define MAX_CHANNELS_PER_FIXTURE 18
#define TOTAL_CHANNELS 27

#include <Arduino.h>

struct Preset {
  const char* name;         //  Preset short name
  int values[MAX_CHANNELS_PER_FIXTURE];           //  *** Fixture channel array size must be max of largest light
};

struct Fixture {
  const char* id;           //  Fixture short name (key)
  const char* name;         //  Fixture long name
  int channel;              //  Starting DMX channel
  int channel_mode;         //  Number of DMX channels for fixture
  const char* channel_map;  //  Description of each channel
  Preset presets[MAX_PRESETS_PER_FIXTURE];        //  Available presets
  const char* onUrl;        // Power on command when using fixture
                            // Some dmx lights have loud fans that are constantly on. 
                            // We can use a IP control plug, such as the Shelly Plus Plug, to toggle the light power when needed.
  const char* offUrl;       // Power off command when no longer using fixture
  int offDelay;             // Delay (in seconds) for powering off to allow fixture to cool down.
  const char* model;        //  Fixture Model
  const char* fixture_type; //  Fixture type (moving head, par, etc...)
  const char* manual;       //  URL of instruction manual
  String currentPreset;     // Default preset and stores the updated value

  //Runtime variables
  unsigned long lastActionTime;  // Handles delayed off commands
  bool isWaitingOff;             // Handles delayed off commands
};

extern Fixture dmx_fixtures[];

extern const int numFixtures;


/*
* Definition for Scenes
* 
* A scene defines a preset for each fixture.
*
*/

#define MAX_FIXTURES_PER_SCENE 2 // This should be the count of fixtures

struct ScenePreset {
  const char* fixtureId;    // Which fixture
  const char* presetName;   // Which preset for that fixture
};

struct Scene {
  const char* id;           //  Scene short name (key)
  const char* name;         //  Scene long name
  ScenePreset presets[MAX_FIXTURES_PER_SCENE];
};

extern Scene dmx_scenes[];

extern const int numScenes;

#endif