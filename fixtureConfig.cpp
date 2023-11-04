#include "fixtureConfig.h"

Fixture dmx_fixtures[] = {
  {
    "adj",
    "ADJ moving head",
    1,
    18,
    "pan,tilt,color,gobo static,gobo rotating,gobo speed,prism,prism speed,shutter strobe,dim,focus,auto focus,zoom,shows,show speed,dimmer mode,pan tilt speed,function",
    {
      {"off", {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
      {"wolf", {8,208,103,1,53,180,0,125,255,255,81,1,255,0,0,0,0,0}},
      {"ceiling", {161,21,110,37,47,181,36,131,255,255,255,0,0,0,0,0,0}}
    },
    "http://192.168.20.27/relay/0?turn=on",
    "http://192.168.20.27/relay/0?turn=off",
    300,
    "ADJ Focus Spot 3Z",
    "moving_head",
    "https://d295jznhem2tn9.cloudfront.net/ItemRelatedFiles/8905/focus_spot_three_z.pdf",
    "off"
  },
  {
    "spot",
    "Spotlight Moving Head",
    19,
    9,
    "pan,tilt,color,gobo,strobe,dim,pan tilt speed,shows,pan tilt running,",
    {
      {"off", {0,0,0,0,0,0,0,0,0}},
      {"wolf", {69,18,0,37,0,255,0,0,0}},
      {"coffee table", {0,0,0,0,0,0,0,0,0}}
    },
    "",
    "",
    0,
    "XPCLEOYZ 90W",
    "moving_head",
    "https://forums.pioneerdj.com/hc/en-us/community/posts/7765303791769-Fixture-Request-XPCLEOYZ-60W-90W-LED-Moving-Head-Light",
    "off"
  }
};

const int numFixtures = sizeof(dmx_fixtures) / sizeof(dmx_fixtures[0]);


Scene dmx_scenes[] = {
  {
    "Wolf",
    "Wolf",
    {
      {"adj","wolf"},
      {"spot","wolf"}
    }
  },
  {
    "Hangout",
    "Hangout",
    {
      {"adj","ceiling"},
      {"spot","coffee table"}      
    }
  },
  {
    "off",
    "off",
    {
      {"adj","off"},
      {"spot","off"}      
    }    
  }
};

const int numScenes = sizeof(dmx_scenes) / sizeof(dmx_scenes[0]);